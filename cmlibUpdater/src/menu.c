/*
 * Prx Common Libraries - cmlibUpdater
 * menu.c
 * 2011/11/02
 * Created by Y.K
 */

#include <pspkernel.h>
#include <pspsdk.h>
#include <pspdebug.h>
#include <pspctrl.h>
#include <pspdisplay.h>

#include "debuglog.h" /* DEBUG */
#include "main.h"
#include "net.h"
#include "script.h"
#include "file.h"
#include "oe_malloc.h"

const char * g_msg[] = {
	MODULE_NAME " " VERSION_STR " By Team Otwibaco",
	"Main menu",
	"Entering",
	"Exiting",
	"Back",
	"Exit",
	"Default",
	"Enabled",
	"Disabled",
	"All update",
	"Individually update",
	"Update",
	"Configuration",
	"Save device",
	"Error",
	"Dummy",
};

//
// Common
//
static int change_option( struct MenuEntry *entry, int direct )
{
	struct ValueOption *c = (struct ValueOption *)entry->arg;

	*c->value -= c->limit_start;
	*c->value = limit_int( *c->value, direct, c->limit_end - c->limit_start );
	*c->value += c->limit_start;

	return 0;
}

static int change_option_by_enter( struct MenuEntry *entry )
{
	char buf[256], *p;

	change_option( entry, 1 );
	strcpy( buf, "> " );
	p = buf + strlen(buf);

	if( entry->display_callback != NULL ) {
		(entry->display_callback)(entry, p, sizeof(buf) - (p - buf));
	} else {
		strcpy( p, *entry->info );
	}

	set_bottom_info( buf, 0 );
	frame_end();
	sceKernelDelayThread( CHANGE_DELAY );
	set_bottom_info( "", 0 );

	return 0;
}

//
// Using plugin menu functions
//
static int change_plugin_option( struct MenuEntry *entry, int direct )
{
	struct UpdateInfo *upinfo = (struct UpdateInfo *)entry->arg;

	upinfo->b_update = limit_int( upinfo->b_update, direct, 2 );

	return 0;
}

static int change_plugin_option_by_enter( struct MenuEntry *entry )
{
	char buf[256], *p;

	change_plugin_option( entry, 1 );
	strcpy( buf, "> " );
	p = buf + strlen(buf);

	if( entry->display_callback != NULL ) {
		(entry->display_callback)(entry, p, sizeof(buf) - (p - buf));
	} else {
		strcpy( p, *entry->info );
	}

	set_bottom_info( buf, 0 );
	frame_end();
	sceKernelDelayThread( CHANGE_DELAY );
	set_bottom_info( "", 0 );

	return 0;
}

static int cb_disp_plugin_name( struct MenuEntry *entry, char *buf, int size )
{
	char title[260];
	struct UpdateInfo *upinfo = (struct UpdateInfo *)entry->arg;

	get_filetitle( title, upinfo->save );
	sprintf( buf, "%-48s %-11s", title, (upinfo->b_update==0)? g_msg[DISABLED] : g_msg[ENABLED] );

	return 0;
}

static int make_plugins_menu( struct Menu *menu, const char **subtitle, struct UpdateInfo *upinfo, int count )
{
	struct MenuEntry *submenu = (struct MenuEntry *)oe_malloc( (count + 1) * sizeof(struct MenuEntry) );
	if( submenu == NULL ) return -1;

	int i;
	for( i = 0; i < count; i++ ) {
		submenu[i].info = NULL;
		submenu[i].b_submenu = 0;
		submenu[i].color = 0;
		submenu[i].display_callback = cb_disp_plugin_name;
		submenu[i].change_value_callback = change_plugin_option;
		submenu[i].enter_callback = change_plugin_option_by_enter;
		submenu[i].arg = &(upinfo[i]);
	}

	struct MenuEntry entry = { &g_msg[UPDATE], 0, 0xFF0000, NULL, NULL, individually_update, upinfo };
	submenu[count] = entry;

	menu->subtitle = subtitle;
	menu->submenu = submenu;
	menu->submenu_size = count + 1;
	menu->cur_sel = 0;
	menu->subtitle_color = 0xFF00;
	menu->b_topmenu = 0;

	return 0;
}

//
// Using top menu functions
//
static int all_updates_func( struct MenuEntry *entry )
{
	set_bottom_info( g_msg[ALL_UPDATE], 0 );
	frame_end();
	sceKernelDelayThread( CHANGE_DELAY );
	set_bottom_info( "", 0 );

	pspDebugScreenClear();

	net_reconnect();
	read_update_script();

	return 0;
}

static int manual_updates_func( struct MenuEntry *entry )
{
	set_bottom_info( g_msg[MANUAL_UPDATES], 0 );
	frame_end();
	sceKernelDelayThread( CHANGE_DELAY );
	set_bottom_info( "", 0 );

	pspDebugScreenClear();

	struct UpdateInfo *upinfo = NULL;
	int count = make_updateinfo( &upinfo );
	if( count <= 0 ) return -1;

	struct Menu menu = { };

	if( make_plugins_menu( &menu, &g_msg[MANUAL_UPDATES], upinfo, count ) < 0 )
		return -1;

	menu.cur_sel = 0;
	menu_loop( &menu );

	free_updateinfo( upinfo, count );
	oe_free( menu.submenu );

	return 0;
}

static struct MenuEntry g_top_menu_entries[] = {
	{ &g_msg[ALL_UPDATE], 0, 0, NULL, NULL, &all_updates_func, NULL },
	{ &g_msg[MANUAL_UPDATES], 1, 0, NULL, NULL, &manual_updates_func, NULL },
};

static struct Menu g_top_menu = {
	&g_msg[MAIN_MENU], /* subtitle */
	g_top_menu_entries, /* submenu */
	NELEMS(g_top_menu_entries), /* submenu_size */
	0, /* cur_sel */
	0xFF00, /* subtitle_color */
	1  /* b_topmenu */
};

void main_menu( void )
{
	g_top_menu.cur_sel = 1;
	menu_loop( &g_top_menu );
}
