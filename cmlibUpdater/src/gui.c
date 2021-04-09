/*
 * Prx Common Libraries - cmlibUpdater
 * gui.c
 * 2011/10/24
 * Created by Y.K
 */

#include <pspkernel.h>
#include <pspsdk.h>
#include <pspdebug.h>
#include <pspctrl.h>
#include <pspdisplay.h>
#include <psppower.h>

#include "debuglog.h" /* DEBUG */
#include "main.h"

static char g_bottom_info[MAX_SCREEN_X + 1];
static int g_bottom_info_color;

static u32 g_last_btn = 0;
static u32 g_last_tick = 0;
static u32 g_deadzone_tick = 0;

static u32 ctrl_read( void )
{
	SceCtrlData pad;

	sceCtrlReadBufferPositive( &pad, 1 );

	if( pad.Buttons == g_last_btn ) {
		if( pad.TimeStamp - g_deadzone_tick < CTRL_DEADZONE_DELAY ) {
			return 0;
		}

		if( pad.TimeStamp - g_last_tick < CTRL_DELAY ) {
			return 0;
		}

		g_last_tick = pad.TimeStamp;

		return g_last_btn;
	}

	g_last_btn = pad.Buttons;
	g_deadzone_tick = g_last_tick = pad.TimeStamp;

	return g_last_btn;
}

static void set_screen_xy( int x, int y )
{
	pspDebugScreenSetXY( x, y );
}

static void write_string_with_color( const char *str, int color )
{
	if( color != 0 )
		pspDebugScreenSetTextColor( color );

	pspDebugScreenPrintf( str );
	pspDebugScreenSetTextColor( 0xFFFFFFFF );
}

static void write_bottom_info( void )
{
	set_screen_xy( 2, MAX_SCREEN_Y - 3 );
	write_string_with_color( g_bottom_info, g_bottom_info_color );
}

static void draw_bottom_line( void )
{
	int i = 1;

	set_screen_xy( i, MAX_SCREEN_Y - 5 );

	for( ; i < MAX_SCREEN_X; ++i )
		write_string_with_color( "*", 0xFF00 );
}

static void menu_draw( struct Menu *menu )
{
	int x, y, i, cur_page_start, total_page;

	/* Main menu title */
	x = 1, y = 1;
	set_screen_xy( x, y );
	write_string_with_color( g_msg[MENU_TITLE], 0xFF00 );

	/* Sub menu title */
	x = 1, y = 2;
	set_screen_xy( x, y );
	write_string_with_color( *menu->subtitle, menu->subtitle_color );

	/* Control menu */
	x = 3, y = 4;
	set_screen_xy( x, y );

	char ctrlmenu_str[10];
	int ctrlmenu_clr;

	if( menu->cur_sel == 0 ) {
		strcpy( ctrlmenu_str, "> " );
		ctrlmenu_clr = CUR_SEL_COLOR;
	} else {
		strcpy( ctrlmenu_str, "  " );
		ctrlmenu_clr = 0;
	}

	if( menu->b_topmenu == 0 ) {
		strcat( ctrlmenu_str, g_msg[BACK] );
	} else {
		strcat( ctrlmenu_str, g_msg[EXIT] );
	}
	write_string_with_color( ctrlmenu_str, ctrlmenu_clr );

	/* Entries menu */
	x = 3, y = 6;
	set_screen_xy( x, y );

	if( menu->cur_sel == 0 ) {
		cur_page_start = 0;
	} else {
		cur_page_start = (menu->cur_sel-1) / MAX_MENU_NUMBER_PER_PAGE * MAX_MENU_NUMBER_PER_PAGE;
	}

	for( i = cur_page_start; i < MIN(menu->submenu_size, cur_page_start + MAX_MENU_NUMBER_PER_PAGE); ++i ) {
		char buf[256], *p;
		int color;
		struct MenuEntry* entry;

		entry = &menu->submenu[i];

		if( menu->cur_sel == i + 1 ) {
			color = CUR_SEL_COLOR;
			strcpy( buf, "> " );
		} else {
			color = entry->color;
			strcpy( buf, "  " );
		}

		p = buf + strlen( buf );

		if( entry->info != NULL ) {
			sprintf( p, "%s", *entry->info );
		} else {
			int (*display_callback)(struct MenuEntry* , char *, int);
			
			display_callback = (*entry->display_callback);
			if( display_callback != NULL ) {
				(*display_callback)(entry, p, sizeof(buf) - (p - buf));
			} else {
				strcpy( p, "FIXME" );
			}
		}

		if( entry->b_submenu != 0 ) {
			strcat( p, " ->" );
		}

		write_string_with_color( buf, color );
		set_screen_xy( x, ++y );
	}

	total_page = (menu->submenu_size + MAX_MENU_NUMBER_PER_PAGE - 1) / MAX_MENU_NUMBER_PER_PAGE;

	if( total_page > 1 ) {
		char buf[20];
		x = MAX_SCREEN_X - 15;
		y = 4;

		sprintf( buf, "Page %d/%d", (cur_page_start / MAX_MENU_NUMBER_PER_PAGE) + 1, total_page );
		set_screen_xy( x, y );
		write_string_with_color( buf, 0 );
	}

	write_bottom_info();
	draw_bottom_line();
}

static void get_sel_index( struct Menu *menu, int direct )
{
	menu->cur_sel = limit_int( menu->cur_sel, direct, menu->submenu_size + 1 );
}

static void menu_change_value( struct Menu *menu, int direct )
{
	struct MenuEntry *entry;

	if( menu->cur_sel != 0 ) {
		entry = &menu->submenu[menu->cur_sel - 1];

		if( entry->change_value_callback != NULL )
			(*entry->change_value_callback)(entry, direct);
	}
}

// exit menu when returns 1
static int menu_ctrl( struct Menu *menu )
{
	char buf[80];

	u32 key = ctrl_read();

	if( key & PSP_CTRL_UP ) {
		get_sel_index( menu, -1 );
	}
	else if( key & PSP_CTRL_DOWN ) {
		get_sel_index( menu, +1 );
	}
	else if( key & PSP_CTRL_RIGHT ) {
		menu_change_value( menu, +1 );
	}
	else if( key & PSP_CTRL_LEFT ) {
		menu_change_value( menu, -1 );
	}
	else if( key & PSP_CTRL_LTRIGGER ) {
		if( menu->cur_sel > MAX_MENU_NUMBER_PER_PAGE ) {
			menu->cur_sel -= MAX_MENU_NUMBER_PER_PAGE;
		} else {
			menu->cur_sel = 0;
		}
	}
	else if( key & PSP_CTRL_RTRIGGER ) {
		if( menu->cur_sel + MAX_MENU_NUMBER_PER_PAGE < menu->submenu_size ) {
			menu->cur_sel += MAX_MENU_NUMBER_PER_PAGE;
		} else {
			menu->cur_sel = menu->submenu_size;
		}
	}
	else if( key & PSP_CTRL_OK && menu->cur_sel != 0 ) {
		struct MenuEntry *entry;
		int (*enter_callback)(struct MenuEntry *);

		entry = &menu->submenu[menu->cur_sel - 1];
		enter_callback = entry->enter_callback;

		if( entry->b_submenu != 0 ) {
			sprintf( buf, "> %s...", g_msg[ENTERING] );
			set_bottom_info( buf, 0xFF00 );
			frame_end();
			sceKernelDelayThread( ENTER_DELAY );
			set_bottom_info( "", 0 );
		}

		if( enter_callback != NULL )
			(*enter_callback)(entry);
	}
	else if( (key & PSP_CTRL_OK && menu->cur_sel == 0) || key & PSP_CTRL_CANCEL ) {
		sprintf( buf, "> %s...", g_msg[EXITING] );
		set_bottom_info( buf, 0xFF00 );
		frame_end();
		sceKernelDelayThread( EXIT_DELAY );
		set_bottom_info( "", 0 );

		return 1;
	}

	return 0;
}

int limit_int( int value, int direct, int limit )
{
	if( limit == 0 || limit == 1 )
		return 0;

	value += direct; // -1

	if( value >= limit ) {
		value = value % limit;
	} else if( value < 0 ) {
		value = limit - ((-value) % limit);
	}

	return value;
}

void set_bottom_info( const char *str, int color )
{
	strcpy( g_bottom_info, str );
	g_bottom_info_color = color;
	write_bottom_info();
}

void frame_start( void )
{
	scePowerTick( 0 );
	sceDisplayWaitVblank();
	pspDebugScreenSetOffset( (int)get_drawing_buffer() - 0x44000000 );
	memset( get_drawing_buffer(), 0, 512 * 272 * 4 );
}

void frame_end( void )
{
	g_disp_flip = !g_disp_flip;
	sceDisplaySetFrameBuf( get_display_buffer(), 512, PSP_DISPLAY_PIXEL_FORMAT_8888, PSP_DISPLAY_SETBUF_NEXTFRAME );
	sceDisplayWaitVblank();
}

void menu_loop( struct Menu *menu )
{
	while( g_running != 0 )
	{
		frame_start();
		menu_draw( menu );
		if( menu_ctrl( menu ) != 0 )
			break; // Exit menu

		frame_end();
	}
}
