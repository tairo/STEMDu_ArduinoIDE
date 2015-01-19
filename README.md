STEMDu_ArduinoIDE
=================

Pre-bundled Arduino IDE for STEM Du
- Including STEM Du hardware profiles (boards.txt, variant and bootloader)
- Including windows CDC USB driver file (only windows package)
- Including Ardublock tool
  - https://github.com/tairo/STEMDu_Ardublock
- Including I2CLiquidCrystal library
  - http://n.mtng.org/ele/arduino/i2c.html
- Including U8glib libray
  - http://code.google.com/p/u8glib/

Current packege is based on Arduino IDE v.1.0.5. You can find original from http://arduino.cc/en/Main/Software

Windows
* http://www.stem-edulab.org/uploads/arduino-1.0.5-r2-stemdu12.zip 
You need to install the device driver in the folder /drivers. To install on Windows 8/8.1 you have to do in the special way i.e next link.

How to Disable Driver Signature Verification on 64-Bit Windows 8.1?
http://mywindows8.org/disable-driver-signature-verification-on-64-bit-windows-8-1/

MacOSX
* http://www.stem-edulab.org/uploads/Arduino_0105_for_STEM_Du_12.zip

You can also find pre-bundled additional files separately from https://github.com/tairo/STEMDu

HISTORY
-------
- v12 2014/08/09 10:41 Fix ArduBlockTool bug (M3M4Backward)
- v11 2014/08/09 10:00 Add U8glib library for SPI Graphic LCD (R3)
