#include <pspkernel.h>
#include <pspsdk.h>
#include <pspge.h>
#include <pspctrl.h>
#include <pspsysclib.h>
#include <pspdisplay.h>
#include <pspsysevent.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "cmlibmenu.h"

#include "color.h"

enum
{
	LIBM_TCMD_SUSPEND	,	//他スレッドを停止
	LIBM_TCMD_RESUME	,	//他スレッドを再開
	LIBM_TCMD_DUMP		,	//他スレッドを停止・再開させる為のセーフリストを作る
	LIBM_TCMD_GET		,	//他スレッドの停止・再開状態を取得
};

#define	ITEM_COUNT					66
#define	LIBM_TSUSPEND				LIBM_TCMD_SUSPEND
#define	LIBM_TRESUME				LIBM_TCMD_RESUME

#define MAX_NUMBER_OF_THREADS 		64

#define	PSP_SYSEVENT_SUSPEND_QUERY	0x100


PSP_MODULE_INFO("MenuTest", PSP_MODULE_KERNEL, 1, 1);


/*
//メニュー作成に必要な context、itemを用意する際
//ゲーム起動と同時にメモリから動的確保しようとすると
//それが原因でゲームが異常終了してしまうことがある

//そのエラーはメモリ確保がゲーム起動前に行われた時
//本来ゲーム側が使用するはずのメモリから確保してしまって
//それを返却しないことが原因で起こる

//それを回避するには完全にゲームが起動してからメモリを動的確保するように
//適当なディレイを入れるのが簡単な方法だが
//それだとゲーム起動直後にメニュー表示することが出来ない仕様になる

//そこでプラグインのスタック上に常置させるようにすれば
//その問題も回避出来てゲーム起動直後からメニュー表示が可能
*/

//プラグイン スタック上にアイテム変数を常置させる
static MenuContext	Context;
static MenuItem item_list[ITEM_COUNT];


static MenuItem *AlphaAFA,*AlphaABA,*AlphaNFA,*AlphaNBA,*sync_trigger;
static libmOpt opt;

libm_draw_info dinfo;
libm_vram_info vinfo;

enum
{
	NoAction,
	TS_Change,
	ReturnChange,
	TypeChange,
	ColorChange,
	LinesChange,
	AlphaChange,
	D_Alpha,
	DELAYChange,
	Trigger_Push
};



enum
{
	ActiveF,
	ActiveFA,
	ActiveB,
	ActiveBA,
	NormalF,
	NormalFA,
	NormalB,
	NormalBA
};

const char *Movie_Test[] =
{
	"ダイ・ハード",
	"アルマゲドン",
	"マトリックス",
	"エイリアン",
	"ゴースト・バスターズ",
	NULL
};
		
const char *Food_Test[] =
{
	"ラーメン",
	"唐揚げ",
	"冷やし中華",
	"食パン",
	"牛乳",
	"キムチ",
	"お寿司",
	NULL
};
		
const char *PC_Test[] =
{
	"モニター",
	"ケース",
	"ハード・ディスク",
	"メモリ",
	"マザー・ボード",
	"マウス",
	"CPU",
	"グラフィック・カード",
	"プリンター",
	NULL
};
		
const char *TypeList[] =
{
	"メニュー全体",
	"アクティブな項目のみ",
	NULL
};
		
const char *ColorList[] =
{
	"なし",
	"BLACK",
	"BLUE",
	"RED",
	"GREEN",
	"DARKBLUE",
	"LIGHTBLUE",
	"BROWN",
	"PINK",
	"DARKGREEN",
	"YELLOGREEN",
	"PURPLE",
	"ORANGE",
	"LEMON",
	"YELLOW",
	"SKYBLUE",
	"PEARLORANGE",
	"GRAY",
	"SILVER",
	"GOLD",
	"WHITE",
	NULL
};



u32 color[] = 
{
	LIBM_NO_DRAW,
	BLACK		,
	BLUE		,
	RED			,
	GREEN		,
	DARKBLUE	,
	LIGHTBLUE	,
	BROWN		,
	PINK		,
	DARKGREEN	,
	YELLOGREEN	,
	PURPLE		,
	ORANGE		,
	LEMON		,
	YELLOW		,
	SKYBLUE		,
	PEARLORANGE	,
	GRAY		,
	SILVER		,
	GOLD		,
	WHITE		,
};


void MenuCreate()
{
	//メニュー アイテムをメモリから動的確保しない設定にする
	memset(&opt,0,sizeof(opt));
	opt.type		= LIBM_OPT_LIST;
	opt.list.val	= item_list;
	opt.list.size 	= sizeof(item_list);
	
	libmSetOpt(&Context,&opt);
	
	//メニュー操作用の各Pad設定
		
	//表示 + & -
	Context.HotKey.Show				= PSP_CTRL_VOLUP | PSP_CTRL_VOLDOWN;
	//戻る △
	Context.HotKey.Back				= PSP_CTRL_TRIANGLE;
	//選択 ×
	Context.HotKey.Select			= PSP_CTRL_CROSS;
	//上へ ↑
	Context.HotKey.Up				= PSP_CTRL_UP;
	//下へ ↓
	Context.HotKey.Down				= PSP_CTRL_DOWN;
	//左へ ←
	Context.HotKey.Left				= PSP_CTRL_LEFT;
	//右へ
	Context.HotKey.Right			= PSP_CTRL_RIGHT;
	
	//メニュータイプは「全体表示」
	Context.MenuInfo.Type 			= LIBM_VIEW_ALL;
	//アイテムが最上部・下部へ来たら自動でターンさせる
	Context.MenuInfo.AutoReturn		= true;
		
	//アクティブな項目のフォント色、背景色
	Context.Color.Active_Font		= PINK;
	Context.Color.Active_Back		= SetAlpha(BLUE,0x82);
		
	//非アクティブな項目のフォント色、背景色
	Context.Color.Normal_Font		= WHITE;
	Context.Color.Normal_Back		= SetAlpha(GRAY,0x64);
		
	//行間
	Context.MenuInfo.Lines			= 1;
	
	libmAddItem(&Context,NULL,libmCreateSpacer(&opt, "メニュー サンプル"),YELLOGREEN,DARKGREEN,NoAction,0);
	
	libmAddItem(&Context,NULL,libmCreateTriggerButton(&opt,"トリガーボタン"),RED,SetAlpha(GREEN,0x66),Trigger_Push,0);
	
	MenuItem* Select_Test = libmAddItem(&Context,NULL,libmCreateContainer(&opt,"セレクト ボックス"),RED,SetAlpha(GREEN,0x66),NoAction,0);
	{
		MenuItem* msg = libmAddItem(&Context,Select_Test,libmCreateSpacer(&opt,"もちろん選択済み項目の指定が\x89\xC2\x94\x5Cです"),Invalid,Invalid,NoAction,0);
		msg->Color.Line = BLACK;
		
		libmAddItem(&Context,Select_Test,libmCreateSpacer(&opt,NULL),Invalid,Invalid,NoAction,0);
		
		libmAddItem(&Context,Select_Test,libmCreateSpacer(&opt,"サンプル 1"),WHITE,SetAlpha(BLACK,0x80),NoAction,0);
		libmAddItem(&Context,Select_Test,libmCreateSelectBox(&opt,"映画:",Movie_Test,2),Invalid,Invalid,NoAction,0);
		
		libmAddItem(&Context,Select_Test,libmCreateSpacer(&opt,NULL),Invalid,Invalid,NoAction,0);
		
		libmAddItem(&Context,Select_Test,libmCreateSpacer(&opt,"サンプル 2"),WHITE,SetAlpha(BLACK,0x80),NoAction,0);
		libmAddItem(&Context,Select_Test,libmCreateSelectBox(&opt,"食べ物:",Food_Test,4),Invalid,Invalid,NoAction,0);
		
		libmAddItem(&Context,Select_Test,libmCreateSpacer(&opt,NULL),Invalid,Invalid,NoAction,0);
		
		libmAddItem(&Context,Select_Test,libmCreateSpacer(&opt,"サンプル 3"),WHITE,SetAlpha(BLACK,0x80),NoAction,0);
		libmAddItem(&Context,Select_Test,libmCreateSelectBox(&opt,"PC部品:",PC_Test,3),Invalid,Invalid,NoAction,0);
	}
	
	MenuItem* Check_Test = libmAddItem(&Context,NULL,libmCreateContainer(&opt,"チェック ボックス"),RED,SetAlpha(GREEN,0x66),NoAction,0);
	{
		libmAddItem(&Context,Check_Test,libmCreateSpacer(&opt,"サンプル 1"),WHITE,SetAlpha(BLACK,0x80),NoAction,0);
		libmAddItem(&Context,Check_Test,libmCreateCheckBox(&opt,"プログラミング大好き？",false),Invalid,Invalid,NoAction,0);
		
		libmAddItem(&Context,Check_Test,libmCreateSpacer(&opt,NULL),Invalid,Invalid,NoAction,0);
		
		libmAddItem(&Context,Check_Test,libmCreateSpacer(&opt,"サンプル 2"),WHITE,SetAlpha(BLACK,0x80),NoAction,0);
		libmAddItem(&Context,Check_Test,libmCreateCheckBox(&opt,"PS2を持っている",false),Invalid,Invalid,NoAction,0);
		libmAddItem(&Context,Check_Test,libmCreateCheckBox(&opt,"PS3を持っている",false),Invalid,Invalid,NoAction,0);
	}
	
	MenuItem* UpDown_Test = libmAddItem(&Context,NULL,libmCreateContainer(&opt,"アップ・ダウン コントロール"),RED,SetAlpha(GREEN,0x66),NoAction,0);
	{
		MenuItem* msg = libmAddItem(&Context,UpDown_Test,libmCreateSpacer(&opt,"初期値、ステップ値、最小値、最大値を設定"),Invalid,Invalid,NoAction,0);
		msg->Color.Line = BLACK;
		
		libmAddItem(&Context,UpDown_Test,libmCreateSpacer(&opt,NULL),Invalid,Invalid,NoAction,0);
		
		libmAddItem(&Context,UpDown_Test,libmCreateSpacer(&opt,"サンプル 1"),WHITE,SetAlpha(BLACK,0x80),NoAction,0);
		libmAddItem(&Context,UpDown_Test,libmCreateUpDownCtrl(&opt,"年齢は？",20,1,0,150,false),Invalid,Invalid,NoAction,0);
		
		libmAddItem(&Context,UpDown_Test,libmCreateSpacer(&opt,NULL),Invalid,Invalid,NoAction,0);
		
		libmAddItem(&Context,UpDown_Test,libmCreateSpacer(&opt,"サンプル 2"),WHITE,SetAlpha(BLACK,0x80),NoAction,0);
		libmAddItem(&Context,UpDown_Test,libmCreateUpDownCtrl(&opt,"RGB(R):",100,5,0,255,true),Invalid,Invalid,NoAction,0);
		libmAddItem(&Context,UpDown_Test,libmCreateUpDownCtrl(&opt,"RGB(G):",220,5,0,255,true),Invalid,Invalid,NoAction,0);
		libmAddItem(&Context,UpDown_Test,libmCreateUpDownCtrl(&opt,"RGB(B):",20,5,0,255,true),Invalid,Invalid,NoAction,0);
	}
	
	MenuItem* Radio_Test = libmAddItem(&Context,NULL,libmCreateContainer(&opt,"ラジオ ボタン"),RED,SetAlpha(GREEN,0x66),NoAction,0);
	{
		MenuItem *group = libmCreateRadioButtonGroup(&opt);
		
		MenuItem* msg = libmAddItem(&Context,Radio_Test,libmCreateSpacer(&opt,"複数のグループも作れます、どこへでも配置OK"),Invalid,Invalid,NoAction,0);
		
		//下線色を指定して有効に
		msg->Color.Line = BLACK;
		
		libmAddItem(&Context,Radio_Test,libmCreateSpacer(&opt,NULL),Invalid,Invalid,NoAction,0);
		
		libmAddItem(&Context,Radio_Test,libmCreateSpacer(&opt,"サンプル"),WHITE,SetAlpha(BLACK,0x80),NoAction,0);
		libmAddItem(&Context,Radio_Test,libmCreateSpacer(&opt,NULL),Invalid,Invalid,NoAction,0);
		
		libmAddItem(&Context,Radio_Test,libmCreateSpacer(&opt,"PSPの所持台数は？"),WHITE,SetAlpha(BLACK,0x80),NoAction,0);
		libmAddItem(&Context,Radio_Test,libmCreateRadioButton(&opt,"1台",false,group),Invalid,Invalid,NoAction,0);
		libmAddItem(&Context,Radio_Test,libmCreateRadioButton(&opt,"2台",true,group),Invalid,Invalid,NoAction,0);
		libmAddItem(&Context,Radio_Test,libmCreateRadioButton(&opt,"3台",false,group),Invalid,Invalid,NoAction,0);
	}
	
	MenuItem* Specar_Test = libmAddItem(&Context,NULL,libmCreateContainer(&opt,"スペーサー"),RED,SetAlpha(GREEN,0x66),NoAction,0);
	{
		MenuItem* msg = libmAddItem(&Context,Specar_Test,libmCreateSpacer(&opt,"スペーサーは選択不可、文字列指定なしだと改行として使えます"),Invalid,Invalid,NoAction,0);
		msg->Color.Line = BLACK;
		
		libmAddItem(&Context,Specar_Test,libmCreateSpacer(&opt,NULL),Invalid,Invalid,NoAction,0);
		
		libmAddItem(&Context,Specar_Test,libmCreateTriggerButton(&opt,"実は　↑　のもスペーサーです^^"),Invalid,Invalid,NoAction,0);
	}
	
	
	MenuItem* Main_Test = libmAddItem(&Context,NULL,libmCreateContainer(&opt,"設定を変えて見る"),WHITE,SetAlpha(ORANGE,0x66),NoAction,0);
	{
		MenuItem* Active_Font = libmAddItem(&Context,Main_Test,libmCreateContainer(&opt,"アクティブ アイテム"),RED,SetAlpha(GREEN,0x66),NoAction,0);
		{
			libmAddItem(&Context,Active_Font,libmCreateSelectBox(&opt,"フォント色:",ColorList,8),Invalid,Invalid,ColorChange,ActiveF);
			AlphaAFA = libmAddItem(&Context,Active_Font,libmCreateUpDownCtrl(&opt,"アルファ　:",GetAlpha(Context.Color.Active_Font),2.5,0,255,false),Invalid,Invalid,AlphaChange,ActiveFA);
			
			libmAddItem(&Context,Active_Font,libmCreateSpacer(&opt,NULL),Invalid,Invalid,NoAction,0);
			
			libmAddItem(&Context,Active_Font,libmCreateSelectBox(&opt,"背景色　　:",ColorList,2),Invalid,Invalid,ColorChange,ActiveB);
			AlphaABA = libmAddItem(&Context,Active_Font,libmCreateUpDownCtrl(&opt,"アルファ　:",GetAlpha(Context.Color.Active_Back),2.5,0,255,false),Invalid,Invalid,AlphaChange,ActiveBA);
		}
		
		MenuItem* Normal_Font = libmAddItem(&Context,Main_Test,libmCreateContainer(&opt,"非アクティブ アイテム"),RED,SetAlpha(GREEN,0x66),NoAction,0);
		{
			libmAddItem(&Context,Normal_Font,libmCreateSelectBox(&opt,"フォント色:",ColorList,20),Invalid,Invalid,ColorChange,NormalF);
			AlphaNFA = libmAddItem(&Context,Normal_Font,libmCreateUpDownCtrl(&opt,"アルファ　:",GetAlpha(Context.Color.Normal_Font),2.5,0,255,false),Invalid,Invalid,AlphaChange,NormalFA);
			
			libmAddItem(&Context,Normal_Font,libmCreateSpacer(&opt,NULL),Invalid,Invalid,NoAction,0);
			
			libmAddItem(&Context,Normal_Font,libmCreateSelectBox(&opt,"背景色　　:",ColorList,17),Invalid,Invalid,ColorChange,NormalB);
			AlphaNBA = libmAddItem(&Context,Normal_Font,libmCreateUpDownCtrl(&opt,"アルファ　:",GetAlpha(Context.Color.Normal_Back),2.5,0,255,false),Invalid,Invalid,AlphaChange,NormalBA);
		}
		
		libmAddItem(&Context,Main_Test,libmCreateSpacer(&opt,NULL),Invalid,Invalid,NoAction,0);
		
		libmAddItem(&Context,Main_Test,libmCreateSpacer(&opt,"その他"),Invalid,Invalid,NoAction,0);
		
		libmAddItem(&Context,Main_Test,libmCreateUpDownCtrl(&opt,"行間:",1,1,0,2,true),Invalid,Invalid,LinesChange,0);
		libmAddItem(&Context,Main_Test,libmCreateSelectBox(&opt,"描画: ",TypeList,(Context.MenuInfo.Type?1:0)),Invalid,Invalid,TypeChange,0);
		libmAddItem(&Context,Main_Test,libmCreateCheckBox(&opt,"最上部・下部でカー\x83\x5cルを自動で反対側へ戻す",true),Invalid,Invalid,ReturnChange,0);
		libmAddItem(&Context,Main_Test,libmCreateCheckBox(&opt,"メニューを開いた時に他スレッドを停止させる",false),Invalid,Invalid,TS_Change,0);
		libmAddItem(&Context,Main_Test,libmCreateCheckBox(&opt,"背景透過（αブレンド）を有効にする",false),Invalid,Invalid,D_Alpha,0);
		libmAddItem(&Context,Main_Test,libmCreateUpDownCtrl(&opt,"ディレイ:",500,100,100,2000,true),Invalid,Invalid,DELAYChange,0);
	}
	
	sync_trigger = libmAddItem(&Context,NULL,libmCreateSpacer(&opt,"トリガーボタンに反応して、このアイテムが\x95\x5C\x8E\xA6/非\x95\x5C\x8E\xA6"),BLACK,PINK,NoAction,0);
	
	//アクティブアイテム 初期値を設定
	libmSetActive( &Context ,Select_Test);
}


//プラグイン以外の他スレッドを停止・再開させる
int libmExecTCmd( int cmd )
{
	static int thid_status = LIBM_TRESUME;
	static bool thid_IsDump = false;
	static bool this_IsBusy = false;
	
	static int thid_list_first[MAX_NUMBER_OF_THREADS];
	static int thid_count_first;
	
	static int thid_list_Current[MAX_NUMBER_OF_THREADS];
	static int thid_count_Current;
	
	if( cmd ==  LIBM_TCMD_DUMP )
	{
		thid_IsDump = sceKernelGetThreadmanIdList( SCE_KERNEL_TMID_Thread, thid_list_first, MAX_NUMBER_OF_THREADS, &thid_count_first ) >= 0;
		
		return thid_IsDump;
	}
	else if( (cmd == LIBM_TCMD_SUSPEND || cmd == LIBM_TCMD_RESUME) && thid_IsDump && cmd != thid_status && !this_IsBusy )
	{
		thid_status = cmd;
		this_IsBusy = true;
		
		int i, j;
		int (*func)(SceUID) =  ( cmd == LIBM_TCMD_SUSPEND ? sceKernelSuspendThread : sceKernelResumeThread );
		SceKernelThreadInfo thinfo;
		
		
		if( cmd == LIBM_TCMD_SUSPEND )
		{
			//停止
			
			int Current_id	= sceKernelGetThreadId();
			
			//現在のスレッドリストを作る
			if( sceKernelGetThreadmanIdList( SCE_KERNEL_TMID_Thread, thid_list_Current, MAX_NUMBER_OF_THREADS, &thid_count_Current ) < 0 )
			{
				//現在のスレッドリスト取得失敗
				this_IsBusy = false;
				return 0;
			}
			
			
			//現在のスレッド一覧と、プラグイン起動時にダンプしたセーフリストを比較
			//セーフリストと現スレッドに一致するものは対象外へ
			for( i = 0; i < thid_count_Current; i++ )
			{
				memset(&thinfo, 0, sizeof(SceKernelThreadInfo));
				thinfo.size = sizeof(SceKernelThreadInfo);
				sceKernelReferThreadStatus(thid_list_Current[i], &thinfo);
				
				if
				(
				//	( strcasecmp( "SceImpose",thinfo.name) == 0 )
				//||
					( thinfo.attr & 0x100000 ) == 0x100000
				||
					( thid_list_Current[i] == Current_id )
				)
				{
					thid_list_Current[i] = 0;
					continue;
				}
				
				for( j = 0; j < thid_count_first; j++ )
				{
					if( thid_list_Current[i] == thid_list_first[j] )
					{
						thid_list_Current[i] = 0;
						break;
					}
				}
			}
		}
		
		
		//最終的な現在のスレッドリストにあるスレッドへ停止・再開の操作
		for( i = 0; i < thid_count_Current; i++ )
		{
			if( thid_list_Current[i] ) ( func )( thid_list_Current[i] );
		}
		
		this_IsBusy = false;
		
		return 1;
	}
	else if( cmd == LIBM_TCMD_GET )
	{
		return thid_status;
	}
	
	return 0;
}



char ms_libmenu_path[] = { "ms0:/seplugins/lib/cmlibmenu.prx"};
char ef_libmenu_path[] = { "ef0:/seplugins/lib/cmlibmenu.prx"};
//------------------------------------------------------
int LoadStartModule(char *module)
{
	SceUID mod = sceKernelLoadModule(module, 0, NULL);

	if (mod < 0)
		return mod;

	return sceKernelStartModule(mod, strlen(module)+1, module, NULL, NULL);
}



int init(void)
{
	while(1)
	{
		if(sceKernelFindModuleByName("sceKernelLibrary")){
			// prxlibmenu loading Check
			if( sceKernelFindModuleByName("cmlibMenu") == NULL ) {
				// load prxlibmenu
				LoadStartModule(ms_libmenu_path);
				
				if( sceKernelFindModuleByName("cmlibMenu") == NULL ){
					// PSP Go Built-in Memory Support
					LoadStartModule(ef_libmenu_path);
				}
			}

			break;
		}
		
		sceKernelDelayThread(1000);
	}
	return 0;
}



int Callback_Suspend(int ev_id, char *ev_name, void *param, int *result)
{
	// 返り値に 0 ではなく -1 を返すと、スリープを無効化できる
	
	// スリープ時
	if( ev_id == PSP_SYSEVENT_SUSPEND_QUERY && libmExecTCmd(LIBM_TCMD_GET) == LIBM_TSUSPEND )
	{
		libmExecTCmd( LIBM_TCMD_RESUME );
		Context.IsOpen = false;
	}
	
	return 0;
}

int threadMain(SceSize args, void *argp)
{
	SceCtrlData pad;
	MenuParams* Params;
	char str[256];
	
	PspSysEventHandler events;
	
	bool StopThread		= false;
	
	SceUInt DELAY = 500;
	
	//メニュー表示中に他スレッド停止を有効にするため
	//プラグイン起動時のスレッドをダンプして安全リストを作っておく
	libmExecTCmd(LIBM_TCMD_DUMP);
	
	//他スレッド停止させたままPSPがサスペンドすると
	//フリーズの原因になるので回避するための処理
	events.size			= 0x40;
	events.name			= "MSE_Suspend";
	events.type_mask	= 0x0000FF00;
	events.handler		= Callback_Suspend;
	
	sceKernelRegisterSysEventHandler(&events);
	
	//メニュー アイテムをメモリから動的確保しない場合は
	//プラグイン起動後にディレイをおく必要はない
	
	
	//初期ロードチェック
	init();
	
	memset(&dinfo, 0, sizeof(dinfo));
	memset(&vinfo, 0, sizeof(vinfo));
	dinfo.vinfo = &vinfo;
	
	// load font
	libmLoadFont(LIBM_FONT_SJIS);
	libmLoadFont(LIBM_FONT_CG);
	libmLoadFont(LIBM_FONT_ICON);
	//libmLoadFont(LIBM_FONT_HANKAKU_KANA);
	
	//メニュー作成
	MenuCreate();
	
	
	sceCtrlSetSamplingCycle(0);
	sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);
	
	int draw_opt = 0;
	libm_vram_info vram_tmp;
	
	while( 1 )
	{
	   	sceCtrlPeekBufferPositive(&pad, 1);
		
		//Key入力を渡して、メニュー内の動作を調べる（結果を得る）
		Params = libmGetHandle(&Context, &pad);
		
		if(Params->Action == Menu_Show )
		{
			if( StopThread )
			{
				//libmGetCurVInfo(&vram_tmp);
				vram_tmp = *(dinfo.vinfo);
				
				//他スレッドをサスペンド
				while(!libmExecTCmd( LIBM_TCMD_SUSPEND ));
				
				while(!libmInitBuffers(false,PSP_DISPLAY_SETBUF_NEXTFRAME, &dinfo));
			}
		}
		else if(Params->Action == Menu_Close)
		{
			if( libmExecTCmd(LIBM_TCMD_GET) == LIBM_TSUSPEND )
			{
				sceDisplaySetFrameBuf( vram_tmp.buffer , vram_tmp.lineWidth , vram_tmp.format , PSP_DISPLAY_SETBUF_IMMEDIATE);
				sceDisplayWaitVblankStart();
				sceDisplayWaitVblankStart();
				
				//サスペンドしていた他スレッドを再開
				while(!libmExecTCmd( LIBM_TCMD_RESUME ));
			}
		}
		
		if (Params->Item)
		{
			switch (Params->Item->actionID)
			{
				//何のアイテムが選択されたかは
				//Params->Item->actionID を調べると分る
				
				//actionIDは同一にしたいけど
				//どれを選択したか判別したいときは
				//libmAddItem で Data にそれぞれ違う値を割り振る
				
				case Trigger_Push:
				{
					//アイテムの表示/非表示を切り替えるには
					//Visibile を切り替え
					sync_trigger->Visible ^= true;
				}
				
				case DELAYChange:
				{
					//Param->Item->Ctrlの後をアイテムタイプに合わせて
					//現在値や選択状況を得る
					
					DELAY = (SceUInt)Params->Item->Ctrl.UD.Now;
				}
				break;
				
				case TS_Change:
				{
					StopThread = Params->Item->Ctrl.CB_Checked;
				}
				break;
				
				case D_Alpha:
				{
					draw_opt = Params->Item->Ctrl.CB_Checked ? LIBM_DRAW_BLEND : 0;
				}
				break;
				
				case TypeChange:
				{
					Context.MenuInfo.Type = Params->Item->Ctrl.SB.Index;
				}
				break;
				
				case ColorChange:
				{
					if(Params->Item->Data == ActiveF)
					{
						Context.Color.Active_Font = color[Params->Item->Ctrl.SB.Index];
					}
					else if(Params->Item->Data == ActiveB)
					{
						Context.Color.Active_Back = color[Params->Item->Ctrl.SB.Index];
					}
					else if(Params->Item->Data == NormalF)
					{
						Context.Color.Normal_Font = color[Params->Item->Ctrl.SB.Index];
					}
					else if(Params->Item->Data == NormalB)
					{
						Context.Color.Normal_Back = color[Params->Item->Ctrl.SB.Index];
					}
				}
				break;
				
				case ReturnChange:
				{
					Context.MenuInfo.AutoReturn = Params->Item->Ctrl.CB_Checked;
				}
				break;
				
				case LinesChange:
				{
					Context.MenuInfo.Lines =  (int)Params->Item->Ctrl.UD.Now;
				}
				break;
			}
			
			if(Context.Color.Active_Font != LIBM_NO_DRAW)
				Context.Color.Active_Font =  SetAlpha(Context.Color.Active_Font,((int)AlphaAFA->Ctrl.UD.Now));
			
			if(Context.Color.Active_Back != LIBM_NO_DRAW)
				Context.Color.Active_Back =  SetAlpha(Context.Color.Active_Back,((int)AlphaABA->Ctrl.UD.Now));
			
			if(Context.Color.Normal_Font != LIBM_NO_DRAW)
				Context.Color.Normal_Font =  SetAlpha(Context.Color.Normal_Font,((int)AlphaNFA->Ctrl.UD.Now));
			
			if(Context.Color.Normal_Back != LIBM_NO_DRAW)
				Context.Color.Normal_Back =  SetAlpha(Context.Color.Normal_Back,((int)AlphaNBA->Ctrl.UD.Now));
		}
		
		if( libmExecTCmd(LIBM_TCMD_GET) == LIBM_TSUSPEND )
		{
			//Homeメニュー表示出来るように
			if( (pad.Buttons & PSP_CTRL_HOME) == PSP_CTRL_HOME  )
			{
				while(!libmExecTCmd( LIBM_TCMD_RESUME ));
				
				Context.IsOpen = false;
			}
			else
			{
				libmClearBuffers(&dinfo);
				libmRender(&Context,20,20,str,256, &dinfo);
				libmSwapBuffers(&dinfo);
			}
		}
		else if( libmInitBuffers(draw_opt,PSP_DISPLAY_SETBUF_NEXTFRAME, &dinfo) )
		{
			//通常のメニュー描画
			
			libmRender(&Context,22,20,str,256, &dinfo);
			
			if( libmIsOpen(&Context) )
			{
				libmPrintXY16(0,256,SetAlpha(WHITE,0xFF),SetAlpha(BLACK,0xFF),"×=選択、△=戻る", &dinfo);
				libmPrintSymbolXY16(4, 220, 0xffff0000, 0xff00ff00, 0xff0000ff, 0, "\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f", &dinfo);
				
				/*
				// 4
				libmPrintSymbolXY(50, 220, 0xffffffff, 0xff00ff00, 0xff00ff00, SetAlpha(BLACK,0xFF), "\x01\x02", &dinfo);
				
				// 3
				libmPrintSymbolXY(70, 220, 0xffffffff, 0xff000000, 0xff00ff80, SetAlpha(BLACK,0xFF), "\x01", &dinfo);
				libmPrintSymbolXY(78, 220, 0xffffffff, 0xff00ff80, 0xff00ff80, SetAlpha(BLACK,0xFF), "\x02", &dinfo);
				
				// 2
				libmPrintSymbolXY(90, 220, 0xffffffff, 0xff000000, 0xff000000, SetAlpha(BLACK,0xFF), "\x01", &dinfo);
				libmPrintSymbolXY(98, 220, 0xffffffff, 0xff00ffff, 0xff00ffff, SetAlpha(BLACK,0xFF), "\x02", &dinfo);
				
				// 1
				libmPrintSymbolXY(110, 220, 0xffffffff, 0xff000000, 0xff000000, SetAlpha(BLACK,0xFF), "\x01", &dinfo);
				libmPrintSymbolXY(118, 220, 0xffffffff, 0xff000000, 0xff0080ff, SetAlpha(BLACK,0xFF), "\x02", &dinfo);
				
				// 0
				libmPrintSymbolXY(130, 220, 0xff0000ff, 0xff000000, 0xff000000, SetAlpha(BLACK,0xFF), "\x01\x02", &dinfo);
				
				
				// 4
				libmPrintSymbolXY16(50, 230, 0xffffffff, 0xff00ff00, 0xff00ff00, SetAlpha(BLACK,0xFF), "\x01\x02", &dinfo);
				
				// 3
				libmPrintSymbolXY16(90, 230, 0xffffffff, 0xff000000, 0xff00ff80, SetAlpha(BLACK,0xFF), "\x01", &dinfo);
				libmPrintSymbolXY16(106, 230, 0xffffffff, 0xff00ff80, 0xff00ff80, SetAlpha(BLACK,0xFF), "\x02", &dinfo);
				
				// 2
				libmPrintSymbolXY16(130, 230, 0xffffffff, 0xff000000, 0xff000000, SetAlpha(BLACK,0xFF), "\x01", &dinfo);
				libmPrintSymbolXY16(146, 230, 0xffffffff, 0xff00ffff, 0xff00ffff, SetAlpha(BLACK,0xFF), "\x02", &dinfo);
				
				// 1
				libmPrintSymbolXY16(170, 230, 0xffffffff, 0xff000000, 0xff000000, SetAlpha(BLACK,0xFF), "\x01", &dinfo);
				libmPrintSymbolXY16(186, 230, 0xffffffff, 0xff000000, 0xff0080ff, SetAlpha(BLACK,0xFF), "\x02", &dinfo);
				
				// 0
				libmPrintSymbolXY16(210, 230, 0xff0000ff, 0xff000000, 0xff000000, SetAlpha(BLACK,0xFF), "\x01\x02", &dinfo);
				*/
			}
			
			sceDisplayWaitVblankStart();
		}
		
		sceKernelDelayThread( 1000 );
	}
	
	return sceKernelExitDeleteThread( 0 );
}



int module_start(SceSize args, void *argp)
{
	//メインスレッドのスタックサイズをアイテムリストの変数サイズ分 増やしておく必要がある
    SceUID main_thid = sceKernelCreateThread("MenuTest_Main", threadMain, 16,0x1500, 0, NULL);
	
    if(main_thid >= 0) sceKernelStartThread(main_thid, args, argp);
	
    return 0;
}

int module_stop(SceSize args, void *argp)
{
    return 0;
}
