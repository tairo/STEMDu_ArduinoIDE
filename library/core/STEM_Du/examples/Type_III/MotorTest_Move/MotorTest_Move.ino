/*
 * STEM Du Library
 *
 * MotorTest_Move
 *
 * This example code is in the public domain.
 *
 */

/*** Include Headerfile for STEM Du ***/
#define STEMDU_DEBUG
#include <STEMDu.h>

/* Initialize STEM Du board */
STEMDu robot = STEMDu();

int threshold = 50;
int flag = 0;

// the setup routine runs once when you press reset:
void setup() {
#if defined(STEMDU_DEBUG)
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
#endif
}

// the loop routine runs over and over again forever:
void loop() {
  int angle = map(robot.readSlider(),0,1023,0,359); // Read value of slider to control the direction
  int speed = 255;
  int pushsw = robot.readPush();

#if defined(STEMDU_DEBUG)
  // print out the angle:
  // JUST FOR DEBUG
  Serial.println(angle);
#endif

  if(pushsw){
    robot.stopM1M2();
  }
  else{
    robot.moveM1M2(angle, speed);
  }
}
