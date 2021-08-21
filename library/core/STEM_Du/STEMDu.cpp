//
// STEMDu.cpp
//
// STEM Du 102/103/104/ESP32 Library
//
// Update:Oct 9, 2020 16:10
//
// 2.0 20201009 : Officially Support ESP32
// 1.0 20191227 : Add experimental support of ESP32
//

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <STEMDu.h>

#if STEMDU > RDC_ESP32
// CHANNEL USE
#define LEDC_CHANNEL_MOTOR1 0
#define LEDC_CHANNEL_MOTOR2 1
#define LEDC_CHANNEL_MOTOR3 2
#define LEDC_CHANNEL_MOTOR4 3
#define LEDC_CHANNEL_SERVO1 4
#define LEDC_CHANNEL_SERVO2 5
#define LEDC_CHANNEL_SERVO3 6
#define LEDC_CHANNEL_SERVO4 7
#define LEDC_CHANNEL_SERVO5 8
#define LEDC_CHANNEL_SERVO6 9
#define LEDC_CHANNEL_SERVO7 10
#define LEDC_CHANNEL_SERVO8 11
#define LEDC_CHANNEL_A12 4
#define LEDC_CHANNEL_A13 5
#define LEDC_CHANNEL_A14 6
#define LEDC_CHANNEL_A18 7
#define LEDC_CHANNEL_A19 8
#define LEDC_CHANNEL_A25 9
#define LEDC_CHANNEL_A26 10
#define LEDC_CHANNEL_A27 11
#define LEDC_CHANNEL_IRLED 12
#define LEDC_CHANNEL_LED 13
#define LEDC_CHANNEL_TONE 14

#define LEDC_TIMER_BIT_MOTOR 13
#define LEDC_BASE_FREQ_MOTOR 4900
#define LEDC_TIMER_BIT_SERVO 10
#define LEDC_BASE_FREQ_SERVO 50
#define LEDC_TIMER_BIT_TONE  13
#define LEDC_BASE_FREQ_TONE  5000

void ledcAnalogWrite(uint8_t channel, uint32_t value, uint32_t valueMax = 255) {
  // calculate duty, 8191 from 2 ^ 13 - 1
  uint32_t duty = (8191 / valueMax) * min(value, valueMax);

  // write duty to LEDC
  ledcWrite(channel, duty);
}

#endif

STEMDu::STEMDu(){
	this->init();
}

void STEMDu::init(){
	pinMode(P_LED,OUTPUT);
	pinMode(P_PUSH,INPUT_PULLUP);

	// Motor
	pinMode(P_M1IN1,OUTPUT);
	pinMode(P_M1IN2,OUTPUT);
	pinMode(P_M2IN1,OUTPUT);
	pinMode(P_M2IN2,OUTPUT);
#if STEMDU > RDC_ESP32
  	ledcSetup(LEDC_CHANNEL_MOTOR1,LEDC_BASE_FREQ_MOTOR,LEDC_TIMER_BIT_MOTOR);
  	ledcAttachPin(P_M1PWM,LEDC_CHANNEL_MOTOR1);
	ledcSetup(LEDC_CHANNEL_MOTOR2,LEDC_BASE_FREQ_MOTOR,LEDC_TIMER_BIT_MOTOR);
	ledcAttachPin(P_M2PWM,LEDC_CHANNEL_MOTOR2);
#endif

#if defined(HAS_MOTOR34)
	pinMode(P_M3IN1,OUTPUT);
	pinMode(P_M3IN2,OUTPUT);
	pinMode(P_M4IN1,OUTPUT);
	pinMode(P_M4IN2,OUTPUT);
#if STEMDU > RDC_ESP32
  	ledcSetup(LEDC_CHANNEL_MOTOR3,LEDC_BASE_FREQ_MOTOR,LEDC_TIMER_BIT_MOTOR);
	ledcAttachPin(P_M3PWM,LEDC_CHANNEL_MOTOR3);
  	ledcSetup(LEDC_CHANNEL_MOTOR4,LEDC_BASE_FREQ_MOTOR,LEDC_TIMER_BIT_MOTOR);
	ledcAttachPin(P_M4PWM,LEDC_CHANNEL_MOTOR4);
#endif
#endif
/*
#if STEMDU > RDC_ESP32
	ledcSetup(LEDC_CHANNEL_A12, LEDC_BASE_FREQ_MOTOR, LEDC_TIMER_BIT_MOTOR);
	ledcAttachPin(12, LEDC_CHANNEL_A12);
	ledcSetup(LEDC_CHANNEL_A13, LEDC_BASE_FREQ_MOTOR, LEDC_TIMER_BIT_MOTOR);
	ledcAttachPin(13, LEDC_CHANNEL_A13);
  	ledcSetup(LEDC_CHANNEL_A14, LEDC_BASE_FREQ_MOTOR, LEDC_TIMER_BIT_MOTOR);
  	ledcAttachPin(14, LEDC_CHANNEL_A14);
	ledcSetup(LEDC_CHANNEL_A18, LEDC_BASE_FREQ_MOTOR, LEDC_TIMER_BIT_MOTOR);
	ledcAttachPin(18, LEDC_CHANNEL_A18);
	ledcSetup(LEDC_CHANNEL_A19, LEDC_BASE_FREQ_MOTOR, LEDC_TIMER_BIT_MOTOR);
	ledcAttachPin(19, LEDC_CHANNEL_A19);
	ledcSetup(LEDC_CHANNEL_A25, LEDC_BASE_FREQ_MOTOR, LEDC_TIMER_BIT_MOTOR);
	ledcAttachPin(25, LEDC_CHANNEL_A25);
	ledcSetup(LEDC_CHANNEL_A26, LEDC_BASE_FREQ_MOTOR, LEDC_TIMER_BIT_MOTOR);
	ledcAttachPin(26, LEDC_CHANNEL_A26);
	ledcSetup(LEDC_CHANNEL_A27, LEDC_BASE_FREQ_MOTOR, LEDC_TIMER_BIT_MOTOR);
	ledcAttachPin(27, LEDC_CHANNEL_A27);
#endif
*/

#if defined(HAS_PHREF)
	pinMode(P_MPX_PHREF1,OUTPUT);
	pinMode(P_MPX_PHREF2,OUTPUT);
	pinMode(P_MPX_PHREF3,OUTPUT);
	pinMode(P_MPX_PHREF4,OUTPUT);
	digitalWrite(P_MPX_PHREF1,HIGH);
	digitalWrite(P_MPX_PHREF2,LOW);
	digitalWrite(P_MPX_PHREF3,LOW);
	digitalWrite(P_MPX_PHREF4,LOW);
#endif

#if STEMDU < RDC_ESP32 && defined(HAS_ONBBOARD_DISTANCE)
	// ESP32 should invoke this initialization exclusively between Ultrasonic sensor and Builtin IR distance sensor
	this->initOnboardDistancePort();
#endif

#if defined(HAS_MPU6050)
    Wire.begin();
    accelgyro.initialize();
#endif
}

#if STEMDU > RDC_ESP32
void STEMDu::initLEDPortAsAnalog(){
	ledcSetup(LEDC_CHANNEL_LED, LEDC_BASE_FREQ_MOTOR, LEDC_TIMER_BIT_MOTOR);
	ledcAttachPin(P_LED, LEDC_CHANNEL_LED);
}
#endif

#if defined(HAS_ONBBOARD_DISTANCE)
void STEMDu::initOnboardDistancePort(){
    pinMode(P_IRLED,OUTPUT);
#if STEMDU < RDC_ESP32
	analogWrite(P_IRLED,0);
#else
  	ledcSetup(LEDC_CHANNEL_IRLED,LEDC_BASE_FREQ_MOTOR,LEDC_TIMER_BIT_MOTOR);
	ledcAttachPin(P_IRLED,LEDC_CHANNEL_IRLED);
	ledcAnalogWrite(LEDC_CHANNEL_IRLED, 0);
#endif
}
#endif

void STEMDu::motor(int n, int speed){
	int in1 = HIGH;
	int in2 = LOW;

	if(speed<0){
		in1 = LOW;
		in2 = HIGH;
		speed = -speed;
	}
	else if(speed == MOTOR_STOP){
		in1 = LOW;
		in2 = LOW;
	}
	else if(speed == MOTOR_BRAKE){
		in1 = HIGH;
		in2 = HIGH;
	}
	
	switch(n){
		case 1:
    		digitalWrite(P_M1IN1, in1);
  			digitalWrite(P_M1IN2, in2);
#if STEMDU < RDC_ESP32
			analogWrite(P_M1PWM, speed);
#else
			ledcAnalogWrite(LEDC_CHANNEL_MOTOR1, speed);
#endif
			break;
		case 2:
    		digitalWrite(P_M2IN1, in1);
		    digitalWrite(P_M2IN2, in2);
#if STEMDU < RDC_ESP32
			analogWrite(P_M2PWM, speed);
#else
			ledcAnalogWrite(LEDC_CHANNEL_MOTOR2, speed);
#endif
			break;
		case 3:
		    digitalWrite(P_M3IN1, in1);
		    digitalWrite(P_M3IN2, in2);
#if STEMDU < RDC_ESP32
			analogWrite(P_M3PWM, speed);
#else
			ledcAnalogWrite(LEDC_CHANNEL_MOTOR3, speed);
#endif
			break;
		case 4:
		    digitalWrite(P_M4IN1, in1);
		    digitalWrite(P_M4IN2, in2);
#if STEMDU < RDC_ESP32
			analogWrite(P_M4PWM, speed);
#else
			ledcAnalogWrite(LEDC_CHANNEL_MOTOR4, speed);
#endif
			break;
		default:
			/* error */
			break;
	}
}

void STEMDu::move(int n1, int n2, int angle, int speed){
	int tmpAngle = angle % 360;
	int tmpSpeed = speed;
	
	if(angle>=0 && tmpAngle <= 90){
		tmpSpeed = tmpSpeed*(90.0 - tmpAngle)/90.0;
		this->motor(n1,speed);
		this->motor(n2,tmpSpeed);
	}
	else if(angle>90 && tmpAngle <= 180){
		tmpSpeed = tmpSpeed*(tmpAngle - 90.0)/90.0;
		this->motor(n1,-speed);
		this->motor(n2,-tmpSpeed);
	}
	else if(angle>180 && tmpAngle <= 270){
		tmpSpeed = tmpSpeed*(270.0 - tmpAngle)/90.0;
		this->motor(n1,-tmpSpeed);
		this->motor(n2,-speed);
	}
	else if(angle>270 && tmpAngle <= 360){
		tmpSpeed = tmpSpeed*(tmpAngle - 270.0)/90.0;
		this->motor(n1,tmpSpeed);
		this->motor(n2,speed);
	}
}

void STEMDu::turn(int n1, int n2, int turnSpeed){
	this->motor(n1,turnSpeed);
	this->motor(n2,-turnSpeed);
}

void STEMDu::tank(int n1, int n2, int speed1, int speed2){
	this->motor(n1,speed1);
	this->motor(n2,speed2);
}

void STEMDu::moveM1M2(int angle, int speed){
	this->move(1,2,angle,speed);
}

void STEMDu::turnM1M2(int turnSpeed){
	this->turn(1,2,turnSpeed);
}

void STEMDu::tankM1M2(int speed1, int speed2){
	this->tank(1,2,speed1,speed2);
}

#if defined(HAS_MOTOR34)
void STEMDu::moveM3M4(int angle, int speed){
	this->move(3,4,angle,speed);
}

void STEMDu::turnM3M4(int turnSpeed){
	this->turn(3,4,turnSpeed);
}

void STEMDu::tankM3M4(int speed3, int speed4){
	this->tank(3,4,speed3,speed4);
}
#endif

void STEMDu::forwardM1(int speed){
	this->motor(1,speed);
}

void STEMDu::forwardM2(int speed){
	this->motor(2,speed);
}

#if defined(HAS_MOTOR34)
void STEMDu::forwardM3(int speed){
	this->motor(3,speed);
}

void STEMDu::forwardM4(int speed){
	this->motor(4,speed);
}
#endif

void STEMDu::backwardM1(int speed){
	this->motor(1,-speed);
}

void STEMDu::backwardM2(int speed){
	this->motor(2,-speed);
}

#if defined(HAS_MOTOR34)
void STEMDu::backwardM3(int speed){
	this->motor(3,-speed);
}

void STEMDu::backwardM4(int speed){
	this->motor(4,-speed);
}
#endif

void STEMDu::stopM1(){
	this->motor(1,MOTOR_STOP);
}

void STEMDu::stopM2(){
	this->motor(2,MOTOR_STOP);
}

#if defined(HAS_MOTOR34)
void STEMDu::stopM3(){
	this->motor(3,MOTOR_STOP);
}

void STEMDu::stopM4(){
	this->motor(4,MOTOR_STOP);
}
#endif

void STEMDu::brakeM1(){
	this->motor(1,MOTOR_BRAKE);
}

void STEMDu::brakeM2(){
	this->motor(2,MOTOR_BRAKE);
}

#if defined(HAS_MOTOR34)
void STEMDu::brakeM3(){
	this->motor(3,MOTOR_BRAKE);
}

void STEMDu::brakeM4(){
	this->motor(4,MOTOR_BRAKE);
}
#endif

void STEMDu::forwardM1M2(int speed){
	this->motor(1,speed);
	this->motor(2,speed);
}

void STEMDu::backwardM1M2(int speed){
	this->motor(1,-speed);
	this->motor(2,-speed);
}

void STEMDu::leftM1M2(int speed){
	this->motor(1,-speed);
	this->motor(2,speed);
}

void STEMDu::rightM1M2(int speed){
	this->motor(1,speed);
	this->motor(2,-speed);
}

void STEMDu::stopM1M2(){
	this->motor(1,MOTOR_STOP);
	this->motor(2,MOTOR_STOP);
}

void STEMDu::brakeM1M2(){
	this->motor(1,MOTOR_BRAKE);
	this->motor(2,MOTOR_BRAKE);
}

#if defined(HAS_MOTOR34)
void STEMDu::forwardM3M4(int speed){
	this->motor(3,speed);
	this->motor(4,speed);
}

void STEMDu::backwardM3M4(int speed){
	this->motor(3,-speed);
	this->motor(4,-speed);
}

void STEMDu::leftM3M4(int speed){
	this->motor(3,-speed);
	this->motor(4,speed);
}

void STEMDu::rightM3M4(int speed){
	this->motor(3,speed);
	this->motor(4,-speed);
}

void STEMDu::stopM3M4(){
	this->motor(3,MOTOR_STOP);
	this->motor(4,MOTOR_STOP);
}

void STEMDu::brakeM3M4(){
	this->motor(3,MOTOR_BRAKE);
	this->motor(4,MOTOR_BRAKE);
}
#endif

int STEMDu::readSound(){
	return analogRead(P_SOUND);
}

int STEMDu::readLight(){
	return analogRead(P_LIGHT);
}

int STEMDu::readSlider(){
	return analogRead(P_SLIDER);
}

bool STEMDu::readPush(){
	pinMode(P_PUSH,INPUT_PULLUP);
	return !digitalRead(P_PUSH);
}

int STEMDu::readResistanceA(){
	return analogRead(P_RESISTA);
}

int STEMDu::readResistanceB(){
	return analogRead(P_RESISTB);
}

int STEMDu::readResistanceC(){
	return analogRead(P_RESISTC);
}

int STEMDu::readResistanceD(){
	return analogRead(P_RESISTD);
}

#if STEMDU > RDC_ESP32
void STEMDu::noTone(int pin){
	ledcSetup(LEDC_CHANNEL_TONE, LEDC_BASE_FREQ_TONE, LEDC_TIMER_BIT_TONE);
	ledcAttachPin(pin, LEDC_CHANNEL_TONE);
	ledcWriteTone(LEDC_CHANNEL_TONE, 0.0);
}
 
void STEMDu::tone(int pin, int freq){
	ledcSetup(LEDC_CHANNEL_TONE, LEDC_BASE_FREQ_TONE, LEDC_TIMER_BIT_TONE);
	ledcAttachPin(pin, LEDC_CHANNEL_TONE);
	ledcWriteTone(LEDC_CHANNEL_TONE, freq);
}

void STEMDu::tone(int pin, int freq, int duration){
	tone(pin, freq);
	delay(duration);
}

void STEMDu::analogWriteM1PWM(int val){
	ledcSetup(LEDC_CHANNEL_MOTOR1, LEDC_BASE_FREQ_MOTOR, LEDC_TIMER_BIT_MOTOR);
	ledcAttachPin(P_M1PWM, LEDC_CHANNEL_MOTOR1);
	ledcAnalogWrite(LEDC_CHANNEL_MOTOR1, val);
}

void STEMDu::analogWriteM2PWM(int val){
	ledcSetup(LEDC_CHANNEL_MOTOR2, LEDC_BASE_FREQ_MOTOR, LEDC_TIMER_BIT_MOTOR);
	ledcAttachPin(P_M2PWM, LEDC_CHANNEL_MOTOR2);
	ledcAnalogWrite(LEDC_CHANNEL_MOTOR2, val);
}

void STEMDu::analogWriteM3PWM(int val){
	ledcSetup(LEDC_CHANNEL_MOTOR3, LEDC_BASE_FREQ_MOTOR, LEDC_TIMER_BIT_MOTOR);
	ledcAttachPin(P_M3PWM, LEDC_CHANNEL_MOTOR3);
	ledcAnalogWrite(LEDC_CHANNEL_MOTOR3, val);
}

void STEMDu::analogWriteM4PWM(int val){
	ledcSetup(LEDC_CHANNEL_MOTOR4, LEDC_BASE_FREQ_MOTOR, LEDC_TIMER_BIT_MOTOR);
	ledcAttachPin(P_M4PWM, LEDC_CHANNEL_MOTOR4);
	ledcAnalogWrite(LEDC_CHANNEL_MOTOR4, val);
}

void STEMDu::analogWrite5(int val){
	ledcSetup(LEDC_CHANNEL_MOTOR1, LEDC_BASE_FREQ_MOTOR, LEDC_TIMER_BIT_MOTOR);
	ledcAttachPin(5, LEDC_CHANNEL_MOTOR1);
	ledcAnalogWrite(LEDC_CHANNEL_MOTOR1, val);
}

void STEMDu::analogWrite17(int val){
	ledcSetup(LEDC_CHANNEL_MOTOR2, LEDC_BASE_FREQ_MOTOR, LEDC_TIMER_BIT_MOTOR);
	ledcAttachPin(17, LEDC_CHANNEL_MOTOR2);
	ledcAnalogWrite(LEDC_CHANNEL_MOTOR2, val);
}

void STEMDu::analogWrite12(int val){
	ledcSetup(LEDC_CHANNEL_A12, LEDC_BASE_FREQ_MOTOR, LEDC_TIMER_BIT_MOTOR);
	ledcAttachPin(12, LEDC_CHANNEL_A12);
	ledcAnalogWrite(LEDC_CHANNEL_A12, val);
}

void STEMDu::analogWrite13(int val){
	ledcSetup(LEDC_CHANNEL_A13, LEDC_BASE_FREQ_MOTOR, LEDC_TIMER_BIT_MOTOR);
	ledcAttachPin(13, LEDC_CHANNEL_A13);
	ledcAnalogWrite(LEDC_CHANNEL_A13, val);
}

void STEMDu::analogWrite14(int val){
  	ledcAttachPin(14, LEDC_CHANNEL_A14);
	ledcSetup(LEDC_CHANNEL_A18, LEDC_BASE_FREQ_MOTOR, LEDC_TIMER_BIT_MOTOR);
	ledcAnalogWrite(LEDC_CHANNEL_A14, val);
}

void STEMDu::analogWrite18(int val){
	ledcSetup(LEDC_CHANNEL_A18, LEDC_BASE_FREQ_MOTOR, LEDC_TIMER_BIT_MOTOR);
	ledcAttachPin(18, LEDC_CHANNEL_A18);
	ledcAnalogWrite(LEDC_CHANNEL_A18, val);
}

void STEMDu::analogWrite19(int val){
	ledcSetup(LEDC_CHANNEL_A19, LEDC_BASE_FREQ_MOTOR, LEDC_TIMER_BIT_MOTOR);
	ledcAttachPin(19, LEDC_CHANNEL_A19);
	ledcAnalogWrite(LEDC_CHANNEL_A19, val);
}

void STEMDu::analogWrite25(int val){
	ledcSetup(LEDC_CHANNEL_A25, LEDC_BASE_FREQ_MOTOR, LEDC_TIMER_BIT_MOTOR);
	ledcAttachPin(25, LEDC_CHANNEL_A25);
	ledcAnalogWrite(LEDC_CHANNEL_A25, val);
}

void STEMDu::analogWrite26(int val){
	ledcSetup(LEDC_CHANNEL_A26, LEDC_BASE_FREQ_MOTOR, LEDC_TIMER_BIT_MOTOR);
	ledcAttachPin(26, LEDC_CHANNEL_A26);
	ledcAnalogWrite(LEDC_CHANNEL_A26, val);
}

void STEMDu::analogWrite27(int val){
	ledcSetup(LEDC_CHANNEL_A27, LEDC_BASE_FREQ_MOTOR, LEDC_TIMER_BIT_MOTOR);
	ledcAttachPin(27, LEDC_CHANNEL_A27);
	ledcAnalogWrite(LEDC_CHANNEL_A27, val);
}

void STEMDu::servo1(int val){
	ledcSetup(LEDC_CHANNEL_SERVO1, LEDC_BASE_FREQ_SERVO, LEDC_TIMER_BIT_SERVO);
	ledcAttachPin(12, LEDC_CHANNEL_SERVO1);
	ledcAnalogWrite(LEDC_CHANNEL_SERVO1, val);
}

#endif

#if defined(HAS_ONBBOARD_DISTANCE)

void STEMDu::initBuiltinDistance(){
  //analogWrite(P_IRLED,BUILTIN_DISTANCE_PWM);

  this->initBuiltinDistanceNoBuffer();
}

void STEMDu::initBuiltinDistanceNoBuffer(){
  for(int i = 0; i < BUILTIN_DISTANCE_BUFFER_SIZE; i++ ) {
    buf[i] = 0;
    out[i] = 0; 
  }
  buffer_index = 0;
  buffer_full = false;

  output = 0;

  // Lets sort out the filter variables before we end setup.

  // Cut-off frequency.
  // We are looking for a 38khz IR TV remote.
  // F is fraction of the sample frequency 
  // It has to be between 0 and 0.5.  Therefore, the interupt
  // needs to be at least *double* the bandpass frequency.
  // I picked 100khz as a nice number to scale from.
  // So, f = (100khz * 0.38) = 38Khz
  //f = 0.38;  
  f = 0.25;
  // Bandwidth (allowance) of bandpass filter.
  // Same principle as above (fraction of 100khz).
  // We are using this filter to get rid of ambient environment
  // noise.  20khz seems like a big band, but I wouldn't expect 
  // there to be much in the khz.  You can fine tune downwards.  
  //bw = 0.2;  
  bw = 0.1;

  // Maths. Read the book.  Does the trick.
  r = 1 - ( 3 * bw ); 
  k = 1 - ( 2 * r * cos(2 * PI * f ) ) + ( r * r );
  k = k / (2 - ( 2 * cos( 2 * PI * f ) ) );

  a0 = 1 - k;
  a1 = (2 * ( k -r ) ) * ( cos( 2 * PI * f ) );
  a2 = ( r * r ) - k;
  b1 = 2 * r * cos( 2 * PI * f );
  b2 = 0 - ( r * r );
}

double STEMDu::readBuiltinDistance(){

  //analogWrite(P_IRLED,BUILTIN_DISTANCE_PWM);
  
  if( buffer_index >= BUILTIN_DISTANCE_BUFFER_SIZE ) {
    buffer_index = 0;
    buffer_full = true; 
  } 
  else if ( buffer_full == false ){
    buf[ buffer_index ] = (double)analogRead(P_LIGHT);
    buffer_index++;  
  }

  if(buffer_full == true){
    // Run the input buffer through the filter
    output = doFilter();

    // We are going to transmit as an integer
    // Move up the decimal place
    //output *= 1000;
    //output -= 50;

    output *= 1000;
    output -= 2100; // Offset tuning 2cm:1600 2.8cm:1000

    output = 7000/sqrt(output); // Amplify

    // Reset our buffer and interupt routine
    buffer_index = 0;  
    buffer_full = false;
  }

  //analogWrite(P_IRLED,0);

  return output;
}

double STEMDu::readBuiltinDistanceNoBuffer(){
  buffer_index = 0;
  //analogWrite(P_IRLED,BUILTIN_DISTANCE_PWM);

  for(buffer_index=0;buffer_index<BUILTIN_DISTANCE_BUFFER_SIZE;buffer_index++){
    buf[ buffer_index ] = (double)analogRead(P_LIGHT);
  }

  // Run the input buffer through the filter
  output = doFilter();

  // We are going to transmit as an integer
  // Move up the decimal place
  //output *= 1000;
  //output -= 50;

  output *= 1000;
  output -= 2100; // Offset tuning 2cm:1600 2.8cm:1000

  output = 7000/sqrt(output); // Amplify

  // Reset our buffer and interupt routine
  buffer_index = 0;  
  buffer_full = false;

  //analogWrite(P_IRLED,0);

  return output;
}

// This filter looks at the previous elements in the 
// input stream and output stream to compound a pre-set
// amplification.  The amplification is set by a0,a1,a2,
// b1,b2.  Please see the linked book, above.
double STEMDu::doFilter() {
  int i;
  double sum;

  // Convolute the input buffer with the filter kernel
  // We work from 2 because we read back by 2 elements.
  // out[0] and out[1] are never set, so we clear them.
  out[0] = out[1] = 0;

  for( i = 2; i < BUILTIN_DISTANCE_BUFFER_SIZE; i++ ) {
    out[i] = a0 * buf[i];
    out[i] += a1 * buf[i-1];
    out[i] += a2 * buf[i-2];
    out[i] += b1 * out[i-1];
    out[i] += b2 * out[i-2]; 
  }

  // Bring all the output values above zero
  // To get a well reinforced average reading.
  for( i = 2; i < BUILTIN_DISTANCE_BUFFER_SIZE; i++ ) {
    if( out[i] < 0 ) out[i] *= -1;
    sum += out[i]; 
  }
  sum /= BUILTIN_DISTANCE_BUFFER_SIZE -2;

  return sum; 
}
#endif


#if defined(HAS_MPU6050)
float STEMDu::readTemperature(){
	return (accelgyro.getTemperature()+ 12412.0) / 340.0;
}
float STEMDu::readAccelX(){
	int16_t ax, ay, az;
    accelgyro.getAcceleration(&ax, &ay, &az);
	return ax / 16384.0;
}

float STEMDu::readAccelY(){
	int16_t ax, ay, az;
    accelgyro.getAcceleration(&ax, &ay, &az);
	return ay / 16384.0;
}

float STEMDu::readAccelZ(){
	int16_t ax, ay, az;
    accelgyro.getAcceleration(&ax, &ay, &az);
	return az / 16384.0;
}

float STEMDu::readGyroX(){
	int16_t gx, gy, gz;
    accelgyro.getRotation(&gx, &gy, &gz);
	return gx / 131.0;
}

float STEMDu::readGyroY(){
	int16_t gx, gy, gz;
    accelgyro.getRotation(&gx, &gy, &gz);
	return gy / 131.0;
}

float STEMDu::readGyroZ(){
	int16_t gx, gy, gz;
    accelgyro.getRotation(&gx, &gy, &gz);
	return gz / 131.0;
}
#endif

#if defined(HAS_PHREF)
int STEMDu::readPhRef(int num){
	if(num>0 && num<5){
		digitalWrite(P_MPX_PHREF1,LOW);
		digitalWrite(P_MPX_PHREF2,LOW);
		digitalWrite(P_MPX_PHREF3,LOW);
		digitalWrite(P_MPX_PHREF4,LOW);
		switch(num){
			case 1:
				digitalWrite(P_MPX_PHREF1,HIGH);
				break;
			case 2:
				digitalWrite(P_MPX_PHREF2,HIGH);
				break;
			case 3:
				digitalWrite(P_MPX_PHREF3,HIGH);
				break;
			case 4:
				digitalWrite(P_MPX_PHREF4,HIGH);
				break;
			default:
				digitalWrite(P_MPX_PHREF1,HIGH);
				break;
		}
		return analogRead(P_PHREF);
	}
	else{
		return 0; //num range error
	}
}

int STEMDu::readPhRef1(){
	return this->readPhRef(1);
}

int STEMDu::readPhRef2(){
	return this->readPhRef(2);
}

int STEMDu::readPhRef3(){
	return this->readPhRef(3);
}

int STEMDu::readPhRef4(){
	return this->readPhRef(4);
}
#endif

void STEMDu::led(bool val){
	digitalWrite(P_LED, val);
}

void STEMDu::led(int val){
#if STEMDU < RDC_ESP32
	analogWrite(P_LED, val);
#else
	ledcAnalogWrite(LEDC_CHANNEL_LED, val);
#endif
}