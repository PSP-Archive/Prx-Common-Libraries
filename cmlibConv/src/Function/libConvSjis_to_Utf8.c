
#include "common.h"

/*---------------------------------------------------------------------------
  Shift_JIS文字列をUTF-8Nに変換する
    sjis: Shift_JIS文字列へのポインタ
    utf: UTF-8N文字列へのポインタ
    return: 変換した文字数
---------------------------------------------------------------------------*/
u32 libConvSjis_to_Utf8(void *utf, const void *sjis)
{
  u16 unicode;
  const u8 *src = (const u8 *)sjis;
  u8 *dst = (u8 *)utf;
  u32 i = 0;

  while(*src)
  {
    if(issjis1(*src) && issjis2(*(src + 1)))
    {
      unicode = libConvSjis_Utf16((*src << 8) | *(src + 1));
      src += 2;
    }
    else
    {
      unicode = libConvSjis_Utf16(*src);
      src++;
    }

    if(unicode < 0x80)
    {
      *dst++ = unicode;
    }
    else if(unicode < 0x800)
    {
      *dst++ = 0xc0 | ((unicode >> 6) & 0x3f);
      *dst++ = 0x80 | (unicode & 0x3f);
    }
    else
    {
      *dst++ = 0xe0 | ((unicode >> 12) & 0x0f);
      *dst++ = 0x80 | ((unicode >> 6) & 0x3f);
      *dst++ = 0x80 | (unicode & 0x3f);
    }
    i++;
  }

  *dst = '\0';

  return i;
}
