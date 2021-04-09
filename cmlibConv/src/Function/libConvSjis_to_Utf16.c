
#include "common.h"

/*---------------------------------------------------------------------------
  Shift_JIS文字列をUTF-16に変換する
    sjis: Shift_JIS文字列へのポインタ
    utf16: UTF-16文字列へのポインタ
    return: 変換した文字数
---------------------------------------------------------------------------*/
u32 libConvSjis_to_Utf16(void *utf16, const void *sjis)
{
  u16 unicode;
  const u8 *src = (const u8 *)sjis;
  u16 *dst = (u16 *)utf16;
  u32 i = 0;

  while (*src)
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

    dst[i++] = unicode;
  }

  dst[i] = 0;

  return i;
}
