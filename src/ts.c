#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>

#include "io.h"
#include "ts.h"
#include "table.h"
#include "filter.h"
#include "utils.h"

/*
* port from ffmpeg for judging TS packet length
*/

static int analyze(const uint8_t *buf, int size, int packet_size, int *index){
	int stat[TS_MAX_PACKET_SIZE];
	int i;
	int x=0;
	int best_score=0;

	memset(stat, 0, packet_size*sizeof(int));

	for (x=i=0; i < size-3; i++)
	{
		if ((buf[i] == 0x47) && !(buf[i+1] & 0x80) && (buf[i+3] & 0x30))
		{
			stat[x]++;

		if (stat[x] > best_score)
		{
			best_score= stat[x];
			if (index) 
				*index= x;
		}
	}

	x++;
	if (x == packet_size) 
		x= 0; 
	}

	return best_score;
}

static int mpegts_probe(unsigned char *buf, int buf_size)
{
#define CHECK_COUNT 7

	const int size= buf_size;
	int score, fec_score, dvhs_score;
	int check_count= size / TS_FEC_PACKET_SIZE;

	if (check_count < CHECK_COUNT)
		return -1;

	score = analyze(buf, TS_PACKET_SIZE *check_count, TS_PACKET_SIZE , NULL) 
		* CHECK_COUNT / check_count;
	dvhs_score= analyze(buf, TS_DVHS_PACKET_SIZE*check_count, TS_DVHS_PACKET_SIZE, NULL)
		* CHECK_COUNT / check_count;
	fec_score = analyze(buf, TS_FEC_PACKET_SIZE *check_count, TS_FEC_PACKET_SIZE , NULL)
		* CHECK_COUNT / check_count;

	/* 
	* we need a clear definition for the returned score ,
	* otherwise things will become messy sooner or later
	*/
	if (score > fec_score && score > dvhs_score && score > 6) 
		return 0;//100 + score - CHECK_COUNT;
	else if(dvhs_score > score && dvhs_score > fec_score && dvhs_score > 6) 
		return 1;//100 + dvhs_score - CHECK_COUNT;
	else if(fec_score > 6) 
		return 2;//100 + fec_score - CHECK_COUNT;
	else 
		return -1;
}

//do memcpy if section length greater than one packet
int16_t section_preproc(uint16_t pid,uint8_t *pkt,uint16_t len,uint8_t **buffering,
		uint8_t payload_unit_start_indicator,uint8_t continuity_counter)
{
	static int total_len[8192] ={0} ;
	static uint8_t cc[8192] = {0};
	static uint8_t buffer[8192][4096];
	static int16_t limit_len[8192] ={0};
	*buffering = NULL;
	if(payload_unit_start_indicator == 1){
		/*skip pointer_field, valid for PSI */
		total_len[pid] = len-1;
		cc[pid] = continuity_counter;
		limit_len[pid] = (int16_t)(((int16_t)pkt[2] << 8) | pkt[3])&0x0FFF;
		limit_len[pid] += 3;
		/*section in one pkt , go without buffering*/
		if(limit_len[pid] <= (len-1))
		{
			*buffering = (pkt+1);
			return limit_len[pid];
		}
		else
		{
			memset(buffer[pid],0,4096);
			memcpy(buffer[pid],pkt+1,len-1);
		}
	}
	else
	{
		if(total_len[pid]==0)
			return -1;
		memcpy(buffer[pid]+total_len[pid],pkt,len);
		total_len[pid] += len;
		if(total_len[pid]>=limit_len[pid])
		{
			*buffering = buffer[pid];
			total_len[pid] = 0;
			return limit_len[pid];
		}
	}
	/*tell us buffering*/
	return -1;
}

struct pid_ops{
	uint16_t pid;
	uint64_t pkts_in;
	uint64_t error_in;
	uint64_t bits_in;
	uint64_t pcr;
	uint64_t bitrate;
};


struct pid_ops pid_dev[MAX_TS_PID_NUM];

uint64_t calc_pcr_clock(pcr_clock pcr)
{
	return pcr.program_clock_reference_base * 300 + pcr.program_clock_reference_extension;
}

int ts_adaptation_field_proc(uint8_t *data,uint8_t len)
{
	ts_adaptation_field adapt;
	pcr_clock pcr,opcr;
	uint8_t *ptr = data;
	adapt.discontinuity_indicator = TS_READ_BIT(ptr,7);
	adapt.random_access_indicator = TS_READ_BIT(ptr,6);
	adapt.elementary_stream_priority_indicator = TS_READ_BIT(ptr,5);
	adapt.PCR_flag = TS_READ_BIT(ptr,4);
	adapt.OPCR_flag = TS_READ_BIT(ptr,3);
	adapt.splicing_point_flag = TS_READ_BIT(ptr,2);
	adapt.transport_private_data_flag = TS_READ_BIT(ptr,1);
	adapt.adaptation_field_extension_flag = TS_READ_BIT(ptr,0);
	ptr += 1;

	if(adapt.PCR_flag)
	{
		pcr.program_clock_reference_base = (((uint64_t)TS_READ32(ptr)<<1)|ptr[4]>>7);
		ptr += 4;
		pcr.program_clock_reference_extension = (TS_READ16(ptr) &0x1FF);
		ptr += 2;
		//printf("clock %lu\n",calc_pcr_clock(pcr));
	}
	if(adapt.OPCR_flag)
	{
		opcr.program_clock_reference_base = (((uint64_t)TS_READ32(ptr)<<1)|ptr[4]>>7);
		ptr += 4;
		opcr.program_clock_reference_extension = (TS_READ16(ptr) &0x1FF);
		ptr += 2;
		//printf("original clock %lu\n",calc_pcr_clock(pcr));
	}
	if(adapt.splicing_point_flag)
	{
		ptr += 1;
	}
	if(adapt.transport_private_data_flag)
	{
		uint8_t transport_private_data_length = TS_READ8(ptr);
		ptr += 1;
		ptr += transport_private_data_length;
	}
	if(adapt.adaptation_field_extension_flag)
	{
		uint8_t adaptation_field_extension_length = TS_READ8(ptr);
		ptr += 1;
		ptr += adaptation_field_extension_length;
	}

	return 0;
}

int ts_proc(uint8_t *data,uint8_t len)
{
	ts_header head;
	uint8_t *ptr = data;
	int16_t sec_len;
	uint8_t *pbuf = NULL;
	if(unlikely(ptr == NULL))
		return -1;
	if(unlikely(ptr[0]!=TS_SYNC_BYTE))
		return -1;
	
	ptr+=1;
	head.PID = TS_READ16(ptr) & 0x1FFF;
	head.transport_error_indicator = TS_READ8(ptr) >>7;
	head.payload_unit_start_indicator = TS_READ8(ptr) >>6;
	ptr += 2;
	head.adaptation_field_control = (TS_READ8(ptr)>>4)&0x3;
	head.continuity_counter = TS_READ8(ptr) & 0x3;
	//memcpy(&head,data,sizeof(ts_header));
	//printf("receive PID 0x%x\n",head.PID);
	ptr+=1;
	len-=4;

	pid_dev[head.PID].pkts_in++;

	if(head.adaptation_field_control ==ADAPT_ONLY||head.adaptation_field_control ==ADAPT_BOTH)
	{
		ts_adaptation_field adapt;
		adapt.adaptation_field_length = TS_READ8(ptr);
		ptr += 1;
		ts_adaptation_field_proc(ptr,adapt.adaptation_field_length);
		ptr += adapt.adaptation_field_length;
		len -=1;
		len -= adapt.adaptation_field_length;
		//TODO
	}

	if(head.transport_error_indicator == 1 )
	{
		pid_dev[head.PID].error_in++;
	}
	
	//printf("pid 0x%x 0x%x\n",head.PID,*ptr);
	if(head.PID != NULL_PID)
	{
		sec_len = section_preproc(head.PID,ptr ,len,&pbuf,head.payload_unit_start_indicator,head.continuity_counter);
		if(sec_len==-1)
			return 0;
	}
	filter_proc(head.PID,pbuf,sec_len);
	return 0;
}

void dump_ts_info(void)
{
	struct tsa_config *tsaconf = get_config();
	if(tsaconf->detail==0)
		return;

	uint16_t pid=0;
	printf("\n");
	printf("TS bits statistics:\n");
	printf("%7s%21s%11s\n","PID","In","Err");
	for(pid = 0; pid <=NULL_PID ; pid++){
		if(pid_dev[pid].pkts_in)
			printf("%04d(0x%04x)  %2c  %10" PRIu64 "%10" PRIu64 "\n",pid,pid,':',pid_dev[pid].pkts_in,pid_dev[pid].error_in );
	}
}

int init_pid_processor(void)
{
	filter_init();
	init_table_ops();
	init_descriptor_parsers();
	return 0;
}

int ts_process()
{
	struct tsa_config *tsaconf = get_config();
	struct io_ops* ops = lookup_io_ops(tsaconf->type);
	void * ptr = NULL;
	size_t len;
	int ts_pktlen = 0;
	int start_index;
	int typ;
	uint8_t pkt_con[TS_FEC_PACKET_SIZE];
	int pkt_con_len = 0;

	if(ops->open(tsaconf->name)<0)
		return -1;

	ops->read(&ptr,&len);

	typ = mpegts_probe((uint8_t *)ptr,len);
	if(typ==0)
	{
		ts_pktlen = TS_PACKET_SIZE;
	}else if(typ == 1)
	{
		ts_pktlen = TS_DVHS_PACKET_SIZE;
	}else if(typ == 2)
	{
		ts_pktlen = TS_FEC_PACKET_SIZE;
	}else
	{
		printf("TS file invalid format\n");
		return -1;
	}

	//hexdump(ptr, 188);
	analyze(ptr, ts_pktlen*2, ts_pktlen , &start_index);
	printf("Ts starting at offset %d\n",start_index);
	//hexdump(ptr+start_index, ts_pktlen);

	ptr += start_index;
	len -= start_index;
	
	while (ops->end())
	{
		if(pkt_con_len == ts_pktlen){
			ts_proc(pkt_con,ts_pktlen);
			pkt_con_len = 0;
		}
		while(len >= ts_pktlen)
		{
			ts_proc(ptr,ts_pktlen);
			len -= ts_pktlen;
			ptr += ts_pktlen;
		}
		if(len){
			memcpy(pkt_con, ptr, len);
			pkt_con_len = len;
		}
		if(ops->read(&ptr,&len) < 0)
			break;
		if(pkt_con_len){
			memcpy(pkt_con + pkt_con_len, ptr , ts_pktlen - pkt_con_len);
			ptr += ts_pktlen - pkt_con_len;
			len -= (ts_pktlen - pkt_con_len);
			pkt_con_len = ts_pktlen;
		}
	}
	ops->close();

	return 0;
}
