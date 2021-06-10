/*
 * STEM Du Library
 *
 * TypeII Basic
 *
 * This example code is in the public domain.
 *
 */

/*** Setup for using Library ***/
//#define TYPE_I
#define TYPE_II
//#define TYPE_III
//#define TYPE_III_R
//#define USE_PHREF
#include <STEMDu.h>
/*** end of setup for using Library ***/

/* Initialize STEM Du board */
STEMDu robot = STEMDu();

// include the library code:
#include <I2CLiquidCrystal.h>
#include <Wire.h>

// initialize the library
// uncomment next line if you are using a LCD from Straberry Linux
I2CLiquidCrystal lcd(20, false);
                  //  |    +--- set true if the power suply is 5V, false if it is 3.3V
                  //  +-------- contrast (0-63)
// uncomment next line if you are using a LCD from Akizuki denshi
// I2CLiquidCrystal lcd;

int menuIndex = 1;
#define MAX_MENU_INDEX 4
int selectedMenu = 0;

int buttonFlag = 0;

int distValue = 0; //0-1024
int speedValue = 0; //0-255
int lastDist = 0;

void clearLCD(){
  lcd.setCursor(0, 0);
  lcd.print("        ");
  lcd.setCursor(0, 1);
  lcd.print("        ");
}

void printLCD(int a){
    if (a<1000)
      lcd.print(' ');    
    if (a<100)
      lcd.print(' ');
    if (a<10)
      lcd.print(' ');
    lcd.print(a);
}

void setup() {
  int sliderValue = 0;

  // set up the LCD's number of columns and rows: 
  lcd.begin(8, 2);
  // Print pin numbers
  lcd.setCursor(0, 0);
  lcd.print("STEM Du ");
  lcd.setCursor(0, 1);
  lcd.print(" v140625");
  delay(1500);

  clearLCD();

  lcd.setCursor(0, 0);
  lcd.print("SPEED = ");

  lcd.setCursor(0, 1);
  while(!readButton()){
    sliderValue = robot.readSlider();
    lcd.setCursor(0, 1);
    printLCD(map(sliderValue,0,1023,0,255));
  }
  sliderValue = robot.readSlider();
  speedValue = map(sliderValue,0,1023,0,255);
  //delay(1500);

  clearLCD();
  delay(500);

  lcd.setCursor(0, 0);
  lcd.print("DIST = ");

  lcd.setCursor(0, 1);
  while(!readButton()){
    sliderValue = robot.readSlider();
    lcd.setCursor(0, 1);
    printLCD(sliderValue);
  }
  sliderValue = robot.readSlider();
  distValue = sliderValue;
  //distValue = 500;
  //delay(1500);

  clearLCD();
  delay(500);

  lcd.setCursor(0, 0);
  lcd.print("READY?  ");
  while(!readButton()){
  }
  delay(500);
  clearLCD();
}

boolean readButton(){
  // read the input on digital port
  int pushValue = robot.readPush(); // Push button
  delay(1);
  int pushValue2 =  robot.readPush(); // Push button

  if(buttonFlag == 0 && pushValue == pushValue2 && pushValue == 1){
    buttonFlag = 1;
    return true;
  }
  else if(buttonFlag == 1 && pushValue == pushValue2 && pushValue == 0){
    buttonFlag = 0;
    return false;
  }
}

void loop() {
  int dist = analogRead(A1);
  if(dist>distValue){
    robot.stopM1M2();
     lcd.setCursor(0, 0);
      printLCD(analogRead(A1));
  }
  else{
    robot.forwardM1M2(speedValue);
    if(dist != lastDist){
      lcd.setCursor(0, 0);
      printLCD(analogRead(A1));
    }
  }
  
  if(readButton()){
    robot.stopM1M2();
    clearLCD();
     lcd.setCursor(0, 0);
    lcd.print("STOP    ");
    while(1);
  }
}
