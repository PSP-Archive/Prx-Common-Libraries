/**
*	sample_prx
*	2011/07/06
*	estuibal
*************************/

#include <pspkernel.h>
#include <pspsdk.h>

#include <string.h>

#include "cmliblog.h"


PSP_MODULE_INFO( "sample_prx", 0x1000, 0, 1 );


typedef struct _tag_prxliblist {
	char *mod_name;
	char *prx_path;
} prxLibList;


int LoadStartModule( char *module )
{
	SceUID mod = sceKernelLoadModule( module, 0, NULL );
	if (mod < 0) {
		return mod;
	}
	
	return sceKernelStartModule( mod, strlen(module)+1, module, NULL, NULL );
}

// @LoadModules
//		������PRX���W���[�������[�h����
//		prxLibList pll[] : prxLibList�\���̂̃A�h���X���w��
//		int c 			: pll�̐�
// Thanks wn and SnyFbSx!
int LoadModules( prxLibList pll[], int c )
{
	while( 1 ) {
		if( sceKernelFindModuleByName( "sceKernelLibrary" ) != NULL ) {
			break;
		}
		sceKernelDelayThread( 1000 );
	}
	
	int n;
	for( n = 0; n < c; n++ ) {
		if( sceKernelFindModuleByName( pll[n].mod_name ) == NULL ) {
			LoadStartModule( pll[n].prx_path );
			if( sceKernelFindModuleByName( pll[n].mod_name ) == NULL ) {
				pll[n].prx_path[0] = 'e';
				pll[n].prx_path[1] = 'f';
				LoadStartModule( pll[n].prx_path );
			}
		}
	}
	
	return 0;
}

int main_thread( SceSize args, void *argp )
{
	// cmLibLog.prx�����[�h
	prxLibList pll = { "cmliblog", "ms0:/seplugins/cmliblog.prx" };
	LoadModules( &pll, 1 );
	
	// ���O�̃I�v�V������ݒ�
	liblogOpt opt1, opt2;
	memset( &opt1, 0, sizeof(liblogOpt) ); // �ꉞ�[���N���A����
	memset( &opt2, 0, sizeof(liblogOpt) );
	opt1.flags		= LIBLOG_TIMESTAMP | LIBLOG_OPENCLOSE; // ���O���Ԃ̋L�^ & ���O�L�^���Ƀ��O�t�@�C�����J������
	opt2.flags		= LIBLOG_TIMESTAMP | LIBLOG_STARTCLEAR; // ���񃍃O�L�^���Ƀ��O���N���A����
	opt1.break_char	= LIBLOG_BC_CRLF; 	// ���s����("\r\n")
	opt2.break_char	= LIBLOG_BC_CR;		// "\r"
	strcpy( opt1.logname, "ms0:/log1.txt" ); // ���O�̃t���p�X���w��
	strcpy( opt2.logname, "ms0:/log2.txt" );
	
	HLOG hLog1 = liblogCreateLog( &opt1 ); // ���O�̃n���h���𐶐�
	HLOG hLog2 = liblogCreateLog( &opt2 ); // �Ȍケ�̃n���h���g�p.������liblogOpt�\���̂͏����Ă��悢
	if( hLog1 == 0 || hLog2 == 0 ) { // ���O�n���h����0���ƃG���[
		return sceKernelExitDeleteThread( 0 );
	}
	
	// ���ۂɋL�^����
	liblogPrint( hLog1, "Hello,World!" ); // ���ŏo��(puts�݂�����)
	liblogPrint( hLog2, "Hello,World for C." );
	
	liblogPrintf( hLog1, "%d - liblog%s[0x%X]", 12345, "Printf", hLog1 ); // printf�֐��̏����t��
	liblogPrintf( hLog2, "%d - liblog%s[0x%x]", 6789, "Printf", hLog2 );
	
	liblogPrintBool( hLog1, "Bool = ", false ); // Bool�l�̏o��
	liblogPrintBool( hLog1, "Bool = ", true );
	
	liblogPrintInt( hLog2, "Int = ", 0x12345 ); // �����t��32bit�����o��
	liblogPrintInt( hLog2, "Int = ", -654321 ); // �}�C�i�X�L�����o�͉�
	liblogPrintUint( hLog2, "unsigned int = ", -123 ); // ������32bit�����o��
	liblogPrintU64( hLog1, "unsigned long long = ", 0xFFFFFFFFFFFFFFFF ); // ������64bit�����o��
	liblogPrintHex( hLog2, "unsigned long (hex) = ", 0xABCDEF ); // 32bit16�i���o��
	liblogPrintHex64( hLog2, "unsigned long long = ", 0xABCDEFFFFF ); // 64bit16�i���o��
	liblogPrintAddr( hLog2, "Addr = ", TRUE_HANDLE( hLog2 ) ); // �|�C���^�o�͓�(liblogPrintHex�̃}�N��)
	liblogPrintPspModel( hLog1 ); // PSP���f���̏o��,���W���[���ԍ���
	liblogPrintMaxFreeMem( hLog1 ); // �L�^���̃������󂫗e�ʏo��
	
	
	// ���O�n���h���̏���
	liblogDestroyLog( hLog1 );
	liblogDestroyLog( hLog2 );
	
	return sceKernelExitDeleteThread( 0 );
}

//
//	Entry function.
//

int module_start( SceSize args, void *argp )
{
	SceUID thid = sceKernelCreateThread( "sample_prx_main", main_thread, 32, 0x800, 0, NULL );
	if( thid >= 0 ) {
		sceKernelStartThread( thid, args, argp );
	}
	return 0;
}

int module_stop( SceSize args, void *argp )
{
	return 0;
}
