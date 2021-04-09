#include "common.h"

inline u32 libmConvert4444_8888(u32 src)
{
	return ((src & 0xf000) << 28) | ((src & 0xf000) << 24) | ((src & 0x0f00) << 20) | ((src & 0x0f00) << 16) | ((src & 0x00f0) << 12) | ((src & 0x00f0) << 8 ) | ((src & 0x000f) << 4 ) | ((src & 0x000f) << 0 );
}

inline u32 libmConvert5551_8888(u32 src)
{
	return ((src & 0x8000) << 16) | ((src & 0x8000) << 15) | ((src & 0x8000) << 14) | ((src & 0x8000) << 13) | ((src & 0x8000) << 12) | ((src & 0x8000) << 11) | ((src & 0x8000) << 10) | ((src & 0x8000) << 9) |
		((src & 0x7c00) << 9) | ((src & 0x7000) << 4) | ((src & 0x03e0) << 6) | ((src & 0x0380) << 1) | ((src & 0x001f) << 3) | ((src & 0x001c) >> 2);
}

inline u32 libmConvert5650_8888(u32 src)
{
	return 0xff000000 | ((src & 0xf800) << 8) | ((src & 0xe000) << 3) | ((src & 0x07e0) << 5) | ((src & 0x0600) >> 1) | ((src & 0x001f) << 3) | ((src & 0x001c) >> 2);
}