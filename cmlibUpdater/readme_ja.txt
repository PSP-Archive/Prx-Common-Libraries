/*
 *	cmLibUpdater v1.1
 *	2011/11/03
 *	Created by Y.K
 *
 *	Author: Team Otwibaco
 *	Project: http://code.google.com/p/prx-common-libraries/
 */


cmLibUpdaterとは？
　Prx Common Libraries プロジェクトでリリースされているPRXライブラリのインストール・アップデートを自動で行うアプリです。
　LCFW/CFWをPSPに導入し、WiFi環境のある方向けです。


動作環境
　LCFW/CFWを導入済みのPSP 1000/2000/3000/ PSP Go
　Wi-Fi


導入
　解凍後に出てくるPSPフォルダをメモリースティックへコピーして下さい。
　配置は
　　ms0:/PSP/GAME/cmlibUpdater/EBOOT.PBP
　または
　　ef0:/PSP/GAME/cmlibUpdater/EBOOT.PBP
　です。


使用
　1.XMBよりcmLibUpdaterを起動します。
　2.ネットワーク接続画面になるので、使用可能なネットワークへ接続して下さい。
　3.接続後メニュー画面が表示されます。
　  メニュー画面では決定がXキー、戻る/キャンセルはOキーです。(2011/10/26修正)

　・All update
　　すべてのPRXライブラリのインストールアップデートを行います。

　・Individually update
　　PRXライブラリを個別にアップデートできます。
　　選択するとインストール・アップデート可能なPRXライブラリの一覧が表示されます。
　　PRXライブラリ名を選択しXキー又は左右キーでEnabled(有効)/Disabled(無効)を切り替えれます。
　　アップデートするには一番下の項目のUpdateです。

　アップデート中はメッセージが流れますので確認して置いてください。
　もし失敗したようであれば時間を置いてから再度お試ください。


謝辞
　今回このアプリを作るのに色々な方にお世話になりました。ありがとうございます。
　特にpopsdeco氏には大変お世話になりました。ありがとうございます。
　procfwプロジェクトにて公開されているソースコードの一部を改変利用しています。
　ソースコードの公開に感謝します。


ライセンス
　GNU GENERAL PUBLIC LICENSE Version 3


履歴
 2011/11/03    v1.1    アップデート後のログ確認が出来る様に修正
                       アップデートスクリプト解析処理のコメント処理抜けを修正
                       メモリリーク一件修正
                       アップデート時のリネーム処理不具合修正
 2011/10/27    v1.0    readme_ja.txt修正,適切なライセンスに変更 GPLv2→GPLv3
 2011/10/26    v1.0    readme_ja.txt修正
 2011/10/24    v1.0    リリース


連絡先
　お手数ですがバグ報告・要望等ありましたらTwitter @estuibal までご連絡下さい。
