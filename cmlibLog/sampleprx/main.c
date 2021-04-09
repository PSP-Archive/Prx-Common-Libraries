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
//		複数のPRXモジュールをロードする
//		prxLibList pll[] : prxLibList構造体のアドレスを指定
//		int c 			: pllの数
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
	// cmLibLog.prxをロード
	prxLibList pll = { "cmliblog", "ms0:/seplugins/cmliblog.prx" };
	LoadModules( &pll, 1 );
	
	// ログのオプションを設定
	liblogOpt opt1, opt2;
	memset( &opt1, 0, sizeof(liblogOpt) ); // 一応ゼロクリア推奨
	memset( &opt2, 0, sizeof(liblogOpt) );
	opt1.flags		= LIBLOG_TIMESTAMP | LIBLOG_OPENCLOSE; // ログ時間の記録 & ログ記録毎にログファイルを開き閉じる
	opt2.flags		= LIBLOG_TIMESTAMP | LIBLOG_STARTCLEAR; // 初回ログ記録時にログをクリアする
	opt1.break_char	= LIBLOG_BC_CRLF; 	// 改行文字("\r\n")
	opt2.break_char	= LIBLOG_BC_CR;		// "\r"
	strcpy( opt1.logname, "ms0:/log1.txt" ); // ログのフルパスを指定
	strcpy( opt2.logname, "ms0:/log2.txt" );
	
	HLOG hLog1 = liblogCreateLog( &opt1 ); // ログのハンドルを生成
	HLOG hLog2 = liblogCreateLog( &opt2 ); // 以後このハンドル使用.引数のliblogOpt構造体は消してもよい
	if( hLog1 == 0 || hLog2 == 0 ) { // ログハンドルが0だとエラー
		return sceKernelExitDeleteThread( 0 );
	}
	
	// 実際に記録する
	liblogPrint( hLog1, "Hello,World!" ); // 直で出力(putsみたいな)
	liblogPrint( hLog2, "Hello,World for C." );
	
	liblogPrintf( hLog1, "%d - liblog%s[0x%X]", 12345, "Printf", hLog1 ); // printf関数の書式付き
	liblogPrintf( hLog2, "%d - liblog%s[0x%x]", 6789, "Printf", hLog2 );
	
	liblogPrintBool( hLog1, "Bool = ", false ); // Bool値の出力
	liblogPrintBool( hLog1, "Bool = ", true );
	
	liblogPrintInt( hLog2, "Int = ", 0x12345 ); // 符号付き32bit整数出力
	liblogPrintInt( hLog2, "Int = ", -654321 ); // マイナス記号も出力可
	liblogPrintUint( hLog2, "unsigned int = ", -123 ); // 符号無32bit整数出力
	liblogPrintU64( hLog1, "unsigned long long = ", 0xFFFFFFFFFFFFFFFF ); // 符号無64bit整数出力
	liblogPrintHex( hLog2, "unsigned long (hex) = ", 0xABCDEF ); // 32bit16進数出力
	liblogPrintHex64( hLog2, "unsigned long long = ", 0xABCDEFFFFF ); // 64bit16進数出力
	liblogPrintAddr( hLog2, "Addr = ", TRUE_HANDLE( hLog2 ) ); // ポインタ出力等(liblogPrintHexのマクロ)
	liblogPrintPspModel( hLog1 ); // PSPモデルの出力,モジュール番号も
	liblogPrintMaxFreeMem( hLog1 ); // 記録時のメモリ空き容量出力
	
	
	// ログハンドルの処理
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
