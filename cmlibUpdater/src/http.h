/*
 * Prx Common Libraries - cmlibUpdater
 * http.h
 * 2011/10/21
 * Created by Y.K
 */

#ifndef _HTTP_H_
#define _HTTP_H_

#include "main.h"

#define HTTP_GET 	"GET"
#define HTTP_HEAD 	"HEAD"

typedef struct _tag_HTTPResponse {
	int http_minor_ver;
	int status;
	unsigned int content_length;
	char last_modified[64];
} HTTPResponse;

// int http_method_request( int sock, const char *method, const char *path, const char *host, const char *date );
// int http_get_response( int sock, HTTPResponse *resp, MemArray *mabuf );
int http_getfile( const char *server, unsigned short uport, const char *path, const char *file );

#endif // _HTTP_H_
