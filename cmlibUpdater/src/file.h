/*
 * Prx Common Libraries - cmlibUpdater
 * file.h
 * 2011/11/01
 * Created by Y.K
 */

#ifndef _FILE_H_
#define _FILE_H_

#include <pspsdk.h>

#include "net.h"
#include "http.h"
#include "main.h"

int read_line( const char *file, char *dest, int size );

char *get_filetitle( char *dest, const char *path );
char *get_curdir( const char *argp );
char *get_device_name( const char *argp );
char *make_dir( char *dest, const char *devname, const char *path );

int download_file( int sock, const char *file, HTTPResponse *resp, MemArray *mabuf );
int rename_file( const char *file, const char *new_name);
int make_md5( const char *file, char *hash );
int check_md5( const char *file, const char *remote_md5 );

// int get_prx_version( const char *prx, u8 *major, u8 *minor );
// int get_prx_version( u8 *prx_buf, u8 *major_ver, u8 *minor_ver );
// int copy_file( const char *dest, const char *src );


#endif // _FILE_H_
