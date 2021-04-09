・注意
　開発者が使用するプログラムです。
　一般の方は使用しないで下さい。


・genupdate
　cmLibUpdaterで使用するアップデートスクリプト生成プログラムです。
　popsdeco氏より頂いたものに手を加えました。ご助力ありがとうございました。
　実行ファイルはWindowsバイナリですので、お手数ですが他環境の開発者の方は各自コンパイルお願いします。

　コマンドラインより
 　　genupdate ..\ < template.txt > upload_script.src
　として使ってください。
　第一引数の"..\"はprxcmlib_pack or sepluginsディレクトリのあるディレクトリを表します。
　PSPがF:\にマウントされsepluginsに全ての最新prxcmlibが配置されている場合
　　genupdate F:\ < template.txt > upload_script.src
　としてもかまいません。

　各prxcmlibの追加・更新毎にgenupdateを実行してアップデートスクリプトの更新をお願いします。
　upload_script.srcがアップデートスクリプトです。配置場所は"/hg/genupdate/upload_script.src"です。
　prxcmlibの更新のみでしたらtemplate.txtの編集は必要ありません。
　prxcmlibの新規追加の場合template.txtに以下のフォーマットで書き加えて下さい。

　例）cmLibHogehoge
　#cmLibHogehoge
　<GET> /hg/prxcmlib_pack/lib/cmlibhogehoge.prx /seplugins/lib/cmlibhogehoge.prx

履歴
 2011/10/24 リリース
