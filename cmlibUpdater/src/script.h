/*
 * Prx Common Libraries - cmlibUpdater
 * script.h
 * 2011/10/13
 * Created by Y.K
 */

#ifndef _SCRIPT_H_
#define _SCRIPT_H_

#include "main.h"

int read_update_script( void );
int download_script( void );
int make_updateinfo( struct UpdateInfo **lpupinfo );
void free_updateinfo( struct UpdateInfo *upinfo, int count );
int individually_update( struct MenuEntry *entry );

#endif // _SCRIPT_H_
