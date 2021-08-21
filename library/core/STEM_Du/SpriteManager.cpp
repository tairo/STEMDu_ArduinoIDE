#include <SpriteManager.h>

SpriteManager::SpriteManager(){

}

void SpriteManager::addSprite(Sprite *sp){
    if(this->_index >= MAX_SPRITE_NUMBER){
        return;
    }
    _sprites[this->_index] = *sp;
    this->_index++;
}

int SpriteManager::spriteNumber(){
    return this->_index;
}

Sprite SpriteManager::sprite(int index){
    if(index < this->_index){
        return this->_sprites[index];
    }
}

void SpriteManager::orderToFront(int spid){
    for(int i=0;i<=this->_index;i++){
        if(i < this->_index && this->_sprites[i].id() == spid){
            Sprite tmp = this->_sprites[i+1];
            this->_sprites[i+1] = this->_sprites[i];
            this->_sprites[i] = tmp;
            break;
        }
    }
}

void SpriteManager::orderToBack(int spid){
    for(int i=0;i<=this->_index;i++){
        if(i > 0 && this->_sprites[i].id() == spid){
            Sprite tmp = this->_sprites[i-1];
            this->_sprites[i-1] = this->_sprites[i];
            this->_sprites[i] = tmp;
            break;
        }
    }
}

void SpriteManager::orderToTop(int spid){
    for(int i=0;i<=this->_index;i++){
        int flag = 0;
        if(flag == 0 && i < this->_index -1 && this->_sprites[i].id() == spid){
            flag = 1;
        }
        if(flag == 1 && i < this->_index -1){
            Sprite tmp = this->_sprites[i+1];
            this->_sprites[i+1] = this->_sprites[i];
            this->_sprites[i] = tmp;
        }
    }
}

void SpriteManager::orderToBotttom(int spid){
    for(int i=this->_index;i>0;i--){
        int flag = 0;
        if(flag == 0 && i > 0 && this->_sprites[i].id() == spid){
            flag = 1;
        }
        if(flag == 1 && i > 0){
            Sprite tmp = this->_sprites[i-1];
            this->_sprites[i+1] = this->_sprites[i];
            this->_sprites[i] = tmp;
        }
    }
}

