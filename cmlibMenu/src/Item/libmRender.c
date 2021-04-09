#include "common.h"


/* PSPボタン文字 */
#ifdef LNGJPN
	#define PB_SYM_PSP_UP			"↑"
	#define PB_SYM_PSP_RIGHT		"→"
	#define PB_SYM_PSP_DOWN			"↓"
	#define PB_SYM_PSP_LEFT			"←"
	#define PB_SYM_PSP_TRIANGLE		"△"
	#define PB_SYM_PSP_CIRCLE		"○"
	#define PB_SYM_PSP_CROSS		"×"
	#define PB_SYM_PSP_SQUARE		"□"
	#define PB_SYM_PSP_NOTE			"♪"
#else
	#define PB_SYM_PSP_UP			"\x80"
	#define PB_SYM_PSP_RIGHT		"\x81"
	#define PB_SYM_PSP_DOWN			"\x82"
	#define PB_SYM_PSP_LEFT			"\x83"
	#define PB_SYM_PSP_TRIANGLE		"\x84"
	#define PB_SYM_PSP_CIRCLE		"\x85"
	#define PB_SYM_PSP_CROSS		"\x86"
	#define PB_SYM_PSP_SQUARE		"\x87"
	#define PB_SYM_PSP_NOTE			"\x88"
#endif


void libmRender(MenuContext* Context,int PosX,int PosY ,char *buf ,int bufLen, libm_draw_info *dinfo)
{
	if (Context && Context->IsOpen && Context->Root && dinfo->vinfo->buffer && dinfo->vinfo->lineWidth )
	{
		u32 bg_color,font_color;
		
		int len ,x=0, y=0 , depth = 0 ,row = 0;
		
		MenuItem* Curr;
		
		
		if( Context->MenuInfo.Type == LIBM_VIEW_ALL )
		{
			Curr = Context->Root;
		}
		else
		{
			Curr = ( Context->Active->Parent ? Context->Active->Parent->Children : Context->Root );
		}
		
		while( Curr )
		{
			len = 0;
			x = PosX + ((depth * 4) * LIBM_CHAR_WIDTH) ;
			y = PosY + (row  * (LIBM_CHAR_HEIGHT + Context->MenuInfo.Lines));
			
			//描画対象がアクティブなアイテムかどうかで
			//フォントと背景の色を変える
			
			//アイテム描画色の優先順位
			//アクティブ(Context)>アイテム>ノーマル(Context)
			
			if( Curr == Context->Active )
			{
				//アクティブ、各色はシステム色
				font_color	= Context->Color.Active_Font;
				bg_color	= Context->Color.Active_Back;
			}
			else
			{
				//アクティブではない
				
				if( Curr->Disable )
				{
					//無効なアイテム、システムの無効アイテム色
					
					font_color	= Context->Color.Disable_Font;
					bg_color	= Context->Color.Disable_Back;
				}
				else
				{
					//フォント色、背景色は現アイテム指定があればその色
					//指定がなければシステム色のノーマルカラー
					
					font_color	= ( Curr->Color.Font != LIBM_NO_DRAW ? Curr->Color.Font : Context->Color.Normal_Font );
					bg_color	= ( Curr->Color.Back != LIBM_NO_DRAW ? Curr->Color.Back : Context->Color.Normal_Back );
				}
			}
			
			
			//可視状態のアイテムのみ描画
			if( Curr->Visible )
			{
				switch ( Curr->Type )
				{
					case RadioButton:
					{
						len = libmPrintfXY( x , y  , font_color, bg_color,buf,bufLen, dinfo, "(%s)%s",((Curr->Ctrl.RB_Group && (Curr->Ctrl.RB_Group)->Ctrl.Group_Sel == Curr) ? "*" : " "), Curr->Name);
					}
					break;
					
					case CheckBox:
					{
						len = libmPrintfXY( x , y  , font_color, bg_color,buf,bufLen, dinfo, "[%s]%s",Curr->Ctrl.CB_Checked ? "X" : " ", Curr->Name);
					}
					break;
					
					case MenuContainer:
					{
						bool flag = false;
						
						if(Curr->Ctrl.CNT.Disp == NULL)
						{
							len = libmPrintfXY( x,y, font_color, bg_color,buf,bufLen, dinfo, "%s%s",Curr->Ctrl.CNT.IsOpen ? "-" : "+", Curr->Name);
						}
						else
						{
							if(Curr->Ctrl.CNT.Disp->Type == RadioButton)
							{
								if(Curr->Ctrl.CNT.Disp->Ctrl.RB_Group && (Curr->Ctrl.CNT.Disp->Ctrl.RB_Group)->Ctrl.Group_Sel->Visible)
								{
									len = libmPrintfXY( x,y, font_color, bg_color,buf,bufLen, dinfo, "%s%s:\"%s\"",Curr->Ctrl.CNT.IsOpen ? "-" : "+", Curr->Name,(Curr->Ctrl.CNT.Disp->Ctrl.RB_Group)->Ctrl.Group_Sel->Name);
								}
								else
								{
									flag = true;
								}
							}
							else if(Curr->Ctrl.CNT.Disp->Type == SelectBox)
							{
								if(Curr->Ctrl.CNT.Disp->Visible)
								{
									len = libmPrintfXY( x,y, font_color, bg_color,buf,bufLen, dinfo, "%s%s:\"%s\"",Curr->Ctrl.CNT.IsOpen ? "-" : "+", Curr->Name,Curr->Ctrl.CNT.Disp->Ctrl.SB.List[Curr->Ctrl.CNT.Disp->Ctrl.SB.Index]);
								}
								else
								{
									flag = true;
								}
							}
							else if(Curr->Ctrl.CNT.Disp->Type == CheckBox)
							{
								if(Curr->Ctrl.CNT.Disp->Visible)
								{
									len = libmPrintfXY( x,y, font_color, bg_color,buf,bufLen, dinfo, "%s%s:[%s]",Curr->Ctrl.CNT.IsOpen ? "-" : "+", Curr->Name,Curr->Ctrl.CNT.Disp->Ctrl.CB_Checked ? "X" : " ");
								}
								else
								{
									flag = true;
								}
							}
							else if(Curr->Ctrl.CNT.Disp->Type == UpDownCtrl)
							{
								if(Curr->Ctrl.CNT.Disp->Visible)
								{
									if(!Curr->Ctrl.CNT.Disp->Ctrl.UD.type)
									{
										len = libmPrintfXY( x,y, font_color, bg_color,buf,bufLen, dinfo, "%s%s:%d.%d",Curr->Ctrl.CNT.IsOpen ? "-" : "+", Curr->Name,(int)Curr->Ctrl.CNT.Disp->Ctrl.UD.Now,(int)((Curr->Ctrl.CNT.Disp->Ctrl.UD.Now*100)-(((int)Curr->Ctrl.CNT.Disp->Ctrl.UD.Now)*100)));
									}
									else
									{
										len = libmPrintfXY( x,y, font_color, bg_color,buf,bufLen, dinfo, "%s%s:%d",Curr->Ctrl.CNT.IsOpen ? "-" : "+", Curr->Name,(int)Curr->Ctrl.CNT.Disp->Ctrl.UD.Now);
									}
								}
								else
								{
									flag = true;
								}
							}
							
							//関連づけられているアイテムが無効な状態だった、通常表示
							if(flag)	len = libmPrintfXY( x,y, font_color, bg_color,buf,bufLen, dinfo, "%s%s",Curr->Ctrl.CNT.IsOpen ? "-" : "+", Curr->Name);
						}
					}
					break;
					
					case SelectBox:
					{
						len = libmPrintfXY( x, y  , font_color, bg_color,buf,bufLen, dinfo, "%s<%s[%s]%s>",
										Curr->Name ? Curr->Name : "",
										(Curr->Ctrl.SB.Index > 0 ? PB_SYM_PSP_LEFT : " "),
										Curr->Ctrl.SB.List[Curr->Ctrl.SB.Index],
										(Curr->Ctrl.SB.List[Curr->Ctrl.SB.Index+1] != NULL ? PB_SYM_PSP_RIGHT : " ")
										);
					}
					break;
					
					case UpDownCtrl:
					{
						if(!Curr->Ctrl.UD.type)
						{
							len = libmPrintfXY( x, y  , font_color, bg_color,buf,bufLen, dinfo, "%s<-[%d.%d]+>",Curr->Name ? Curr->Name : "",(int)Curr->Ctrl.UD.Now,(int)((Curr->Ctrl.UD.Now*100)-(((int)Curr->Ctrl.UD.Now)*100)));
						}
						else
						{
							len = libmPrintfXY( x, y  , font_color, bg_color,buf,bufLen, dinfo, "%s<-[%d]+>",Curr->Name ? Curr->Name : "",(int)Curr->Ctrl.UD.Now);
						}
					}
					break;
					
					case Spacer: 	if(Curr->Name == NULL) break;//名前があればdefaultで表示させる
					
					default:
					{
						len = libmPrintXY( x, y  , font_color, bg_color,Curr->Name, dinfo);
					}
					break;
				}
				
				//下線が有効なら描画
				if(Context->MenuInfo.Lines != 0 && Curr->Color.Line != LIBM_NO_DRAW)
				{
					libmLine( x, y+LIBM_CHAR_HEIGHT, x+(LIBM_CHAR_WIDTH	*len), y+LIBM_CHAR_HEIGHT, Curr->Color.Line, dinfo);
				}
				
				row++;
			}
			
			
			//メニュータイプによって別処理
			if( Context->MenuInfo.Type == LIBM_VIEW_ALL )
			{
				//タイプ0 全体表示
				//他のアイテムを描画するために移動
				if ( Curr->Type == MenuContainer && Curr->Children &&  Curr->Ctrl.CNT.IsOpen )
				{
					Curr = Curr->Children;
					++depth;
				}
				else
				{
					MenuItem *last = Curr;
					Curr = Curr->Next;
					
					if (!Curr && last->Parent)
					{
						while(last->Parent->Parent && !last->Parent->Next)
						{
							last = last->Parent;
							depth--;
						}
						Curr = last->Parent->Next;
						--depth;
					}
				}
			}
			else
			{
				//タイプ1 アクティブなアイテムのみ
				//現コンテナーのみを巡回
				Curr = Curr->Next;
			}
		}
	}
}
