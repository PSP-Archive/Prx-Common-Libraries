
#include <psptypes.h>
#include <pspiofilemgr.h>
#include <pspkernel.h>
#include <pspsysmem_kernel.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "memory.h"
#include "cmlibconv.h"

#define ERR (0)
PSP_MODULE_INFO( "cmlibConv", PSP_MODULE_KERNEL, 0, 1 );


//Thanks takka!!
/*------------------------------------------------------------------------------------------*/
//文字列変換

static u16 *StoU_convert_table[0x100] ={0};
static u16 *UtoS_convert_table[0x100] = {0};


void SetSUPoint()
{
	StoU_convert_table[0x00] = SU->S00;
	StoU_convert_table[0x81] = SU->S81;
	StoU_convert_table[0x82] = SU->S82;
	StoU_convert_table[0x83] = SU->S83;
	StoU_convert_table[0x84] = SU->S84;
	StoU_convert_table[0x87] = SU->S87;
	StoU_convert_table[0x88] = SU->S88;
	StoU_convert_table[0x89] = SU->S89;
	StoU_convert_table[0x8a] = SU->S8a;
	StoU_convert_table[0x8b] = SU->S8b;
	StoU_convert_table[0x8c] = SU->S8c;
	StoU_convert_table[0x8d] = SU->S8d;
	StoU_convert_table[0x8e] = SU->S8e;
	StoU_convert_table[0x8f] = SU->S8f;
	StoU_convert_table[0x90] = SU->S90;
	StoU_convert_table[0x91] = SU->S91;
	StoU_convert_table[0x92] = SU->S92;
	StoU_convert_table[0x93] = SU->S93;
	StoU_convert_table[0x94] = SU->S94;
	StoU_convert_table[0x95] = SU->S95;
	StoU_convert_table[0x96] = SU->S96;
	StoU_convert_table[0x97] = SU->S97;
	StoU_convert_table[0x98] = SU->S98;
	StoU_convert_table[0x99] = SU->S99;
	StoU_convert_table[0x9a] = SU->S9a;
	StoU_convert_table[0x9b] = SU->S9b;
	StoU_convert_table[0x9c] = SU->S9c;
	StoU_convert_table[0x9d] = SU->S9d;
	StoU_convert_table[0x9e] = SU->S9e;
	StoU_convert_table[0x9f] = SU->S9f;
	StoU_convert_table[0xe0] = SU->Se0;
	StoU_convert_table[0xe1] = SU->Se1;
	StoU_convert_table[0xe2] = SU->Se2;
	StoU_convert_table[0xe3] = SU->Se3;
	StoU_convert_table[0xe4] = SU->Se4;
	StoU_convert_table[0xe5] = SU->Se5;
	StoU_convert_table[0xe6] = SU->Se6;
	StoU_convert_table[0xe7] = SU->Se7;
	StoU_convert_table[0xe8] = SU->Se8;
	StoU_convert_table[0xe9] = SU->Se9;
	StoU_convert_table[0xea] = SU->Sea;
	StoU_convert_table[0xed] = SU->Sed;
	StoU_convert_table[0xee] = SU->See;
	StoU_convert_table[0xfa] = SU->Sfa;
	StoU_convert_table[0xfb] = SU->Sfb;
	StoU_convert_table[0xfc] = SU->Sfc;
}


void SetUSPoint()
{
	UtoS_convert_table[0x00] = US->U00;
	UtoS_convert_table[0x03] = US->U03;
	UtoS_convert_table[0x04] = US->U04;
	UtoS_convert_table[0x20] = US->U20;
	UtoS_convert_table[0x21] = US->U21;
	UtoS_convert_table[0x22] = US->U22;
	UtoS_convert_table[0x23] = US->U23;
	UtoS_convert_table[0x25] = US->U25;
	UtoS_convert_table[0x26] = US->U26;
	UtoS_convert_table[0x30] = US->U30;
	UtoS_convert_table[0x4e] = US->U4e;
	UtoS_convert_table[0x4f] = US->U4f;
	UtoS_convert_table[0x50] = US->U50;
	UtoS_convert_table[0x51] = US->U51;
	UtoS_convert_table[0x52] = US->U52;
	UtoS_convert_table[0x53] = US->U53;
	UtoS_convert_table[0x54] = US->U54;
	UtoS_convert_table[0x55] = US->U55;
	UtoS_convert_table[0x56] = US->U56;
	UtoS_convert_table[0x57] = US->U57;
	UtoS_convert_table[0x58] = US->U58;
	UtoS_convert_table[0x59] = US->U59;
	UtoS_convert_table[0x5a] = US->U5a;
	UtoS_convert_table[0x5b] = US->U5b;
	UtoS_convert_table[0x5c] = US->U5c;
	UtoS_convert_table[0x5d] = US->U5d;
	UtoS_convert_table[0x5e] = US->U5e;
	UtoS_convert_table[0x5f] = US->U5f;
	UtoS_convert_table[0x60] = US->U60;
	UtoS_convert_table[0x61] = US->U61;
	UtoS_convert_table[0x62] = US->U62;
	UtoS_convert_table[0x63] = US->U63;
	UtoS_convert_table[0x64] = US->U64;
	UtoS_convert_table[0x65] = US->U65;
	UtoS_convert_table[0x66] = US->U66;
	UtoS_convert_table[0x67] = US->U67;
	UtoS_convert_table[0x68] = US->U68;
	UtoS_convert_table[0x69] = US->U69;
	UtoS_convert_table[0x6a] = US->U6a;
	UtoS_convert_table[0x6b] = US->U6b;
	UtoS_convert_table[0x6c] = US->U6c;
	UtoS_convert_table[0x6d] = US->U6d;
	UtoS_convert_table[0x6e] = US->U6e;
	UtoS_convert_table[0x6f] = US->U6f;
	UtoS_convert_table[0x70] = US->U70;
	UtoS_convert_table[0x71] = US->U71;
	UtoS_convert_table[0x72] = US->U72;
	UtoS_convert_table[0x73] = US->U73;
	UtoS_convert_table[0x74] = US->U74;
	UtoS_convert_table[0x75] = US->U75;
	UtoS_convert_table[0x76] = US->U76;
	UtoS_convert_table[0x77] = US->U77;
	UtoS_convert_table[0x78] = US->U78;
	UtoS_convert_table[0x79] = US->U79;
	UtoS_convert_table[0x7a] = US->U7a;
	UtoS_convert_table[0x7b] = US->U7b;
	UtoS_convert_table[0x7c] = US->U7c;
	UtoS_convert_table[0x7d] = US->U7d;
	UtoS_convert_table[0x7e] = US->U7e;
	UtoS_convert_table[0x7f] = US->U7f;
	UtoS_convert_table[0x80] = US->U80;
	UtoS_convert_table[0x81] = US->U81;
	UtoS_convert_table[0x82] = US->U82;
	UtoS_convert_table[0x83] = US->U83;
	UtoS_convert_table[0x84] = US->U84;
	UtoS_convert_table[0x85] = US->U85;
	UtoS_convert_table[0x86] = US->U86;
	UtoS_convert_table[0x87] = US->U87;
	UtoS_convert_table[0x88] = US->U88;
	UtoS_convert_table[0x89] = US->U89;
	UtoS_convert_table[0x8a] = US->U8a;
	UtoS_convert_table[0x8b] = US->U8b;
	UtoS_convert_table[0x8c] = US->U8c;
	UtoS_convert_table[0x8d] = US->U8d;
	UtoS_convert_table[0x8e] = US->U8e;
	UtoS_convert_table[0x8f] = US->U8f;
	UtoS_convert_table[0x90] = US->U90;
	UtoS_convert_table[0x91] = US->U91;
	UtoS_convert_table[0x92] = US->U92;
	UtoS_convert_table[0x93] = US->U93;
	UtoS_convert_table[0x94] = US->U94;
	UtoS_convert_table[0x95] = US->U95;
	UtoS_convert_table[0x96] = US->U96;
	UtoS_convert_table[0x97] = US->U97;
	UtoS_convert_table[0x98] = US->U98;
	UtoS_convert_table[0x99] = US->U99;
	UtoS_convert_table[0x9a] = US->U9a;
	UtoS_convert_table[0x9b] = US->U9b;
	UtoS_convert_table[0x9c] = US->U9c;
	UtoS_convert_table[0x9d] = US->U9d;
	UtoS_convert_table[0x9e] = US->U9e;
	UtoS_convert_table[0x9f] = US->U9f;
	UtoS_convert_table[0xff] = US->Uff;
}

int LoadFile(int flag){
    SceUID fd;
    SceSize size, readsize, struct_zize = flag == 1 ? sizeof(StoU) : sizeof(UtoS);
    char path[64] = "ms0:/seplugins/lib/conv/";
    char *conv_bin[] = {"StoU.bin", "UtoS.bin"};
	void *conv_buf;
    
    // make path
    strcat(path, conv_bin[flag - 1]);
    
    // file open
    fd = sceIoOpen(path, PSP_O_RDONLY, 0777);
    if(fd < 0){
        path[0] = 'e';
        path[1] = 'f';
        fd = sceIoOpen(path, PSP_O_RDONLY, 0777);
        if(fd < 0){
            return fd;
        }
    }
    
    // get file size
    size = sceIoLseek(fd, 0, SEEK_END);
    if(size <= 0 || struct_zize != size){
        sceIoClose(fd);
        return -2;
    }
    
    // malloc
    //mem_set_alloc_mode(MEM_AUTO);
    conv_buf = mem_alloc(size);
    if(conv_buf == NULL){
        sceIoClose(fd);
        return -3;
    }
    
    // read font
    sceIoLseek(fd, 0, SEEK_SET);
    readsize = sceIoRead(fd, conv_buf, size);
    sceIoClose(fd);
    if(readsize != size){
        mem_free(conv_buf);
		conv_buf = NULL;
        return -4;
    }
	if(flag == 1)
	{
		SU = conv_buf;
	} else {
		US = conv_buf;
	}
    return 0;
}


/*---------------------------------------------------------------------------
  Shift_JISの一文字をUTF-16に変換する
    sjis: Shift_JIS
    return: UTF-16
---------------------------------------------------------------------------*/
u16 libConvSjis_Utf16(u16 sjis)
{
	const u16 *table;

	if(SU == NULL)
	{
		int ret = LoadFile(1);
		if(ret < 0)return ret;
		SetSUPoint();
	}
	if ((table = StoU_convert_table[sjis >> 8]) != ERR)
		return table[sjis & 0xff];

	return 0;
}

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

/*---------------------------------------------------------------------------
  UTF-16の一文字をShift_JISに変換する
    utf16: UTF-16
    return: Shift_JIS
---------------------------------------------------------------------------*/
u16 libConvUtf16_Sjis(u16 utf16)
{
    const u16 *table;
	
	if(US == NULL)
	{
		int ret = LoadFile(2);
		if(ret < 0)return ret;
		SetUSPoint();
	}
    if ((table = UtoS_convert_table[utf16 >> 8]) != ERR){
        return table[utf16 & 0xff];
	}

    return 0;
}

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

/*---------------------------------------------------------------------------
  UFT-8Nの文字列をUTF-16に変換する
    *utf16: 変換後の文字列(UTF-16)へのポインタ
    *utf8: UFT-8N文字列へのポインタ
---------------------------------------------------------------------------*/
void libConvUtf8_to_Utf16(u16 *utf16, const char *utf8)
{
  while(*utf8 !='\0')
  {
    utf8 = libConvUtf8_Utf16(utf16++, utf8);
  }
  *utf16 = '\0';
}

/*---------------------------------------------------------------------------
  UTF-16の文字列の長さを得る
    *utf16: 文字列(UTF-16)へのポインタ
    return: 文字数
---------------------------------------------------------------------------*/
u16 libConvUtf16len(const u16 *utf16)
{
  u16 len = 0;
  while(utf16[len] != '\0')
    len++;
  return len;
}

/*---------------------------------------------------------------------------
  UFT-8Nの文字列をShift_JISに変換する
    *sjis: 変換後の文字列(Shift_JIS)へのポインタ
    *utf8: UFT-8N文字列へのポインタ
---------------------------------------------------------------------------*/
void libConvUtf8_to_Sjis(void *sjis, const char *utf8)
{
	char *buf = mem_alloc(strlen(utf8)*2);
	
	libConvUtf8_to_Utf16((void *)buf, utf8);
	//UTF-8をUTF-16に変換
	libConvUtf16_to_Sjis(sjis, buf);
	//UTF-16をSJISに変換
	
	mem_free(buf);
}


void libConvFreeMem()
{
	if(US != NULL){
		mem_free(US);
		memset(UtoS_convert_table, 0, sizeof(UtoS_convert_table));
	}
	if(SU != NULL){
		mem_free(SU);
		memset(StoU_convert_table, 0, sizeof(StoU_convert_table));
	}
}

// entry point
int module_start(SceSize args, void *argp){
	return 0;
}

int module_stop(SceSize args, void *argp){
	return 0;
}

