cmibCtrl by ABCanG

【はじめに】
ボタン関係をまとめたものです。

【使い方】
　1.プログラムのソースファイルに"cmlibctrl.h"をインクルードしてください。

　2.プログラム内で"cmlibCtrl"が読み込まれているかチェックして、必要に応じて読み込むようにしてください。
　　（詳しくはサンプルを見てください）

　3.ビルド時に、"cmlibCtrl.S"を一緒にビルドしてください。
　　（例：Makefileに"OBJS += cmlibCtrl.o"と記述）

　4.ライブラリである"cmlibctrl.prx"は"/seplugins/lib/"以下に配置するようにお願いします。


/////Changelog/////
*1.2 (2011.07.07)
[!]関数名を「libCtrl」→「libctrl」に変更
[!]libctrlWaitButtonUpを修正
[!]libctrlWaitButtonDownを修正

*1.1 (2011.07.04)
[-]libCtrlCheckButtonを削除
[+]libCtrlCountButtonsを追加
[+]libCtrlWaitButtonUpを追加
[+]libCtrlWaitButtonDownを追加

*1.0 (2011.07.03)
[] 最初のリリース。
