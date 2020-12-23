#include <STEMDuArchade.h>

STEMDuArchade::STEMDuArchade(){

}

void STEMDuArchade::addSprite(Sprite *sp){
    _spm.addSprite(sp);
}

void STEMDuArchade::drawSprites(){
    for(int i=0;i<_spm.spriteNumber();i++){
        Sprite tmp = _spm.sprite(i);
        this->drawBitmap(tmp.x(), tmp.y(), bmp[tmp.bitmapNumber()], SPRITE_WIDTH, SPRITE_HEIGHT, SSD1306_WHITE);
    }
}

void STEMDuArchade::addSprite(Sprite *sp){
    _spm.addSprite(sp);
}

void STEMDuArchade::moveSpriteXY(int spid, int x, int y){
    Sprite tmp = _smp.sprite(spid);
    tmp.move(x,y);
}

void STEMDuArchade::moveSpriteX(int spid, int x){

}

void STEMDuArchade::moveSpriteY(int spid, int y){

}

bool STEMDuArchade::isShow(int spid){

}

void STEMDuArchade::setShow(int spid, bool flag){

}

void STEMDuArchade::show(int spid){

}

void STEMDuArchade::hide(int spid){

}

int STEMDuArchade::width(int spid){

}

int STEMDuArchade::height(int spid){

}

int STEMDuArchade::direction(int spid){

}

bool STEMDuArchade::isCollideTo(int spid1, int spid2){

}

bool STEMDuArchade::isCollideAny(int spid){

}