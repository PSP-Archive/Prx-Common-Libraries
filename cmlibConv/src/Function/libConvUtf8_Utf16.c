
#include "common.h"

/*---------------------------------------------------------------------------
  UFT-8Nの一文字をUTF-16に変換する
    *utf16: 変換後の文字(UTF-16)へのポインタ
    *utf8: UFT-8N文字へのポインタ
    return: UTF-8Nの次の文字へのポインタ
---------------------------------------------------------------------------*/
char* libConvUtf8_Utf16(u16 *utf16, const char *utf8)
{
  u8 c = *utf8++;
  u16 code;
  s32 tail = 0;

  if((c <= 0x7f) || (c >= 0xc2))
  {
    /* Start of new character. */
    if(c < 0x80)
    {
      /* U-00000000 - U-0000007F, 1 byte */
      code = c;
    }
    else if(c < 0xe0)   /* U-00000080 - U-000007FF, 2 bytes */
    {
      tail = 1;
      code = c & 0x1f;
    }
    else if(c < 0xf0)   /* U-00000800 - U-0000FFFF, 3 bytes */
    {
      tail = 2;
      code = c & 0x0f;
    }
    else if(c < 0xf5)   /* U-00010000 - U-001FFFFF, 4 bytes */
    {
      tail = 3;
      code = c & 0x07;
    }
    else                /* Invalid size. */
    {
      code = 0xfffd;
    }

    while(tail-- && ((c = *utf8++) != 0))
    {
      if((c & 0xc0) == 0x80)
      {
        /* Valid continuation character. */
        code = (code << 6) | (c & 0x3f);

      }
      else
      {
        /* Invalid continuation char */
        code = 0xfffd;
        utf8--;
        break;
      }
    }
  }
  else
  {
    /* Invalid UTF-8 char */
    code = 0xfffd;
  }
  /* currently we don't support chars above U-FFFF */
  *utf16 = (code < 0x10000) ? code : 0xfffd;
  return (char*)utf8;
}
