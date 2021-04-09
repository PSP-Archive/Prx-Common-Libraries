//
// genupdate
// 2011/10/24
// Created by popsdeco and Y.K.
// Thanks to popsdeco!
//

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include "md5.h"

#if defined(WIN32) || !defined(__GNUC__)
#define initstdio() setmode(fileno(stdin),O_BINARY),setmode(fileno(stdout),O_BINARY),setmode(fileno(stderr),O_BINARY);
#else
#define initstdio()
#endif

#define PSP_O_RDONLY  O_RDONLY
#define PSP_O_WRONLY  O_WRONLY
#define PSP_O_RDWR    O_RDWR

#define sceIoOpen open
#define sceIoClose close
#define sceIoRead read
#define sceIoWrite write
#define sceIoChdir chdir

// accepts LF/CRLF
static char *myfgets( char *buf, int n, FILE *fp )
{
	int len;
	char *ret = fgets( buf, n, fp );
	if( ret != NULL && (len = strlen(buf)) ) {
		if( buf[len - 1] == '\n' || buf[len - 1] == '\r' ) {
			buf[len - 1] = 0;
		}
	}
	return ret;
}

static int myopen( const char *file )
{
	char path[260] = "";
	char *pos;
	int fd = sceIoOpen( file, PSP_O_RDONLY | O_BINARY, 0777 );
	if( fd < 0 ) {
		pos = strchr( file, '/' );
		if( pos != NULL ) {
			strcpy( path, "prxcmlib_pack" );
			strcat( path, pos );
			fd = sceIoOpen( path, PSP_O_RDONLY | O_BINARY, 0777 );
			if( fd < 0 ) return fd;
		}
	}
	return fd;
}

static char line[1024];
static unsigned char buf[0x2000];

static int make_md5( const char *file, unsigned char *md5 )
{
	int fd, readlen;
	unsigned char digest[16] = "";
	MD5_CTX md5ctx;
	int i, x, y;

	if( (fd = myopen( file )) < 0 ) {
		return -1;
	}

	MD5Init( &md5ctx );

	while( (readlen = sceIoRead( fd, buf, sizeof buf )) > 0 ) {
		MD5Update( &md5ctx, (unsigned char *)buf, readlen );
	}

	MD5Final( digest, &md5ctx );
	sceIoClose( fd );

	for( i = 0; i < 16; i++ ) {
		x = digest[i] >> 4;
		y = digest[i] & 0xF;
		md5[2 * i + 0] = (x > 9)? ((x - 10) + 'a') : (x + '0');
		md5[2 * i + 1] = (y > 9)? ((y - 10) + 'a') : (y + '0');
	}

	md5[32] = '\0';

	return 0;
}

// usage: genupdate root/of/PSP < template.txt > upload_script.src
int main( int argc, char **argv )
{
	char *cmd, *remote, *local;
	char md5[33] = "";

	if( argc != 2 ) {
		perror( "usage: genupdate root/of/PSP" );
		return 0;
	}

	initstdio();
	sceIoChdir( argv[1] );

	while( myfgets( line, 1024, stdin ) )
	{
		if( memcmp( line, "<GET>", 5 ) ) {
			fprintf( stdout, "%s\n", line );
			continue;
		}

		cmd = strtok( line, " \t" );
		remote = strtok( NULL, " \t");
		local = strtok( NULL, " \t" );

		if( make_md5( local + 1, md5 ) < 0 ) {
			continue;
		}

		fprintf( stdout, "%s %s %s %s\n", cmd, remote, md5, local );
	}

	return 0;
}
