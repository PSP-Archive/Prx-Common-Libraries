#ifndef LIBCONV_COMMON_H
#define LIBCONV_COMMON_H

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

typedef struct StoU_ {
	u16 S00[0x100];
	u16 S81[0x100];
	u16 S82[0x100];
	u16 S83[0x100];
	u16 S84[0x100];
	u16 S87[0x100];
	u16 S88[0x100];
	u16 S89[0x100];
	u16 S8a[0x100];
	u16 S8b[0x100];
	u16 S8c[0x100];
	u16 S8d[0x100];
	u16 S8e[0x100];
	u16 S8f[0x100];
	u16 S90[0x100];
	u16 S91[0x100];
	u16 S92[0x100];
	u16 S93[0x100];
	u16 S94[0x100];
	u16 S95[0x100];
	u16 S96[0x100];
	u16 S97[0x100];
	u16 S98[0x100];
	u16 S99[0x100];
	u16 S9a[0x100];
	u16 S9b[0x100];
	u16 S9c[0x100];
	u16 S9d[0x100];
	u16 S9e[0x100];
	u16 S9f[0x100];
	u16 Se0[0x100];
	u16 Se1[0x100];
	u16 Se2[0x100];
	u16 Se3[0x100];
	u16 Se4[0x100];
	u16 Se5[0x100];
	u16 Se6[0x100];
	u16 Se7[0x100];
	u16 Se8[0x100];
	u16 Se9[0x100];
	u16 Sea[0x100];
	u16 Sed[0x100];
	u16 See[0x100];
	u16 Sfa[0x100];
	u16 Sfb[0x100];
	u16 Sfc[0x100];
} StoU;

typedef struct UtoS_ {
	u16 U00[0x100];
	u16 U03[0x100];
	u16 U04[0x100];
	u16 U20[0x100];
	u16 U21[0x100];
	u16 U22[0x100];
	u16 U23[0x100];
	u16 U25[0x100];
	u16 U26[0x100];
	u16 U30[0x100];
	u16 U4e[0x100];
	u16 U4f[0x100];
	u16 U50[0x100];
	u16 U51[0x100];
	u16 U52[0x100];
	u16 U53[0x100];
	u16 U54[0x100];
	u16 U55[0x100];
	u16 U56[0x100];
	u16 U57[0x100];
	u16 U58[0x100];
	u16 U59[0x100];
	u16 U5a[0x100];
	u16 U5b[0x100];
	u16 U5c[0x100];
	u16 U5d[0x100];
	u16 U5e[0x100];
	u16 U5f[0x100];
	u16 U60[0x100];
	u16 U61[0x100];
	u16 U62[0x100];
	u16 U63[0x100];
	u16 U64[0x100];
	u16 U65[0x100];
	u16 U66[0x100];
	u16 U67[0x100];
	u16 U68[0x100];
	u16 U69[0x100];
	u16 U6a[0x100];
	u16 U6b[0x100];
	u16 U6c[0x100];
	u16 U6d[0x100];
	u16 U6e[0x100];
	u16 U6f[0x100];
	u16 U70[0x100];
	u16 U71[0x100];
	u16 U72[0x100];
	u16 U73[0x100];
	u16 U74[0x100];
	u16 U75[0x100];
	u16 U76[0x100];
	u16 U77[0x100];
	u16 U78[0x100];
	u16 U79[0x100];
	u16 U7a[0x100];
	u16 U7b[0x100];
	u16 U7c[0x100];
	u16 U7d[0x100];
	u16 U7e[0x100];
	u16 U7f[0x100];
	u16 U80[0x100];
	u16 U81[0x100];
	u16 U82[0x100];
	u16 U83[0x100];
	u16 U84[0x100];
	u16 U85[0x100];
	u16 U86[0x100];
	u16 U87[0x100];
	u16 U88[0x100];
	u16 U89[0x100];
	u16 U8a[0x100];
	u16 U8b[0x100];
	u16 U8c[0x100];
	u16 U8d[0x100];
	u16 U8e[0x100];
	u16 U8f[0x100];
	u16 U90[0x100];
	u16 U91[0x100];
	u16 U92[0x100];
	u16 U93[0x100];
	u16 U94[0x100];
	u16 U95[0x100];
	u16 U96[0x100];
	u16 U97[0x100];
	u16 U98[0x100];
	u16 U99[0x100];
	u16 U9a[0x100];
	u16 U9b[0x100];
	u16 U9c[0x100];
	u16 U9d[0x100];
	u16 U9e[0x100];
	u16 U9f[0x100];
	u16 Uff[0x100];
} UtoS;

StoU *SU;
UtoS *US;

extern u16 *StoU_convert_table[];
extern u16 *UtoS_convert_table[];

#define issjis1(c)	(((c) >= 0x81 && (c) <= 0x9f) | ((c) >= 0xe0 && (c) <= 0xfc))
#define issjis2(c)	((c) >= 0x40 && (c) <= 0xfc && (c) != 0x7f)

int LoadFile(int flag);
void SetSUPoint();
void SetUSPoint();


#endif
