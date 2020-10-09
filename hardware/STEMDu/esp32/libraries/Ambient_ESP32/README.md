# Ambient_ESP32_lib

[Ambient](https://ambidata.io)はIoTクラウドサービスです。 マイコンから送られたデーターを受信し、蓄積し、可視化(グラフ化)します。

![Ambient structure](https://ambidata.io/wp/wp-content/uploads/2016/09/AmbientStructure.jpg)

Ambientにユーザー登録(無料)し、マイコンからデーターを送ると、こんな感じでグラフ表示させることができます。

![Ambient chart](https://ambidata.io/wp/wp-content/uploads/2016/09/fig3-1024x651.jpg)

ここではArduino ESP32用のライブラリーとサンプルを示しています。サンプルには次のプログラムがあります。

* サンプルプログラム(examples/Ambient_ESP8266): ESP32からランダムで0－1000の範囲で値を送信します。

## 材料

* Ambient.h: Ambient用のヘッダーファイル
* Ambient.cpp: Ambientライブラリーのソースファイル
* examples/Ambient_ESP32: サンプルプログラムのソースファイル

ライブラリーのインポート方法、サンプルプログラムの動かし方は[Ambientサイト](https://ambidata.io/docs/esp8266/)に書きましたので、ご参照ください。
