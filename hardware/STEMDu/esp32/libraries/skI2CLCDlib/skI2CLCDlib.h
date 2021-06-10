/*******************************************************************************
*  skI2CLCDlib.h - Ｉ２Ｃ接続ＬＣＤ関数ライブラリのインクルードファイル        *
*                                                                              *
* ============================================================================ *
*   VERSION  DATE        BY             CHANGE/COMMENT                         *
* ---------------------------------------------------------------------------- *
*   1.00     2015-02-25  きむ茶工房     Create                                 *
* ============================================================================ *
*   Arduino IDE 1.0.5-r2 (Ardino Duemilanove 328/UNO)                          *
*******************************************************************************/
#ifndef skI2CLCDlib_h
#define skI2CLCDlib_h

#include "arduino.h"

/******************************************************************************/
/*  定数の定義                                                                */
/******************************************************************************/
#define LCD_VDD3V                  1   // LCDの電源は3.3Vで使用する(昇圧回路ON)
#define LCD_VDD5V                  0   // LCDの電源は5.0Vで使用する(昇圧回路OFF)
#define LCD_USE_ICON               1   // アイコンを使う(アイコン付LCDのみ)
#define LCD_NOT_ICON               0   // アイコンは使わない

/******************************************************************************/
/*  LCDのアイコン用のアドレス定義(ST7032i液晶コントローラ)                    */
/******************************************************************************/
#define LCD_ICON_ANTENNA           0x4010    // アンテナ
#define LCD_ICON_PHONE             0x4210    // 電話
#define LCD_ICON_COMMUNICATION     0x4410    // 通信
#define LCD_ICON_INCOMING          0x4610    // 着信
#define LCD_ICON_UP                0x4710    // △
#define LCD_ICON_DOWN              0x4708    // ▽
#define LCD_ICON_LOCK              0x4910    // 錠
#define LCD_ICON_KINSHI            0x4B10    // 禁止(着信音OFF？)
#define LCD_ICON_BATTERY_LOW       0x4D10    // 電池が少ない充電しようよ
#define LCD_ICON_BATTERY_HALF      0x4D08    // 電池がまだまだ使えるよぉ
#define LCD_ICON_BATTERY_FULL      0x4D04    // 電池がまんぱい
#define LCD_ICON_BATTERY_EMPTY     0x4D02    // 電池が空っぽもうだめ
#define LCD_ICON_HANAMARU          0x4F10    // 大変よく出来ました(あ、ツールかも？)

/*******************************************************************************
*	クラスの定義                                                           *
*******************************************************************************/
class skI2CLCDlib
{
  private:
    int  LCD_NowPage ;
    int  LCD_ColumnSu ;
    int  LCD_adrs ;
    unsigned int FuncSet_DT ;
    unsigned int ContSet_DT ;
    void command(unsigned char c) ;

  public:
         skI2CLCDlib(int address, int colsu) ;
    void Init(int icon, int contrast, int bon) ;
    void Clear(void) ;
    void SetCursor(int col, int row) ;
    void Putc(char c) ;
    void Puts(const char * s) ;
    void CreateChar(int p, char *dt) ;
    void IconOnOff(int flag, unsigned int dt) ;
    void IconClear(void) ;
    void Contrast(int contrast) ;
    int  PageSet(int no) ;
    int  PageNowNo(void) ;
    void PageSetCursor(int col, int row) ;
    void PageClear(void) ;
} ;
#endif
