/*
 STEM Du RDC-102 ScratchBoard compatible sketch
 
 modified by Tairo Nomura (tairo_nomura@mac.com)
 v.1.0 2013.12.25 adapted for JRTA1
 v.1.1 2014.2.25  adapted for RDC-102
 
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

// Sensor <--> Analog port mapping for JRTA1 and RDC-102
#define SoundSensor 0
#define LightSensor 4
#define Slider 5
#define ResistanceA 1
#define ResistanceB 2
#define ResistanceC 3
#define ResistanceD 4 // NOT implemented on JRTA1 and RDC-102
                      // replace as DigitalD

// Sensor <--> Digital port mapping for JRTA1 and RDC-102
#define Button 12     // implemented as digital inpurt on JRTA1 and RDC-102
#define DigitalD 11   // replacement of ResistanceD on JRTA1 and RDC-102

// motor port mapping fro JRTA1 and RDC-102
#define PWM_PIN_A 6
#define THISWAY_PIN_A 4
#define THATWAY_PIN_A 5
#define PWM_PIN_B 9
#define THISWAY_PIN_B 7
#define THATWAY_PIN_B 8
// JRTA1 and RDC-102 has 2 motor driver and can control 4 motors maximum
#define PWM_PIN_C 10
#define THISWAY_PIN_C 0
#define THATWAY_PIN_C 1

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

void setup() {
     setupSmoothing();  
     Serial.begin(38400);
     pinMode(13, OUTPUT);           // JRTA1 and RDC-102 LED port
     pinMode(Button, INPUT_PULLUP); // JRTA1 and RDC-102 PUSH button port

     // set pin mode for motor
     pinMode(PWM_PIN_A, OUTPUT);
     pinMode(THISWAY_PIN_A, OUTPUT);
     pinMode(THATWAY_PIN_A, OUTPUT);
     pinMode(PWM_PIN_B, OUTPUT);
     pinMode(THISWAY_PIN_B, OUTPUT);
     pinMode(THATWAY_PIN_B, OUTPUT);
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
            digitalWrite(13, HIGH);   // set JRTA1 and RDC-102 LED on
            
            // rotate motor
            motorPowerA = ((incomingByte >> 4) & B111) * 36;
            motorDirectionA = (incomingByte >> 7) & B1;
            isMotorOnA = motorPowerA > 0;
            analogWrite(PWM_PIN_A, motorPowerA);
            digitalWrite(THISWAY_PIN_A, motorDirectionA & isMotorOnA);
            digitalWrite(THATWAY_PIN_A, ~motorDirectionA & isMotorOnA);  
            motorPowerB = (incomingByte & B111) * 36;
            motorDirectionB = (incomingByte >> 3) & B1;
            isMotorOnB = motorPowerB > 0;
            analogWrite(PWM_PIN_B, motorPowerB);
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
  value = analogRead(adc);
  value = smoothingValue(adc, value, 5);
  if (value == 1022) value = 1023;
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
  sliderValue = analogRead(Slider);
  sliderValue = smoothingValue(Slider, sliderValue, 3);
  return sliderValue;
}

int readLight() {
  int light;
  light = 1024 - analogRead(LightSensor);
  light = calibrateLightSensor(light);
  light = smoothingValue(LightSensor,light, 20);
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
  sound = analogRead(SoundSensor);
  sound = smoothingValue(SoundSensor,sound, 20);
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
