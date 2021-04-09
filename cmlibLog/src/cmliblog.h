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

// 改行文字指定
#define LIBLOG_BC_CRLF		0	// "\r\n"	Windows
#define LIBLOG_BC_CR		1	// "\r"		Mac
#define LIBLOG_BC_LF		2	// "\n"		UNIX/Linux系

// 各オプションフラグ(liblobOpt.flags)
#define LIBLOG_TIMESTAMP	0x1		// 時刻記録をする
#define LIBLOG_OPENCLOSE	0x2		// 記録毎にログを開き、閉じる(低速だが安全)
//#define LIBLOG_TIMEFMT		0x4		// 時刻の書式設定をする(未実装)
#define LIBLOG_STARTCLEAR	0x8		// ログ記録開始時にログをクリアする
#define LIBLOG_ALLFLAG		(LIBLOG_TIMESTAMP | LIBLOG_OPENCLOSE | /*LIBLOG_TIMEFMT |*/ LIBLOG_STARTCLEAR)


typedef struct _tag_liblogopt {
	// char timefmt[32];	// 時刻フォーマット(未実装)
	int break_char;		// テキスト改行文字指定
	char logname[256];	// ログファイルパス
	u32 flags;			// 各オプションフラグ
} liblogOpt;

typedef u32 HLOG; // ログハンドル


#ifdef __cplusplus
extern "C" {
#endif


// char *GetSizeStr(u64 size, char *dest);

HLOG liblogCreateLog(liblogOpt *pOpt);	// ログハンドルを作成する
int liblogDestroyLog(HLOG hLog);		// ログハンドルを解放する(終了時に呼んでください)

int liblogClear(HLOG hLog);				// ログを消去します。
int liblogPrint(HLOG hLog, char *text); // 文字列を直接出力します
int liblogPrintf(HLOG hLog, char *textfmt, ...) __attribute__((format(printf, 2, 3))); // 書式付
int liblogPrintBool(HLOG hLog, char *text, bool b);	// Bool値の出力 [text][b]
int liblogPrintInt(HLOG hLog, char *text, int num); // 符号付き32bit整数出力 [text][num]
int liblogPrintUint(HLOG hLog, char *text, unsigned int num); // 符号無32bit整数出力 [text][num]
int liblogPrintU64(HLOG hLog, char *text, u64 num);	// 符号無64bit整数出力 [text][num]
int liblogPrintHex(HLOG hLog, char *text, u32 hex);	// 32bit16進数出力 [text][hex]
int liblogPrintHex64(HLOG hLog, char *text, u64 hex); // 64bit16進数出力 [text][hex]
int liblogPrintPspModel(HLOG hLog);		// PSPモデルの出力(Fat/Slim2000/Slim3000/Go)
int liblogPrintMaxFreeMem(HLOG hLog);	// ログ記録時の最大空きメモリ容量の出力

void liblogSetLogName(HLOG hLog, char *new_name);			// ログファイルの名前変更(フルパス)
int liblogGetLogName(HLOG hLog, char *buf, size_t bufsize); // ログファイルの名前取得(フルパス)

#define liblogSetFlags(hLog, new_flags)  ( ((liblogOpt *)TRUE_HANDLE(hLog))->flags = (u32)(new_flags & LIBLOG_ALLFLAG) )
#define liblogSetBreakChar(hLog, new_break_char)  ( ((liblogOpt *)TRUE_HANDLE(hLog))->break_char = (int)(new_break_char) )

#define liblogGetFlags(hLog)  ( (u32)(((liblogOpt *)TRUE_HANDLE(hLog))->flags) )
#define liblogGetBreakChar(hLog)  ( (int)(((liblogOpt *)TRUE_HANDLE(hLog))->break_char) )

#define liblogPrintAddr(hLog, text, addr)  liblogPrintHex( (HLOG)(hLog), (char *)(text), (u32)(addr) );

#ifdef __cplusplus
}
#endif

#endif // _CM_LIB_LOG_H_
