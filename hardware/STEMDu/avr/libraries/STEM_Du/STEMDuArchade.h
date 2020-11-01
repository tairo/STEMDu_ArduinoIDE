//
// STEMDuArchade.h
//
// STEM Du Archade related class, function
//
// Update:Oct 13, 2020 1:13
//
// 1.0 2020101201 : Initial file
//

#ifndef STEM_Du_Archade_h
#define STEM_Du_Archade_h

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <SpriteManager.h>
#include <Sprite.h>

#include "bitmap.h"

class STEMDuArchade : public Adafruit_SSD1306 {
    SpriteManager _spm;
public:
    STEMDuArchade();
    void drawSprites();
};

#endif