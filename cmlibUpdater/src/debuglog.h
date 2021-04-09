/*
 * debuglog.h
 * 2011/11/02
 * Created by Y.K
 */

#ifndef _DEBUGLOG_H_
#define _DEBUGLOG_H_

#include <pspkernel.h>
#include <pspsysmem.h>
#include <stdio.h>
#include <string.h>

#if defined(DEBUG)

// Thanks to hiroi01
#define PSP_FIRMWARE_REVERSE(f) ( (((f >> 24) & 0xF) << 8) | (((f >> 16) & 0xF) << 4) | ((f >> 8) & 0xF) )

static char DBG_LOG_FILE[] = "ms0:/cmlibUpdate.log";
static SceUID dbg_fd;
static char dbg_buf[1024];

// mainŠÖ”“™ˆê”ÔÅ‰‚ÉŒÄ‚Ño‚·
#define DBG_INIT(...) do {\
	dbg_fd = sceIoOpen( DBG_LOG_FILE, PSP_O_CREAT | PSP_O_WRONLY | PSP_O_TRUNC, 0777 ); \
	if( dbg_fd < 0 ) { \
		DBG_LOG_FILE[0] = 'e'; DBG_LOG_FILE[1] = 'f'; \
		dbg_fd = sceIoOpen( DBG_LOG_FILE, PSP_O_CREAT | PSP_O_WRONLY | PSP_O_TRUNC, 0777 ); \
	} \
	int dbg_devkit = sceKernelDevkitVersion(); \
	sprintf( dbg_buf, "Log file : %s\r\nFW Version : %X [0x%08X]\r\n", \
		DBG_LOG_FILE, PSP_FIRMWARE_REVERSE(dbg_devkit), (u32)dbg_devkit ); \
	sceIoWrite( dbg_fd, dbg_buf, strlen(dbg_buf) ); \
	sceIoClose( dbg_fd ); \
} while(0);\

// ƒƒO‘‚«‚İŠÖ” printfŠÖ”‚Æ“¯‚¶ˆµ‚¢‚ÅOK‚Å‚·
#define DBG_LOG(...) do {\
	dbg_fd = sceIoOpen( DBG_LOG_FILE, PSP_O_CREAT | PSP_O_WRONLY | PSP_O_APPEND, 0777 ); \
	sprintf( dbg_buf, "FILE:%s, \tLINE:%03d  \t", __FILE__, __LINE__ ); \
	sprintf( dbg_buf + strlen(dbg_buf), __VA_ARGS__ ); \
	strcat( dbg_buf, "\r\n" ); \
	sceIoWrite( dbg_fd, dbg_buf, strlen(dbg_buf) ); \
	sceIoClose( dbg_fd ); \
} while(0);\

#else
#define DBG_INIT(...)
#define DBG_LOG(...)
#endif

#endif // _DEBUGLOG_H_
