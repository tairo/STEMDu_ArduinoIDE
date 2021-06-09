/*******************************************************************************
*  skI2CLCDlib - Ｉ２Ｃ接続ＬＣＤ関数ライブラリ                                *
*                液晶コントローラはST7032iを想定しています。                   *
*                                                                              *
*    skI2CLCD      - この関数ライブラリを生成する時の初期化処理                *
*    Init          - ＬＣＤの初期化を行う処理                                  *
*    Clear         - ＬＣＤモジュールの画面を消し初期状態に戻す処理            *
*    SetCursor     - ＬＣＤモジュール画面内のカーソル位置を移動する処理        *
*    Putc          - ＬＣＤにデータを１バイト出力する処理                      *
*    Puts          - ＬＣＤに文字列データを出力する処理                        *
*    CreateChar    - オリジナルのキャラクタを登録します                        *
*    Contrast      - ＬＣＤのコントラスト調整を行う処理                        *
*    IconClear     - 全部のアイコン表示を消す処理                              *
*    IconOnOff     - 指定アイコンの表示ON/OFFを行う処理                        *
*    PageSet       - ページ画面の切り替えを行う処理                            *
*    PageClear     - 現在表示中のページ画面内の消去を行う処理                  *
*    PageSetCursor - 現在表示中のページ画面内でのカーソル設定を行う処理        *
*    PageNowNo     - 現在表示中のページ画面番号を返す処理                      *
*                                                                              *
* ============================================================================ *
*   VERSION  DATE        BY             CHANGE/COMMENT                         *
* ---------------------------------------------------------------------------- *
*   1.00     2015-02-25  きむ茶工房     Create                                 *
*   1.10     2015-03-29  きむ茶工房     32-bit MCU に対応しました。            *
* ============================================================================ *
*   Arduino IDE 1.0.5-r2 (Ardino Duemilanove 328/UNO)                          *
*   Arduino Zero Pro (Dueも動作すると思うがぁ...)                              *
*******************************************************************************/
#include <Wire.h>
#include "arduino.h"
#include "skI2CLCDlib.h"


/*******************************************************************************
*  skI2CLCDlib(address)                                                        *
*    この関数ライブラリを生成する時の初期化処理(コンストラクタ)                *
*    address : デバイス(スレーブ)のI2Cアドレスを指定します                     *
*    colsu   : LCD画面の横文字数を指定する                                     *
*******************************************************************************/
skI2CLCDlib::skI2CLCDlib(int address, int colsu)
{
     LCD_adrs     = address ;
     LCD_ColumnSu = colsu ;
}
/*******************************************************************************
*  command( )                                                                  *
*    ＬＣＤにコマンドを発行する処理                                            *
*******************************************************************************/
void skI2CLCDlib::command(unsigned char c)
{
     Wire.beginTransmission(LCD_adrs) ;      // 通信の開始
     // command word の送信
     Wire.write((uint8_t)0b10000000) ;       // control byte の送信(コマンドを指定)
     Wire.write((uint8_t)c) ;                // data byte の送信
     Wire.endTransmission() ;                // データの送信と通信の終了
     delayMicroseconds(27) ;
}
/*******************************************************************************
*  Clear( )                                                                    *
*    ＬＣＤモジュールの画面を消し初期状態に戻す処理                            *
*    全てのDisplay Data RAM(2x40byte)に20Hのスペースを書き込みます。           *
*    ページ画面も初期状態に戻す                                                *
*******************************************************************************/
void skI2CLCDlib::Clear(void)
{
     command(0x01) ;          // Clear Display : 画面全体に20Hのｽﾍﾟｰｽで表示、ｶｰｿﾙはcol=0,row=0に移動
     delayMicroseconds(1100) ;// LCDが処理(1.08ms)するのを待ちます
     command(0x02) ;          // Return Home   : 画面を初期ポジションに戻す
     delayMicroseconds(1100) ;// LCDが処理(1.08ms)するのを待ちます
     LCD_NowPage  = 0 ;       // 初期ページ画面は０ページとする
}
/*******************************************************************************
*  SetCursor(col,row)                                                          *
*    ＬＣＤモジュール画面内のカーソル位置を移動する処理                        *
*    実際のDisplay Data RAMは2x40byteのエリアが有ります。(但し2-line display)  *
*    指定位置の数値データ内容チェックは行っていないので数値は正しく設定する事。*
*                                                                              *
*    col : 横(列)方向のカーソル位置(0-39)                                      *
*    row : 縦(行)方向のカーソル位置(0-1)                                       *
*******************************************************************************/
void skI2CLCDlib::SetCursor(int col, int row)
{
     int row_offsets[] = { 0x00, 0x40 } ;

     command(0x80 | (col + row_offsets[row])) ; // Set DDRAM Adddress : 00H-27H,40H-67H
}
/*******************************************************************************
*  Putc(c)                                                                     *
*    ＬＣＤにデータを１バイト出力する処理                                      *
*                                                                              *
*    c :  出力する文字データを指定                                             *
*******************************************************************************/
void skI2CLCDlib::Putc(char c)
{
     Wire.beginTransmission(LCD_adrs) ;      // 通信の開始
     // command word の送信
     Wire.write((uint8_t)0b11000000) ;       // control byte の送信(データを指定)
     Wire.write((uint8_t)c) ;                // data byte の送信
     Wire.endTransmission() ;                // データの送信と通信の終了
     delayMicroseconds(27) ;
}
/*******************************************************************************
*  Puts(*s)                                                                    *
*    ＬＣＤに文字列データを出力する処理                                        *
*    文字列は、NULL(0x00)まで繰返し出力します。(最大32文字までの送信です)      *
*                                                                              *
*    *s :  出力する文字列のデータを格納した場所のアドレスを指定                *
*******************************************************************************/
void skI2CLCDlib::Puts(const char *s)
{
     while(*s) {
          Putc(*s++) ;                       // data byte の送信
     }
}
/*******************************************************************************
*  CreateChar(p,*dt)                                                           *
*    オリジナルのキャラクタを登録します                                        *
*                                                                              *
*    p   : 登録する場所の指定(０～５の６ヶ所のみ)(LCDによっては0-15の16ヶ所有) *
*    *dt : 登録したいキャラクタのデータを格納したバッファを指定                *
********************************************************************************/
void skI2CLCDlib::CreateChar(int p, char *dt)
{
     int i ;

     // LCD(CGRAM)にキャラ保存先のアドレスを指示
     command(0x40 | (p << 3)) ;              // control byte の送信(コマンドを指定)
     // キャラのデータを送信する
     for (i=0; i < 7; i++) {
          Wire.beginTransmission(LCD_adrs) ; // 通信の開始
          Wire.write((uint8_t)0b01000000) ;  // control byte の送信(データを指定)
          Wire.write((uint8_t)*dt++) ;
          Wire.endTransmission() ;           // データの送信と通信の終了
          delayMicroseconds(27) ;
     }
}
/*******************************************************************************
*  IconClear( )                                                                *
*    全部のアイコン表示を消す処理(アイコン対応LCDのみ)                         *
*******************************************************************************/
void skI2CLCDlib::IconClear(void)
{
     int i ;

     // 拡張コマンドの設定を有効にする
     command(0x39) ;
     for (i=0x40 ; i<0x50 ; i++) {
          // LCDのアイコンアドレスを指示する
          command(i) ;                       // control byte の送信(コマンドを指定)
          // アイコンのデータビットを指定する
          Wire.beginTransmission(LCD_adrs) ; // 通信の開始
          Wire.write((uint8_t)0b01000000) ;  // control byte の送信(データを指定)
          Wire.write((uint8_t)0x00) ;
          Wire.endTransmission() ;           // データの送信と通信の終了
          delayMicroseconds(27) ;
     }
     // 拡張コマンドを設定を無効にする
     command(FuncSet_DT) ;
}
/*******************************************************************************
*  IconOnOff(flag,dt)                                                          *
*    指定アイコンの表示ON/OFFを行う処理(アイコン対応LCDのみ)                   *
*    消すのはアドレス単位で全て消去、例えば△▽を表示していれば両方消えます。  *
*                                                                              *
*    flag : 指定したアイコンの表示をするしない(1=ON 0=OFF)                     *
*    dt   : アイコンのアドレスとビットを指定します                             *
*           "skI2CLCDlib.hのdefine宣言で指定します。                           *
*******************************************************************************/
void skI2CLCDlib::IconOnOff(int flag, unsigned int dt)
{
     // 拡張コマンドの設定を有効にする
     command(0x39) ;
     // LCDのアイコンアドレスを指示する
     command(dt >> 8) ;                      // control byte の送信(コマンドを指定)
     // アイコンのデータビットを指定する
     Wire.beginTransmission(LCD_adrs) ;      // 通信の開始
     Wire.write((uint8_t)0b01000000) ;       // control byte の送信(データを指定)
     if (flag == 1) Wire.write((uint8_t)(dt & 0x00FF)) ;
     else           Wire.write((uint8_t)0x00) ;
     Wire.endTransmission() ;                // データの送信と通信の終了
     delayMicroseconds(27) ;
     // 拡張コマンドを設定を無効にする
     command(FuncSet_DT) ;
}
/*******************************************************************************
*  Contrast(contrast)                                                          *
*    ＬＣＤのコントラスト調整を行う処理                                        *
*                                                                              *
*    contrast : LCDのコントラストを指定します(０－６３)                        *
*******************************************************************************/
void skI2CLCDlib::Contrast(int contrast)
{
     // 拡張コマンドの設定を有効にする
     command(0x39) ;
     // コントラストの下位４ビット
     command(0x70 | (contrast & 0x0F)) ;
     // コントラストの上位２ビット
     ContSet_DT = (ContSet_DT & 0xFC) | ((contrast & 0x30) >> 4) ;
     command(ContSet_DT) ;
     // 拡張コマンドを設定を無効にする
     command(FuncSet_DT) ;
}
/*******************************************************************************
*  ans = PageSet(no)                                                           *
*    ページ画面の切り替えを行う処理                                            *
*                                                                              *
*    no  : 表示するページ画面の番号を指定(8x2なら0-4／16x2なら0-1)             *
*    ans : ０＝正常  －１＝指定したページページ番号がおかしい                  *
*******************************************************************************/
int skI2CLCDlib::PageSet(int no)
{
     int ans, c , c2 ;

     ans = -1 ;
     if (LCD_NowPage != no) {      // 指定ページと現在のページが異なるなら処理する
          // 指定ページの先頭DDRAM位置を計算する
          c = no * LCD_ColumnSu ;
          // 指定ページ - 現在ページ の差は？
          c2 = c - (LCD_NowPage * LCD_ColumnSu) ;
          if (c < (40/LCD_ColumnSu)*LCD_ColumnSu) {    // 指定ページは有効範囲なら処理する
               if (c2 > 0) {
                    // 右方向に差の分だけ画面をシフトさせる
                    for (c=0 ; c < c2 ; c++) command(0x18) ;
               } else {
                    // 左方向に差の分だけ画面をシフトさせる
                    c2 = c2 * -1 ;
                    for (c=0 ; c < c2 ; c++) command(0x1C) ;
               }
               LCD_NowPage = no ;  // 指定ページ画面の番号を保存する
               ans = 0 ;
          }
     }
     return ans ;
}
/*******************************************************************************
*  PageClear( )                                                                *
*    現在表示中のページ画面内の消去を行う処理                                  *
*******************************************************************************/
void skI2CLCDlib::PageClear(void)
{
     int c , i ;

     // 現在ページの先頭DDRAM位置を計算する
     c = LCD_NowPage * LCD_ColumnSu ;
     // 1行目を消す
     SetCursor(c, 0) ;
     for (i=0 ; i < LCD_ColumnSu ; i++) {
          Putc(0x20) ;
     }
     // 2行目を消す
     SetCursor(c, 1) ;
     for (i=0 ; i < LCD_ColumnSu ; i++) {
          Putc(0x20) ;
     }
     SetCursor(c, 0) ;
}
/*******************************************************************************
*  PageSetCursor(col,row)                                                      *
*    現在表示中のページ画面内でのカーソル設定を行う処理                        *
*    指定位置の数値データ内容チェックは行っていないので数値は正しく設定する事。*
*                                                                              *
*    col : 横(列)方向のカーソル位置(8x2なら0-7／16x2なら0-15)                  *
*    row : 縦(行)方向のカーソル位置(0-1)                                       *
*******************************************************************************/
void skI2CLCDlib::PageSetCursor(int col, int row)
{
     SetCursor((LCD_NowPage * LCD_ColumnSu) + col, row) ;
}
/*******************************************************************************
*  ans = PageNowNo()                                                           *
*    現在表示中のページ画面番号を返す処理                                      *
*                                                                              *
*    ans : ページ画面番号を返します(8x2なら0-4／16x2なら0-1)                   *
*******************************************************************************/
int skI2CLCDlib::PageNowNo(void)
{
     return LCD_NowPage ;
}
/*******************************************************************************
*  Init(icon,contrast,bon)                                                     *
*    ＬＣＤの初期化を行う処理                                                  *
*                                                                              *
*    icon     : アイコンを使用するのかを指定します(1=使う 0=使わない)          *
*    contrast : LCDのコントラストを指定します(０－６３)                        *
*    bon      : 昇圧回路の利用有無  1:ON(VDD=3.3V) 0:OFF(VDD=5.0V)             *
*******************************************************************************/
void skI2CLCDlib::Init(int icon, int contrast, int bon)
{
     unsigned int d ;

     Wire.begin() ;      // Ｉ２Ｃの初期化マスターとする

     delay(40) ;         // 電源ＯＮ後40msまで待ってから初期化
     FuncSet_DT = 0x38 ;
     command(FuncSet_DT);// function set           : データ線は8本・表示は2行・フォントは5x8ドット
     command(0x39) ;     // function set           : 拡張コマンドの設定を有効にする
     command(0x14) ;     // Internal OSC frequency : バイアスの選択と内部OSC周波数の調整
     d = 0x70 | (contrast & 0x0F) ;                // (下位4ビット)の取り出し
     command(d) ;        // Contrast set           : コントラスト調整データ
     d = 0x50 | ((contrast & 0x30) >> 4) ;         // (上位2ビット)の取り出し
     if (icon == 1) d = d | 0x08 ;                 // アイコンを利用する場合
     if (bon  == 1) d = d | 0x04 ;                 // 昇圧回路を利用する場合
     ContSet_DT = d ;
     command(d) ;        // Contrast set           : 昇圧回路、コントラスト調整データ
     command(0x6C) ;     // Follower control       : フォロア回路をON、増幅率の調整を行う
     delay(200) ;        // 電力が安定するまで待つ(200ms)
     command(FuncSet_DT);// function set           : 拡張コマンドを設定を無効にする
     command(0x0C) ;     // display control        : 画面表示はON・カーソル表示はOFF・カーソル点滅はOFF
     command(0x06) ;     // entry mode set         : 文字を表示した次にカーソルを移動するを指示
     Clear() ;           // Clear Display          : 画面を消去する、初期状態に戻す
}
