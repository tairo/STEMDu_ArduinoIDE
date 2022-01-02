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
  // Print pin numbers
  lcd.print(" A0  A1  A2  A3");
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  for (int i=A0; i<=A3; i++) {
    int a = analogRead(i);
    if (a<1000)
      lcd.print(' ');    
    if (a<100)
      lcd.print(' ');
    if (a<10)
      lcd.print(' ');
    lcd.print(a);
  }
  delay(100);
}
