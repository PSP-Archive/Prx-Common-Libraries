#include "common.h"

MenuParams* libmGetHandle(MenuContext* Context, SceCtrlData* Input)
{
	//Context�������A�A�N�e�B�u�ȃA�C�e�����Ȃ�
	if( !Context || Context->Active == NULL ) return NULL;
	
	Context->Params.Item	= NULL;
	Context->Params.Action	= Menu_None;
	
	//�O�ƈႤ�{�^����������Ă��邩�ǂ���
	if( Context->LastState.Buttons != Input->Buttons )
	{
		//���j���[���J����Ă���ARoot���쐬�ς�
		if( Context->IsOpen && Context->Root )
		{
			if( (Input->Buttons & Context->HotKey.Left) == Context->HotKey.Left )
			{
				//�\���L�[�̍��������ꂽ
				Context->Params.Action = Menu_Left;
				
				if( Context->Active->Type == SelectBox && Context->Active->Ctrl.SB.Index > 0 )
				{
					//���X�g�{�b�N�X�̃A�C�e����O��
					Context->Active->Ctrl.SB.Index--;
					Context->Params.Item = Context->Active;
				}
				else if( Context->Active->Type == UpDownCtrl )
				{
					//�A�b�v�_�E���̃A�C�e����Step�l���A���Z
					if( (Context->Active->Ctrl.UD.Now - Context->Active->Ctrl.UD.Step) >= Context->Active->Ctrl.UD.Min )
					{
						Context->Active->Ctrl.UD.Now -= Context->Active->Ctrl.UD.Step;
					}
					
					Context->Params.Item = Context->Active;
				}
			}
			else if( (Input->Buttons & Context->HotKey.Right) == Context->HotKey.Right )
			{
				//�\���L�[�̉E�������ꂽ
				Context->Params.Action = Menu_Right;
				
				if( Context->Active->Type == SelectBox && Context->Active->Ctrl.SB.List[Context->Active->Ctrl.SB.Index+1] != NULL )
				{
					//���X�g�{�b�N�X�̃A�C�e��������
					Context->Active->Ctrl.SB.Index++;
					Context->Params.Item = Context->Active;
					
				}
				else if( Context->Active->Type == UpDownCtrl )
				{
					//�A�b�v�_�E���̃A�C�e����Step�l���A���Z
					if( (Context->Active->Ctrl.UD.Now + Context->Active->Ctrl.UD.Step) <= Context->Active->Ctrl.UD.Max )
					{
						Context->Active->Ctrl.UD.Now += Context->Active->Ctrl.UD.Step;
					}
					
					Context->Params.Item = Context->Active;
				}
			}
			else if( (Input->Buttons & Context->HotKey.Up) == Context->HotKey.Up )
			{
				//�\���L�[�̏オ�����ꂽ
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
				//�\���L�[�̉��������ꂽ
				Context->Params.Action = Menu_Down;
				
				//���ɗL���ȃA�C�e�������邩�ǂ���
				MenuItem *Curr = libmGetNextItem(Context->Active,true);
				
				if( !Curr && Context->MenuInfo.AutoReturn )
				{
					//���R���e�i�[�̍ŏ��ֈ�C�ɖ߂�
					Curr = libmGetTopItem(Context->Active,true);
				}
				
				if(Curr) Context->Active = Curr;
			}
			else if( (Input->Buttons & Context->HotKey.Select) == Context->HotKey.Select )
			{
				//����L�[�����������̓���
				Context->Params.Action = Menu_Select;
				
				//�^�C�v�ɂ�蕪��
				switch ( Context->Active->Type )
				{
					//�R���e�i�[
					case MenuContainer:
					{
						//�q������
						if ( Context->Active->Children )
						{
							//��Ԃ̓A�N�e�B�u�A�q�ֈړ�
							MenuItem  *Curr = Context->Active->Children;
							
							if( libmIsInvalidItem(Curr) )
							{
								Curr = libmGetNextItem(Curr,true);
							}
							
							
							//�q�ɗL���ȃA�C�e�����L�����ǂ���
							if( Curr )
							{
								//�A�N�e�B�u�ȃA�C�e�����q��
								Context->Active->Ctrl.CNT.IsOpen	= true;
								Context->Active						= Curr;
							}
						}
						
						break;
					}
					
					//���W�I�{�^��
					case RadioButton:
					{
						if ( Context->Active->Ctrl.RB_Group )
						{
							(Context->Active->Ctrl.RB_Group)->Ctrl.Group_Sel	= Context->Active;
							Context->Params.Item								= Context->Active;
						}
						
						break;
					}
					
					//�`�F�b�N�{�b�N�X
					case CheckBox:
					{
						//�I����Ԃ𔽓]
						Context->Active->Ctrl.CB_Checked	= !Context->Active->Ctrl.CB_Checked;
						Context->Params.Item				= Context->Active;
						
						break;
					}
					
					
					//�g���K�[�{�^��
					case TriggerButton:
					{
						//�����ꂽID��ԋp
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
					//�߂�A����
					Context->Params.Action = Menu_Back;
					
					//�����̂� root �ł͂Ȃ��i�R���e�i�[�j
					
					Context->Active = Context->Active->Parent;
					Context->Active->Ctrl.CNT.IsOpen = false;
				}
				else
				{
					//���j���[������ꂽ
					Context->Params.Action	= Menu_Close;
					Context->IsOpen 		= false;
				}
			}
		}
		else
		{
			if( (Input->Buttons & Context->HotKey.Show) == Context->HotKey.Show )
			{
				//���j���[���\�����ꂽ
				Context->Params.Action = Menu_Show;
				Context->IsOpen = true;
			}
		}
	}
	
	//���݂�Pad�������̂��߂ɕێ�
	Context->LastState = *Input;
	
	return &(Context->Params);
}

