/*
	_stdlib.h
	2011/06/17
*/

// #include<string.h>

#include "_stdlib.h"

#define EOS		'\0'
#define WEOS	L'\0'

#define MUL10(x) ( ( ((x) << 2) + (x) ) << 1 )

static const char num_tab[16] = "0123456789ABCDEF";
static const wchar_t wnum_tab[16] = L"0123456789ABCDEF";

static wchar_t buf[32] = L"";


static inline size_t strlen(const char *s)
{
	size_t len = 0;
	while( *s++ ) {
		len++;
	}
	return len;
}

static inline size_t wcslen( const wchar_t *wcs )
{
	size_t len = 0;
	while( *wcs++ ) {
		len++;
	}
	return len;
}

char *_ultoahex(unsigned long hex,char *dest)
{
	const unsigned long mask = 0x0F;
	char *p = dest + 2;
	
	*dest++ = '0';
	*dest++ = 'x';
	
	dest += 8;
	*dest-- = EOS;
	while(p <= dest)
	{
		*dest-- = num_tab[ hex & mask ];
		hex = hex >> 4;
	}
	
	return(p - 2);
}

wchar_t *_ultowchex(unsigned long hex,wchar_t *dest)
{
	const unsigned long mask = 0x0F;
	wchar_t *p = dest + 2;
	
	*dest++ = L'0';
	*dest++ = L'x';
	
	dest += 8;
	*dest-- = WEOS;
	while(p <= dest)
	{
		*dest-- = wnum_tab[ hex & mask ];
		hex = hex >> 4;
	}
	
	return(p - 2);
}

char *_ulltoahex(unsigned long long hex, char *dest)
{
	const unsigned long long mask = 0x0F;
	char *p = dest;

	*dest++ = '0';
	*dest++ = 'x';

	dest += 17;
	p += 9 + 2;	// 9~16
	*dest-- = EOS; // 17 = '\0';
	while(p <= dest)
	{
		*dest-- = num_tab[ hex & mask ];
		hex = hex >> 4;
	}
	*dest-- = ' '; // 8 = ' ';
	p -= 9; // 0~7
	while(p <= dest)
	{
		*dest-- = num_tab[ hex & mask ];
		hex = hex >> 4;
	}

	return(p - 2);
}

wchar_t *_ulltowchex(unsigned long long hex, wchar_t *dest)
{
	const unsigned long long mask = 0x0F;
	wchar_t *p = dest;

	*dest++ = L'0';
	*dest++ = L'x';

	dest += 17;
	p += 9 + 2;	// 9~16
	*dest-- = WEOS; // 17 = L'\0';
	while(p <= dest)
	{
		*dest-- = wnum_tab[ hex & mask ];
		hex = hex >> 4;
	}
	*dest-- = L' '; // 8 = L' ';
	p -= 9; // 0~7
	while(p <= dest)
	{
		*dest-- = wnum_tab[ hex & mask ];
		hex = hex >> 4;
	}

	return(p - 2);
}

char *_ltoa10(long l, char *dest)
{
	unsigned long ul = 0, num = 0;
	char *p = dest, *b;
	
	b = (char *)buf;
	if(l < 0) {
		*dest++ = '-';
		ul = (unsigned long) ~(l - 1);
	} else {
		ul = (unsigned long)l;
	}
	
	while(num = ul / 10)
	{
		*b++ = num_tab[ul - MUL10(num)];
		ul = num;
	}
	
	*b++ = num_tab[ul];
	*b = EOS;
	
	dest += strlen((char *)buf);
	*dest-- = EOS;
	b = (char *)buf;
	while(*b)
		*dest-- = *b++;
	
	return p;
}

wchar_t *_ltowc10(long l, wchar_t *dest)
{
	unsigned long ul = 0, num = 0;
	wchar_t *p = dest, *b;
	
	b = buf;
	if(l < 0) {
		*dest++ = L'-';
		ul = (unsigned long) ~(l - 1);
	} else {
		ul = (unsigned long)l;
	}
	
	while(num = ul / 10)
	{
		*b++ = wnum_tab[ul - MUL10(num)];
		ul = num;
	}
	
	*b++ = wnum_tab[ul];
	*b = WEOS;
	
	dest += wcslen(buf);
	*dest-- = WEOS;
	b = buf;
	while(*b)
		*dest-- = *b++;
	
	return p;
}

char *_lltoa10(long long ll, char *dest)
{
	unsigned long long ull = 0, num = 0;
	char *p = dest, *b;
	
	b = (char *)buf;
	if(ll < 0) {
		*dest++ = '-';
		ull = (unsigned long long) ~(ll - 1);
	} else {
		ull = (unsigned long long)ll;
	}
	
	while(num = ull / 10)
	{
		*b++ = num_tab[ull - MUL10(num)];
		ull = num;
	}
	
	*b++ = num_tab[ull];
	*b = EOS;
	
	dest += strlen((const char *)buf);
	*dest-- = EOS;
	b = (char *)buf;
	while(*b)
		*dest-- = *b++;
	
	return p;
}

wchar_t *_lltowc10(long long ll, wchar_t *dest)
{
	unsigned long long ull = 0, num = 0;
	wchar_t *p = dest, *b;
	
	b = buf;
	if(ll < 0) {
		*dest++ = L'-';
		ull = (unsigned long long) ~(ll - 1);
	} else {
		ull = (unsigned long long)ll;
	}
	
	while(num = ull / 10)
	{
		*b++ = wnum_tab[ull - MUL10(num)];
		ull = num;
	}
	
	*b++ = wnum_tab[ull];
	*b = WEOS;
	
	dest += wcslen(buf);
	*dest-- = WEOS;
	b = buf;
	while(*b)
		*dest-- = *b++;
	
	return p;
}

char *_ultoa10(unsigned long ul, char *dest)
{
	unsigned long num = 0;
	char *p = dest, *b;

	b = (char *)buf;
	while(num = ul / 10)
	{
		*b++ = num_tab[ul - MUL10(num)];
		ul = num;
	}

	*b++ = num_tab[ul];
	*b = EOS;

	dest += strlen((char *)buf);
	*dest-- = EOS;
	b = (char *)buf;
	while(*b)
		*dest-- = *b++;

	return p;
}

wchar_t *_ultowc10(unsigned long ul, wchar_t *dest)
{
	unsigned long num = 0;
	wchar_t *p = dest, *b;

	b = buf;
	while(num = ul / 10)
	{
		*b++ = wnum_tab[ul - MUL10(num)];
		ul = num;
	}

	*b++ = wnum_tab[ul];
	*b = WEOS;

	dest += wcslen(buf);
	*dest-- = WEOS;
	b = buf;
	while(*b)
		*dest-- = *b++;

	return p;
}

char *_ulltoa10(unsigned long long ull, char *dest)
{
	unsigned long long num = 0;
	char *p = dest, *b;

	b = (char *)buf;
	while(num = ull / 10)
	{
		*b++ = num_tab[ull - MUL10(num)];
		ull = num;
	}

	*b++ = num_tab[ull];
	*b = EOS;

	dest += strlen((char *)buf);
	*dest-- = EOS;
	b = (char *)buf;
	while(*b)
		*dest-- = *b++;

	return p;
}

wchar_t *_ulltowc10(unsigned long long ull, wchar_t *dest)
{
	unsigned long long num = 0;
	wchar_t *p = dest, *b;

	b = buf;
	while(num = ull / 10)
	{
		*b++ = wnum_tab[ull - MUL10(num)];
		ull = num;
	}

	*b++ = wnum_tab[ull];
	*b = WEOS;

	dest += wcslen(buf);
	*dest-- = WEOS;
	b = buf;
	while(*b)
		*dest-- = *b++;

	return p;
}
