//
// Sprite.h
//
// STEM Du Archade related class, function
//
// Update:Oct 13, 2020 1:13
//
// 1.0 2020101201 : Initial file
//

#ifndef Sprite_h
#define Sprite_h

#define SPRITE_WIDTH  8
#define SPRITE_HEIGHT 8

class Sprite {
    int _id;
    int _x;
    int _y;
    bool _isShow;
    int _width = SPRITE_WIDTH;
    int _height = SPRITE_HEIGHT;
    int _direction = 90; // 0~360 same manner as Scratch software
    int _bitmap_num = 0;
public:
    Sprite();
    Sprite(int id, int bitmap_num, int x, int y, bool isShow);
    void move(int x, int y);
    void moveX(int x);
    void moveY(int y);
    void moveDX(int dx);
    void moveDY(int dy);
    int abs_diff(int v1, int v2);
    bool intersect(Sprite *sp);
    int bitmapNumber();
    int id();
    int x();
    int y();
    bool isShow();
    int width();
    int height();
    int direction();
};

#endif