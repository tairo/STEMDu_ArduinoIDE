#include <Sprite.h>

Sprite::Sprite(){

}

Sprite::Sprite(int id, int bitmap_num, int x, int y, bool isShow){
    this->_id = id;
    this->_bitmap_num = bitmap_num;
    this->_x = x;
    this->_y = y;
    this->_isShow = isShow;
}

int Sprite::bitmapNumber(){
    return this->_bitmap_num;
}

void Sprite::move(int x, int y){
    this->_x = x;
    this->_y = y;
}

void Sprite::moveX(int x){
    this->_x = x;
}

void Sprite::moveY(int y){
    this->_y = y;
}

void Sprite::moveDX(int dx){
    this->_x += dx;
}

void Sprite::moveDY(int dy){
    this->_y += dy;
}

int Sprite::abs_diff(int v1, int v2){
    if(v1>v2){
        return v1 - v2;
    }
    else{
        return v2 - v1;
    }
}

bool Sprite::intersect(Sprite *sp){
    if(abs_diff(this->_x, sp->_x) < SPRITE_WIDTH
        && abs_diff(this->_y, sp->_y) < SPRITE_HEIGHT){
        return true;
    }
    else{
        return false;
    }
}

int Sprite::id(){
    return _id;
}

int Sprite::x(){
    return _x;
}

int Sprite::y(){
    return _y;
}

bool Sprite::isShow(){
    return _isShow;
}

int Sprite::width(){
    return _width;
}

int Sprite::height(){
    return _height;
}

int Sprite::direction(){
    return _direction;
}