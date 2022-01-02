I2CLiquidCrystal ライブラリは Arduino で I2C キャラクタ液晶を使うための
ライブラリです。Arduino IDE に標準の LiquidCrystal ライブラリを基にして
おり使い方もほぼ変わりません。ライセンスはオリジナルのファイルに従います。

このライブラリには MGLCD ライブラリ (モノクログラフィックLCDモジュール
を Arduino で使うためのライブラリ)

http://www3.big.or.jp/~schaft/hardware/MGLCD/page001.html

用に作られた mglcd.cpp と mglcd.h を利用しています。ファイルのライセンス
は LGPL バージョン2.1以降です。LGPL については

http://www.gnu.org/licenses/old-licenses/lgpl-2.1.en.html

を確認してください。これらのファイルは kana()関数で UTF-8 の半角カナを
１バイトのカナに変換するために利用しています。

I2CLiquidLibrary の使い方は下記を参照してください

http://n.mtng.org/ele/arduino/i2c.html
