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
	LIBM_TCMD_SUSPEND	,	//���X���b�h���~
	LIBM_TCMD_RESUME	,	//���X���b�h���ĊJ
	LIBM_TCMD_DUMP		,	//���X���b�h���~�E�ĊJ������ׂ̃Z�[�t���X�g�����
	LIBM_TCMD_GET		,	//���X���b�h�̒�~�E�ĊJ��Ԃ��擾
};

#define	ITEM_COUNT					66
#define	LIBM_TSUSPEND				LIBM_TCMD_SUSPEND
#define	LIBM_TRESUME				LIBM_TCMD_RESUME

#define MAX_NUMBER_OF_THREADS 		64

#define	PSP_SYSEVENT_SUSPEND_QUERY	0x100


PSP_MODULE_INFO("MenuTest", PSP_MODULE_KERNEL, 1, 1);


/*
//���j���[�쐬�ɕK�v�� context�Aitem��p�ӂ����
//�Q�[���N���Ɠ����Ƀ��������瓮�I�m�ۂ��悤�Ƃ����
//���ꂪ�����ŃQ�[�����ُ�I�����Ă��܂����Ƃ�����

//���̃G���[�̓������m�ۂ��Q�[���N���O�ɍs��ꂽ��
//�{���Q�[�������g�p����͂��̃���������m�ۂ��Ă��܂���
//�����ԋp���Ȃ����Ƃ������ŋN����

//������������ɂ͊��S�ɃQ�[�����N�����Ă��烁�����𓮓I�m�ۂ���悤��
//�K���ȃf�B���C������̂��ȒP�ȕ��@����
//���ꂾ�ƃQ�[���N������Ƀ��j���[�\�����邱�Ƃ��o���Ȃ��d�l�ɂȂ�

//�����Ńv���O�C���̃X�^�b�N��ɏ�u������悤�ɂ����
//���̖�������o���ăQ�[���N�����ォ�烁�j���[�\�����\
*/

//�v���O�C�� �X�^�b�N��ɃA�C�e���ϐ�����u������
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
	"�_�C�E�n�[�h",
	"�A���}�Q�h��",
	"�}�g���b�N�X",
	"�G�C���A��",
	"�S�[�X�g�E�o�X�^�[�Y",
	NULL
};
		
const char *Food_Test[] =
{
	"���[����",
	"���g��",
	"��₵����",
	"�H�p��",
	"����",
	"�L���`",
	"�����i",
	NULL
};
		
const char *PC_Test[] =
{
	"���j�^�[",
	"�P�[�X",
	"�n�[�h�E�f�B�X�N",
	"������",
	"�}�U�[�E�{�[�h",
	"�}�E�X",
	"CPU",
	"�O���t�B�b�N�E�J�[�h",
	"�v�����^�[",
	NULL
};
		
const char *TypeList[] =
{
	"���j���[�S��",
	"�A�N�e�B�u�ȍ��ڂ̂�",
	NULL
};
		
const char *ColorList[] =
{
	"�Ȃ�",
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
	//���j���[ �A�C�e�������������瓮�I�m�ۂ��Ȃ��ݒ�ɂ���
	memset(&opt,0,sizeof(opt));
	opt.type		= LIBM_OPT_LIST;
	opt.list.val	= item_list;
	opt.list.size 	= sizeof(item_list);
	
	libmSetOpt(&Context,&opt);
	
	//���j���[����p�̊ePad�ݒ�
		
	//�\�� + & -
	Context.HotKey.Show				= PSP_CTRL_VOLUP | PSP_CTRL_VOLDOWN;
	//�߂� ��
	Context.HotKey.Back				= PSP_CTRL_TRIANGLE;
	//�I�� �~
	Context.HotKey.Select			= PSP_CTRL_CROSS;
	//��� ��
	Context.HotKey.Up				= PSP_CTRL_UP;
	//���� ��
	Context.HotKey.Down				= PSP_CTRL_DOWN;
	//���� ��
	Context.HotKey.Left				= PSP_CTRL_LEFT;
	//�E��
	Context.HotKey.Right			= PSP_CTRL_RIGHT;
	
	//���j���[�^�C�v�́u�S�̕\���v
	Context.MenuInfo.Type 			= LIBM_VIEW_ALL;
	//�A�C�e�����ŏ㕔�E�����֗����玩���Ń^�[��������
	Context.MenuInfo.AutoReturn		= true;
		
	//�A�N�e�B�u�ȍ��ڂ̃t�H���g�F�A�w�i�F
	Context.Color.Active_Font		= PINK;
	Context.Color.Active_Back		= SetAlpha(BLUE,0x82);
		
	//��A�N�e�B�u�ȍ��ڂ̃t�H���g�F�A�w�i�F
	Context.Color.Normal_Font		= WHITE;
	Context.Color.Normal_Back		= SetAlpha(GRAY,0x64);
		
	//�s��
	Context.MenuInfo.Lines			= 1;
	
	libmAddItem(&Context,NULL,libmCreateSpacer(&opt, "���j���[ �T���v��"),YELLOGREEN,DARKGREEN,NoAction,0);
	
	libmAddItem(&Context,NULL,libmCreateTriggerButton(&opt,"�g���K�[�{�^��"),RED,SetAlpha(GREEN,0x66),Trigger_Push,0);
	
	MenuItem* Select_Test = libmAddItem(&Context,NULL,libmCreateContainer(&opt,"�Z���N�g �{�b�N�X"),RED,SetAlpha(GREEN,0x66),NoAction,0);
	{
		MenuItem* msg = libmAddItem(&Context,Select_Test,libmCreateSpacer(&opt,"�������I���ςݍ��ڂ̎w�肪\x89\xC2\x94\x5C�ł�"),Invalid,Invalid,NoAction,0);
		msg->Color.Line = BLACK;
		
		libmAddItem(&Context,Select_Test,libmCreateSpacer(&opt,NULL),Invalid,Invalid,NoAction,0);
		
		libmAddItem(&Context,Select_Test,libmCreateSpacer(&opt,"�T���v�� 1"),WHITE,SetAlpha(BLACK,0x80),NoAction,0);
		libmAddItem(&Context,Select_Test,libmCreateSelectBox(&opt,"�f��:",Movie_Test,2),Invalid,Invalid,NoAction,0);
		
		libmAddItem(&Context,Select_Test,libmCreateSpacer(&opt,NULL),Invalid,Invalid,NoAction,0);
		
		libmAddItem(&Context,Select_Test,libmCreateSpacer(&opt,"�T���v�� 2"),WHITE,SetAlpha(BLACK,0x80),NoAction,0);
		libmAddItem(&Context,Select_Test,libmCreateSelectBox(&opt,"�H�ו�:",Food_Test,4),Invalid,Invalid,NoAction,0);
		
		libmAddItem(&Context,Select_Test,libmCreateSpacer(&opt,NULL),Invalid,Invalid,NoAction,0);
		
		libmAddItem(&Context,Select_Test,libmCreateSpacer(&opt,"�T���v�� 3"),WHITE,SetAlpha(BLACK,0x80),NoAction,0);
		libmAddItem(&Context,Select_Test,libmCreateSelectBox(&opt,"PC���i:",PC_Test,3),Invalid,Invalid,NoAction,0);
	}
	
	MenuItem* Check_Test = libmAddItem(&Context,NULL,libmCreateContainer(&opt,"�`�F�b�N �{�b�N�X"),RED,SetAlpha(GREEN,0x66),NoAction,0);
	{
		libmAddItem(&Context,Check_Test,libmCreateSpacer(&opt,"�T���v�� 1"),WHITE,SetAlpha(BLACK,0x80),NoAction,0);
		libmAddItem(&Context,Check_Test,libmCreateCheckBox(&opt,"�v���O���~���O��D���H",false),Invalid,Invalid,NoAction,0);
		
		libmAddItem(&Context,Check_Test,libmCreateSpacer(&opt,NULL),Invalid,Invalid,NoAction,0);
		
		libmAddItem(&Context,Check_Test,libmCreateSpacer(&opt,"�T���v�� 2"),WHITE,SetAlpha(BLACK,0x80),NoAction,0);
		libmAddItem(&Context,Check_Test,libmCreateCheckBox(&opt,"PS2�������Ă���",false),Invalid,Invalid,NoAction,0);
		libmAddItem(&Context,Check_Test,libmCreateCheckBox(&opt,"PS3�������Ă���",false),Invalid,Invalid,NoAction,0);
	}
	
	MenuItem* UpDown_Test = libmAddItem(&Context,NULL,libmCreateContainer(&opt,"�A�b�v�E�_�E�� �R���g���[��"),RED,SetAlpha(GREEN,0x66),NoAction,0);
	{
		MenuItem* msg = libmAddItem(&Context,UpDown_Test,libmCreateSpacer(&opt,"�����l�A�X�e�b�v�l�A�ŏ��l�A�ő�l��ݒ�"),Invalid,Invalid,NoAction,0);
		msg->Color.Line = BLACK;
		
		libmAddItem(&Context,UpDown_Test,libmCreateSpacer(&opt,NULL),Invalid,Invalid,NoAction,0);
		
		libmAddItem(&Context,UpDown_Test,libmCreateSpacer(&opt,"�T���v�� 1"),WHITE,SetAlpha(BLACK,0x80),NoAction,0);
		libmAddItem(&Context,UpDown_Test,libmCreateUpDownCtrl(&opt,"�N��́H",20,1,0,150,false),Invalid,Invalid,NoAction,0);
		
		libmAddItem(&Context,UpDown_Test,libmCreateSpacer(&opt,NULL),Invalid,Invalid,NoAction,0);
		
		libmAddItem(&Context,UpDown_Test,libmCreateSpacer(&opt,"�T���v�� 2"),WHITE,SetAlpha(BLACK,0x80),NoAction,0);
		libmAddItem(&Context,UpDown_Test,libmCreateUpDownCtrl(&opt,"RGB(R):",100,5,0,255,true),Invalid,Invalid,NoAction,0);
		libmAddItem(&Context,UpDown_Test,libmCreateUpDownCtrl(&opt,"RGB(G):",220,5,0,255,true),Invalid,Invalid,NoAction,0);
		libmAddItem(&Context,UpDown_Test,libmCreateUpDownCtrl(&opt,"RGB(B):",20,5,0,255,true),Invalid,Invalid,NoAction,0);
	}
	
	MenuItem* Radio_Test = libmAddItem(&Context,NULL,libmCreateContainer(&opt,"���W�I �{�^��"),RED,SetAlpha(GREEN,0x66),NoAction,0);
	{
		MenuItem *group = libmCreateRadioButtonGroup(&opt);
		
		MenuItem* msg = libmAddItem(&Context,Radio_Test,libmCreateSpacer(&opt,"�����̃O���[�v�����܂��A�ǂ��ւł��z�uOK"),Invalid,Invalid,NoAction,0);
		
		//�����F���w�肵�ėL����
		msg->Color.Line = BLACK;
		
		libmAddItem(&Context,Radio_Test,libmCreateSpacer(&opt,NULL),Invalid,Invalid,NoAction,0);
		
		libmAddItem(&Context,Radio_Test,libmCreateSpacer(&opt,"�T���v��"),WHITE,SetAlpha(BLACK,0x80),NoAction,0);
		libmAddItem(&Context,Radio_Test,libmCreateSpacer(&opt,NULL),Invalid,Invalid,NoAction,0);
		
		libmAddItem(&Context,Radio_Test,libmCreateSpacer(&opt,"PSP�̏����䐔�́H"),WHITE,SetAlpha(BLACK,0x80),NoAction,0);
		libmAddItem(&Context,Radio_Test,libmCreateRadioButton(&opt,"1��",false,group),Invalid,Invalid,NoAction,0);
		libmAddItem(&Context,Radio_Test,libmCreateRadioButton(&opt,"2��",true,group),Invalid,Invalid,NoAction,0);
		libmAddItem(&Context,Radio_Test,libmCreateRadioButton(&opt,"3��",false,group),Invalid,Invalid,NoAction,0);
	}
	
	MenuItem* Specar_Test = libmAddItem(&Context,NULL,libmCreateContainer(&opt,"�X�y�[�T�["),RED,SetAlpha(GREEN,0x66),NoAction,0);
	{
		MenuItem* msg = libmAddItem(&Context,Specar_Test,libmCreateSpacer(&opt,"�X�y�[�T�[�͑I��s�A������w��Ȃ����Ɖ��s�Ƃ��Ďg���܂�"),Invalid,Invalid,NoAction,0);
		msg->Color.Line = BLACK;
		
		libmAddItem(&Context,Specar_Test,libmCreateSpacer(&opt,NULL),Invalid,Invalid,NoAction,0);
		
		libmAddItem(&Context,Specar_Test,libmCreateTriggerButton(&opt,"���́@���@�̂��X�y�[�T�[�ł�^^"),Invalid,Invalid,NoAction,0);
	}
	
	
	MenuItem* Main_Test = libmAddItem(&Context,NULL,libmCreateContainer(&opt,"�ݒ��ς��Č���"),WHITE,SetAlpha(ORANGE,0x66),NoAction,0);
	{
		MenuItem* Active_Font = libmAddItem(&Context,Main_Test,libmCreateContainer(&opt,"�A�N�e�B�u �A�C�e��"),RED,SetAlpha(GREEN,0x66),NoAction,0);
		{
			libmAddItem(&Context,Active_Font,libmCreateSelectBox(&opt,"�t�H���g�F:",ColorList,8),Invalid,Invalid,ColorChange,ActiveF);
			AlphaAFA = libmAddItem(&Context,Active_Font,libmCreateUpDownCtrl(&opt,"�A���t�@�@:",GetAlpha(Context.Color.Active_Font),2.5,0,255,false),Invalid,Invalid,AlphaChange,ActiveFA);
			
			libmAddItem(&Context,Active_Font,libmCreateSpacer(&opt,NULL),Invalid,Invalid,NoAction,0);
			
			libmAddItem(&Context,Active_Font,libmCreateSelectBox(&opt,"�w�i�F�@�@:",ColorList,2),Invalid,Invalid,ColorChange,ActiveB);
			AlphaABA = libmAddItem(&Context,Active_Font,libmCreateUpDownCtrl(&opt,"�A���t�@�@:",GetAlpha(Context.Color.Active_Back),2.5,0,255,false),Invalid,Invalid,AlphaChange,ActiveBA);
		}
		
		MenuItem* Normal_Font = libmAddItem(&Context,Main_Test,libmCreateContainer(&opt,"��A�N�e�B�u �A�C�e��"),RED,SetAlpha(GREEN,0x66),NoAction,0);
		{
			libmAddItem(&Context,Normal_Font,libmCreateSelectBox(&opt,"�t�H���g�F:",ColorList,20),Invalid,Invalid,ColorChange,NormalF);
			AlphaNFA = libmAddItem(&Context,Normal_Font,libmCreateUpDownCtrl(&opt,"�A���t�@�@:",GetAlpha(Context.Color.Normal_Font),2.5,0,255,false),Invalid,Invalid,AlphaChange,NormalFA);
			
			libmAddItem(&Context,Normal_Font,libmCreateSpacer(&opt,NULL),Invalid,Invalid,NoAction,0);
			
			libmAddItem(&Context,Normal_Font,libmCreateSelectBox(&opt,"�w�i�F�@�@:",ColorList,17),Invalid,Invalid,ColorChange,NormalB);
			AlphaNBA = libmAddItem(&Context,Normal_Font,libmCreateUpDownCtrl(&opt,"�A���t�@�@:",GetAlpha(Context.Color.Normal_Back),2.5,0,255,false),Invalid,Invalid,AlphaChange,NormalBA);
		}
		
		libmAddItem(&Context,Main_Test,libmCreateSpacer(&opt,NULL),Invalid,Invalid,NoAction,0);
		
		libmAddItem(&Context,Main_Test,libmCreateSpacer(&opt,"���̑�"),Invalid,Invalid,NoAction,0);
		
		libmAddItem(&Context,Main_Test,libmCreateUpDownCtrl(&opt,"�s��:",1,1,0,2,true),Invalid,Invalid,LinesChange,0);
		libmAddItem(&Context,Main_Test,libmCreateSelectBox(&opt,"�`��: ",TypeList,(Context.MenuInfo.Type?1:0)),Invalid,Invalid,TypeChange,0);
		libmAddItem(&Context,Main_Test,libmCreateCheckBox(&opt,"�ŏ㕔�E�����ŃJ�[\x83\x5c���������Ŕ��Α��֖߂�",true),Invalid,Invalid,ReturnChange,0);
		libmAddItem(&Context,Main_Test,libmCreateCheckBox(&opt,"���j���[���J�������ɑ��X���b�h���~������",false),Invalid,Invalid,TS_Change,0);
		libmAddItem(&Context,Main_Test,libmCreateCheckBox(&opt,"�w�i���߁i���u�����h�j��L���ɂ���",false),Invalid,Invalid,D_Alpha,0);
		libmAddItem(&Context,Main_Test,libmCreateUpDownCtrl(&opt,"�f�B���C:",500,100,100,2000,true),Invalid,Invalid,DELAYChange,0);
	}
	
	sync_trigger = libmAddItem(&Context,NULL,libmCreateSpacer(&opt,"�g���K�[�{�^���ɔ������āA���̃A�C�e����\x95\x5C\x8E\xA6/��\x95\x5C\x8E\xA6"),BLACK,PINK,NoAction,0);
	
	//�A�N�e�B�u�A�C�e�� �����l��ݒ�
	libmSetActive( &Context ,Select_Test);
}


//�v���O�C���ȊO�̑��X���b�h���~�E�ĊJ������
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
			//��~
			
			int Current_id	= sceKernelGetThreadId();
			
			//���݂̃X���b�h���X�g�����
			if( sceKernelGetThreadmanIdList( SCE_KERNEL_TMID_Thread, thid_list_Current, MAX_NUMBER_OF_THREADS, &thid_count_Current ) < 0 )
			{
				//���݂̃X���b�h���X�g�擾���s
				this_IsBusy = false;
				return 0;
			}
			
			
			//���݂̃X���b�h�ꗗ�ƁA�v���O�C���N�����Ƀ_���v�����Z�[�t���X�g���r
			//�Z�[�t���X�g�ƌ��X���b�h�Ɉ�v������̂͑ΏۊO��
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
		
		
		//�ŏI�I�Ȍ��݂̃X���b�h���X�g�ɂ���X���b�h�֒�~�E�ĊJ�̑���
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
	// �Ԃ�l�� 0 �ł͂Ȃ� -1 ��Ԃ��ƁA�X���[�v�𖳌����ł���
	
	// �X���[�v��
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
	
	//���j���[�\�����ɑ��X���b�h��~��L���ɂ��邽��
	//�v���O�C���N�����̃X���b�h���_���v���Ĉ��S���X�g������Ă���
	libmExecTCmd(LIBM_TCMD_DUMP);
	
	//���X���b�h��~�������܂�PSP���T�X�y���h�����
	//�t���[�Y�̌����ɂȂ�̂ŉ�����邽�߂̏���
	events.size			= 0x40;
	events.name			= "MSE_Suspend";
	events.type_mask	= 0x0000FF00;
	events.handler		= Callback_Suspend;
	
	sceKernelRegisterSysEventHandler(&events);
	
	//���j���[ �A�C�e�������������瓮�I�m�ۂ��Ȃ��ꍇ��
	//�v���O�C���N����Ƀf�B���C�������K�v�͂Ȃ�
	
	
	//�������[�h�`�F�b�N
	init();
	
	memset(&dinfo, 0, sizeof(dinfo));
	memset(&vinfo, 0, sizeof(vinfo));
	dinfo.vinfo = &vinfo;
	
	// load font
	libmLoadFont(LIBM_FONT_SJIS);
	libmLoadFont(LIBM_FONT_CG);
	libmLoadFont(LIBM_FONT_ICON);
	//libmLoadFont(LIBM_FONT_HANKAKU_KANA);
	
	//���j���[�쐬
	MenuCreate();
	
	
	sceCtrlSetSamplingCycle(0);
	sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);
	
	int draw_opt = 0;
	libm_vram_info vram_tmp;
	
	while( 1 )
	{
	   	sceCtrlPeekBufferPositive(&pad, 1);
		
		//Key���͂�n���āA���j���[���̓���𒲂ׂ�i���ʂ𓾂�j
		Params = libmGetHandle(&Context, &pad);
		
		if(Params->Action == Menu_Show )
		{
			if( StopThread )
			{
				//libmGetCurVInfo(&vram_tmp);
				vram_tmp = *(dinfo.vinfo);
				
				//���X���b�h���T�X�y���h
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
				
				//�T�X�y���h���Ă������X���b�h���ĊJ
				while(!libmExecTCmd( LIBM_TCMD_RESUME ));
			}
		}
		
		if (Params->Item)
		{
			switch (Params->Item->actionID)
			{
				//���̃A�C�e�����I�����ꂽ����
				//Params->Item->actionID �𒲂ׂ�ƕ���
				
				//actionID�͓���ɂ���������
				//�ǂ��I�����������ʂ������Ƃ���
				//libmAddItem �� Data �ɂ��ꂼ��Ⴄ�l������U��
				
				case Trigger_Push:
				{
					//�A�C�e���̕\��/��\����؂�ւ���ɂ�
					//Visibile ��؂�ւ�
					sync_trigger->Visible ^= true;
				}
				
				case DELAYChange:
				{
					//Param->Item->Ctrl�̌���A�C�e���^�C�v�ɍ��킹��
					//���ݒl��I���󋵂𓾂�
					
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
			//Home���j���[�\���o����悤��
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
			//�ʏ�̃��j���[�`��
			
			libmRender(&Context,22,20,str,256, &dinfo);
			
			if( libmIsOpen(&Context) )
			{
				libmPrintXY16(0,256,SetAlpha(WHITE,0xFF),SetAlpha(BLACK,0xFF),"�~=�I���A��=�߂�", &dinfo);
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
	//���C���X���b�h�̃X�^�b�N�T�C�Y���A�C�e�����X�g�̕ϐ��T�C�Y�� ���₵�Ă����K�v������
    SceUID main_thid = sceKernelCreateThread("MenuTest_Main", threadMain, 16,0x1500, 0, NULL);
	
    if(main_thid >= 0) sceKernelStartThread(main_thid, args, argp);
	
    return 0;
}

int module_stop(SceSize args, void *argp)
{
    return 0;
}
