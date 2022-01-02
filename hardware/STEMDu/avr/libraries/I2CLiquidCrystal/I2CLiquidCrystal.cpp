#include "I2CLiquidCrystal.h"

#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <Wire.h>
#include "Arduino.h"

// When the display powers up, it is configured as follows:
//
// 1. Display clear
// 2. Function set: 
//    DL = 1; 8-bit interface data 
//    N = 0; 1-line display 
//    F = 0; 5x8 dot character font 
// 3. Display on/off control: 
//    D = 0; Display off 
//    C = 0; Cursor off 
//    B = 0; Blinking off 
// 4. Entry mode set: 
//    I/D = 1; Increment by 1 
//    S = 0; No shift 
//
// Note, however, that resetting the Arduino doesn't reset the LCD, so we
// can't assume that its in that state when a sketch starts (and the
// I2CLiquidCrystal constructor is called).

/// This library has been modified for I2C based LCD by Straberry Linux in Japan.
// The controller is ST7032i.
//  21 Aug. 2012, Noriaki Mitsunaga

const static uint8_t I2C_ADDR_AKIZUKI = 0x50;
const static uint8_t I2C_ADDR_GROVE_RGB = 0x3e;
const static uint8_t I2C_ADDR_STRAWBERRY = 0x3e;
const static uint8_t LCD_UNDEF = 0;

// For Grove RGB backlight LCD
const static uint8_t I2C_ADDR_RGB = (0xc4>>1);

I2CLiquidCrystal::I2CLiquidCrystal()
{
  I2C_ADDR = I2C_ADDR_AKIZUKI;  // Akizuki denshi
  I2C_RS = 0x80;
  lcd_type = LCD_UNDEF;
  wire = &Wire;
  init();
}

I2CLiquidCrystal::I2CLiquidCrystal(uint8_t type)
{
  if (type == LCD_GROVE_RGB) {
    I2C_ADDR = I2C_ADDR_GROVE_RGB;  // Grobe RGB Backlight LCD
    I2C_RS = 0x40;
  }
  lcd_type = type;
  wire = &Wire;
  init();
}

I2CLiquidCrystal::I2CLiquidCrystal(uint8_t contrast, bool is5V)
{
  I2C_ADDR = I2C_ADDR_STRAWBERRY; // Strawberry Linux
  I2C_RS = 0x40;
  _contrast = contrast;
  _is5V = is5V;
  lcd_type = LCD_UNDEF;
  wire = &Wire;
  init();
}

I2CLiquidCrystal::I2CLiquidCrystal(uint8_t addr, uint8_t contrast)
{
  I2C_ADDR = addr; // Akizuki denshi (OLED, SO1602A series)
  I2C_RS = 0x40;
  _contrast = contrast;
  lcd_type = LCD_UNDEF;
  wire = &Wire;
  init();
}

void I2CLiquidCrystal::init()
{
  _displayfunction = 0;
  //  begin(16, 1);  
}

void I2CLiquidCrystal::setWire(TwoWire *w)
{
  wire = w;
}

void I2CLiquidCrystal::begin(uint8_t cols, uint8_t lines, uint8_t dotsize) {
  if (lines > 1) {
    _displayfunction |= LCD_2LINE;
  }
  _numlines = lines;
  _currline = 0;

  // for some 1 line displays you can select a 10 pixel high font
  if ((dotsize != 0) && (lines == 1)) {
    _displayfunction |= LCD_5x10DOTS;
  }

  wire->begin();

  // SEE PAGE 45/46 FOR INITIALIZATION SPECIFICATION!
  // according to datasheet, we need at least 40ms after power rises above 2.7V
  // before sending commands. Arduino can turn on way befer 4.5V so we'll wait 50
  delayMicroseconds(50000); 
 
  if (I2C_ADDR == I2C_ADDR_STRAWBERRY) { // Strawberry Linux
    // set # lines, font size, etc.
    //command(0b00110000 | _displayfunction);  
    command(0x38);
    delayMicroseconds(50);

    // again
    //command(0b00110000 | _displayfunction);  
    command(0x39);
    delayMicroseconds(50);
    
    // Internal OSC frequency
    command(0x14);
    delayMicroseconds(50);
    
    // Contrast set
    command(0x70 | (_contrast & 0xF));
    delayMicroseconds(50);

    // Power/ICON/Contrast control
    if (!_is5V)
      command(0x5c | ((_contrast >> 4) & 0x3));
    else
      command(0x58 | ((_contrast >> 4) & 0x3)); // ”{“dˆ³‰ñ˜HƒIƒt
    delayMicroseconds(50);
    
    // Follower Control
    command(0x6c);
    delay(400);
  } else if (I2C_ADDR == I2C_ADDR_AKIZUKI) { // Akizuki LCD
    command(0b00110000 | _displayfunction);  
    delayMicroseconds(4100);
    command(0b00110000 | _displayfunction);  
    delayMicroseconds(100);
  } else { // Akizuki OLED (SO1602A)
    delay(100);
    command(0x01); // clear display
    delay(20);
    command(0x02); // return home
    delay(2);
    command(0x0f); // display on
    delay(2);
    command(0x01); // clear display
    delay(20);

    command(0x2a);
    command(0x79);
    command(0x81);
    command(_contrast);
    command(0x78);
    delay(100);
  }

  // Function set (set so as to be compatible with parallel LCD)
  command(0b00110000 | _displayfunction);  

  // turn the display on with no cursor or blinking default
  _displaycontrol = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;  
  display();

  // clear it off
  clear();

  // Initialize to default text direction (for romance languages)
  _displaymode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;
  // set the entry mode
  command(LCD_ENTRYMODESET | _displaymode);

  if (lcd_type == LCD_GROVE_RGB) {
    // Initialize backlight
    setReg(0, 0);
    setReg(1, 0);
    setReg(0x08, 0xAA);     // all led control by pwm
  
    setColorWhite();
  }
}

/********** high level commands, for the user! */
void I2CLiquidCrystal::clear()
{
  command(LCD_CLEARDISPLAY);  // clear display, set cursor position to zero
  delayMicroseconds(2000);  // this command takes a long time!
}

void I2CLiquidCrystal::home()
{
  command(LCD_RETURNHOME);  // set cursor position to zero
  delayMicroseconds(2000);  // this command takes a long time!
}

void I2CLiquidCrystal::setCursor(uint8_t col, uint8_t row)
{
  if (I2C_ADDR == I2C_ADDR_AKIZUKI || I2C_ADDR == I2C_ADDR_STRAWBERRY) {
    int row_offsets[] = { 0x00, 0x40, 0x14, 0x54 };
    if ( row >= _numlines ) {
      row = _numlines-1;    // we count rows starting w/0
    }
  
    command(LCD_SETDDRAMADDR | (col + row_offsets[row]));
  } else {
    int row_offsets[] = {0x00, 0x20};

    command(LCD_SETDDRAMADDR | (col + row_offsets[row]));
  }
}

// Turn the display on/off (quickly)
void I2CLiquidCrystal::noDisplay() {
  _displaycontrol &= ~LCD_DISPLAYON;
  command(LCD_DISPLAYCONTROL | _displaycontrol);
}
void I2CLiquidCrystal::display() {
  _displaycontrol |= LCD_DISPLAYON;
  command(LCD_DISPLAYCONTROL | _displaycontrol);
}

// Turns the underline cursor on/off
void I2CLiquidCrystal::noCursor() {
  _displaycontrol &= ~LCD_CURSORON;
  command(LCD_DISPLAYCONTROL | _displaycontrol);
}
void I2CLiquidCrystal::cursor() {
  _displaycontrol |= LCD_CURSORON;
  command(LCD_DISPLAYCONTROL | _displaycontrol);
}

// Turn on and off the blinking cursor
void I2CLiquidCrystal::noBlink() {
  _displaycontrol &= ~LCD_BLINKON;
  command(LCD_DISPLAYCONTROL | _displaycontrol);
}
void I2CLiquidCrystal::blink() {
  _displaycontrol |= LCD_BLINKON;
  command(LCD_DISPLAYCONTROL | _displaycontrol);
}

// These commands scroll the display without changing the RAM
void I2CLiquidCrystal::scrollDisplayLeft(void) {
  command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVELEFT);
}
void I2CLiquidCrystal::scrollDisplayRight(void) {
  command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVERIGHT);
}

// This is for text that flows Left to Right
void I2CLiquidCrystal::leftToRight(void) {
  _displaymode |= LCD_ENTRYLEFT;
  command(LCD_ENTRYMODESET | _displaymode);
}

// This is for text that flows Right to Left
void I2CLiquidCrystal::rightToLeft(void) {
  _displaymode &= ~LCD_ENTRYLEFT;
  command(LCD_ENTRYMODESET | _displaymode);
}

// This will 'right justify' text from the cursor
void I2CLiquidCrystal::autoscroll(void) {
  _displaymode |= LCD_ENTRYSHIFTINCREMENT;
  command(LCD_ENTRYMODESET | _displaymode);
}

// This will 'left justify' text from the cursor
void I2CLiquidCrystal::noAutoscroll(void) {
  _displaymode &= ~LCD_ENTRYSHIFTINCREMENT;
  command(LCD_ENTRYMODESET | _displaymode);
}

// Allows us to fill the first 8 CGRAM locations
// with custom characters
void I2CLiquidCrystal::createChar(uint8_t location, uint8_t charmap[]) {
  location &= 0x7; // we only have 8 locations 0-7
  command(LCD_SETCGRAMADDR | (location << 3));
  for (int i=0; i<8; i++) {
    write(charmap[i]);
  }
}

/*********** mid level commands, for sending data/cmds */

inline void I2CLiquidCrystal::command(uint8_t value) {
  send(value, LOW);
}

inline size_t I2CLiquidCrystal::write(uint8_t value) {
  send(value, HIGH);
  return 1; // assume sucess
}

/************ low level data pushing commands **********/

// write either command or data, with automatic 4/8-bit selection
void I2CLiquidCrystal::send(uint8_t value, uint8_t mode) {

  wire->beginTransmission(I2C_ADDR);
  if (mode == LOW)
    wire->write((uint8_t)0x0);   // Co = 0, RS = 0    // Co: continue
  else
    wire->write(I2C_RS);  // Co = 0, RS = 1
  wire->write(value);
  wire->endTransmission();
}

/************ Control backlight of Grove RGB backlight LCD **********/

void I2CLiquidCrystal::setReg(unsigned char addr, unsigned char data)
{
    wire->beginTransmission(I2C_ADDR_RGB); // transmit to device #4
    wire->write(addr);
    wire->write(data);
    wire->endTransmission();    // stop transmitting
}

void I2CLiquidCrystal::setRGB(unsigned char r, unsigned char g, unsigned char b)
{
    setReg(REG_RED, r);
    setReg(REG_GREEN, g);
    setReg(REG_BLUE, b);
}

const unsigned char color_define[4][3] = 
{
    {255, 255, 255},            // white
    {255, 0, 0},                // red
    {0, 255, 0},                // green
    {0, 0, 255},                // blue
};

void I2CLiquidCrystal::setColor(unsigned char color)
{
    if(color > 3)return ;
    setRGB(color_define[color][0], color_define[color][1], color_define[color][2]);
}


/************ Kana support **********/

void I2CLiquidCrystal::kana(const char *p) {
  while (*p) {
    unsigned char q = MGLCD_CODE_UTF8(*p);
    if (q>0)
      write(q);
    p ++;
  }
}
