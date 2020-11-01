#ifndef SpriteManager_h
#define SpriteManager_h

#include <Sprite.h>

#define MAX_SPRITE_NUMBER 16

class SpriteManager {
    Sprite _sprites[MAX_SPRITE_NUMBER];
    int _index = 0;

public:
    SpriteManager();
    void addSprite(Sprite *sp);
    int spriteNumber();
    Sprite sprite(int index);
    void orderToFront(int spid);
    void orderToBack(int spid);
    void orderToTop(int spid);
    void orderToBotttom(int spid);
};

#endif