#include "common.h"

MenuParams* libmGetHandle(MenuContext* Context, SceCtrlData* Input)
{
	//Contextが無効、アクティブなアイテムがない
	if( !Context || Context->Active == NULL ) return NULL;
	
	Context->Params.Item	= NULL;
	Context->Params.Action	= Menu_None;
	
	//前と違うボタンが押されているかどうか
	if( Context->LastState.Buttons != Input->Buttons )
	{
		//メニューが開かれている、Rootを作成済み
		if( Context->IsOpen && Context->Root )
		{
			if( (Input->Buttons & Context->HotKey.Left) == Context->HotKey.Left )
			{
				//十字キーの左が押された
				Context->Params.Action = Menu_Left;
				
				if( Context->Active->Type == SelectBox && Context->Active->Ctrl.SB.Index > 0 )
				{
					//リストボックスのアイテムを前へ
					Context->Active->Ctrl.SB.Index--;
					Context->Params.Item = Context->Active;
				}
				else if( Context->Active->Type == UpDownCtrl )
				{
					//アップダウンのアイテムをStep値分、減算
					if( (Context->Active->Ctrl.UD.Now - Context->Active->Ctrl.UD.Step) >= Context->Active->Ctrl.UD.Min )
					{
						Context->Active->Ctrl.UD.Now -= Context->Active->Ctrl.UD.Step;
					}
					
					Context->Params.Item = Context->Active;
				}
			}
			else if( (Input->Buttons & Context->HotKey.Right) == Context->HotKey.Right )
			{
				//十字キーの右が押された
				Context->Params.Action = Menu_Right;
				
				if( Context->Active->Type == SelectBox && Context->Active->Ctrl.SB.List[Context->Active->Ctrl.SB.Index+1] != NULL )
				{
					//リストボックスのアイテムを次へ
					Context->Active->Ctrl.SB.Index++;
					Context->Params.Item = Context->Active;
					
				}
				else if( Context->Active->Type == UpDownCtrl )
				{
					//アップダウンのアイテムをStep値分、加算
					if( (Context->Active->Ctrl.UD.Now + Context->Active->Ctrl.UD.Step) <= Context->Active->Ctrl.UD.Max )
					{
						Context->Active->Ctrl.UD.Now += Context->Active->Ctrl.UD.Step;
					}
					
					Context->Params.Item = Context->Active;
				}
			}
			else if( (Input->Buttons & Context->HotKey.Up) == Context->HotKey.Up )
			{
				//十字キーの上が押された
				Context->Params.Action = Menu_Up;
				
				MenuItem *Curr = libmGetPrevItem(Context->Active,true);
				
				if( !Curr && Context->MenuInfo.AutoReturn )
				{
					Curr = libmGetBottomItem(Context->Active,true);
				}
				
				if( Curr ) Context->Active = Curr;
			}
			else if( (Input->Buttons & Context->HotKey.Down) == Context->HotKey.Down )
			{
				//十字キーの下が押された
				Context->Params.Action = Menu_Down;
				
				//次に有効なアイテムがあるかどうか
				MenuItem *Curr = libmGetNextItem(Context->Active,true);
				
				if( !Curr && Context->MenuInfo.AutoReturn )
				{
					//現コンテナーの最初へ一気に戻る
					Curr = libmGetTopItem(Context->Active,true);
				}
				
				if(Curr) Context->Active = Curr;
			}
			else if( (Input->Buttons & Context->HotKey.Select) == Context->HotKey.Select )
			{
				//決定キーを押した時の動作
				Context->Params.Action = Menu_Select;
				
				//タイプにより分岐
				switch ( Context->Active->Type )
				{
					//コンテナー
					case MenuContainer:
					{
						//子がある
						if ( Context->Active->Children )
						{
							//状態はアクティブ、子へ移動
							MenuItem  *Curr = Context->Active->Children;
							
							if( libmIsInvalidItem(Curr) )
							{
								Curr = libmGetNextItem(Curr,true);
							}
							
							
							//子に有効なアイテムが有効かどうか
							if( Curr )
							{
								//アクティブなアイテムを子へ
								Context->Active->Ctrl.CNT.IsOpen	= true;
								Context->Active						= Curr;
							}
						}
						
						break;
					}
					
					//ラジオボタン
					case RadioButton:
					{
						if ( Context->Active->Ctrl.RB_Group )
						{
							(Context->Active->Ctrl.RB_Group)->Ctrl.Group_Sel	= Context->Active;
							Context->Params.Item								= Context->Active;
						}
						
						break;
					}
					
					//チェックボックス
					case CheckBox:
					{
						//選択状態を反転
						Context->Active->Ctrl.CB_Checked	= !Context->Active->Ctrl.CB_Checked;
						Context->Params.Item				= Context->Active;
						
						break;
					}
					
					
					//トリガーボタン
					case TriggerButton:
					{
						//押されたIDを返却
						Context->Params.Item = Context->Active;
						
						break;
					}
					
					default: break;
				}
			}
			else if( (Input->Buttons & Context->HotKey.Back) == Context->HotKey.Back )
			{
				if( Context->Active->Parent )
				{
					//戻る、閉じる
					Context->Params.Action = Menu_Back;
					
					//閉じたのは root ではない（コンテナー）
					
					Context->Active = Context->Active->Parent;
					Context->Active->Ctrl.CNT.IsOpen = false;
				}
				else
				{
					//メニューが閉じられた
					Context->Params.Action	= Menu_Close;
					Context->IsOpen 		= false;
				}
			}
		}
		else
		{
			if( (Input->Buttons & Context->HotKey.Show) == Context->HotKey.Show )
			{
				//メニューが表示された
				Context->Params.Action = Menu_Show;
				Context->IsOpen = true;
			}
		}
	}
	
	//現在のPad情報を次のために保持
	Context->LastState = *Input;
	
	return &(Context->Params);
}

