#include "common.h"


inline u32 libmAlphaBlend8888( u8 alpha, u32 src, u32 dst )
{
	if( ! alpha )
	{
		return dst;
	}
	else if( alpha == 0xFF )
	{
		return src;
	}
	else
	{
		u32 color = alpha << 24;
		color |= BLEND_FUNC( ( src       ) & 0xFF, ( dst       ) & 0xFF, alpha, 8 );
		color |= BLEND_FUNC( ( src >>  8 ) & 0xFF, ( dst >>  8 ) & 0xFF, alpha, 8 ) << 8;
		color |= BLEND_FUNC( ( src >> 16 ) & 0xFF, ( dst >> 16 ) & 0xFF, alpha, 8 ) << 16;
		return color;
	}
}

inline u32 libmAlphaBlend4444( u8 alpha, u32 src, u32 dst )
{
	alpha = (alpha >> 4) & 0x0F;
	
	if( ! alpha )
	{
		return dst;
	}
	else if( alpha == 0xF )
	{
		return src;
	}
	else
	{
		u16 color = alpha << 12;
		
		color |= BLEND_FUNC( ( src      ) & 0xF, ( dst      ) & 0xF, alpha, 4 );
		color |= BLEND_FUNC( ( src >> 4 ) & 0xF, ( dst >> 4 ) & 0xF, alpha, 4 ) << 4;
		color |= BLEND_FUNC( ( src >> 8 ) & 0xF, ( dst >> 8 ) & 0xF, alpha, 4 ) << 8;
		
		return color;
	}
}

inline u32 libmAlphaBlend5551( u8 alpha, u32 src, u32 dst )
{
	alpha = (alpha >> 3) & 0x1F;
	
	if( ! alpha )
	{
		return dst;
	}
	else if( alpha == 0x1F )
	{
		return src;
	}
	else
	{
		u16 color = ( alpha ? 1 : 0 ) << 15;
		
		color |= BLEND_FUNC( ( src       ) & 0x1F, ( dst       ) & 0x1F, alpha, 5 );
		color |= BLEND_FUNC( ( src >>  5 ) & 0x1F, ( dst >>  5 ) & 0x1F, alpha, 5 ) << 5;
		color |= BLEND_FUNC( ( src >> 10 ) & 0x1F, ( dst >> 10 ) & 0x1F, alpha, 5 ) << 10;
		
		return color;
	}
}

inline u32 libmAlphaBlend5650( u8 alpha, u32 src, u32 dst )
{
	alpha = (alpha >> 2) & 0x3F;
	
	if( ! alpha )
	{
		return dst;
	}
	else if( alpha == 0x3F )
	{
		return src;
	}
	else
	{
		u16 color = 0;
		
		color |= BLEND_FUNC( ( src       ) & 0x1F, ( dst       ) & 0x1F, ( alpha >> 1 ) & 0x1F, 5 );
		color |= BLEND_FUNC( ( src >>  5 ) & 0x3F, ( dst >>  5 ) & 0x3F, alpha                , 6 ) << 5;
		color |= BLEND_FUNC( ( src >> 11 ) & 0x1F, ( dst >> 11 ) & 0x1F, ( alpha >> 1 ) & 0x1F, 5 ) << 11;
		
		return color;
	}
}


//	color |= BLEND_FUNC( SR	, SR, A, MBR );
//	color |= BLEND_FUNC( SG	, SG, A, MBG ) << 8;
//	color |= BLEND_FUNC( SB	, SB, A, MBB ) << 16;
