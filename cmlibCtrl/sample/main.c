//sample

#include <pspsdk.h>
#include <pspkernel.h>
#include <pspctrl.h>
#include <pspctrl_kernel.h>

#include <stdio.h>
#include <string.h>

#include "cmlibctrl.h"

/*-----------------------------------------------------------------*/

PSP_MODULE_INFO("cmlibCtrlsample", 0x1000, 1, 0);


/*------------------------------------------------------------------*/

// �v���g�^�C�v�錾
int main_thread(SceSize args, void *argp);
int module_start(SceSize args, void *argp);
int module_stop(SceSize args, void *argp);

/*------------------------------------------------------------------*/


bool status = false;

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  INIT METHOD		by SnyFbSx and estuibal
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
char cmLibCtrl_path[] = { "ms0:/seplugins/lib/cmlibctrl.prx"};
//------------------------------------------------------
int LoadStartModule(char *module)
{
	SceUID mod = sceKernelLoadModule(module, 0, NULL);

	if (mod < 0)
		return mod;

	return sceKernelStartModule(mod, strlen(module)+1, module, NULL, NULL);
}

int load_module( char *prx_title, char *prx_path )
{
	if( sceKernelFindModuleByName( prx_title ) == NULL ) {
		LoadStartModule( prx_path );
		if( sceKernelFindModuleByName( prx_title ) == NULL ) {
			prx_path[0] = 'e';
			prx_path[1] = 'f';
			LoadStartModule( prx_path );
		}
	}
	sceKernelDelayThread( 1000 );
	return 0;
}


int init(void)
{
	while(1)
	{
		if(sceKernelFindModuleByName("sceKernelLibrary")){
			// prxlibmenu loading Check
			load_module("cmlibCtrl",cmLibCtrl_path);

			break;
		}
		
		sceKernelDelayThread(1000);
	}
	return 0;
}

/*------------------------------------------------------------------*/


//���C��
int main_thread(SceSize args, void *argp)
{
	init();
	SceCtrlData pad;

	while (1)
	{
		sceKernelDelayThread(50000);
		sceCtrlPeekBufferPositive(&pad, 1);
		if(pad.Buttons & (PSP_CTRL_HOME + PSP_CTRL_TRIANGLE))
		//�����������@������
		{	
			libctrlMaskAllButtonOn(&status);
			//�A�h���X��n���Ȃ��Ɠ����Ȃ�
		}
		else if(pad.Buttons & (PSP_CTRL_HOME | PSP_CTRL_CIRCLE))
		//������������������
		{
			if(libctrlCountButtons((PSP_CTRL_HOME + PSP_CTRL_CIRCLE),3))
			//�����n���Ƃ��́u+�v���u|�v�łȂ��B
				libctrlMaskAllButtonOff(&status);
		}
		
	}
	return 0;
}


int module_start(SceSize args, void *argp)
{

	int thid = sceKernelCreateThread("cmlibCtrlsample", main_thread, 32, 0x800, 0, NULL);
	if(thid >= 0)sceKernelStartThread(thid, args, argp);

	return 0;
}


int module_stop(SceSize args, void *argp)
{
	return 0;
}
