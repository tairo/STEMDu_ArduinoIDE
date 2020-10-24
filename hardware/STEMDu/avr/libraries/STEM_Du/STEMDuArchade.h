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

#include "bitmap.h"

class Sprite {
    public:
    int x;
    int y;
    bool isShow;
    Sprite(int x, int y, bool isShow);
}

#endif