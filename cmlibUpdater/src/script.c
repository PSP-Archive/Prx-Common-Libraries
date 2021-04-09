/*
 * Prx Common Libraries - cmlibUpdater
 * script.c
 * 2011/11/02
 * Created by Y.K
 */

#include <pspsdk.h>
#include <pspkernel.h>
#include <pspdebug.h>
#include <pspctrl.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"
#include "net.h"
#include "file.h"
#include "http.h"
#include "oe_malloc.h"
#include "script.h"

#include "debuglog.h"

static char script_path[260];
static char server_name[1024];
static unsigned short server_port;

//
// private
//
static int strcpy_tok( char *dest, const char *src, char tok )
{
	int len = 0;
	while( *src != '\0' && *src != tok ) {
		*dest++ = *src++;
		len++;
	}
	*dest = '\0';
	return len;
}

static inline void jumptok( char **str, char tok )
{
	while( **str == tok ) *str += 1;
}

static inline void jump_space( char **pos )
{
	while( *(*pos) == ' ' || *(*pos) == '\t' )
		*pos += 1;
}

static void wait_x_button(void)
{
	SceCtrlData pad;

	printf("Press X to exit...\n");

	while(1) {
		sceCtrlReadBufferPositive(&pad, 1);
		if( pad.Buttons & PSP_CTRL_CROSS )
			break;
		sceKernelDelayThread(CTRL_DELAY);
	}
	sceKernelDelayThread(CTRL_DEADZONE_DELAY);
}

static int parse_server_tag( char *line, char *server, unsigned short *uport )
{
	jump_space( &line );
	line += strcpy_tok( server, line, ':' ) + 1;
	DBG_LOG( "server = \"%s\"", server );

	*uport = (unsigned short) strtol( line, NULL, 10 );
	DBG_LOG( "uport = %d", *uport );

	return (*uport == 0)? -1 : 0;
}

static int get_server_info( void )
{
	char line[1024];
	int nret;
	do {
		nret = read_line( script_path, line, sizeof line );
		if( line[0] == '#' || line[0] == '\0' ) {
			continue;
		}

		if( !strncmp( line, "<SERVER>", 8 ) ) {
			if( parse_server_tag( line + 8, server_name, &server_port ) < 0 ) {
				nret = -1;
			}
		}
	} while( nret == 1 );

	read_line( NULL, NULL, 0 );
	return nret;
}

static int parse_get_tag( char *line, const char *server, unsigned short uport )
{
	char path[512] = "";
	char save[260] = "";
	char save_tmp[260] = "";
	char remote_md5[33] = "";
	char local_md5[33] = "";
	char title[260] = "";

	jump_space( &line );
	line += strcpy_tok( path, line, ' ' );
	DBG_LOG( "path = \"%s\"", path );

	jump_space( &line );
	line += strcpy_tok( remote_md5, line, ' ' );
	DBG_LOG( "remote_md5 = \"%s\"", remote_md5 );

	jump_space( &line );
	line += strcpy_tok( save_tmp, line, ' ' );
	make_dir( save, get_device_name( NULL ), save_tmp );
	DBG_LOG( "save = \"%s\"", save );
	strcpy( save_tmp, save );
	strcat( save_tmp, ".tmp" );

	make_md5( save, local_md5 );
	if( !strcmp( local_md5, remote_md5 ) ) {
		printf( "No need to update \"%s\".\n", save );
		DBG_LOG( "No need to update \"%s\".\n", save );
		return 1;
	}

	get_filetitle( title, save );
	printf( "Downloading \"%s\"...\n", title );

	if( http_getfile( server, uport, path, save_tmp ) < 0 ) {
		goto error;
	} else if( check_md5( save_tmp, remote_md5 ) != 1 ) {
		goto error;
	} else if( rename_file( save_tmp, save ) < 0 ) {
		DBG_LOG( "Error, sceIoRename()." );
		goto error;
	}

	printf( "Update success \"%s\".\n", save );
	DBG_LOG( "Update success \"%s\".\n", save );
	sceIoRemove( save_tmp );
	return 0;

error:
	printf( "Failed to update \"%s\".\n", save );
	DBG_LOG( "Failed to update \"%s\".", save );
	sceIoRemove( save_tmp );
	return -1;
}

static int get_tag_count( const char *file )
{
	int i = 0;
	char line[1024] = "";
	int nret;

	do {
		nret = read_line( file, line, sizeof line );
		if( line[0] == '#' || line[0] == '\0' )
			continue;
		if( !strncmp( line, "<GET>", 5 ) )
			i++;
	} while( nret == 1 );

	read_line( NULL, NULL, 0 );
	return i;
}

static int get_updateinfo( char *line, struct UpdateInfo *upinfo )
{
	char path[512] = "";
	char save[260] = "";
	char save_tmp[260] = "";
	char remote_md5[33] = "";

	jump_space( &line );
	line += strcpy_tok( path, line, ' ' );
	DBG_LOG( "path = \"%s\"", path );
	upinfo->path = oe_strmalloc( path );
	if( upinfo->path == NULL ) {
		return -1;
	}

	jump_space( &line );
	line += strcpy_tok( remote_md5, line, ' ' );
	DBG_LOG( "remote_md5 = \"%s\"", remote_md5 );
	strcpy( upinfo->remote_md5, remote_md5 );

	jump_space( &line );
	line += strcpy_tok( save_tmp, line, ' ' );
	make_dir( save, get_device_name( NULL ), save_tmp );
	DBG_LOG( "save = \"%s\"", save );
	upinfo->save = oe_strmalloc( save );
	if( upinfo->save == NULL ) {
		oe_free( (void *)(upinfo->path) );
		return -1;
	}

	upinfo->b_update = 1;
	return 0;
}

//
// public
//
int download_script( void )
{
//	const char server[] = "dl.dropbox.com";
	const char server[] = "prx-common-libraries.googlecode.com";
//	const char path[] = "/u/25123967/upload_script_md5.txt";
	const char path[] = "/hg/genupdate/upload_script.src";
	unsigned short uport = 80;

	printf( "Downloading the script file...\n" );

	strcpy( script_path, get_curdir(NULL) );
	strcat( script_path, SCRIPT_NAME );

	if( http_getfile( server, uport, path, script_path ) != 0 ) {
		printf( "Failed to download the script file.\n" );
		DBG_LOG( "Failed to download the script file." );
		return -1;
	}

	sceKernelDelayThread( 100000 );

	if( get_server_info() < 0 ) {
		printf( "Failed to get the server name and the port number.\n" );
		DBG_LOG( "Failed to get the server name and the port number.\n" );
		return -1;
	}

	sceKernelDelayThread( 100000 );
	return 0;
}

int read_update_script( void )
{
	char buf[1024] = "";

	int nret;
	do {
		nret = read_line( script_path, buf, sizeof buf );
		if( buf[0] == '#' || buf[0] == '\0' ) { // コメント行 空行の無視
			continue;
		}

		DBG_LOG( "  \"%s\"", buf );

		if( !strncmp( buf, "<GET>", 5 ) ) {
			parse_get_tag( buf + 5, server_name, server_port );
		}

	} while( nret == 1 );

	if( nret == 0 ) {
		printf( "\nComplete updates!\n" );
		DBG_LOG( "Complete updates!\n" );
	} else {
		printf( "\nFailed to updates.\n" );
		DBG_LOG( "Failed to updates.\n" );
	}

	read_line( NULL, NULL, 0 );
	wait_x_button();
	return nret;
}

int make_updateinfo( struct UpdateInfo **lpupinfo )
{
	int plugin_count = get_tag_count( script_path );
	if( plugin_count <= 0 ) {
		return -1;
	}

	struct UpdateInfo *upinfo = (struct UpdateInfo *)oe_malloc( (plugin_count + 1) * sizeof(struct UpdateInfo) );
	if( upinfo == NULL ) {
		return -2;
	}

	int nret;
	char line[1024] = "";
	int i = 0;

	do {
		nret = read_line( script_path, line, sizeof line );
		if( line[0] == '#' || line[0] == '\0' ) {
			continue;
		}

		if( !strncmp( line, "<GET>", 5 ) ) {
			if( get_updateinfo( line + 5, &(upinfo[i++]) ) < 0 ) {
				i--;
			}
		}
	} while( nret == 1 && i < plugin_count );

	read_line( NULL, NULL, 0 );

	struct UpdateInfo null_upinfo = { };
	upinfo[i] = null_upinfo;

	*lpupinfo = upinfo;
	return i;
}

void free_updateinfo( struct UpdateInfo *upinfo, int count )
{
	int i;
	for( i = 0; i < count; i++ ) {
		oe_free( (void *)upinfo[i].save );
		oe_free( (void *)upinfo[i].path );
	}
	oe_free( upinfo );
}

int individually_update( struct MenuEntry *entry )
{
	set_bottom_info( g_msg[UPDATE], 0 );
	frame_end();
	sceKernelDelayThread( CHANGE_DELAY );
	set_bottom_info( "", 0 );

	net_reconnect();

	char save_tmp[260] = "";
	struct UpdateInfo *upinfo = (struct UpdateInfo *)entry->arg;
	for( ; upinfo->save != NULL && upinfo->path != NULL; upinfo++ )
	{
		const char *save = upinfo->save;
		const char *path = upinfo->path;
		const char *remote_md5 = upinfo->remote_md5;

		if( !upinfo->b_update ) {
			continue;
		}

		char local_md5[33] = "";
		make_md5( save, local_md5 );
		if( !strcmp( local_md5, remote_md5 ) ) {
			printf( "No need to update \"%s\".\n", save );
			DBG_LOG( "No need to update \"%s\".\n", save );
			continue;
		}

		strcpy( save_tmp, save );
		strcat( save_tmp, ".tmp" );

		char title[260] = "";
		get_filetitle( title, save );
		printf( "Downloading \"%s\"...\n", title );

		int err = 0;
		if( http_getfile( server_name, server_port, path, save_tmp ) < 0 ) {
			err--;
		} else if( check_md5( save_tmp, remote_md5 ) != 1 ) {
			err--;
		} else if( rename_file( save_tmp, save ) < 0 ) {
			err--;
			DBG_LOG( "Error, sceIoRename()." );
		}

		if( err < 0 ) {
			printf( "Failed to download \"%s\".\n", save );
			DBG_LOG( "Failed to download \"%s\".", save );
		} else {
			printf( "Update success \"%s\".\n", save );
			DBG_LOG( "Update success \"%s\".\n", save );
		}

		sceIoRemove( save_tmp );
	}

	printf( "\nComplete updates!\n" );
	DBG_LOG( "Complete updates!\n" );
	wait_x_button();
	return 0;
}
