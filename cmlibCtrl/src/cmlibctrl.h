
#ifndef _CM_LIB_CTRL_
#define	_CM_LIB_CTRL_


#include <pspkernel.h>
#include <pspsdk.h>
#include <pspctrl.h>
#include <pspctrl_kernel.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>


#define LIB_CTRL_ALL (PSP_CTRL_SELECT | PSP_CTRL_START | PSP_CTRL_UP | PSP_CTRL_RIGHT | \
PSP_CTRL_DOWN | PSP_CTRL_LEFT | PSP_CTRL_LTRIGGER | PSP_CTRL_RTRIGGER | PSP_CTRL_TRIANGLE | \
PSP_CTRL_CIRCLE | PSP_CTRL_CROSS | PSP_CTRL_SQUARE | PSP_CTRL_NOTE | PSP_CTRL_HOME | \
PSP_CTRL_SCREEN | PSP_CTRL_VOLUP | PSP_CTRL_VOLDOWN )

/**
 * ���[�U�[���[�h�Ŏg����{�^���̓��͂����ׂĖ����ɂ���
 * ���̃v���O�C�������̊֐����g���Ă���ꍇ�A
 * ��ł��I���ɂ��Ă���v���O�C������������{�^���̓��͖͂���������܂��B
 * 
 * @param status - ���ꂼ��̃v���O�C�����ł̃I��/�I�t��ۑ�����|�C���^�B
 * 		libctrlMaskAllButtonOn��libctrlMaskAllButtonOff�ȊO�ł��̒l��ύX����Ƃ��������Ȃ�܂��B
 *
 * @return 0 ����, < 0 ���s�i���ɃI���ɂȂ��Ă���j
 */
int libctrlMaskAllButtonOn(bool *status);

/**
 * ���[�U�[���[�h�Ŏg����{�^���̓��͂����ׂėL���ɂ���
 * ���̃v���O�C�������̊֐����g���Ă���ꍇ�A
 * ���ׂẴv���O�C�����I�t�ɂ��ĂȂ��ƃ{�^���̓��͂��L���ɂȂ�܂���B
 * 
 * @param status - ���ꂼ��̃v���O�C�����ł̃I��/�I�t��ۑ�����|�C���^�B
 * 		libctrlMaskAllButtonOn��libctrlMaskAllButtonOff�ȊO�ł��̒l��ύX����Ƃ��������Ȃ�܂��B
 *
 * @return 0 ����, < 0 ���s�i���ɃI�t�ɂȂ��Ă���j
 */
int libctrlMaskAllButtonOff(bool *status);

/**
 * �{�^���̓��͂����ׂėL�����ǂ������ׂ�
 *
 * @return true �L��, false ����
 */
bool libctrlMaskAllButtonStatus();

/**
 * �{�^���̓��̗͂L��/�������ăZ�b�g����
 * ���̃v���O�C�������̊֐����g���Ă���ꍇ�A
 * ��ł��I���ɂ��Ă���v���O�C������������{�^���̓��͖͂���������A
 * ���ׂẴv���O�C�����I�t�ɂȂ��Ă�����{�^���̓��͂͗L���ɂȂ�܂��B
 *
 * @return true �L��, false ����
 */
bool libctrlMaskAllButtonAgain();

/**
 * �w�肵���{�^���̓��͂𖳌��ɂ���i���̃v���O�C���Ƌ�������\��������܂��j
 * �����n���Ƃ��́u+�v���u|�v�łȂ��ŉ������B
 * 
 * @param PspCtrlButtons - �����ɂ������{�^��
 *
 * @return ���0
 */
int libctrlMaskButtonOn(int PspCtrlButtons);

/**
 * �w�肵���{�^���̓��͂�L���ɂ���i���̃v���O�C���Ƌ�������\��������܂��j
 * �����n���Ƃ��́u+�v���u|�v�łȂ��ŉ������B
 * 
 * @param PspCtrlButtons - �L���ɂ������{�^��
 *
 * @return ���0
 */
int libctrlMaskButtonOff(int PspCtrlButtons);

/**
 * �w�肵���{�^���̗L��/�����𒲂ׂ܂�
 * �����ɕ����n���Ƃǂ��Ȃ邩�͕s��
 * 
 * @param PspCtrlButtons - ���ׂ����{�^��
 *
 * @return true �L��, false ����
 */
bool libctrlMaskButtonStatus(int PspCtrlButtons);

/**
 * �w�肵���{�^��������������Ă��邩�ǂ����𒲂ׂ܂�
 * �����ɕ����n���Ƃ��́u+�v���u|�v�łȂ��ŉ������B
 * 
 * @param buttons - ���ׂ����{�^��
 * @param count - �������̕b��
 *
 * @return 1 �w�莞�Ԃ܂ŉ����� , 0 �w�莞�ԂɂȂ�O�ɗ�����
 *
 */
int libctrlCountButtons(u32 buttons, int count);

/**
 * �w�肵���{�^�����������܂ő҂�
 * �����ɕ����n���Ƃ��́u+�v���u|�v�łȂ��ŉ������B
 * 
 * @param buttons - �{�^��
 *
 * @return 0
 *
 */
int libctrlWaitButtonUp(u32 buttons);

/**
 * �w�肵���{�^�����������܂ő҂�
 * �����ɕ����n���Ƃ��́u+�v���u|�v�łȂ��ŉ������B
 * 
 * @param buttons - �{�^��
 *
 * @return 0
 *
 */
int libctrlWaitButtonDown(u32 buttons);


#endif
