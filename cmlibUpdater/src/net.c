/*
 * Prx Common Libraries - cmlibUpdater
 * net.c
 * 2011/10/24
 * Created by Y.K
 */

#include <pspkernel.h>
#include <pspdebug.h>
#include <pspctrl.h>
#include <psputility.h>
#include <psputility_netmodules.h>
#include <pspgu.h>
#include <pspgum.h>
#include <pspdisplay.h>

#include <string.h>
#include <unistd.h>

#include <pspnet.h>
#include <pspnet_inet.h>
#include <pspnet_apctl.h>
#include <pspnet_resolver.h>

#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <errno.h>

#include "net.h"
#include "main.h"


int net_loadinit_module( void )
{
	if( net_load_module() ) return -1;
	net_init();
	return 0;
}

int net_load_module( void )
{
	int nret = 0;
	nret = sceUtilityLoadNetModule( PSP_NET_MODULE_COMMON );
	if( nret != 0 ) {
		printf( "Error, could not load inet module %x\n", nret );
		return -1;
	}
	nret = sceUtilityLoadNetModule( PSP_NET_MODULE_INET );
	if( nret != 0 ) {
		printf( "Error, could not load inet module %x\n", nret );
		return -1;
	}
	return 0;
}

void net_init( void )
{
	sceNetInit( 0x20000, 0x2A, 0x1000, 0x2A, 0x1000 );
	sceNetInetInit();
	sceNetApctlInit( 0x8000, 48 );
}

void net_term( void )
{
	static int flag;
	if( !flag ) {
		sceNetApctlTerm();
		sceNetInetTerm();
		sceNetTerm();
		flag = 1;
	}
}

/*
// Connect to an access point
int net_connect_to_apctl( int config )
{
	int err;
	int stateLast = -1;

	// Connect using the first profile
	if( err = sceNetApctlConnect( config ) ) {
		printf( MODULE_NAME ": sceNetApctlConnect returns %08X\n", err );
		return -1;
	}

	while( 1 ) {
		int state;
		if( err = sceNetApctlGetState( &state ) ) {
			printf( MODULE_NAME ": sceNetApctlGetState returns $%x\n", err );
			break;
		}
		if( state > stateLast ) {
			printf( "  connection state %d of 4\n", state );
			stateLast = state;
		}
		if( state == 4 )
			break;  // connected with static IP
		
		// wait a little before polling again
		sceKernelDelayThread( 50000 ); // 50ms
	}

	if( err != 0 )
		return -1;

	return 0;
}
*/

int net_disconnect_to_apctl( void )
{
	return sceNetApctlDisconnect();
}

int net_is_connected( void )
{
	int state;
	if( sceNetApctlGetState( &state ) < 0 ) {
		return -1;
	}

	return state == PSP_NET_APCTL_STATE_DISCONNECTED ? 0 : 1;
}

void net_not_connected( void )
{
	pspDebugScreenInit();
	pspDebugScreenSetXY( 19, 16 );
	printf( "Not connected an access point.\n" ); // 30
	pspDebugScreenSetXY( 10, 17 );
	printf( "Press X to exit, or press O to reconnect network.\n" ); // 49

	SceCtrlData pad;
	while( 1 ) {
		sceCtrlReadBufferPositive( &pad, 1 );
		if( pad.Buttons & PSP_CTRL_CROSS ) {
			exit_eboot();
			sceKernelSleepThread();
			break;
		}
		if( pad.Buttons & PSP_CTRL_CIRCLE ) {
			break;
		}
		sceKernelDelayThread( CTRL_DELAY );
	}
}

void net_reconnect( void )
{
	if( net_is_connected() == 0 ) {
		while( net_dialog() ) {
			net_not_connected();
		}
	}
	pspDebugScreenInit();
}

static int resolver_n2a( const char *name, struct in_addr *addr )
{
	int result = -1;
	int rid = -1;
	char buf[1024];

	if( sceNetResolverCreate( &rid, buf, sizeof(buf) ) >= 0 ) {
		if( sceNetResolverStartNtoA( rid, name, addr, 3, 3 ) >= 0 )
			result = 0;
		sceNetResolverDelete( rid );
	}
	return result;
}

int net_connect_to_server( const char *server, unsigned short uport )
{
	int sock;
	struct in_addr addr;
	struct sockaddr_in saddr;

	if( (sock = socket( PF_INET, SOCK_STREAM, 0 )) < 0 ) {
		return -1;
	}

	memset( &saddr, 0, sizeof(struct sockaddr_in) );
	saddr.sin_family 		= PF_INET;
	saddr.sin_port 			= htons( uport );

	if( resolver_n2a( server, &addr ) == 0 ) {
		saddr.sin_addr = addr;
	} else {
		u32 uladdr = inet_addr( server );
		saddr.sin_addr.s_addr = htonl( uladdr );
	}

	if( connect( sock, (struct sockaddr *)&saddr, sizeof(saddr) ) < 0 ) {
		close( sock );
		return -1;
	}
	return sock;
}

/*
int net_connect_to_server( char *server, uint16_t uport )
{
	int sock;
	struct sockaddr_in saddr;
	struct hostent *lpHost;
	unsigned long ul_addr;

	if( (sock = socket( PF_INET, SOCK_STREAM, 0 )) < 0 )
		return -1;

	if( (ul_addr = inet_addr( server )) == 0xFFFFFFFF )
		lpHost = gethostbyname( server );
	else
		lpHost = gethostbyaddr( (char *)&ul_addr, 4, PF_INET );

	memset( &saddr, 0, sizeof(struct sockaddr_in) );
	if( lpHost != NULL ) {
		saddr.sin_family 		= lpHost->h_addrtype;
		saddr.sin_port 			= htons( uport );
		saddr.sin_addr.s_addr 	= htonl( *(unsigned long *)lpHost->h_addr );
	}
	else { // No host name
		saddr.sin_family 		= PF_INET;
		saddr.sin_port 			= htons( uport );
		saddr.sin_addr.s_addr 	= htonl( ul_addr );
	}

	if( connect( sock, (struct sockaddr *)&saddr, sizeof(saddr) ) < 0 ) {
		close( sock );
		return -1;
	}
	return sock;
}
*/

int net_send_msg( int s, char *msg )
{
	if( msg == NULL || msg[0] == 0 )
		return 1;

	int size = (int)strlen( msg );
	while( size > 0 ) {
		int nsend = write( s, msg, size );
		if( nsend < 0) return -1;
		msg += nsend;
		size -= nsend;
	}
	return 0;
}

int net_recv_const_data( int s, void *buf, int size )
{
	char *p = (char *)buf;
	while( size > 0 ) {
		int nread = read( s, p, size );
		if( nread <= 0 ) return -1;
		p += nread;
		size -= nread;
	}
	return 0;
}

int net_recv_data( int s, void *buf, int size, int *p_read )
{
	char *p = (char *)buf;
	while( size > 0 ) {
		int nread = read( s, p, size );
		if( nread == 0 ) break;
		if( nread < 0 ) {
			*p_read = 0;
			return -1;
		}
		p += nread;
		size -= nread;
	}
	*p_read = (int)( p - (char *)buf );
	return 0;
}


//*******************************************//

//#define BUF_WIDTH (512)
//#define SCR_WIDTH (480)
//#define SCR_HEIGHT (272)

#define RGB32(r, g, b) (0xff000000 | ((b & 0xff) << 16) | ((g & 0xff) << 8) | (r & 0xff))

static unsigned int __attribute__((aligned(16))) list[262144];

static void setupGu()
{
	sceGuInit();
	sceGuStart( GU_DIRECT, list );
	sceGuDrawBuffer( GU_PSM_8888, 0, BUF_WIDTH );
	sceGuDispBuffer( SCR_WIDTH, SCR_HEIGHT, (void *)0x88000, BUF_WIDTH );
	sceGuDepthBuffer( (void *)0x110000, BUF_WIDTH );
	sceGuOffset( 0, 0 );
	sceGuScissor( 0, 0, SCR_WIDTH, SCR_HEIGHT );
	sceGuEnable( GU_SCISSOR_TEST );
	sceGuBlendFunc( GU_ADD, GU_SRC_ALPHA, GU_ONE_MINUS_SRC_ALPHA, 0, 0 );
	sceGuEnable( GU_BLEND );
	sceGuClearColor( 0 );
	sceGuClearDepth( 0 );
	sceGuClearStencil( 0 );
	sceGuFinish();
	sceGuSync( 0, 0 );
	sceDisplayWaitVblankStart();
	sceGuDisplay( GU_TRUE );
}

int net_dialog( void )
{
	int done = 0;

	struct pspUtilityNetconfAdhoc adhocparam = { };
	pspUtilityNetconfData data = { };

	data.base.size = sizeof data;
	data.base.language = PSP_SYSTEMPARAM_LANGUAGE_JAPANESE;
	data.base.buttonSwap = PSP_UTILITY_ACCEPT_CIRCLE;
	data.base.graphicsThread = 17;
	data.base.accessThread = 19;
	data.base.fontThread = 18;
	data.base.soundThread = 16;
	data.action = PSP_NETCONF_ACTION_CONNECTAP;
	data.adhocparam = &adhocparam;

	sceUtilityNetconfInitStart( &data );

	setupGu();

	do
	{
		sceGuStart( GU_DIRECT, list );
		sceGuClearColor( RGB32( 64, 64, 64 ) );
		sceGuClearDepth( 0 );
		sceGuClear( GU_COLOR_BUFFER_BIT | GU_DEPTH_BUFFER_BIT );

		sceGuFinish();
		sceGuSync( 0, 0 );

		switch( sceUtilityNetconfGetStatus() )
		{
		case PSP_UTILITY_DIALOG_NONE:
			break;

		case PSP_UTILITY_DIALOG_VISIBLE:
			sceUtilityNetconfUpdate( 1 );
			break;

		case PSP_UTILITY_DIALOG_QUIT:
			sceUtilityNetconfShutdownStart();
			break;

		case PSP_UTILITY_DIALOG_FINISHED:
			done = 1;
			break;

		default:
			break;
		}

		sceDisplayWaitVblankStart();
		sceGuSwapBuffers();

	} while( !done );

	sceGuSwapBuffers();
	sceGuStart( GU_DIRECT, list );
	sceGuClearColor( 0 );
	sceGuClearDepth( 0 );
	sceGuClear( GU_COLOR_BUFFER_BIT | GU_DEPTH_BUFFER_BIT );
	sceGuSwapBuffers();

	sceGuFinish();
	sceGuSync( 0, 0 );

	return data.base.result;
}
