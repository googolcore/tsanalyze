#ifndef _DESCRIPTOR_H_
#define _DESCRIPTOR_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "types.h"

typedef struct descriptor{
	uint8_t tag;
	uint8_t length;
	struct descriptor * next;
	uint8_t data[0];
}__attribute__((packed)) descriptor_t;



#if 0
enum descriptor_e{
	/* ISO/IEC 13818-1 */
	video_stream_descriptor		= 0x02,
	audio_stream_descriptor		= 0x03,
	hierarchy_descriptor		= 0x04,
	registration_descriptor		= 0x05,
	data_stream_alignment_descriptor = 0x06,
	target_background_grid_descriptor = 0x07,
	video_window_descriptor		= 0x08,
	CA_descriptor				= 0x09,
	ISO_639_language_descriptor	= 0x0A,
	system_clock_descriptor		= 0x0B,
	multiplex_buffer_utilization_descriptor = 0x0C,
	copyright_descriptor		= 0x0D,
	maximum_bitrate_descriptor	= 0x0E,
	private_data_indicator_descriptor = 0x0F,
	smoothing_buffer_descriptor	= 0x10,
	STD_descriptor				= 0x11,
	ibp_descriptor				= 0x12,
	/* 0x12 - 0x1A Defined in ISO/IEC 13818-6*/
	
	MPEG4_video_descriptor		= 0x1B,
	MPEG4_audio_descriptor		= 0x1C,
	IOD_descriptor				= 0x1D,
	SL_descriptor				= 0x1E,
	FMC_descriptor				= 0x1F,
	external_ES_ID_descriptor	= 0x20,
	muxcode_descriptor			= 0x21,
	FmxBufferSize_descriptor	= 0x22,
	MultiplexBuffer_descriptor	= 0x23,
	/* 0x24 - 0x3F reserved */

	/* EN 300 468*/
	network_name_descriptor		= 0x40,
	service_list_descriptor 	= 0x41,
	stuffing_descriptor			= 0x42,
	satellite_delivery_system_descriptor = 0x43,
	cable_delivery_system_descriptor = 0x44,
	VBI_data_descriptor			= 0x45,
	VBI_teletext_descripto		= 0x46,
	bouquet_name_descriptor		= 0x47,
	service_descriptor			= 0x48,
	country_availability_descriptor = 0x49,
	linkage_descriptor			= 0x4A,
	NVOD_reference_descriptor	= 0x4B,
	time_shifted_service_descriptor = 0x4C,
	short_event_descriptor		= 0x4D,
	extended_event_descriptor	= 0x4E,
	time_shifted_event_descriptor = 0x4F,
	component_descriptor		= 0x50,
	mosaic_descriptor			= 0x51,
	stream_identifier_descriptor	= 0x52,
	CA_identifier_descriptor	= 0x53,
	content_descriptor			= 0x54,
	parental_rating_descriptor	= 0x55,
	teletext_descriptor			= 0x56,
	telephone_descriptor		= 0x57,
	local_time_offset_descriptor	= 0x58,
	subtitling_descriptor		= 0x59,
	terrestrial_delivery_system_descriptor = 0x5A,
	multilingual_network_name_descriptor =0x5B,
	multilingual_bouquet_name_descriptor = 0x5C,
	multilingual_service_name_descriptor = 0x5D,
	multilingual_component_descriptor = 0x5E,
	private_data_specifier_descriptor = 0x5F,
	service_move_descriptor		= 0x60,
	short_smoothing_buffer_descriptor = 0x61,
	frequency_list_descriptor	= 0x62,
	partial_transport_stream_descriptor = 0x63,
	data_broadcast_descriptor	= 0x64,
	scrambling_descriptor		= 0x65,
	data_broadcast_id_descriptor	= 0x66,
	transport_stream_descriptor	= 0x67,
	DSNG_descriptor 			= 0x68,
	PDC_descriptor				= 0x69,
	AC3_descriptor				= 0x6A,
	ancillary_data_descriptor	= 0x6B,
	cell_list_descriptor		= 0x6C,
	cell_frequency_link_descriptor	= 0x6D,
	announcement_support_descriptor	= 0x6E,
	application_signalling_descriptor = 0x6F,
	adaptation_field_data_descriptor = 0x70,
	service_identifier_descriptor	= 0x71,
	service_availability_descriptor = 0x72,
	default_authority_descriptor 	= 0x73,
	related_content_descriptor	= 0x74,
	TVA_id_descriptor			= 0x75,
	content_identifier_descriptor	= 0x76,
	time_slice_fec_identifier_descriptor = 0x77,
	ECM_repetition_rate_descriptor = 0x78,
	S2_satellite_delivery_system_descriptor = 0x79,
	enhanced_AC3_descriptor		= 0x7A,
	DTS_descriptor				= 0x7B,
	AAC_descriptor				= 0x7C,
	XAIT_location_descriptor	= 0x7D,
	FTA_content_management_descriptor = 0x7E,
	extension_descriptor		= 0x7F,

	/*0x80 to 0xFE user defined */
	/*0xFF forbidden */
};
#endif

/* ISO/IEC 13818-1 */
#define foreach_enum_descriptor \
	_(video_stream, 0x02)\
	_(audio_stream,	0x03)\
	_(hierarchy,		0x04)\
	_(registration,	0x05)\
	_(data_stream_alignment,	0x06)\
	_(target_background_grid,	0x07)\
	_(video_window,			0x08)\
	_(CA,			0x09)\
	_(ISO_639_language,	0x0A)\
	_(system_clock,		0x0B)\
	_(multiplex_buffer_utilization,	0x0C)\
	_(copyright,			0x0D)\
	_(maximum_bitrate,	0x0E)\
	_(private_data_indicator,	0x0F)\
	_(smoothing_buffer,	0x10)\
	_(STD,				0x11)\
	_(ibp,				0x12)\
	/* 0x12 - 0x1A Defined in ISO/IEC 13818-6*/\
	\
	_(MPEG4_video,		0x1B)\
	_(MPEG4_audio,		0x1C)\
	_(IOD,				0x1D)\
	_(SL,				0x1E)\
	_(FMC,				0x1F)\
	_(external_ES_ID,	0x20)\
	_(muxcode,			0x21)\
	_(FmxBufferSize,	0x22)\
	_(MultiplexBuffer,	0x23)\
	/* 0x24 - 0x3F reserved */\
	/* EN 300 468*/\
	_(network_name,		0x40)\
	_(service_list,		0x41)\
	_(stuffing,			0x42)\
	_(satellite_delivery_system, 0x43)\
	_(cable_delivery_system,	0x44)\
	_(VBI_data,			0x45)\
	_(VBI_teletext,		0x46)\
	_(bouquet_name,		0x47)\
	_(service,			0x48)\
	_(country_availability,	0x49)\
	_(linkage,			0x4A)\
	_(NVOD_reference,	0x4B)\
	_(time_shifted_service,	0x4C)\
	_(short_event,		0x4D)\
	_(extended_event,	0x4E)\
	_(time_shifted_event,	0x4F)\
	_(component,			0x50)\
	_(mosaic,			0x51)\
	_(stream_identifier,	0x52)\
	_(CA_identifier,		0x53)\
	_(content,			0x54)\
	_(parental_rating,	0x55)\
	_(teletext,			0x56)\
	_(telephone,			0x57)\
	_(local_time_offset,	0x58)\
	_(subtitling,		0x59)\
	_(terrestrial_delivery_system,	0x5A)\
	_(multilingual_network_name,	0x5B)\
	_(multilingual_bouquet_name,	0x5C)\
	_(multilingual_service_name,	0x5D)\
	_(multilingual_component,	0x5E)\
	_(private_data_specifier,	0x5F)\
	_(service_move,		0x60)\
	_(short_smoothing_buffer, 0x61)\
	_(frequency_list,	0x62)\
	_(partial_transport_stream, 0x63)\
	_(data_broadcast,	0x64)\
	_(scrambling,		0x65)\
	_(data_broadcast_id,	0x66)\
	_(transport_stream,	0x67)\
	_(DSNG,			0x68)\
	_(PDC,				0x69)\
	_(AC3,				0x6A)\
	_(ancillary_data,	0x6B)\
	_(cell_list,			0x6C)\
	_(cell_frequency_link,	0x6D)\
	_(announcement_support,	0x6E)\
	_(application_signalling,	0x6F)\
	_(adaptation_field_data,	0x70)\
	_(service_identifier,	0x71)\
	_(service_availability,	0x72)\
	_(default_authority,	0x73)\
	_(related_content,	0x74)\
	_(TVA_id,			0x75)\
	_(content_identifier,	0x76)\
	_(time_slice_fec_identifier, 0x77)\
	_(ECM_repetition_rate, 0x78)\
	_(S2_satellite_delivery_system, 0x79)\
	_(enhanced_AC3,		0x7A)\
	_(DTS,				0x7B)\
	_(AAC,				0x7C)\
	_(XAIT_location,	0x7D)\
	_(FTA_content_management,0x7E)\
	_(extension,		0x7F)
	/*0x80 to 0xFE user defined */
	/*0xFF forbidden */

enum descriptor_e{
#define _(a,b)  dr_##a = b,
	foreach_enum_descriptor
#undef _
};

/* see ISO/IEC 13818-1 chapter 2.6*/

typedef struct {
	EXT_STD_C11
	union{
		descriptor_t descriptor;
		struct {
			uint8_t descriptor_tag;
			uint8_t descriptor_length;
			void *next;
			uint8_t multiple_frame_rate_flag:1; /*set to '1' indicates that multiple frame rates may be present*/
			uint8_t frame_rate_code:4;
			uint8_t MPEG_1_only_flag:1; /*set to '1' indicates that the video stream contains only ISO/IEC 11172-2 data*/
			uint8_t constrained_parameter_flag:1;
			uint8_t still_picture_flag:1; /*set to '1' indicates that the video stream contains only still pictures.*/
			/*exist only when MPEG_1_only_flag == 0*/
			uint8_t profile_and_level_indication;
			uint8_t chroma_format:2;
			uint8_t frame_rate_extension_flag:1;
			uint8_t reserved:5;
		};
	};
}video_stream_descriptor_t;

typedef struct {
	EXT_STD_C11
	union {
		descriptor_t descriptor;
		struct {
			uint8_t descriptor_tag;
			uint8_t descriptor_length;
			void *next;
			uint8_t free_format_flag:1;
			uint8_t ID:1;
			uint8_t layer:2;
			uint8_t variable_rate_audio_indicator:1;
			uint8_t reserved:3;
		};
	};
} audio_stream_descriptor_t;

enum hierarchy_type_e{
	spatial_scalability = 1, /*ITU-T Rec. H.262 | ISO/IEC 13818-2 spatial_scalability*/
	SNR_scalability = 2, /*ITU-T Rec. H.262 | ISO/IEC 13818-2 SNR_scalability */
	temporal_scalability = 3,/* ITU-T Rec. H.262 | ISO/IEC 13818-2 temporal_scalability*/
	data_partitioning = 4,/* ITU-T Rec. H.262 | ISO/IEC 13818-2 data_partitioning */
	extension_bitstream = 5, /*ISO/IEC 13818-3 extension_bitstream*/
	private_stream = 6,	 /* ITU-T Rec.H222.0 | ISO/IEC 13818-1 Private Stream private_stream*/
	multiview_profile = 7,/* ITU-T Rec. H.262 | ISO/IEC 13818-2 Multi-view Profile*/
	base_layer = 15,
};

typedef struct {
	EXT_STD_C11
	union{
		descriptor_t descriptor;
		struct {
			uint8_t descriptor_tag;
			uint8_t descriptor_length;
			void *next;
			uint8_t reserved:4;
			uint8_t hierarchy_type:4; /*see definition in @hierarchy_type_e*/
			uint8_t reserved1:2;
			uint8_t hierarchy_layer_index:6;
			uint8_t reserved2:2;
			uint8_t hierarchy_embedded_layer_index:6;
			uint8_t reserved3:2;
			uint8_t hierarchy_channel:6;
		};
	};

}hierarchy_descriptor_t;

typedef struct {
	EXT_STD_C11
	union{
		descriptor_t descriptor;
		struct {
			uint8_t descriptor_tag;
			uint8_t descriptor_length;
			void *next;
			uint32_t format_identifier;
			uint8_t* additional_identification_info;
		};
	};
} registration_descriptor_t;

enum video_alignment_type_e{
	slice_or_video_access_unit = 1,
	video_access_unit = 2,
	GOP_or_SEQ = 3,
	SEQ = 4,
	/* 0x05 - 0xFF reserved*/
};

typedef struct {
	EXT_STD_C11
	union{
		descriptor_t descriptor;
		struct {
			uint8_t descriptor_tag;
			uint8_t descriptor_length;
			void *next;
			uint8_t alignment_type; /* see definition in @video_alignment_type_e */
		};
	};
} data_stream_alignment_descriptor_t;

typedef struct {
	EXT_STD_C11
	union{
		descriptor_t descriptor;
		struct {
			uint8_t descriptor_tag;
			uint8_t descriptor_length;
			void * next;
			uint32_t horizontal_size:14;
			uint32_t vertical_size:14;
			uint32_t aspect_ratio_information:4;
		};
	};
} target_background_grid_descriptor_t;

typedef struct {
	EXT_STD_C11
	union{
		descriptor_t descriptor;
		struct {
			uint8_t descriptor_tag;
			uint8_t descriptor_length;
			void *next;
			uint32_t horizontal_offset:14;
			uint32_t vertical_offset:14;
			uint32_t window_priority:4;
		};
	};
} video_window_descriptor_t;

typedef struct {
	EXT_STD_C11
	union{
		descriptor_t descriptor;
		struct {
			uint8_t descriptor_tag;
			uint8_t descriptor_length;
			void *next;
			uint16_t CA_system_ID;
			uint16_t reserved:3;
			uint16_t CA_PID:13;
			uint8_t* private_data_byte;
		};
	};
} CA_descriptor_t;

enum audio_type_e{
	undefined = 0x0,
	clean_effects = 0x1,
	hearing_impaired = 0x2,
	visual_impaired_commentary = 0x3,
	/*0x04-0xFF reserved*/
};

struct language_info{
	uint32_t ISO_639_language_code:24;
	uint32_t audio_type:8; /*see definition in @audio_type_e */
	struct language_info * next;
};

typedef struct {
	EXT_STD_C11
	union{
		descriptor_t descriptor;
		struct {
			uint8_t descriptor_tag;
			uint8_t descriptor_length;
			void *next;
			//uint32_t lang_num;
			struct language_info* language_list;
		};
	};
} ISO_639_language_descriptor_t;

typedef struct {
	EXT_STD_C11
	union{
		descriptor_t descriptor;
		struct {
			uint8_t descriptor_tag;
			uint8_t descriptor_length;
			void *next;
			uint8_t external_clock_reference_indicator:1;
			uint8_t reserved:1;
			uint8_t clock_accuracy_integer:6;
			uint8_t clock_accuracy_exponent:3;
			uint8_t reserved1:5;
		};
	};
}system_clock_descriptor_t;

typedef struct {
	EXT_STD_C11
	union{
		descriptor_t descriptor;
		struct {
			uint8_t descriptor_tag;
			uint8_t descriptor_length;
			void *next;
			uint16_t bound_valid_flag:1;
			uint16_t LTW_offset_lower_bound:15;
			uint16_t reserved:1;
			uint16_t LTW_offset_upper_bound:15;
		};
	};
} multiplex_buffer_utilization_descriptor_t;

typedef struct {
	EXT_STD_C11
	union{
		descriptor_t descriptor;
		struct {
			uint8_t descriptor_tag;
			uint8_t descriptor_length;
			void *next;
			uint32_t copyright_identifier;
			uint8_t *additional_copyright_info;
		};
	};
} copyright_descriptor_t;

typedef struct {
	EXT_STD_C11
	union{
		descriptor_t descriptor;
		struct {
			uint8_t descriptor_tag;
			uint8_t descriptor_length;
			void *next;
			uint24_t maximum_bitrate;
			//uint24_t reserved:2;
			//uint24_t maximum_bitrate:22;
		};
	};
} maximum_bitrate_descriptor_t;

typedef struct {
	EXT_STD_C11
	union{
		descriptor_t descriptor;
		struct {
			uint8_t descriptor_tag;
			uint8_t descriptor_length;
			void *next;
			uint32_t private_data_indicator;
		};
	};
}private_data_indicator_descriptor_t;

typedef struct {
	EXT_STD_C11
	union{
		descriptor_t descriptor;
		struct {
			uint8_t descriptor_tag;
			uint8_t descriptor_length;
			void *next;
			uint24_t sb_leak_rate;
			uint24_t sb_size;
			//uint24_t reserved:2;
			//uint24_t sb_leak_rate:22;
			//uint24_t reserved1:2;
			//uint24_t sb_size:22;
		};
	};
}smoothing_buffer_descriptor_t;

typedef struct {
	EXT_STD_C11
	union{
		descriptor_t descriptor;
		struct {
			uint8_t descriptor_tag;
			uint8_t descriptor_length;
			void *next;
			uint8_t reserved:7;
			uint8_t leak_valid_flag:1;
		};
	};
}STD_descriptor_t;

typedef struct {
	EXT_STD_C11
	union{
		descriptor_t descriptor;
		struct {
			uint8_t descriptor_tag;
			uint8_t descriptor_length;
			void *next;
			uint16_t closed_gop_flag:1;
			uint16_t identical_gop_flag:1;
			uint16_t max_gop_length:14;
		};
	};
}ibp_descriptor_t;

typedef struct {
	EXT_STD_C11
	union{
		descriptor_t descriptor;
		struct {
			uint8_t descriptor_tag;
			uint8_t descriptor_length;
			void *next;
			uint8_t MPEG4_visual_profile_and_level;
		};
	};
}MPEG4_video_descriptor_t;

enum MPEG4_audio_profile_and_level_e{
	main_profile_lv1 = 0x10,
	main_profile_lv2 = 0x11,
	main_profile_lv3 = 0x12,
	main_profile_lv4 = 0x13,
	/*0x14-0x17 reserved */
	
	
};

typedef struct {
	EXT_STD_C11
	union{
		descriptor_t descriptor;
		struct {
			uint8_t descriptor_tag;
			uint8_t descriptor_length;
			void *next;
			uint8_t MPEG4_audio_profile_and_level;
		};
	};
} MPEG4_audio_descriptor_t;

typedef struct {
	EXT_STD_C11
	union{
		descriptor_t descriptor;
		struct {
			uint8_t descriptor_tag;
			uint8_t descriptor_length;
			void *next;
			uint8_t Scope_of_IOD_label;
			uint8_t IOD_label;
		};
	};
} IOD_descriptor_t;

typedef struct {
	EXT_STD_C11
	union{
		descriptor_t descriptor;
		struct {
			uint8_t descriptor_tag;
			uint8_t descriptor_length;
			void *next;
			uint16_t ES_ID;
		};
	};
} SL_descriptor_t;

struct FMC_info{
	uint16_t ES_ID;
	uint8_t FlexMuxChannel;
	struct FMC_info*next;
};

typedef struct {
	EXT_STD_C11
	union{
		descriptor_t descriptor;
		struct {
			uint8_t descriptor_tag;
			uint8_t descriptor_length;
			void *next;
			struct FMC_info *FMC_info_list;
		};
	};
}FMC_descriptor_t;

typedef struct {
	EXT_STD_C11
	union{
		descriptor_t descriptor;
		struct {
			uint8_t descriptor_tag;
			uint8_t descriptor_length;
			void *next;
			uint16_t external_ES_ID;
		};
	};
}external_ES_ID_descriptor_t;

typedef struct {
}muxcode_descriptor_t;

typedef struct {
	
}FmxBufferSize_descriptor_t;

typedef struct {
	EXT_STD_C11
	union{
		descriptor_t descriptor;
		struct {
			uint8_t descriptor_tag;
			uint8_t descriptor_length;
			void *next;
			uint24_t MB_buffer_size;
			uint24_t TB_leak_rate;/* in units of 400 bits per second the rate at which data is transferred */
		};
	};
}MultiplexBuffer_descriptor_t;

/*see EN_300 468 chapter 6*/

typedef struct {
}network_name_descriptor_t;

typedef struct {
	
}service_list_descriptor_t;

typedef struct{}stuffing_descriptor_t;

typedef struct {

}satellite_delivery_system_descriptor_t;

typedef struct {

}cable_delivery_system_descriptor_t;

typedef struct {

}VBI_data_descriptor_t;
typedef struct {

}VBI_teletext_descriptor_t;

typedef struct {
	EXT_STD_C11
	union{
		descriptor_t descriptor;
		struct {
			uint8_t descriptor_tag;
			uint8_t descriptor_length;
			void * next;
			char *sub_table;
		};
	};
}bouquet_name_descriptor_t;

typedef struct {
	
}service_descriptor_t;


enum country_code_e{
	AFG,
	ALA,
	ALB,
	DZA,
	ASM,
	AND,
	AGO,
	AIA,
	ATA,
	ATG,
	ARG,
	ARM,
	ABW,
	AUS,
	AUT,
	AZE,
	BHS,
	BHR,
	BGD,
	BRB,
	BLR,
};

struct country_code{
	uint24_t country_code;
	struct country_code * next;
};

typedef struct {
	EXT_STD_C11
	union{
		descriptor_t descriptor;
		struct {
			uint8_t descriptor_tag;
			uint8_t descriptor_length;
			void * next;
			uint8_t country_availability_flag:1;
			uint8_t reserved_future_use:7;
			struct country_code* country_list;
		};
	};
}country_availability_descriptor_t;

typedef struct {
}linkage_descriptor_t;

typedef struct {
}NVOD_reference_descriptor_t;

typedef struct{
}time_shifted_service_descriptor_t;

typedef struct{

}short_event_descriptor_t;

typedef struct {
}extended_event_descriptor_t;

typedef struct{

}time_shifted_event_descriptor_t;

typedef struct { 
	EXT_STD_C11
	union{
		descriptor_t descriptor;
		struct {
			uint8_t descriptor_tag;
			uint8_t descriptor_length;
			void * next;
			uint8_t stream_content_ext:4; 
			uint8_t stream_content:4;
			uint8_t component_type;
			uint32_t component_tag:8; 
			uint32_t ISO_639_language_code:24; 
			uint8_t *text_char;
		};
	};
} component_descriptor_t;

typedef struct {
}mosaic_descriptor_t;

typedef struct{
}stream_identifier_descriptor_t;

typedef struct {
	EXT_STD_C11
	union{
		descriptor_t descriptor;
		struct {
			uint8_t descriptor_tag;
			uint8_t descriptor_length;
			void * next;
			uint16_t *CA_system_id; /*ETSI TS 101 162 [i.1]*/
		};
	};
}CA_identifier_descriptor_t;

struct content_info{
	uint8_t content_nibble_level_1:4;
	uint8_t content_nibble_level_2:4;
	uint8_t byte;
	struct content_info * next;
};

typedef struct {
	EXT_STD_C11
	union{
		descriptor_t descriptor;
		struct {
			uint8_t descriptor_tag;
			uint8_t descriptor_length;
			void * next;
			struct content_info * content_list;
		};
	};
}content_descriptor_t;


typedef struct {
}parental_rating_descriptor_t;

typedef struct{
}teletext_descriptor_t;

typedef struct{

}telephone_descriptor_t;

typedef struct {
}local_time_offset_descriptor_t;

typedef struct{
}subtitling_descriptor_t;

typedef struct {
}terrestrial_delivery_system_descriptor_t;

typedef struct {
}multilingual_network_name_descriptor_t;

typedef struct {
}multilingual_bouquet_name_descriptor_t;

typedef struct {
}multilingual_service_name_descriptor_t;
typedef struct {
}multilingual_component_descriptor_t;

typedef struct {
}private_data_specifier_descriptor_t;

typedef struct{}service_move_descriptor_t;

typedef struct{}short_smoothing_buffer_descriptor_t;

typedef struct {
}frequency_list_descriptor_t;

typedef struct {}partial_transport_stream_descriptor_t;

typedef struct {

}data_broadcast_descriptor_t;

typedef struct {
}scrambling_descriptor_t;

typedef struct {

}data_broadcast_id_descriptor_t;


typedef struct{ }transport_stream_descriptor_t;

typedef struct {
}DSNG_descriptor_t;

typedef struct {
}PDC_descriptor_t;


typedef struct {
}AC3_descriptor_t;

/*ancillary_data_descriptor*/
struct ancillary_data_identifier
{
	uint8_t DVD_video_ancillary_data:1;
	uint8_t extended_ancillary_data:1;
	uint8_t announcement_switching_data:1;
	uint8_t DAB_ancillary_data:1;
	uint8_t scale_factor_error_check:1;
	uint8_t MPEG4_ancillary_data:1;
	uint8_t RDS_via_UECP:1;
	uint8_t reserved:1;
};

typedef struct {
	EXT_STD_C11
	union{
		descriptor_t descriptor;
		struct {
			uint8_t descriptor_tag;
			uint8_t descriptor_length;
			void * next;
			struct ancillary_data_identifier identifier;
		};
	};
}ancillary_data_descriptor_t;


struct subcell_list_info{
	uint64_t cell_id_extension:8;
	uint64_t subcell_latitude:16;
	uint64_t subcell_longitude:16;
	uint64_t subcell_extent_of_latitude:12;
	uint64_t subcell_extent_of_longitude:12;
	struct subcell_list_info *next;
};

struct cell_list_info{
	uint16_t cell_id;
	uint16_t cell_latitude;
	uint16_t cell_longitude;
	uint32_t cell_extent_of_latitude:12;
	uint32_t cell_extent_of_longitude:12;
	uint32_t subcell_info_loop_length:8;
	struct subcell_list_info *subcell_list;
	struct cell_list_info *next;
};

typedef struct {
	EXT_STD_C11
	union{
		descriptor_t descriptor;
		struct {
			uint8_t descriptor_tag;
			uint8_t descriptor_length;
			void * next;
			struct cell_list_info * cell_list;
		};
	};
} cell_list_descriptor_t;

struct subcell_info{
	uint8_t cell_id_extension;
	uint32_t transposer_frequency;
	struct subcell_info *next;
};

struct cell_frequency_info{
	uint16_t cell_id;
	uint32_t frequency;
	uint8_t subcell_info_loop_length;
	struct subcell_info *subcell_info_list;
};

typedef struct {
	EXT_STD_C11
	union{
		descriptor_t descriptor;
		struct {
			uint8_t descriptor_tag;
			uint8_t descriptor_length;
			void * next;
			struct cell_frequency_info *cell_info_list;
		};
	};
}cell_frequency_link_descriptor_t;


/*Announcement support descriptor*/
struct announcement_support_indicator {
	uint16_t emergency_alarm:1;
	uint16_t road_traffic_flash:1;
	uint16_t public_transport_flash:1;
	uint16_t warning_message:1;
	uint16_t news_flash:1;
	uint16_t weather_flash:1;
	uint16_t event_announcement:1;
	uint16_t personal_call:1;
	uint16_t reserved:8;
};

struct reference{
	uint16_t original_network_id;
	uint16_t transport_stream_id;
	uint16_t service_id;
	uint8_t component_tag;
};

struct announcement_info {
	uint8_t announcement_type:4;
	uint8_t reserved_future_use:1;
	uint8_t reference_type:3;
	struct reference ref;
	struct announcement_info * next;
};

typedef struct {
	EXT_STD_C11
	union{
	descriptor_t descriptor;
	struct {
		uint8_t descriptor_tag;
		uint8_t descriptor_length;
		void *next;
		struct announcement_support_indicator indicator;
		struct announcement_info *info;
		};
	};
}announcement_support_descriptor_t;


typedef struct{}application_signalling_descriptor_t;

/*adaptation_field_data_descriptor*/
struct adaptation_field_data_identifier
{
	uint8_t announcement_switching_data:1;
	uint8_t AU_information_data:1;
	uint8_t PVR_assist_information_data:1;
	uint8_t tsap_timeline:1;
	uint8_t reserved:4;
};

typedef struct {
	EXT_STD_C11
	union{
		descriptor_t descriptor;
		struct {
			uint8_t descriptor_tag;
			uint8_t descriptor_length;
			void * next;
			struct adaptation_field_data_identifier identifier;
		};
	};
}adaptation_field_data_descriptor_t;

typedef struct{}service_identifier_descriptor_t;

typedef struct {
}service_availability_descriptor_t;

typedef struct {}default_authority_descriptor_t;
typedef struct {} related_content_descriptor_t;
typedef struct{}TVA_id_descriptor_t;


typedef struct {

}content_identifier_descriptor_t;

typedef struct{

}time_slice_fec_identifier_descriptor_t;

typedef struct{

}ECM_repetition_rate_descriptor_t;

typedef struct {
}S2_satellite_delivery_system_descriptor_t;

typedef struct {
}enhanced_AC3_descriptor_t;


typedef struct{

}DTS_descriptor_t;


typedef struct{

}AAC_descriptor_t;

typedef struct{

}XAIT_location_descriptor_t;

typedef struct { /*0x7E*/
}FTA_content_management_descriptor_t;

typedef struct {
}extension_descriptor_t;

struct descriptor_ops{
	uint8_t tag;
	char tag_name[64];
	int ( *descriptor_parse)(uint8_t *data, uint32_t len,void *ptr);
	void* (*descriptor_alloc)(void);
};


#ifdef __cplusplus
}
#endif

#endif /* _DESCRIPTOR_H_ */
