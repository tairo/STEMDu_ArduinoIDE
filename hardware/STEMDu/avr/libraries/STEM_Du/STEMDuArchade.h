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

<<<<<<< Updated upstream
#include "bitmap.h"

class STEMDuArchade : public Adafruit_SSD1306 {
    SpriteManager _spm;
public:
    STEMDuArchade();
    void addSprite(Sprite *sp);
    void drawSprites();
    void moveSpriteXY(int spid, int x, int y);
    void moveSpriteX(int spid, int x);
    void moveSpriteY(int spid, int y);
    bool isShow(int spid);
    void setShow(int spid, bool flag);
    void show(int spid);
    void hide(int spid);
    int width(int spid);
    int height(int spid);
    int direction(int spid);
    bool isCollideTo(int spid1, int spid2);
    bool isCollideAny(int spid);
};
=======
class Sprite {
    public:
    int x;
    int y;
    bool isShow;
    Sprite(int x, int y, bool isShow);
}
>>>>>>> Stashed changes

#endif