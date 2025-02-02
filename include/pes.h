#ifndef _PES_H_
#define _PES_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "types.h"
#include "ps.h"

enum stream_id {
	program_stream_map = 0xBC,
	private_stream_1 = 0xBD,
	padding_stream = 0xBE,
	private_stream_2 = 0xBF,
	/*0x110x xxxx is ISO/IEC 13818-3 or ISO/IEC 11172-3 or 
		ISO/IEC 13818-7 or ISO/IEC 14496-3 audio stream number x xxxx*/
	/* 0x1110 xxxx is ITU-T Rec. H.262 | ISO/IEC 13818-2 or 
		ISO/IEC 11172-2 or ISO/IEC 14496-2 video stream number xxxx*/
	ECM_stream = 0xF0,
	EMM_stream = 0xF1,
	DSMCC_stream = 0xF2,
	ISO13522_stream = 0xF3,
	H222_1_A = 0xF4,
	H222_1_B = 0xF5,
	H222_1_C = 0xF6,
	H222_1_D = 0xF7,
	H222_1_E = 0xF8,
	ancillary_stream = 0xF9,
	SL_packetized_stream = 0xFA,
	FlexMux_stream = 0xFB,
	/* reserved 0xFC, 0xFD, 0xFE */
	program_stream_directory = 0xFF,
};

#if 0
enum PES_scrambling_control{
	PES_non_scrambled = 0x00,
	PES_user_defined = 0x01,
	
};
#endif

typedef struct {
	uint8_t flag:4;
	uint8_t PTS_DTS_1:3;
	uint8_t mark_bit1:1;
	uint16_t PTS_DTS_2:15;
	uint16_t mark_bit2:1;
	uint16_t PTS_DTS_3:15;
	uint16_t mark_bit3:1;
}PTS_DTS;

typedef struct {
	uint64_t reserved:2;
	uint64_t ESCR_base_1:3;
	uint64_t mark_bit_1:1;
	uint64_t ESCR_base_2:15;
	uint64_t mark_bit_2:1;
	uint64_t ESCR_base_3:15;
	uint64_t mark_bit_3:1;
	uint64_t ESCR_extension:9;
	uint64_t mark_bit_4:1;
}__attribute__((packed))ESCR;

typedef struct{
	uint32_t mark_bit_1:1;
	uint32_t ES_rate:22;
	uint32_t mark_bit_2:1;
}__attribute__((packed))ES_rate;

typedef struct{
	EXT_STD_C11
	union{
		struct{
			uint8_t DSM_trick_mode_control:3;
			uint8_t rep_cntrl:5;
		};
		struct{
			uint8_t DSM_trick_mode_control1:3;
			uint8_t field_id:2;
			uint8_t intra_slice_refresh:1;
			uint8_t frequency_truncation:2;
		};
		struct{
			uint8_t DSM_trick_mode_control2:3;
			uint8_t reserved:5;
		};
	};
}DSM_trick_mode;

typedef struct{
	uint8_t mark_bit:1;
	uint8_t additional_copy_info:7;
}additional_copy;


typedef struct{
	uint8_t marker_bit:1;
	uint8_t program_packet_sequence_counter:7;
	uint8_t marker_bit1:1;
	uint8_t MPEG1_MPEG2_identifier:1;
	uint8_t original_stuff_length:6;
}program_packet_sequence_counter;

typedef struct{
	uint16_t zero_one:2;
	uint16_t PSTD_buffer_scale:1;
	uint16_t PSTD_buffer_size:13;
}PSTD_buffer;

typedef struct {
	uint8_t PES_private_data_flag:1;
	uint8_t pack_header_field_flag:1;
	uint8_t program_packet_sequence_counter_flag:1;
	uint8_t P_STD_buffer_flag:1;
	uint8_t reserved:3;
	uint8_t PES_extension_flag_2:1;
	uint8_t PES_private_data[16];
	//pack_header pack_head;
	program_packet_sequence_counter ppsc;
	PSTD_buffer pstd_buffer;
	uint8_t marker_bit:1;
	uint8_t PES_extension_field_length:7;
}PES_extension;

typedef struct {
	uint8_t reserved:2;
	uint8_t PES_scrambling_control:2;
	uint8_t PES_priority:1;
	uint8_t data_alignment_indicator:1;
	uint8_t copyright:1;
	uint8_t original_or_copy:1;
	uint8_t PTS_DTS_flags:2;	/*00 none ,01 forbiden, 10 PTS present, 11 both*/
	uint8_t ESCR_flag:1;	/* 1 ESCR base and extension fields are present */
	uint8_t ES_rate_flag:1;	/* 1 ES_rate field is present in the PES packet header*/
	uint8_t DSM_trick_mode_flag:1; /*1indicates 8-bit trick mode field*/
	uint8_t additional_copy_info_flag:1; 
	uint8_t PES_CRC_flag:1;
	uint8_t PES_extension_flag:1;
	uint8_t PES_header_data_length;
	PTS_DTS pts;
	PTS_DTS dts;
	ES_rate rate;
	DSM_trick_mode trick_mode;
	additional_copy copy_info;
	uint16_t previous_PES_packet_CRC;
}non_ps;


typedef struct {
	uint32_t packet_start_code_prefix:24;
	uint32_t stream_id:8;
	uint16_t PES_packet_length;
	union{
		non_ps packet_data;
		uint8_t* PES_packet_data_byte;
		uint8_t* padding_byte;
	};
} pes_t;



#ifdef __cplusplus
}
#endif

#endif /*_PES_H_*/
