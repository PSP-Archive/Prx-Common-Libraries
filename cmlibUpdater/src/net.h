/*
 * Prx Common Libraries - cmlibUpdater
 * net.h
 * 2011/10/24
 * Created by Y.K
 */

#ifndef _NET_H_
#define _NET_H_

int net_load_module( void );
void net_init( void );
void net_term( void );
int net_loadinit_module( void );

// int net_connect_to_apctl( int config );
int net_disconnect_to_apctl( void );
int net_is_connected( void );	// 1 on connected or 0 disconnected or < 0 on error.
void net_not_connected( void );
void net_reconnect( void );

int net_connect_to_server( const char *server, unsigned short uport );
int net_send_msg( int s, char *msg );
int net_recv_const_data( int s, void *buf, int size );
int net_recv_data( int s, void *buf, int size, int *read );

int net_dialog( void );

#endif // _NET_H_
