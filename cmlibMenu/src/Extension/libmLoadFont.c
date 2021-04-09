#include "common.h"
#include "memory.h"
#include <pspsysevent.h>
#include <kubridge.h>

char *font_cg = NULL, *font_hankaku_kana = NULL, *font_sjis = NULL, *font_icon = NULL;
char no_font[] = {0x7F, 0x63, 0x55, 0x49, 0x49, 0x55, 0x63, 0x7F};
int font_size[4];
int semaid;
u8 font_md5[4][16];
SceUID states_fd;

void start_FontThread();

int libmLoadFont(int flag){
    SceUID fd;
    SceSize size, readsize;
    SceKernelUtilsMd5Context ctx;
    char *font_buf;
    char path[64] = "ms0:/seplugins/lib/font/";
    char *font_bin[] = {"cg.bin", "hankaku_kana.bin", "sjis.bin", "icon.bin"};
    int k1;
    u32 *font_addr[4] = {(u32*)&font_cg, (u32*)&font_hankaku_kana, (u32*)&font_sjis, (u32*)&font_icon};
    
	if(!(*font_addr[0] || *font_addr[1] || *font_addr[2] || *font_addr[3]))
	{
		start_FontThread();
	}
	
    if(*font_addr[flag - 1]){
        return -1;
    }
    
    k1 = pspSdkSetK1(0);
    
    // make path
    strcat(path, font_bin[flag - 1]);
    
    // file open
    fd = sceIoOpen(path, PSP_O_RDONLY, 0777);
    if(fd < 0){
        path[0] = 'e';
        path[1] = 'f';
        fd = sceIoOpen(path, PSP_O_RDONLY, 0777);
        if(fd < 0){
            pspSdkSetK1(k1);
            return fd;
        }
    }
    
    // get file size
    size = sceIoLseek(fd, 0, SEEK_END);
    if(size <= 0){
        sceIoClose(fd);
        pspSdkSetK1(k1);
        return -2;
    }
    
    // malloc
    //mem_set_alloc_mode(MEM_AUTO);
    font_buf = mem_alloc(size);
    if(font_buf == NULL){
        sceIoClose(fd);
        pspSdkSetK1(k1);
        return -3;
    }
    
    // read font
    sceIoLseek(fd, 0, SEEK_SET);
    readsize = sceIoRead(fd, font_buf, size);
    sceIoClose(fd);
    if(readsize != size){
        mem_free(font_buf);
        pspSdkSetK1(k1);
        return -4;
    }
    
    *font_addr[flag - 1] = (u32)font_buf;
    
    //check md5
    font_size[flag - 1] = size;
    sceKernelUtilsMd5BlockInit(&ctx);
    sceKernelUtilsMd5BlockUpdate(&ctx, (u8 *)*font_addr[flag - 1] , font_size[flag - 1]);
    sceKernelUtilsMd5BlockResult(&ctx, font_md5[flag - 1]);
    
    pspSdkSetK1(k1);
    
    return 0;
}

//Thanks neur0n
int libmCheckFont(int flag){
    u8 digest[16];
    SceKernelUtilsMd5Context ctx;
    u32 *font_addr[4] = {(u32*)&font_cg, (u32*)&font_hankaku_kana, (u32*)&font_sjis, (u32*)&font_icon};
    
    if(!(*font_addr[flag - 1])){
        return -1;
    }
    
    //check md5
    sceKernelUtilsMd5BlockInit(&ctx);
    sceKernelUtilsMd5BlockUpdate(&ctx, (u8 *)*font_addr[flag - 1] , font_size[flag - 1]);
    sceKernelUtilsMd5BlockResult(&ctx, digest);
    
    if ( memcmp( font_md5[flag - 1] , digest , 16) ) {
        *font_addr[flag - 1] = 0;
        libmLoadFont(flag);
        return 1;
    }
    return 0;
}


int SysEventHandler(int ev_id, char *ev_name, void *param, int *result)
{
	// Resume Complete
	if(ev_id == 0x400000)
	{
		sceKernelSignalSema(semaid, 1);
	}

	return 0;
}

int font_thread(SceSize args, void *argp)
{
	int i;
	PspSysEventHandler events =
	{
		sizeof(PspSysEventHandler),
		"SysEventHandler",
		0x00FFFF00,
		SysEventHandler,
	};
	
	sceKernelRegisterSysEventHandler(&events);
	
	semaid = sceKernelCreateSema("sema", 0, 0, 1, 0);
	
	while(1)
	{
		sceKernelWaitSema(semaid,1,0);
		sceKernelDelayThread(1*1000*1000);
		for(i=1; i<5; i++)
		{
			libmCheckFont(i);
		}
		sceKernelSignalSema(semaid, 0);
	}

	return 0;
}

void start_FontThread()
{
	int mode = (sceKernelInitKeyConfig() >> 8) - 1; // 0 = VSH, 1 = GAME, 2 = POPS
	int model = kuKernelGetModel();                 // 0 = 1000, 1 = 2000, 2,3,5,6,7,8 = 3000, 4 = go

	if(mode && model)
	{
		int thid = sceKernelCreateThread("FontThread", font_thread, 32, 0x2000, 0, NULL);
		if(thid >= 0)sceKernelStartThread(thid, 0, NULL);
	}
	return;
}
