/*
  LiquidCrystal Library - Hello World
 
 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the 
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.
 
 This sketch prints "Hello World!" to the LCD
 and shows the time.
  
 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 modified 21 Aug 2012
 by Noriaki Mitsunaga for I2C LCD
 
 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystal
 */

// include the library code:
#include <I2CLiquidCrystal.h>
#include <Wire.h>

// initialize the library
// uncomment next line if you are using a LCD from Straberry Linux
I2CLiquidCrystal lcd(20, (bool)true);
                  //  |          +--- set true if the power suply is 5V, false if it is 3.3V
                  //  +-------- contrast (0-63)
// uncomment next line if you are using a LCD from Akizuki denshi
// I2CLiquidCrystal lcd;

// uncomment next line if you are using a OLED from Akizuki denshi(SO1602 series)
// I2CLiquidCrystal lcd(0x3c, (uint8_t)127);
                  //  |             +--- contrast (0-255)
                  //  +-------- I2C ADDR (SA0=L: 0x3c, SA0=H: 0x3d)

// uncomment next line if you are using a Grove RGB Backlight LCD
// I2CLiquidCrystal lcd(LCD_GROVE_RGB);

void setup() {
  // uncomment next line if you want to use Wire1 with Arduino Due
  // lcd.setWire(&Wire1);
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // uncomment next line if you want to change backlight color 
  // (Grove RGB backlight LCD only)
  // lcd.setRGB(0, 255, 0); // specify PWM of Red, Green, and Blue in 0-255
  // Print a message to the LCD.
  lcd.print("hello, world!");
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print(millis()/1000);
}

