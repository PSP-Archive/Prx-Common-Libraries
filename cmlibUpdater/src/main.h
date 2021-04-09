/*
 * Prx Common Libraries - cmlibUpdater
 * main.h
 * 2011/11/01
 * Created by Y.K
 */

#ifndef _MAIN_H_
#define _MAIN_H_

#define MODULE_NAME 	"cmLibUpdater TEST"
#define MAJOR_VER 		1
#define MAINOR_VER 		1

#define VERSION_STR 	"1.1"

#define SCRIPT_NAME 	"update_script.txt"

#define CUR_SEL_COLOR 			0x0000FF00

#define MAX_SCREEN_X 			68
#define MAX_SCREEN_Y 			33
#define BUF_WIDTH 				(512)
#define SCR_WIDTH 				(480)
#define SCR_HEIGHT 				(272)
#define PIXEL_SIZE 				(4)
#define FRAME_SIZE 				(BUF_WIDTH * SCR_HEIGHT * PIXEL_SIZE)

#define CTRL_DELAY   			100000
#define CTRL_DEADZONE_DELAY 	500000
#define ENTER_DELAY  			500000
#define EXIT_DELAY   			500000
#define CHANGE_DELAY 			500000
#define UPDATE_EXIT_DELAY 		4000000

#define DRAW_BUF 				(void *)(0x44000000)
#define DISPLAY_BUF 			(void *)(0x44000000 + FRAME_SIZE)
#define MAX_MENU_NUMBER_PER_PAGE (MAX_SCREEN_Y-5-2-5)

#define PSP_CTRL_OK 		PSP_CTRL_CROSS
#define PSP_CTRL_CANCEL 	PSP_CTRL_CIRCLE

extern int g_running;
extern int g_disp_flip;

enum {
	MENU_TITLE = 0,
	MAIN_MENU,
	ENTERING,
	EXITING,
	BACK,
	EXIT,
	DEFAULT,
	ENABLED,
	DISABLED,
	ALL_UPDATE,
	MANUAL_UPDATES,
	UPDATE,
	CONFIG,
	SAVE_DEVICE,
	ERROR,
	DUMMY,
};

extern const char * g_msg[];

struct MenuEntry {
	const char **info;
	int b_submenu;
	int color;
	int (*display_callback)(struct MenuEntry *, char *, int);
	int (*change_value_callback)(struct MenuEntry *, int);
	int (*enter_callback)(struct MenuEntry *);
	void *arg;
};

struct ValueOption {
	s16 *value;
	int limit_start;
	int limit_end;
};

struct Menu {
	const char **subtitle;
	struct MenuEntry *submenu;
	int submenu_size;
	int cur_sel;
	int subtitle_color;
	int b_topmenu;
};

struct UpdateInfo {
	const char *path;
	const char *save;
	char remote_md5[33];
	int b_update;
};

typedef struct {
	char *ptr;
	unsigned int size;
	unsigned int len;
} MemArray;


#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

#define NELEMS(a) (sizeof(a) / sizeof(a[0]))

#define printf pspDebugScreenPrintf

static inline void *get_drawing_buffer( void ){ return (void *)((g_disp_flip)? DRAW_BUF : DISPLAY_BUF); }
static inline void *get_display_buffer( void ){ return (void *)((g_disp_flip)? DISPLAY_BUF : DRAW_BUF); }

int exit_eboot( void );

int limit_int( int value, int direct, int limit );
void set_bottom_info( const char *str, int color );
void frame_start( void );
void frame_end( void );
void menu_loop( struct Menu *menu );

void main_menu( void );

#endif // _MAIN_H_
