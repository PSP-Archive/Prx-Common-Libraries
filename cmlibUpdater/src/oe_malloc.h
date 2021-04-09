/*
 * Prx Common Libraries - cmlibUpdater
 * oe_malloc.h
 * 2011/10/12
 * Created by Y.K
 */

#ifndef _MY_MALLOC_H_
#define _MY_MALLOC_H_

void *oe_malloc( int size );
void *oe_realloc( void *ptr, int resize );
void oe_free( void *ptr );

char *oe_strmalloc( char *str );

#endif // _MY_MALLOC_H_
