/**
*	cmliblog.h
*	2011/07/06
*	estuibal
*********************/

#ifndef _CM_LIB_LOG_H_
#define _CM_LIB_LOG_H_


#include <stdbool.h>


#define HANDLE_MASK			0xF917D628
#define TRUE_HANDLE(h)		( ((u32)(h)) ^ HANDLE_MASK )

// ���s�����w��
#define LIBLOG_BC_CRLF		0	// "\r\n"	Windows
#define LIBLOG_BC_CR		1	// "\r"		Mac
#define LIBLOG_BC_LF		2	// "\n"		UNIX/Linux�n

// �e�I�v�V�����t���O(liblobOpt.flags)
#define LIBLOG_TIMESTAMP	0x1		// �����L�^������
#define LIBLOG_OPENCLOSE	0x2		// �L�^���Ƀ��O���J���A����(�ᑬ�������S)
//#define LIBLOG_TIMEFMT		0x4		// �����̏����ݒ������(������)
#define LIBLOG_STARTCLEAR	0x8		// ���O�L�^�J�n���Ƀ��O���N���A����
#define LIBLOG_ALLFLAG		(LIBLOG_TIMESTAMP | LIBLOG_OPENCLOSE | /*LIBLOG_TIMEFMT |*/ LIBLOG_STARTCLEAR)


typedef struct _tag_liblogopt {
	// char timefmt[32];	// �����t�H�[�}�b�g(������)
	int break_char;		// �e�L�X�g���s�����w��
	char logname[256];	// ���O�t�@�C���p�X
	u32 flags;			// �e�I�v�V�����t���O
} liblogOpt;

typedef u32 HLOG; // ���O�n���h��


#ifdef __cplusplus
extern "C" {
#endif


// char *GetSizeStr(u64 size, char *dest);

HLOG liblogCreateLog(liblogOpt *pOpt);	// ���O�n���h�����쐬����
int liblogDestroyLog(HLOG hLog);		// ���O�n���h�����������(�I�����ɌĂ�ł�������)

int liblogClear(HLOG hLog);				// ���O���������܂��B
int liblogPrint(HLOG hLog, char *text); // ������𒼐ڏo�͂��܂�
int liblogPrintf(HLOG hLog, char *textfmt, ...) __attribute__((format(printf, 2, 3))); // �����t
int liblogPrintBool(HLOG hLog, char *text, bool b);	// Bool�l�̏o�� [text][b]
int liblogPrintInt(HLOG hLog, char *text, int num); // �����t��32bit�����o�� [text][num]
int liblogPrintUint(HLOG hLog, char *text, unsigned int num); // ������32bit�����o�� [text][num]
int liblogPrintU64(HLOG hLog, char *text, u64 num);	// ������64bit�����o�� [text][num]
int liblogPrintHex(HLOG hLog, char *text, u32 hex);	// 32bit16�i���o�� [text][hex]
int liblogPrintHex64(HLOG hLog, char *text, u64 hex); // 64bit16�i���o�� [text][hex]
int liblogPrintPspModel(HLOG hLog);		// PSP���f���̏o��(Fat/Slim2000/Slim3000/Go)
int liblogPrintMaxFreeMem(HLOG hLog);	// ���O�L�^���̍ő�󂫃������e�ʂ̏o��

void liblogSetLogName(HLOG hLog, char *new_name);			// ���O�t�@�C���̖��O�ύX(�t���p�X)
int liblogGetLogName(HLOG hLog, char *buf, size_t bufsize); // ���O�t�@�C���̖��O�擾(�t���p�X)

#define liblogSetFlags(hLog, new_flags)  ( ((liblogOpt *)TRUE_HANDLE(hLog))->flags = (u32)(new_flags & LIBLOG_ALLFLAG) )
#define liblogSetBreakChar(hLog, new_break_char)  ( ((liblogOpt *)TRUE_HANDLE(hLog))->break_char = (int)(new_break_char) )

#define liblogGetFlags(hLog)  ( (u32)(((liblogOpt *)TRUE_HANDLE(hLog))->flags) )
#define liblogGetBreakChar(hLog)  ( (int)(((liblogOpt *)TRUE_HANDLE(hLog))->break_char) )

#define liblogPrintAddr(hLog, text, addr)  liblogPrintHex( (HLOG)(hLog), (char *)(text), (u32)(addr) );

#ifdef __cplusplus
}
#endif

#endif // _CM_LIB_LOG_H_
