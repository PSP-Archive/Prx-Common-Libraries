/**
*	cmliblog.c
*	2011/07/06
*	estuibal
*********************************/

#include <pspkernel.h>
#include <psprtc.h>
#include <pspsysmem_kernel.h>

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#include "_stdlib.h"
#include "cmliblog.h"

// #define _DEBUG_

#ifdef	_DEBUG_
#define LogOutPut(text)		_logOutPut(text)
#else
#define LogOutPut(text)
#endif

#define EOS					'\0'
#define MODEL_PSP_GO		4
#define MUL100(x)			( ((x) << 6) + ((x) << 5) + ((x) << 2) )
#define FALSE_HANDLE(h)		( ((u32)(h)) ^ HANDLE_MASK )

#define OPTLIST_SIZE	64


PSP_MODULE_INFO( "cmliblog", PSP_MODULE_KERNEL, 0, 4 );


typedef struct _tag_OPTLIST_ {
	// char timefmt[32];	// 時刻フォーマット(sprintf第二引数)
	int break_char;		// テキスト改行文字指定 (CRLF/CR/LF)
	char logname[256];	// ログファイルパス
	u32 flags;			// タイムスタンプ、ログ記録毎のオープンクローズオプション
	SceUID fd;
	bool f;
} optList;

static optList opt_list[OPTLIST_SIZE];


//
//	Private function.
//

inline void _logOutPut(char *text)
{
	SceUID fd = sceIoOpen( "ms0:/debugLog.txt", PSP_O_WRONLY | PSP_O_CREAT | PSP_O_APPEND, 0777 );
	if( fd < 0 ) {
		return;
	}
	
	sceIoWrite( fd, text, strlen(text) );
	sceIoWrite( fd, "\r\n", 2 );
	
	sceIoClose( fd );
}

static int WriteLine(HLOG hLog, char *text)
{
	optList *optl = (optList *)TRUE_HANDLE(hLog);
	if( optl == NULL || optl->f == false || text == NULL || text[0] == EOS ) {
		return(-1);
	}
	
	if( optl->fd < 0 ) {
		int flags;
		if( optl->flags & LIBLOG_STARTCLEAR ) {
			flags = PSP_O_WRONLY | PSP_O_CREAT | PSP_O_TRUNC;
			optl->flags &= ~LIBLOG_STARTCLEAR;
		} else {
			flags = PSP_O_WRONLY | PSP_O_CREAT | PSP_O_APPEND;
		}
		if( (optl->fd = sceIoOpen( optl->logname, flags, 0777 )) < 0 ) {
			return(-1);
		}
	}

	if( optl->flags & LIBLOG_TIMESTAMP ) {
		char strtime[32];
		pspTime time;
		sceRtcGetCurrentClockLocalTime( &time );
		int nlen = sprintf( strtime,
			/*(optl->flags & LIBLOG_TIMEFMT)? optl->timefmt :*/ "[%02i:%02i:%02i] ",
			time.hour, time.minutes, time.seconds );
		sceIoWrite( optl->fd, strtime, nlen );
	}
	
	sceIoWrite( optl->fd, text, strlen(text) );
	
	switch( optl->break_char )
	{
	case LIBLOG_BC_CR:
		sceIoWrite( optl->fd, "\r", 1 );
		break;
	case LIBLOG_BC_LF:
		sceIoWrite( optl->fd, "\n", 1 );
		break;
	case LIBLOG_BC_CRLF:
	default:
		sceIoWrite( optl->fd, "\r\n", 2 );
		break;
	}

	if( optl->flags & LIBLOG_OPENCLOSE ) {
		sceIoClose( optl->fd );
		optl->fd = -1;
	}
	return 0;
}

char *GetSizeStr(u64 size, char *dest)
{
	u64 lo = 0;
	char *p = dest;
	
	if( 0x100000 < size )
	{
		lo = MUL100(size & 0x0FFFFF) >> 20;
		size = size >> 20;
		_ulltoa10(size, dest);
		while(*p) {
			p++;
		}
		*p++ = '.';
		_ulltoa10(lo, p);
		strcat(dest, " MB");
	}
	else if( 1024 < size )
	{
		lo = MUL100(size & 0x3FF) >> 10;
		size = size >> 10;
		_ulltoa10(size, dest);
		while(*p) {
			p++;
		}
		*p++ = '.';
		_ulltoa10(lo, p);
		strcat(dest, " KB");
	}
	else
	{
		_ulltoa10(size, dest);
		strcat(dest, " B");
	}

	return dest;
}

//
//	Public function.
//

HLOG liblogCreateLog(liblogOpt *pOpt)
{
	if( pOpt == NULL ) {
		return 0;
	}
	
	LogOutPut( "Start CreateLog function." );
	
	int n;
	for( n = 0; n < OPTLIST_SIZE; n++ ) {
		if( opt_list[n].f == false ) {
			break;
		}
	}
	if( n >= OPTLIST_SIZE ) {
		return 0;
	}
	
	memcpy( &(opt_list[n]), pOpt, sizeof(liblogOpt));
	opt_list[n].flags 	&= LIBLOG_ALLFLAG;
	opt_list[n].fd		= -1;
	opt_list[n].f		= true;
	
	if( MODEL_PSP_GO == sceKernelGetModel() ) {
		opt_list[n].logname[0] = 'e';
		opt_list[n].logname[1] = 'f';
	}
	
	LogOutPut( "End CreateLog function." );
	
	return (HLOG)FALSE_HANDLE(&(opt_list[n]));
}

int liblogDestroyLog(HLOG hLog)
{
	if( hLog == 0 || hLog == HANDLE_MASK ) {
		return(-1);
	}
	optList *optl = (optList *)TRUE_HANDLE(hLog);
	optl->f = false;
	if( 0 <= optl->fd ) {
		sceIoClose( optl->fd );
	}
	return 0;
}

int liblogClear(HLOG hLog)
{
	optList *optl = ((optList *)TRUE_HANDLE(hLog));
	if( 0 <= optl->fd ) {
		sceIoClose( optl->fd );
	}
	
	if( (optl->fd = sceIoOpen(optl->logname, PSP_O_WRONLY | PSP_O_TRUNC, 0777)) < 0 ) {
		optl->f = false;
		return(-1);
	}
	
	if(	optl->flags & LIBLOG_OPENCLOSE ) {
		sceIoClose( optl->fd );
	}
	return 0;
}

void liblogSetLogName(HLOG hLog, char *new_name)
{
	if( new_name != NULL && new_name != EOS ) {
		optList *optl = (optList *)TRUE_HANDLE(hLog);
		if( MODEL_PSP_GO == sceKernelGetModel() ) {
			new_name[0] = 'e';
			new_name[1] = 'f';
		}
		strcpy( optl->logname, new_name );
		if( optl->fd >= 0 ) {
			sceIoClose( optl->fd );
		}
	}
}

int liblogGetLogName(HLOG hLog, char *buf, size_t bufsize)
{
	int len;
	if( bufsize > (len = strlen(((optList *)TRUE_HANDLE(hLog))->logname)) ) {
		strcpy( buf, ((optList *)TRUE_HANDLE(hLog))->logname );
	} else {
		return len;
	}
	return 0;
}

int liblogPrint(HLOG hLog, char *text)
{
	if( text != NULL || text[0] != EOS ) {
		return WriteLine(hLog, text);
	}
	return(-1);
}

int liblogPrintf(HLOG hLog, char *textfmt, ...)
{
	char buf[256];
	va_list al;
	va_start(al, textfmt);
	int nlen = vsnprintf( buf, 256, textfmt, al );
	va_end( al );
	
	if( 0 < nlen ) {
		return WriteLine( hLog, buf );
	}
	return(-1);
}

int liblogPrintBool(HLOG hLog, char *text, bool b)
{
	char buf[260] = "";
	if( text != NULL && text[0] != EOS ) {
		strncpy( buf, text, 255 );
	}
	strcat( buf, (b == false)? "False" : "True" );
	return WriteLine( hLog, buf );
}

int liblogPrintInt(HLOG hLog, char *text, int num)
{
	char sznum[32];
	
	_ltoa10( (long)num, sznum );
	if( text != NULL || text[0] != EOS ) {
		char buf[288] = "";
		strncpy( buf, text, 255 );
		strcat( buf, sznum );
		return WriteLine( hLog, buf );
	} else {
		return WriteLine( hLog, sznum );
	}
	return 0;
}

int liblogPrintUint(HLOG hLog, char *text, unsigned int num)
{
	char sznum[32];
	
	_ultoa10( (unsigned long)num, sznum );
	if( text != NULL || text[0] != EOS ) {
		char buf[288] = "";
		strncpy( buf, text, 255 );
		strcat( buf, sznum );
		return WriteLine( hLog, buf );
	} else {
		return WriteLine( hLog, sznum );
	}
	return 0;
}

int liblogPrintU64(HLOG hLog, char *text, u64 num)
{
	char sznum[32];
	
	_ulltoa10( num, sznum );
	if( text != NULL || text[0] != EOS ) {
		char buf[288] = "";
		strncpy( buf, text, 255 );
		strcat( buf, sznum );
		return WriteLine( hLog, buf );
	} else {
		return WriteLine( hLog, sznum );
	}
	return 0;
}

int liblogPrintHex(HLOG hLog, char *text, u32 hex)
{
	char sznum[32];
	
	_ultoahex( hex, sznum );
	if( text != NULL || text[0] != EOS ) {
		char buf[288] = "";
		strncpy( buf, text, 255 );
		strcat( buf, sznum );
		return WriteLine( hLog, buf );
	} else {
		return WriteLine( hLog, sznum );
	}
	return 0;
}

int liblogPrintHex64(HLOG hLog, char *text, u64 hex)
{
	char sznum[32];
	
	_ulltoahex( hex, sznum );
	if( text != NULL || text[0] != EOS ) {
		char buf[288] = "";
		strncpy( buf, text, 255 );
		strcat( buf, sznum );
		return WriteLine( hLog, buf );
	} else {
		return WriteLine( hLog, sznum );
	}
	return 0;
}

int liblogPrintPspModel(HLOG hLog)
{
	static const char fat[] = "Fat", slim2[] = "Slim2000", slim3[] = "Slim3000",
						go[] = "Go", unknown[] = "Unknown model";
	const char *p = NULL;
	
	int model = sceKernelGetModel();
	switch( model )
	{
	case 0:		p = fat;		break;
	case 1:		p = slim2;		break;
	case 2:
	case 3:
	case 6:
	case 8:
	case 9:		p = slim3;		break;
	case 4:		p = go;			break;
	default:	p = unknown;	break;
	}
	
	char buf[64];
	if( sprintf( buf, "PSP model = %s [%02dg]", p, (p == unknown)? 99: model + 1) > 0 ) {
		return WriteLine( hLog, buf );
	}
	return(-1);
}

int liblogPrintMaxFreeMem(HLOG hLog)
{
	char buf[64];
	strcpy( buf, "Max free memory size = " );
	GetSizeStr( (u64)sceKernelMaxFreeMemSize(), buf + strlen(buf) );
	return WriteLine( hLog, buf );
}

//
//	Entry function.
//

int module_start(SceSize args, void *argp)
{
	int n;
	for( n = 0; n < OPTLIST_SIZE; n++) {
		opt_list[n].f = false;
	}
	return 0;
}

int module_stop(SceSize args, void *argp)
{
	return 0;
}
