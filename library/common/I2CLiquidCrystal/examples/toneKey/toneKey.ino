// include the library code:
#include <I2CLiquidCrystal.h>
#include <Wire.h>
#include "pitches.h"

// initialize the library
// uncomment next line if you are using a LCD from Straberry Linux
I2CLiquidCrystal lcd(20, true);
                  //  |    +--- set true if the power suply is 5V, false if it is 3.3V
                  //  +-------- contrast (0-63)
// uncomment next line if you are using a LCD from Akizuki denshi
// I2CLiquidCrystal lcd;

const int tonePin = 10;
const int ledPin = 13;
unsigned long next;
bool LED = LOW;

void setup() {
  for (int i=2; i<=12; i++)
    pinMode(i, INPUT_PULLUP);
  pinMode(tonePin, OUTPUT);
  pinMode(ledPin, OUTPUT);

  for (int i=A0; i<=A3; i++)
    pinMode(i, INPUT_PULLUP);

  next = millis();

  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // Print pin numbers
  lcd.print("23456789ABCD0123");
}

void loop() {
  int freq = 0;  
  if (digitalRead(2) == LOW)
    freq = NOTE_C4;
  if (digitalRead(3) == LOW)
    freq = NOTE_D4;
  if (digitalRead(4) == LOW)
    freq = NOTE_E4;
  if (digitalRead(5) == LOW)
    freq = NOTE_F4;
  if (digitalRead(6) == LOW)
    freq = NOTE_G4;
  if (digitalRead(7) == LOW)
    freq = NOTE_A4;
  if (digitalRead(8) == LOW)
    freq = NOTE_B4;
  if (digitalRead(9) == LOW)
    freq = NOTE_C5;

  if (freq == 0)
    noTone(tonePin);
  else
    tone(tonePin, freq);

  if ((next - millis())>500) {
    LED = !LED;
    digitalWrite(ledPin, LED);
    next += 500;
  }

  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  for (int i=2; i<=13; i++) {
    if (digitalRead(i) == LOW)
      lcd.print('L');
    else
      lcd.print('H');
  }
  for (int i=A0; i<=A3; i++)
    if (digitalRead(i) == LOW)
      lcd.print('L');
    else
      lcd.print('H');
}
