#include <STEMDuArchade.h>

STEMDuArchade::STEMDuArchade(){

}

void STEMDuArchade::drawSprites(){
    for(int i=0;i<_spm.spriteNumber();i++){
        Sprite tmp = _spm.sprite(i);
        this->drawBitmap(tmp.x(), tmp.y(), bmp[tmp.bitmapNumber()], SPRITE_WIDTH, SPRITE_HEIGHT, SSD1306_WHITE);
    }
}
