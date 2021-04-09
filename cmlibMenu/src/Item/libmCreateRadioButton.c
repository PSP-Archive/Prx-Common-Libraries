#include "common.h"

MenuItem* libmCreateRadioButton(libmOpt *opt , const char* Name, bool State ,MenuItem *Group )
{
	//�e���R���e�i�[����Ȃ���Βǉ��o���Ȃ�
	
	MenuItem* Item = _createItem(opt,Name,RadioButton);
	
	//Item�쐬���s
	if( !Item || !Group || Group->Type != RadioButtonGroup ) return NULL;
	
	//�`�F�b�N���
	Item->Ctrl.RB_Group = Group;
	
	//�I���ς݂����݂̃A�C�e����
	if( State ) Group->Ctrl.Group_Sel = Item;
	
	return Item;
}


