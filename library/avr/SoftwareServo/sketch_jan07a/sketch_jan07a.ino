#include <STEMDu.h>
#include <SoftwareServo.h> 

SoftwareServo myservo;  // create servo object to control a servo 

int val;    // variable to read the value from the analog pin 

STEMDu myrobot;

void setup() 
{ 
  myrobot = STEMDu();
  myservo.attach(10);  // 10万ポートにサーボモータ 
} 

void loop() 
{ 
  val = analogRead(potpin);            // reads the value of the potentiometer (value between 0 and 1023) 
  val = map(val, 0, 1023, 0, 179);     // scale it to use it with the servo (value between 0 and 180) 
  myservo.write(val);                  // sets the servo position according to the scaled value 
  delay(15);                           // waits for the servo to get there 

  SoftwareServo::refresh();
} 
