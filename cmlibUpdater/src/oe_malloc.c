/*
 * Prx Common Libraries - cmlibUpdater
 * oe_malloc.c
 * 2011/10/12
 * Created by Y.K
 */

#include <pspkernel.h>
#include <pspsdk.h>
#include <pspsysmem_kernel.h>
#include <string.h>

#include "oe_malloc.h"

void *oe_malloc( int size )
{
	SceUID memid = sceKernelAllocPartitionMemory( 2, "", 0, size + sizeof(SceUID), NULL );
	u32 addr = (u32)sceKernelGetBlockHeadAddr( memid );
	*(SceUID *)addr = memid;
	return (void *)(addr + sizeof(SceUID));
}

void *oe_realloc( void *ptr, int resize )
{
	SceUID memid = sceKernelAllocPartitionMemory( 2, "", 0, resize + sizeof(SceUID), NULL );
	u32 addr = (u32)sceKernelGetBlockHeadAddr( memid );
	*(SceUID *)addr = memid;
	addr += sizeof(SceUID);

	if( ptr != NULL ) {
		memcpy( (void *)addr, ptr, resize );
		oe_free( ptr );
	}

	return (void *)addr;
}

void oe_free( void *ptr )
{
	SceUID memid = *(SceUID *)((u32)ptr - sizeof(SceUID));
	sceKernelFreePartitionMemory( memid );
}

char *oe_strmalloc( char *str )
{
	if( str == NULL || *str == '\0' )
		return NULL;

	char *buf = (char *)oe_malloc( strlen(str) + 1 );
	if( buf != NULL )
		strcpy( buf, str );
	return buf;
}
