
/*
 * STEM Du Library
 *
 * Blink
 *
 * This example code is in the public domain.
 *
 */

/*** Include Headerfile for STEM Du ***/
#include <STEMDu.h>

/* Initialize STEM Du board */
STEMDu robot = STEMDu();

void setup(){
  
}

void loop(){
  int delayTime = map(robot.readSlider(),0,1023,20,1000);
  robot.led(255);
  delay(delayTime);
  robot.led(0);
  delay(delayTime);
}
