#include <STEMDuArchade.h>

STEMDuArchade::STEMDuArchade(){

}

void STEMDuArchade::addSprite(Sprite *sp){
    this->_spm.addSprite(sp);
}

void STEMDuArchade::drawSprites(){
    for(int i=0;i<this->_spm.spriteNumber();i++){
        Sprite tmp = this->_spm.sprite(i);
        this->drawBitmap(tmp.x(), tmp.y(), bmp[tmp.bitmapNumber()], SPRITE_WIDTH, SPRITE_HEIGHT, SSD1306_WHITE);
    }
}

void STEMDuArchade::moveSpriteXY(int spid, int x, int y){
    Sprite tmp = this->_spm.sprite(spid);
    tmp.move(x,y);
}

void STEMDuArchade::moveSpriteX(int spid, int x){

}

void STEMDuArchade::moveSpriteY(int spid, int y){

}

bool STEMDuArchade::isShow(int spid){
    return false;
}

void STEMDuArchade::setShow(int spid, bool flag){

}

void STEMDuArchade::show(int spid){

}

void STEMDuArchade::hide(int spid){

}

int STEMDuArchade::width(int spid){
    return 0;
}

int STEMDuArchade::height(int spid){
    return 0;
}

int STEMDuArchade::direction(int spid){
    return 0;
}

bool STEMDuArchade::isCollideTo(int spid1, int spid2){
    return false;
}

bool STEMDuArchade::isCollideAny(int spid){
    return false;
}