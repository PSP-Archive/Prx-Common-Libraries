#ifndef _CM_LIB_AUDIO_
#define	_CM_LIB_AUDIO_


#include <pspimpose_driver.h>
#include <pspkernel.h>
#include <pspsdk.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

/**
 * ���݂̉��ʂ��擾����
 *
 * @return ���݂̉���
 */
int libaudioGetVolume(void);

/**
 * ���ʂ�ݒ肷��
 * 
 * @param value - �ݒ肵��������
 *
 * @return < 0 ���s
 */
int libaudioSetVolume(int value);

/**
 * �~���[�g��L���ɂ���
 * 
 * @param status - ���ꂼ��̃v���O�C�����ł̗L��/������ۑ�����|�C���^�B
 * 		libaudioMuteOn��libaudioMuteOff�ȊO�ł��̒l��ύX����Ƃ��������Ȃ�܂��B
 *
 * @return 0 ����, < 0 ���s�i���ɗL���ɂȂ��Ă���j
 */
int libaudioMuteOn(bool *status);

/**
 * �~���[�g�𖳌��ɂ���
 * 
 * @param status - ���ꂼ��̃v���O�C�����ł̗L��/������ۑ�����|�C���^�B
 * 		libaudioMuteOn��libaudioMuteOff�ȊO�ł��̒l��ύX����Ƃ��������Ȃ�܂��B
 *
 * @return 0 ����, < 0 ���s�i���ɖ����ɂȂ��Ă���j
 */
int libaudioMuteOff(bool *status);

/**
 * ���݃~���[�g���ǂ������ׂ�
 *
 * @return 1 �L��, 0 ����
 */
int libaudioMuteGetStatus(void);

/**
 * �~���[�g�̗L��/�������ăZ�b�g����
 * ���̃v���O�C�������̊֐����g���Ă���ꍇ�A
 * ��ł��L���ɂ��Ă���v���O�C������������{�^���̓��͖͂���������A
 * ���ׂẴv���O�C���������ɂȂ��Ă�����{�^���̓��͂͗L���ɂȂ�܂��B
 *
 * @return true �L��, false ����
 */
bool libaudioMuteSetAgain(void);

/**
 * ���̏o�͂�L���ɂ���
 * �~���[�g�Ƃ͏����Ⴂ�܂��B
 * 
 * @param status - ���ꂼ��̃v���O�C�����ł̗L��/������ۑ�����|�C���^�B
 * 		libaudioIoEnable��libaudioIoDisable�ȊO�ł��̒l��ύX����Ƃ��������Ȃ�܂��B
 *
 * @return 0 ����, < 0 ���s�i���ɗL���ɂȂ��Ă���j
 */
int libaudioIoEnable(bool *status);

/**
 * ���̏o�͂𖳌��ɂ���
 * �~���[�g�Ƃ͏����Ⴂ�܂��B
 * 
 * @param status - ���ꂼ��̃v���O�C�����ł̗L��/������ۑ�����|�C���^�B
 * 		libaudioIoEnable��libaudioIoDisable�ȊO�ł��̒l��ύX����Ƃ��������Ȃ�܂��B
 *
 * @return 0 ����, < 0 ���s�i���ɖ����ɂȂ��Ă���j
 */
int libaudioIoDisable(bool *status);

/**
 * ���̏o�̗͂L��/�����𒲂ׂ�
 * 
 * @return true �L��, false ����
 */
bool libaudioIoGetStatus(void);

/**
 * ���̏o�̗͂L��/�������ăZ�b�g����
 * ���̃v���O�C�������̊֐����g���Ă���ꍇ�A
 * ��ł��L���ɂ��Ă���v���O�C������������{�^���̓��͖͂���������A
 * ���ׂẴv���O�C���������ɂȂ��Ă�����{�^���̓��͂͗L���ɂȂ�܂��B
 *
 * @return true �L��, false ����
 */
bool libaudioIoSetAgain(void);


#endif