/* 
  mgcld.h
  
  This file is part of Monochrome Graphic LCD library (MGLCD) for Arduino
  Uno/Mega 2560.
  
  MGLCD was developed by Synapse(Hiroshi Tanigawa) from 2012 to 2013.  This Library is
  originally distributed at Team Schaft's Homepage. 
  <http://www3.big.or.jp/~schaft/hardware>

  MGLCD is now under beta testing, so specification may be changed 
  in the future.

  MGLCD is free software: you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License as published by
  the Free Software Foundation, either version 2.1 of the License, or
  (at your option) any later version.

  MGLCD is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public License
  along with MGLCD.  If not, see <http://www.gnu.org/licenses/>.

*/

#ifndef MGLCD_H
#define MGLCD_H

#include <arduino.h>
#include <Print.h>

// version 
#define MGLCD_VERSION 34 // version 0.34
// Common constants
#define MGLCD_FONT_WIDTH  6   // width of font
#define MGLCD_FONT_HEIGHT 8   // height of font

// Constants for SetInvertMode
#define MGLCD_NON_INVERT 0
#define MGLCD_INVERT     1

// Constants for SetScrollMode
#define MGLCD_NON_SCROLL 0
#define MGLCD_SCROLL     1

// Constants for UserChars
#define MGLCD_ROM 0
#define MGLCD_RAM 1

// Constants for digitalPinToPort/digitalPinToBitMask functons
#ifdef __AVR_ATmega32U4__
#define MGLCD_NUM_DIGITAL_PINS 30 // for Leonardo
#else
#define MGLCD_NUM_DIGITAL_PINS NUM_DIGITAL_PINS // for others
#endif

// type definition
typedef unsigned char (*PDecodeFunc)(unsigned char);

// function prototypes
unsigned char MGLCD_CODE_STRAIGHT(unsigned char ch);
unsigned char MGLCD_CODE_UTF8(unsigned char ch);
signed char CodeModeToIndex(PDecodeFunc CodeMode);
PDecodeFunc IndexToCodeMode(unsigned char index);

#endif // #ifndef MGLCD_H
