#include <systemctrl.h>
#include "common.h"
#include "memory.h"

//Thanks libhook_test_2 by hiroi01
//Thanks RedirectFunction  by hiroi01

#define NOP 0x00000000
#define MAKE_JUMP(a, f) _sw(0x08000000 | (((u32)(f) & 0x0ffffffc) >> 2), a); 

/*------------------------------------------------------------*/

int (*sceDisplaySetFrameBuf_Real)(void *topaddr, int bufferwidth, int pixelformat, int sync);
int (*sceDisplaySetFrameBuf_Handler)(void *topaddr, int bufferwidth, int pixelformat, int sync) = NULL;

/*------------------------------------------------------------*/

int sceDisplaySetFrameBuf_Patched(void *topaddr, int bufferwidth, int pixelformat, int sync)
{
	if( sceDisplaySetFrameBuf_Handler ){
		sceDisplaySetFrameBuf_Handler(topaddr, bufferwidth, pixelformat, sync);
	}
	return sceDisplaySetFrameBuf_Real(topaddr, bufferwidth, pixelformat, sync);
}

void ClearCaches(void)
{
	sceKernelDcacheWritebackAll();
	sceKernelIcacheClearAll();
}

void *RedirectFunction(void *addr, void *func)
{
	u32 orgaddr = (u32)addr;
	if( orgaddr != 0 )
	{
		int before_mode =  mem_get_alloc_mode();
		mem_set_alloc_mode(1);
		u32 buff = (u32)mem_alloc( 4 * 4 );
		mem_set_alloc_mode(before_mode);
		if( buff == 0 ) return 0;
		
		memcpy( (void *)buff, (void *)orgaddr, 4 * 2 );
		MAKE_JUMP( (buff + 4 * 2) , (orgaddr + 4 * 2) );
		_sw( NOP, buff + 4 * 3 );
		
		MAKE_JUMP( (u32)(orgaddr), (u32)(func) );
		_sw( NOP, orgaddr + 4 * 1 );
		
		orgaddr = (u32)buff;
		
		ClearCaches();
	}
	
	return (void *)orgaddr;
}

void init()
{
	u32 addr = FindProc("sceDisplay_Service", "sceDisplay", 0x289D82FE);
	sceDisplaySetFrameBuf_Real = RedirectFunction((void *)addr, sceDisplaySetFrameBuf_Patched);
}

void* libmHookDisplayHandler(int (*func)(void *topaddr, int bufferwidth, int pixelformat, int sync))
{
	if(sceDisplaySetFrameBuf_Handler == NULL)
	{
		init();
	}

	void *previous = sceDisplaySetFrameBuf_Handler;
	sceDisplaySetFrameBuf_Handler = func;
	return previous;
}

