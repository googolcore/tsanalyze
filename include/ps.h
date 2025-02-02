#ifndef _PS_H_
#define _PS_H_

#ifdef __cplusplus
extern "C"{
#endif

#define PACK_START 0x000001BA
#define SYSTEM_START 0x000001BB
#define PACKET_START 0x000001
#define PROGRAM_END 0x000001B9

typedef struct{
	uint8_t stream_id;
	uint16_t one:2;
	uint16_t PSTD_buffer_bound_scale:1;
	uint16_t PSTD_buffer_size_bound:13;
}estd;

typedef struct{
	uint32_t system_header_start_code;
	uint16_t header_length;
	uint32_t marker_bit:1;
	uint32_t rate_bound:22;
	uint32_t marker_bit1:1;
	uint32_t audio_bound:6;
	uint32_t fixed_flag:1;
	uint32_t CSPS_flag:1;
	uint8_t system_audio_lock_flag:1;
	uint8_t system_video_lock_flag:1;
	uint8_t marker_bit2:1;
	uint8_t video_bound:5;
	uint8_t packet_rate_restriction_flag:1;
	uint8_t reserved_bits:7;
	estd es;
}system_header;


typedef struct {
	uint8_t pack_start_code;
	uint64_t zero_one:2;
	uint64_t system_clock_reference_base1:3;
	uint64_t marker_bit1:1;
	uint64_t system_clock_reference_base2:15;
	uint64_t marker_bit2:1;
	uint64_t system_clock_reference_base3:15;
	uint64_t marker_bit3:1;
	uint64_t system_clock_reference_extension:9;
	uint64_t marker_bit4:1;
	uint64_t program_mux_rate:22;
	uint64_t marker_bit5:1;
	uint64_t marker_bit6:1;
	uint8_t reserved:3;
	uint8_t pack_stuffing_length:5;
}pack_header;

typedef struct{
	uint32_t packet_start_code_prefix:24;
	uint32_t map_stream_id:8;
	uint16_t program_stream_map_length;
	uint8_t current_next_indicator:1;
	uint8_t reserved:2;
	uint8_t program_stream_map_version:5;
	uint8_t reserved1:7;
	uint8_t marker_bit:1;
	uint16_t program_stream_info_length;

	uint16_t elementary_stream_map_length;
	
	uint32_t crc_32;
}PSM;

typedef struct{
	uint8_t packet_stream_id;
	uint16_t PES_header_position_offset_sign:1;
	uint16_t PES_header_position_offset1:14;
	uint16_t marker_bit1:1;
	uint16_t PES_header_position_offset2:15;
	uint16_t marker_bit2:1;
	uint16_t PES_header_position_offset3:15;
	uint16_t marker_bit3:1;
	uint16_t reference_offset;
	uint8_t marker_bit4:1;
	uint8_t reserved:3;
	uint8_t PTS1:3;
	uint8_t marker_bit5:1;
	uint16_t PTS2:15;
	uint16_t marker_bit6:1;
	uint16_t PTS3:15;
	uint16_t marker_bit7:1;
	uint16_t bytes_to_read1:15;
	uint16_t marker_bit8:1;
	uint8_t bytes_to_read2;
	uint8_t marker_bit9:1;
	uint8_t intra_coded_indicator:1;
	uint8_t coding_parameters_indicator:2;
	uint8_t reserved1:4;
}access_unit;

typedef struct {
	uint32_t packet_start_code_prefix:24;
	uint32_t directory_stream_id:8;
	uint16_t PES_packet_length;
	uint16_t number_of_access_units:15;
	uint16_t marker_bit:1;
	uint16_t prev_directory_offset1:15;
	uint16_t marker_bit1:1;
	uint16_t prev_directory_offset2:15;
	uint16_t marker_bit2:1;
	uint16_t prev_directory_offset3:15;
	uint16_t marker_bit3:1;
	uint16_t prev_directory_offset4:15;
	uint16_t marker_bit4:1;
	uint16_t prev_directory_offset5:15;
	uint16_t marker_bit5:1;
	uint16_t prev_directory_offset6:15;
	uint16_t marker_bit6:1;
	//access_unit units;
}directory_PES_packet;

typedef struct{
	pack_header head;
	//PES_packet;
}pack;

typedef struct{
	pack pack;
	uint32_t MPEG_program_end_code;
}MPEG2_PS;

#ifdef __cplusplus
}
#endif

#endif /*_PS_H_*/
