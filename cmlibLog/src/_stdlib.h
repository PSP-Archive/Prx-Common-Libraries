/*
	_stdlib.h
	2011/02/27
*/

#ifndef __STD_LIB_HEADER_
#define __STD_LIB_HEADER_

#include<stddef.h>
#include<pspkerneltypes.h>

#ifdef __cplusplus
extern "C" {
#endif

char *_ultoahex(unsigned long hex, char *dest);
wchar_t *_ultowchex(unsigned long hex, wchar_t *dest);

char *_ulltoahex(unsigned long long hex, char *dest);
wchar_t *_ulltowchex(unsigned long long hex, wchar_t *dest);

char *_ltoa10(long l, char *dest);
wchar_t *_ltowc10(long l, wchar_t *dest);

char *_lltoa10(long long ll, char *dest);
wchar_t *_lltowc10(long long ll, wchar_t *dest);

char *_ultoa10(unsigned long ul, char *dest);
wchar_t *_ultowc10(unsigned long ul, wchar_t *dest);

char *_ulltoa10(unsigned long long ull, char *dest);
wchar_t *_ulltowc10(unsigned long long ull, wchar_t *dest);

#ifdef __cplusplus
}
#endif

#endif // __STD_LIB_HEADER_