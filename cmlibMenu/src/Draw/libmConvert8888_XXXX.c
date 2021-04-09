#include "common.h"

/*
struct ColorConvertCache{
	u32 src;
	u16 dst;
};

static struct ColorConvertCache cache_5650;
static struct ColorConvertCache cache_5551;
static struct ColorConvertCache cache_4444;
*/

inline u32 libmConvert8888_5650( u32 src )
{
/*
	u32 ret;
	
	if(src == cache_5650.src){
		ret = cache_5650.dst;
	}
	else{
		ret = ((src & 0x00f80000) >> 8) | ((src & 0x0000fc00) >> 5) | ((src & 0x000000f8) >> 3);
		cache_5650.src = src;
		cache_5650.dst = ret;
	}

	return ret;
*/
	
	return ((src & 0x00f80000) >> 8) | ((src & 0x0000fc00) >> 5) | ((src & 0x000000f8) >> 3);
}

inline u32 libmConvert8888_5551( u32 src )
{
/*
	u32 ret;
	
	if(src == cache_5551.src){
		ret = cache_5551.dst;
	}
	else{
		ret = (( ( src >> 24 ) ? 1 : 0 ) << 15) | ((src & 0x00f80000) >> 9 ) | ((src & 0x0000f800) >> 6 ) | ((src & 0x000000f8) >> 3 );
		cache_5551.src = src;
		cache_5551.dst = ret;
	}
	
	return ret;
*/
	
	return (( ( src >> 24 ) ? 1 : 0 ) << 15) | ((src & 0x00f80000) >> 9 ) | ((src & 0x0000f800) >> 6 ) | ((src & 0x000000f8) >> 3 );
}

inline u32 libmConvert8888_4444( u32 src )
{
/*
	u32 ret;
	
	if(src == cache_4444.src){
		ret = cache_4444.dst;
	}
	else{
		ret = ((src & 0xf0000000) >> 16) | ((src & 0x00f00000) >> 12) | ((src & 0x0000f000) >> 8 ) | ((src & 0x000000f0) >> 4 );
		cache_4444.src = src;
		cache_4444.dst = ret;
	}
	
	return ret;
*/
	
	return ((src & 0xf0000000) >> 16) | ((src & 0x00f00000) >> 12) | ((src & 0x0000f000) >> 8 ) | ((src & 0x000000f0) >> 4 );
}

