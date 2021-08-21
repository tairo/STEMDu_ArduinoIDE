/*
 * STEM Du Library
 *
 * MotorTest
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
  int speed = map(robot.readSlider(),0,1023,0,255); // Read value of slider to control the speed
  int lightValue = robot.readLight();

#if defined(STEMDU_DEBUG)
  // print out the value you read:
  // JUST FOR DEBUG
  Serial.println(lightValue);
#endif

  if(lightValue<threshold){
    robot.forwardM1(speed);
    robot.forwardM2(speed);
    robot.forwardM3(speed);
    robot.forwardM4(speed);
  }
  else{
    robot.backwardM1(speed);
    robot.backwardM2(speed);
    robot.backwardM3(speed);
    robot.backwardM4(speed);
  }
}
