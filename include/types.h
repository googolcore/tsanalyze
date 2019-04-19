#ifndef _TYPES_H_
#define _TYPES_H_

#ifdef __cplusplus
extern "C"{
#endif


/** C extension macro for environments lacking C11 features. */
#if !defined(__STDC_VERSION__) || __STDC_VERSION__ < 201112L
#define EXT_STD_C11 __extension__
#else
#define EXT_STD_C11
#endif


#pragma pack(push, 1)
typedef struct uint24 {
	uint32_t bits:24;
}uint24_t;
#pragma pack(pop)

#ifdef __cplusplus
}
#endif

#endif /* _TYPES_H_ */