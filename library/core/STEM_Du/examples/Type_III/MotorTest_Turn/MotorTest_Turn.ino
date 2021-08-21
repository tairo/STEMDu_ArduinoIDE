/*
 * STEM Du Library
 *
 * MotorTest_Turn
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
  int speed = map(robot.readSlider(),0,1023,-255,255); // Read value of slider to control the speed
  int pushsw = robot.readPush();

#if defined(STEMDU_DEBUG)
  // print out the angle:
  // JUST FOR DEBUG
  Serial.println(speed);
#endif

  if(pushsw){
    robot.stopM1M2();
  }
  else{
    robot.turnM1M2(speed);
  }
}
