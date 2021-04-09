/*
 * Prx Common Libraries - cmlibUpdater
 * http.c
 * 2011/11/02
 * Created by Y.K
 */

#include <pspkernel.h>
#include <pspdebug.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "net.h"
#include "file.h"
#include "http.h"
#include "main.h"

#include "debuglog.h"


//
// Private functions.
//
static
char *strtok_CRLF( char *str )
{
	static char *save;
	char *begin, *end;

	if( str != NULL ) {
		begin = str;
	} else if( save != NULL ) {
		begin = save;
	} else {
		return NULL;
	}

	if( ( end = strstr( begin, "\r\n" ) ) == NULL ) {
		save = NULL;
		return NULL;
	}
	end[0] = '\0';
	end[1] = '\0';
	save = end + 2;
	return begin;
}

static inline
int get_minor_ver( char cnum )
{
	if( cnum == '0' ) {
		return 0;
	} else if( cnum == '1' ) {
		return 1;
	}
	return -1;
/*
	cnum -= '0';
	return (cnum < 0)? -1 : (cnum > 9)? -1 : cnum;
*/
}

static
int check_statuscode( int status )
{
	DBG_LOG( "status code = %d", status );

	switch( status )
	{
	case 200:
// printf("Request OK!\n" );
		return status;

	case 304:
printf( "Not Modified (304)\n" );
		break;

	case 400:
printf( "Bad Request (400)\n" );
		break;

	case 404:
printf( "Not Found (404)\n" );
		break;

	case 408:
printf( "Request Timeout (408)\n" );
		break;

	default:
printf( "Error, unknown status code.\n" );
		break;
	}
	return -1;
}

static
int read_response_line( char *buf, HTTPResponse *resp, char **pos )
{
	char *line = NULL, *back = NULL;

	if( (back = strtok_CRLF( buf )) == NULL ) {
		return 2;
	}

	do {
		line = back;

		if( !strncmp( line, "HTTP/1.", 7 ) )
		{
			DBG_LOG( "    %s", line );
			line += 7;
			resp->http_minor_ver = get_minor_ver( *line );
			line += 2;
			line[3] = '\0';
			int status = check_statuscode( strtol( line, NULL, 10 ) );
			if( status < 0 ) return -1;
			resp->status = status;
		}
		else if( !strncmp( line, "Content-Length: ", 16 ) )
		{
			DBG_LOG( "    %s", line );
			line += 16;
			unsigned int length = (unsigned int)strtol( line, NULL, 10 );
			DBG_LOG( "content_length = %d", length );
			resp->content_length = length;
		}
		else if( !strncmp( line, "Last-Modified: ", 15 ) )
		{
			DBG_LOG( "    %s", line );
			line += 15;
			strncpy( resp->last_modified, line, 63 );
		}
		else if( line[0] == '\0' )
		{
			*pos = line + 2;
			DBG_LOG( "Response end line!" );
			return 1;
		}
	} while( ( back = strtok_CRLF(NULL) ) != NULL );

	*pos = line + strlen(line) + 2;

	return 0;
}

static
int http_method_request( int sock, const char *method, const char *path, const char *host, const char *date )
{
	char request[2048] = "";
	char buf[290];

	DBG_LOG( "Request = \"%s %s HTTP/1.0\"", method, path );
	sprintf( buf, "%s %s HTTP/1.0\r\n", method, path );
	strcat( request, buf );
	sprintf( buf, "Host: %s\r\n", host );
	strcat( request, buf );
	strcat( request, "User-Agent: Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.0)\r\n" );
//	strcat( request, "Content-Type: application/octet-stream; charset=binary\r\n" );
	strcat( request, "Accept: */*\r\n" );
	strcat( request, "Pragma: no-cache\r\n" );
	strcat( request, "Cache-Control: no-cache\r\n" );
	strcat( request, "Connection: close\r\n" );
	if( date != NULL ) {
		sprintf( buf, "If-Modified-Since: %s\r\n", date );
		strcat( request, buf );
	}
	strcat( request, "\r\n" ); // End line
	return net_send_msg( sock, request );
}

static
int http_get_response( int sock, HTTPResponse *resp, MemArray *mabuf )
{
	char *lpbuf = mabuf->ptr;
	int bufsize = mabuf->size - 2;
	int nrecv = 0, sumlen = 0;

	char *pos = NULL;
	int nret;

	while( bufsize > 0 ) {
		nret = net_recv_data( sock, lpbuf, bufsize - 1, &nrecv );
		if( nret < 0 || nrecv == 0 ) {
			DBG_LOG( "Error, net_recv_data() nret = %d, nrecv = %d", nret, nrecv );
			break;
		}

		bufsize -= nrecv;
		lpbuf += nrecv;
		*lpbuf = '\0';
		sumlen += nrecv;

		nret = read_response_line( mabuf->ptr, resp, &pos );
		if( nret < 0 ) {
			DBG_LOG( "Error, read_response_line() nret = %d", nret );
			break;
		}
		if( nret == 0 ) {
			strcpy( mabuf->ptr, pos );
			int len = strlen( mabuf->ptr );
			lpbuf = mabuf->ptr + len;
			bufsize = mabuf->size - len;
			sumlen = len;
		}
		if( nret == 1 ) { // exit
			mabuf->len = sumlen - ( pos - mabuf->ptr );
			memmove( mabuf->ptr, pos, mabuf->len );
			return 0;
		}
	}
	memset( mabuf->ptr, 0, mabuf->size );
	return -1;
}

//
// Public functions.
//
int http_getfile( const char *server, unsigned short uport, const char *path, const char *file )
{
	int sock = -1;
	char buf[4096] = "";
	MemArray mabuf = { buf, sizeof buf, 0 };
	HTTPResponse resp = { };

	if( (sock = net_connect_to_server( server, uport )) < 0 ) {
		DBG_LOG( "Error, net_connect_to_server()" );
		goto error;
	}

	if( http_method_request( sock, HTTP_GET, path, server, NULL ) < 0 ) {
		DBG_LOG( "Error, http_method_request()" );
		goto error;
	}

	if( http_get_response( sock, &resp, &mabuf ) < 0 ) {
		DBG_LOG( "Error, http_get_response()" );
		goto error;
	}

	if( download_file( sock, file, &resp, &mabuf ) < 0 ) {
		DBG_LOG( "Error, download_file()" );
		goto error;
	}

	DBG_LOG( "OK, http_getfile()" );
	close( sock );
	return 0;

error:
	if( sock >= 0 ) close( sock );
	DBG_LOG( "Error, http_getfile()" );
	return -1;
}
