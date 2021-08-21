#include "U8glib.h"
#include <STEMDu.h>

U8GLIB_AQM1248A_2X u8g(10,11); // Hw SPI CS=10, A0=11

/* Initialize STEM Du board */
STEMDu robot = STEMDu();

String lineBufferString;
char lineBuffer[16];

int soundValue; // Sound sensor
int lightValue; // Light sensor
int sliderValue; // Slider sensor
int pushValue; // Push button

void draw(void) {
  // graphic commands to redraw the complete screen should be placed here  
  u8g.setFont(u8g_font_unifont);
  //u8g.setFont(u8g_font_osb21);
  lineBufferString = String("");
  lineBufferString += "Sound = ";
  lineBufferString += soundValue;
  lineBufferString.toCharArray(lineBuffer,16);
  u8g.drawStr(0, 11, lineBuffer);
  lineBufferString = String("");
  lineBufferString += "Light = ";
  lineBufferString += lightValue;
  lineBufferString.toCharArray(lineBuffer,16);
  u8g.drawStr(0, 23, lineBuffer);
  lineBufferString = String("");
  lineBufferString += "Slider = ";
  lineBufferString += sliderValue;
  lineBufferString.toCharArray(lineBuffer,16);
  u8g.drawStr(0, 35, lineBuffer);
  lineBufferString = String("");
  lineBufferString += "Button = ";
  lineBufferString += pushValue;
  lineBufferString.toCharArray(lineBuffer,16);
  u8g.drawStr(0, 47, lineBuffer);
}

void setup(void) {
  // flip screen, if required
  //u8g.setRot180();
  
  // set SPI backup if required
  //u8g.setHardwareBackup(u8g_backup_avr_spi);

}

void loop(void) {
  // read the input on analog port
  soundValue = robot.readSound(); // Sound sensor
  lightValue = robot.readLight(); // Light sensor
  sliderValue = robot.readSlider(); // Slider sensor
  pushValue = robot.readPush(); // Push button

  // picture loop
  u8g.firstPage();  
  do {
    draw();
  } while( u8g.nextPage() );
  
  // rebuild the picture after some delay
  delay(50);
}

