//
// STEMDu.h
//
// STEM Du 102/103/104/ESP32 Library Header File
//
// Update:Oct 10, 2020 7:47
//
// 2.0 20201009 : Officially Support ESP32
// 1.0 20191227 : Add experimental support of ESP32
//

#ifndef STEM_Du_h
#define STEM_Du_h

#define NANOBOARD_AG     990
#define CHIBIDUINO       991
#define JRTA1            999
#define RDC_102         1020
#define RDC_102_NO_MARK 1020
#define RDC_102_R0      1021
#define RDC_102_R1      1022
#define RDC_102_R2      1023
#define RDC_102_R3      1024
#define RDC_103         1030
#define RDC_103_R1      1031
#define RDC_103_R2      1032
#define RDC_103_R3      1033
#define RDC_103_R4      1034
#define RDC_103_R5      1035
#define RDC_104         1040
#define RDC_104_R1      1041
#define RDC_104_R2      1042
// PencilProgrammer
#define RDC_PP328		2000 //5bit 328
#define RDC_PP			2010 //5bit 32U4
#define RDC_PP2			2020 //4bit 32U4
#define RDC_PP2_R1		2021
#define RDC_PP2_R2		2022
#define RDC_PP2_R3		2023
#define RDC_PP2_R4		2024
// RDC-ESP32
#define RDC_ESP32		3000
#define RDC_ESP32_R1	3001
#define RDC_ESP32_R2	3002

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "pitches.h"

////////////////////////////////////////////////////////

#define HAS_MOTOR12 1
#define HAS_MOTOR34 2
#define HAS_PICOBOARD_SENSOR 3

#if STEMDU <= RDC_102_R3

#define HAS_I2C_LCD 4 // I2C LCD 8x2
#define HAS_PHREF 5
#define HAS_TWL 6

#else //RDC_103 or upper

#define HAS_ONBBOARD_DISTANCE 9
#define HAS_MPU6050 8

#if STEMDU >= RDC_104

#define HAS_I2C_LCD 4
#undef HAS_MPU6050

#else

#define HAS_SPI_LCD 7 // SPI Graphic 128x64
#define HAS_MPU6050 8

#endif // STEMDU >= RDC_104
#endif // STEMDU <= RDC_102_R3

////////////////////////////////////////////////////////

#if defined(HAS_MPU6050)
#include <Wire.h>
#include <I2Cdev.h>
#include <MPU6050.h>
#endif

#if defined(HAS_I2C_LCD)
#if STEMDU <= RDC_102_R3
// RDC_102 ==> AQM0802A-RN-GBW 8x2
#define STEMDU_I2CLCD_WIDTH 8
#define STEMDU_I2CLCD_HEIGHT 2
#else
// RDC_104 ==> AQM1602Y-RN-GBW 16x2
#define STEMDU_I2CLCD_WIDTH 16
#define STEMDU_I2CLCD_HEIGHT 2
#endif
#include <I2CLiquidCrystal.h>
#include <Wire.h>
#endif

#if defined(HAS_ONBBOARD_DISTANCE)
#define BUILTIN_DISTANCE_BUFFER_SIZE 45     // use an odd number
#define BUILTIN_DISTANCE_PWM 218
#define P_IRLED  11
#endif

#if defined(HAS_SPI_LCD)
#define SPILCD_CS 10
#if STEMDU < RDC_103_R4
#define SPILCD_RS 11
#else
#define SPILCD_RS 1
#endif
#define STEMDU_SPILCD_WIDTH 16
#define STEMDU_SPILCD_HEIGHT 4
#endif

#if defined(HAS_PHREF)
#define P_PHREF  3
#define P_MPX_PHREF1 0
#define P_MPX_PHREF2 1
#define P_MPX_PHREF3 10
#define P_MPX_PHREF4 11
#endif

////////////////////////////////////////////////////////

#define MOTOR_STOP  0
#define MOTOR_BRAKE 1023

#if STEMDU == NANOBOARD_AG || STEMDU == CHIBIDUINO
#define P_M1IN1 7
#define P_M1IN2 8
#define P_M1PWM 9
#define P_M2IN1 5
#define P_M2IN2 6
#define P_M2PWM 10
#else
#if STEMDU <= RDC_103_R4
#define P_M1IN1 4
#define P_M1IN2 5
#define P_M1PWM 6
#define P_M2IN1 7
#define P_M2IN2 8
#define P_M2PWM 9
#else
#if STEMDU < RDC_ESP32
#define P_M1IN1 4
#define P_M1IN2 9
#define P_M1PWM 6
#define P_M2IN1 7
#define P_M2IN2 8
#define P_M2PWM 5
#else
#define P_M1IN1 2
#define P_M1IN2 4
#define P_M1PWM 5
#define P_M2IN1 15
#define P_M2IN2 16
#define P_M2PWM 17
#endif
#endif
#if STEMDU == JRTA_1
// Only JRTA-1
#define P_M3IN1 10
#define P_M3IN2 11
#define P_M3PWM 12
#define P_M4IN1 0
#define P_M4IN2 1
#define P_M4PWM 13
#else
#if STEMDU <= RDC_103_R4
#define P_M3IN1 0
#define P_M3IN2 1
#define P_M3PWM 10
#define P_M4IN1 11
#define P_M4IN2 12
#define P_M4PWM 13
#else
#if STEMDU < RDC_ESP32
#define P_M3IN1 0
#define P_M3IN2 1
#define P_M3PWM 11
#define P_M4IN1 10
#define P_M4IN2 12
#define P_M4PWM 13
#else
#define P_M3IN1 12
#define P_M3IN2 13
#define P_M3PWM 14
#define P_M4IN1 25
#define P_M4IN2 26
#define P_M4PWM 27
#endif
#endif
#endif
#endif

////////////////////////////////////////////////////////

#if STEMDU < RDC_ESP32
#define P_PUSH   12
#define P_LED    13
#else
#define P_PUSH   18
#define P_LED    19
#endif

#if STEMDU < RDC_104
#define P_SOUND  A0
#define P_LIGHT  A4
#define P_SLIDER A5

#define P_RESISTA A0
#define P_RESISTB A1
#define P_RESISTC A2
#define P_RESISTD A3
#else
#if STEMDU < RDC_ESP32
#define P_SOUND  A4
#define P_LIGHT  A2
#define P_SLIDER A3

#define P_RESISTA A0
#define P_RESISTB A1
#define P_RESISTC A5 //pull up
#define P_RESISTD A3 //dummy
#else
#define P_SOUND  A5
#define P_LIGHT  A6
#define P_SLIDER A7

#define P_RESISTA A6 //dummy
#define P_RESISTB A7 //dummy
#define P_RESISTC A4 //pull up
#define P_RESISTD A5 //dummy
#endif
#endif

////////////////////////////////////////////////////////

class STEMDu {
public:
  STEMDu();

  void init();
  
  //Motor
  void motor(int n, int speed);

  //Motor Helper method for robot control
  void move(int n1, int n2, int angle, int speed);
  void turn(int n1, int n2, int turnSpeed);
  void tank(int n1, int n2, int speed1, int speed2);

  void moveM1M2(int angle, int speed);
  void turnM1M2(int turnSpeed);
  void tankM1M2(int speed1, int speed2);

#if defined(HAS_MOTOR34)
  void moveM3M4(int angle, int speed);
  void turnM3M4(int turnSpeed);
  void tankM3M4(int speed3, int speed4);
#endif

  void forwardM1M2(int speed);
  void backwardM1M2(int speed);
  void leftM1M2(int speed);
  void rightM1M2(int speed);
  void stopM1M2();
  void brakeM1M2();

#if defined(HAS_MOTOR34)
  void forwardM3M4(int speed);
  void backwardM3M4(int speed);
  void leftM3M4(int speed);
  void rightM3M4(int speed);
  void stopM3M4();
  void brakeM3M4();
#endif

  void forwardM1(int speed);
  void forwardM2(int speed);

#if defined(HAS_MOTOR34)
  void forwardM3(int speed);
  void forwardM4(int speed);
#endif

  void backwardM1(int speed);
  void backwardM2(int speed);

#if defined(HAS_MOTOR34)
  void backwardM3(int speed);
  void backwardM4(int speed);
#endif

  void stopM1();
  void stopM2();

#if defined(HAS_MOTOR34)
  void stopM3();
  void stopM4();
#endif

  void brakeM1();
  void brakeM2();

#if defined(HAS_MOTOR34)
  void brakeM3();
  void brakeM4();
#endif

  //Sensor
  int readSound();
  int readLight();
  int readSlider();
  void initPush();
  bool readPush();
  int readResistanceA();
  int readResistanceB();
  int readResistanceC();
  int readResistanceD();

#if STEMDU > RDC_ESP32
  void noTone(int pin);
  void tone(int pin, int freq);
  void tone(int pin, int freq, int duration);

  void analogWrite12(int val);
  void analogWrite13(int val);
  void analogWrite14(int val);
  void analogWrite18(int val);
  void analogWrite19(int val);
  void analogWrite25(int val);
  void analogWrite26(int val);
  void analogWrite27(int val);
#endif

#if defined(HAS_MPU6050)
  float readTemperature();
  float readAccelX();
  float readAccelY();
  float readAccelZ();
  float readGyroX();
  float readGyroY();
  float readGyroZ();
#endif

#if defined(HAS_ONBBOARD_DISTANCE)
  void initBuiltinDistance();
  void initBuiltinDistanceNoBuffer();
  double readBuiltinDistance();
  double readBuiltinDistanceNoBuffer();
#endif 

#if defined(HAS_PHREF)
  int readPhRef(int num);
  int readPhRef1();
  int readPhRef2();
  int readPhRef3();
  int readPhRef4();
#endif

  //LED
  void led(bool val);
  void led(int val);
  
  //
private:
#if defined(HAS_ONBBOARD_DISTANCE)
  // Global variables.
  double buf[BUILTIN_DISTANCE_BUFFER_SIZE];  // Analog readings at 100khz & stored here
  double out[BUILTIN_DISTANCE_BUFFER_SIZE];  // output of filter stored here.
  int buffer_index;         // Interupt increments buffer
  boolean buffer_full;      // Flag for when complete.

  double a0,a1,a2,b1,b2; // filter kernel poles
  double f,bw;           // frequency cutoff and bandwidth
  double r,k;            // filter coefficients

  double output;

  double doFilter();
#endif

#if defined(HAS_MPU6050)
  MPU6050 accelgyro;
#endif
};

#endif //STEM_Du_h
