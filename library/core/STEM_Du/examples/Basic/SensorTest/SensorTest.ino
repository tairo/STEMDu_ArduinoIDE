/*
 * STEM Du Library
 *
 * SensorTest
 *
 * This example code is in the public domain.
 *
 */

/*** Setup for using Library ***/
//#define TYPE_I
//#define TYPE_II
#define TYPE_III
//#define TYPE_III_R
//#define USE_PHREF
#include <STEMDu.h>
/*** end of setup for using Library ***/

/* Initialize STEM Du board */
STEMDu robot = STEMDu();

int bright = 0;
int brightFlag = 0;

int mode = 0;
int flag = 0;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog port
  int soundValue = robot.readSound(); // Sound sensor
  int lightValue = robot.readLight(); // Light sensor
  int sliderValue = robot.readSlider(); // Slider sensor

  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 3.3V):
  float soundVoltage = soundValue * (3.3 / 1023.0);
  float lightVoltage = lightValue * (3.3 / 1023.0);
  float sliderVoltage = sliderValue * (3.3 / 1023.0);

  // read the input on digital port
  int pushValue = robot.readPush(); // Push button
  delay(1);
  int pushValue2 =  robot.readPush(); // Push button

  if(flag == 0 && pushValue == pushValue2 && pushValue == 1){
    mode++;
    flag = 1;
    if(mode > 5) mode = 0;
  }
  else if(flag == 1 && pushValue == pushValue2 && pushValue == 0){
    flag = 0;
  }

  // print out the value you read:
  switch (mode) {
    case 0:
      Serial.print("0 Sound =");
      Serial.println(soundValue);
      break;
    case 1:
      Serial.print("1 Sound =");
      Serial.print(soundVoltage);
      Serial.println("[V]");
      break;
    case 2:
      Serial.print("2 Light =");
      Serial.println(lightValue);
      break;
    case 3:
      Serial.print("3 Light =");
      Serial.print(lightVoltage);
      Serial.println("[V]");
      break;
    case 4:
      Serial.print("4 Slider =");
      Serial.println(sliderValue);
      break;
    case 5:
      Serial.print("5 Slider =");
      Serial.print(sliderVoltage);
      Serial.println("[V]");
      break;
    default:
      break;
  }
  
  robot.led(bright);
  
  // LED
  if(brightFlag == 0){
    bright++;
    if(bright>254) brightFlag = 1;
  }
  else{
    bright--;
    if(bright<1) brightFlag = 0;
  }
}
