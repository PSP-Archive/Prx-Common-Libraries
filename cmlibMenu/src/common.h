#ifndef LIBMENU_COMMON_H
#define LIBMENU_COMMON_H

#include <psptypes.h>
#include <pspkernel.h>
#include <pspsdk.h>
#include <pspsysclib.h>

#include <pspdisplay.h>
#include <pspge.h>


#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>


#include "cmlibmenu.h"

#ifdef __cplusplus
extern "C" {
#endif


#ifndef SCR_WIDTH
#define SCR_WIDTH 			480
#endif

#ifndef SCR_HEIGHT
#define SCR_HEIGHT 			272
#endif

#ifndef BUF_WIDTH
#define BUF_WIDTH 			512
#endif

#define	DRAW_CHR_XMAX		472
#define	DRAW_CHR_YMAX		264



//0x44000000
//0x40000000
#define	VRAM_ADDR_TOP		0x40000000




#define	IS_OPT(opt)			(opt && opt->type != LIBM_OPT_NONE)
#define	IS_OPT_FUNC(opt)	(opt && opt->type == LIBM_OPT_FUNC)
#define	IS_OPT_LIST(opt)	(opt && opt->type == LIBM_OPT_LIST)

#define	IS_OPT_FUNC_M(opt)	(IS_OPT_FUNC(opt) && opt->func.malloc_p)
#define	IS_OPT_FUNC_F(opt)	(IS_OPT_FUNC(opt) && opt->func.free_p)

#define	GET_ARRAY_SIZE(size)	( size / sizeof(MenuItem*) )

//#define BLEND_FUNC( src_ch, dst_ch, alpha, maxbits ) ( ( ( ( src_ch ) + 1 - ( dst_ch ) ) * ( alpha ) >> ( maxbits ) ) + ( dst_ch ) )
#define BLEND_FUNC(src_ch, dst_ch, alpha, maxbits) ((dst_ch) + ((((src_ch) - (dst_ch)) * (alpha)) >> (maxbits)))


#define SWAP( a, b )		\
{							\
	int t = *(int *)a;		\
	*(int *)a = *(int *)b;	\
	*(int *)b = t;			\
}

#define	VRAM_INIT(adr,f,w,s)					{															\
													vinfo.format	= f;									\
													vinfo.lineWidth	= w;									\
													vinfo.buffer	= (void*) (VRAM_ADDR_TOP | (u32)(adr));	\
													sceDisplaySetFrameBuf(adr, w, f, s);					\
												}

bool _vram_sync(int sync);
MenuItem* _createItem(libmOpt *opt ,const char* Name,MenuItemType type);
/*
extern u32 (*convert)(u32);
extern u32 (*blend)(u8,u32,u32);
extern libm_vram_info vinfo,vinfo_tmp;
extern int psx,psy;
*/

extern int vsnprintf( char *buf, size_t n, const char *fmt, va_list ap );
extern int snprintf( char *buf, size_t n, const char *fmt, ... );


#ifdef __cplusplus
}
#endif

#endif
