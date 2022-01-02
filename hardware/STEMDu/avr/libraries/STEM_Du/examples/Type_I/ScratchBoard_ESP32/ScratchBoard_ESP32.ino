/*
 STEM Du RDC-104 ScratchBoard compatible sketch
 
 modified by Tairo Nomura (tairo_nomura@mac.com)
 v.1.0 2013.12.25 adapted for JRTA1
 v.1.1 2014.2.25  adapted for RDC-102
 v.1.2 2018.1.20  adapted for RDC-104
 v.1.3 2020.5.10  adapted for RDC-ESP32
 =====
 Based on following contributions.

 - BASED ON NanoBoard and NanoBoardAG
 
 mod 7 July, 2011
 by tiisai.dip.jp

 Add multipule motor function for NanoBoardAG on 11 June 2012
 by Kazuhiro Abe <abee@squeakland.jp>

 - BASED ON HelloBoardV2 

 Created 30 October. 2009
 by PINY and Song Hojun.
*/

#include <STEMDu.h>

// Sensor <--> Analog port mapping for JRTA1 and RDC-102
#define SoundSensor P_SOUND
#define LightSensor P_LIGHT
#define Slider P_SLIDER
#define ResistanceA P_RESISTA
#define ResistanceB P_RESISTB
#define ResistanceC P_RESISTC
#define ResistanceD P_RESISTD // NOT implemented on JRTA1 and RDC-102
                              // replace as DigitalD

// Sensor <--> Digital port mapping for JRTA1 and RDC-102
#define Button P_PUSH // implemented as digital inpurt on JRTA1 and RDC-102
#define DigitalD 11   // replacement of ResistanceD on JRTA1 and RDC-102

// motor port mapping fro JRTA1 and RDC-102
#define PWM_PIN_A P_M1PWM
#define THISWAY_PIN_A P_M1IN1
#define THATWAY_PIN_A P_M1IN2
#define PWM_PIN_B P_M2PWM
#define THISWAY_PIN_B P_M2IN1
#define THATWAY_PIN_B P_M2IN2

int sliderValue = 0;
int lightValue = 0;
int soundValue = 0;
int buttonValue = 0;
int pushsw_flag = 0;
int resistanceAValue = 0;
int resistanceBValue = 0;
int resistanceCValue = 0;
int resistanceDValue = 0;

unsigned long lastIncommingMicroSec = 0;

uint8_t incomingByte;

const int sensorChannels = 8;
const int maxNumReadings = 30;

int smoothingValues[sensorChannels][maxNumReadings];
int smoothingIndex[sensorChannels];
int smoothingTotal[sensorChannels];

// motor variables
byte motorDirectionA = 0;
byte isMotorOnA = 0;
byte motorPowerA = 0;
byte motorDirectionB = 0;
byte isMotorOnB = 0;
byte motorPowerB = 0;

#if STEMDU > RDC_ESP32
// use first channel of 16 channels (started from zero)
#define LEDC_CHANNEL_0     0
#define LEDC_CHANNEL_1     1
// use 13 bit precission for LEDC timer
#define LEDC_TIMER_13_BIT  13
// use 5000 Hz as a LEDC base frequency
#define LEDC_BASE_FREQ     4900

void ledcAnalogWrite(uint8_t channel, uint32_t value, uint32_t valueMax = 255);

/*
// Arduino like analogWrite
// value has to be between 0 and valueMax
void ledcAnalogWrite(uint8_t channel, uint32_t value, uint32_t valueMax = 255) {
  // calculate duty, 8191 from 2 ^ 13 - 1
  uint32_t duty = (8191 / valueMax) * min(value, valueMax);

  // write duty to LEDC
  ledcWrite(channel, duty);
}
*/
#endif

void setup() {
     setupSmoothing();  
     Serial.begin(38400);
     pinMode(13, OUTPUT);           // JRTA1 and RDC-102 LED port
     pinMode(Button, INPUT_PULLUP); // JRTA1 and RDC-102 PUSH button port

#if STEMDU > RDC_ESP32
     // Setup timer and attach timer to a led pin
     ledcSetup(LEDC_CHANNEL_0, LEDC_BASE_FREQ, LEDC_TIMER_13_BIT);
     ledcSetup(LEDC_CHANNEL_1, LEDC_BASE_FREQ, LEDC_TIMER_13_BIT);
     ledcAttachPin(PWM_PIN_A, LEDC_CHANNEL_0);
     ledcAttachPin(PWM_PIN_B, LEDC_CHANNEL_1);
     // set pin mode for motor
     pinMode(THISWAY_PIN_A, OUTPUT);
     pinMode(THATWAY_PIN_A, OUTPUT);
     pinMode(THISWAY_PIN_B, OUTPUT);
     pinMode(THATWAY_PIN_B, OUTPUT);
#else
     // set pin mode for motor
     pinMode(PWM_PIN_A, OUTPUT);
     pinMode(THISWAY_PIN_A, OUTPUT);
     pinMode(THATWAY_PIN_A, OUTPUT);
     pinMode(PWM_PIN_B, OUTPUT);
     pinMode(THISWAY_PIN_B, OUTPUT);
     pinMode(THATWAY_PIN_B, OUTPUT);
#endif
}

void setupSmoothing() {
     for(int i = 0; i < sensorChannels; i++) {
       for(int j = 0 ; j < maxNumReadings ; j++) {
         smoothingValues[i][j]=0;
       }
     smoothingTotal[i]=0;
     smoothingIndex[i]=0;
     }
}

void loop() {
    readSensors();

    if( Serial.available() > 0) {
        incomingByte = Serial.read();
        if (incomingByte >= 0x00) {

 /* DEBUG
    if(1){
        if(1){
  */
            digitalWrite(13, HIGH);   // set JRTA1 and RDC-102 LED on
            
            // rotate motor
            motorPowerA = ((incomingByte >> 4) & B111) * 36;
            motorDirectionA = (incomingByte >> 7) & B1;
            isMotorOnA = motorPowerA > 0;

#if STEMDU > RDC_ESP32
            ledcAnalogWrite(LEDC_CHANNEL_0, motorPowerA);
#else
            analogWrite(PWM_PIN_A, motorPowerA);
#endif
            digitalWrite(THISWAY_PIN_A, motorDirectionA & isMotorOnA);
            digitalWrite(THATWAY_PIN_A, ~motorDirectionA & isMotorOnA);  
           
            motorPowerB = (incomingByte & B111) * 36;
            motorDirectionB = (incomingByte >> 3) & B1;
            isMotorOnB = motorPowerB > 0;
            
#if STEMDU > RDC_ESP32
            ledcAnalogWrite(LEDC_CHANNEL_1, motorPowerB);
#else
            analogWrite(PWM_PIN_B, motorPowerB);
#endif
            digitalWrite(THISWAY_PIN_B, motorDirectionB & isMotorOnB);
            digitalWrite(THATWAY_PIN_B, ~motorDirectionB & isMotorOnB);  

            sendFirstSecondBytes(15, 0x04);
            sendFirstSecondBytes(0, resistanceDValue);  
            sendFirstSecondBytes(1, resistanceCValue);
            sendFirstSecondBytes(2, resistanceBValue);
            sendFirstSecondBytes(3, buttonValue);
            sendFirstSecondBytes(4, resistanceAValue);
            sendFirstSecondBytes(5, lightValue);
            sendFirstSecondBytes(6, soundValue);
            sendFirstSecondBytes(7, sliderValue);

/* DEBUG
  Serial.print("slider:");
  Serial.print(sliderValue);
  Serial.print(" ");
  Serial.print("sound:");
  Serial.print(soundValue);
  Serial.print(" ");
  Serial.print("light:");
  Serial.print(lightValue);
  Serial.println();
*/
           digitalWrite(13, LOW);    // set JRTA1 and RDC-102 LED off
        }  
    }        
}

void readSensors() {
    sliderValue = readSlider();
    lightValue = readLight();
    soundValue = readSound();
    buttonValue = readButton();
    
    resistanceAValue = readResistance(ResistanceA);
    resistanceBValue = readResistance(ResistanceB);
    resistanceCValue = readResistance(ResistanceC);
    resistanceDValue = readDigital(DigitalD);       // replace as digital input
}

int readButton() {
  if(digitalRead(Button) == 1){
    return 1023;
  }
  else{
    return 0;
  }

  /*
  int pushsw_sample1 = digitalRead(Button);
  delay(10);
  int pushsw_sample2 = digitalRead(Button);
  if(pushsw_sample1 == pushsw_sample2){
    if(pushsw_sample1 == 0 && pushsw_flag == 0){
      pushsw_flag = 1;
    }
    else if(pushsw_sample1 == 1 && pushsw_flag == 1){
      pushsw_flag = 0;
    }
  }
  if(pushsw_flag == 1){
    return 0;
  }
  else{
    return 1023;
  }
  */
}

int readResistance(int adc) {
  int value;
#if STEMDU > RDC_ESP32
  value = map(analogRead(adc),0,4095,0,1023);
#else
  value = analogRead(adc);
#endif
//  value = smoothingValue(adc, value, 5);
//  if (value == 1022) value = 1023;
  return value;
}

int readDigital(int adc) {
  if(digitalRead(adc) == 1){
    return 1023;
  }
  else{
    return 0;
  }
}

int readSlider() {
  int sliderValue;
#if STEMDU > RDC_ESP32
  sliderValue = map(analogRead(Slider),0,4095,0,1023);
//  Serial.println(sliderValue);
#else
  sliderValue = analogRead(Slider);
#endif
  //sliderValue = smoothingValue(Slider, sliderValue, 3);
  return sliderValue;
}

int readLight() {
  int light;
#if STEMDU > RDC_ESP32
  light = 1024 - map(analogRead(LightSensor),0,4095,0,1023);
#else
  light = 1024 - analogRead(LightSensor);
#endif
  light = calibrateLightSensor(light);
  //light = smoothingValue(LightSensor,light, 20);
  return light;
}

int calibrateLightSensor(int light) {
    // make s-curve
    int mid = 600;
    int mid2 = 900;
    if ( light < mid) {
        light = int(round((40.0/mid)*light));
    } else if (light < mid2) {
        light = int(round((mid2-40)/(mid2-float(mid))* light) - 1680);
    }
    light = constrain(light, 0, 1023);    
    return light;
}

int smoothingValue(int channel, int value, int numReadings) {
    int total;
    int index = smoothingIndex[channel];
    total = smoothingTotal[channel] - smoothingValues[channel][index];
    smoothingValues[channel][index] = value;
    smoothingTotal[channel] = total + value;
    smoothingIndex[channel]++;
    if(smoothingIndex[channel] >=numReadings) {
      smoothingIndex[channel]=0;
    }
    return int(round(smoothingTotal[channel] / (numReadings)));
}

int readSound() {
  int sound;
#if STEMDU > RDC_ESP32
  sound = map(analogRead(SoundSensor),0,4095,0,1023);
#else
  sound = analogRead(SoundSensor);
#endif
  //sound = smoothingValue(SoundSensor,sound, 20);
  // noise ceiling 
  if (sound < 60) { sound = 0; }
  return sound;
}

void sendFirstSecondBytes(byte channel, int value) {
      byte firstByte;
      byte secondByte;
      firstByte = (1 << 7) | (channel << 3) | (value >> 7);
      secondByte = value & 0b01111111 ;

      Serial.write(firstByte);  
      Serial.write(secondByte);
}
