
#include "common.h"

/*---------------------------------------------------------------------------
  UTF-16文字列をShift_JISに変換する
    sjis: Shift_JIS文字列へのポインタ
    utf16: UTF-16文字列へのポインタ
    return: 変換した文字数
---------------------------------------------------------------------------*/
u32 libConvUtf16_to_Sjis(void *sjis, const void *utf16)
{
  u16 shift_jis;
  const u16 *src = (const u16 *)utf16;
  u8 *dst = (u8 *)sjis;
  u32 i = 0;

  while (*src)
  {
    shift_jis = libConvUtf16_Sjis(*src);
    if(shift_jis < 0x100)
    {
      *dst = shift_jis;
      dst++;
    }
    else
    {
      *dst = shift_jis >> 8;
      dst++;
      *dst = shift_jis & 0xff;
      dst++;
    }
    i++;
    src++;
  }

  *dst = 0;

  return i;
}
