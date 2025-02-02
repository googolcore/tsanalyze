#ifndef _STATISTICS_H_
#define _STATISTICS_H_

#ifdef __cplusplus
extern "C"{
#endif

typedef struct stats{
	uint64_t pat_sections;
	uint64_t cat_sections;
	uint64_t pmt_sections;
	uint64_t nit_sections;
	uint64_t sdt_sections;
	uint64_t eit_sections;
	uint64_t bat_sections;
	uint64_t tdt_sections;
	uint64_t tot_sections;
	
	uint64_t ecm_sections;
	uint64_t emm_sections;
}stats_t;


#ifdef __cplusplus
}
#endif

#endif

