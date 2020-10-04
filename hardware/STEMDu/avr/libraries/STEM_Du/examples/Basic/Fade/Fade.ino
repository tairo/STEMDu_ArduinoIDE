
/*
 * STEM Du Library
 *
 * Fade
 *
 * This example code is in the public domain.
 *
 */

/*** Include Headerfile for STEM Du ***/
#include <STEMDu.h>

/* Initialize STEM Du board */
STEMDu robot = STEMDu();

int bright = 0;
int flag = 1;
int tic = 5;

void setup(){
  
}

void loop(){
  int delayTime = map(robot.readSlider(),0,1023,10,50);
  robot.led(bright);
  delay(delayTime);
  
  if(flag == 1){
    bright += tic;
  }
  else{
    bright -= tic;
  }
  if(bright<0){
    flag = 1;
    bright = 0;
  }
  else if(bright > 255){
    flag = 0;
    bright = 255;
  }
}
