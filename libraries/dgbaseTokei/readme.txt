2014/6/29 a.ide

dgbaseTOKEI library

・dgbaseTOKEI
  ・dgbaseAlarm00 ※未使用
  ・dgbaseAlarm01 ...パターン1
  ・dgbaseAlarm02 ...パターン2
  ・dgbaseAlarm03 ...パターン3



dgbaseTOKEIを継承して、各パターン処理(プログラム)を作る。
詳細は以下を参考にしてみてください
・dgbaseAlarm01.h
・dgbaseAlarm01.cpp


基本的には、xxx.cppファイルのコンストラクタに、
LEDの点灯パターンをコーディングします。


リファレンス

setColor(位置, 色);
・LEDの配列[位置]に色を設定する。

syncLED(待ち時間);
・LEDを点灯する。
・待ち時間はミリ秒

