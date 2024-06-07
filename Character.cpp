#include "Character.h"
 
bool Character::SetAnimation(std::string path, SDL_Renderer *r){
    animationPath = path;
    if(animationPath == ""){
        return false;
    }
    const char* p = animationPath.c_str();
    animation = IMG_LoadAnimation(p);
    if(animation == nullptr){
        return false;
    }
    for(int i=0; i<animation->count; i++){
        SDL_Texture* tex = SDL_CreateTextureFromSurface(r, animation->frames[i]); 
        sprites.push_back(tex);
    }
    
    return true;
}
void Character::Move(int w, int h){
    srand(time(0));
    int dir = rand()%4;
    switch(dir){
        case 0:{
            pos.first++;
            if(pos.first+width>w){
                pos.first--;
            }
            break;
        }
        case 1:{
            pos.second++;
            if(pos.second+height>h){
                pos.second--;
            }
            break;
        }
        case 2:{
            pos.first--;
            if(pos.first<width){
                pos.first++;
            }
            break;
        }
        case 3:{
            pos.second--;
            if(pos.second<height){
                pos.second++;
            }
            break;
        }
    }    
    return;
}
void Character::SetHoldPoint(){
    x3 = pos.first;
    y3 = pos.second;
}
void Character::ForceMove(int x1, int y1, int x2, int y2){
    pos.first = x2-(x1-x3);
    pos.second = y2-(y1-y3);
    return;
}
void Character::Animate(int now){
    if(now - lastTime>=*animation->delays){
        frameIndex = (frameIndex+1)%animation->count;
        lastTime = now;
    }
    
}
void Character::Display(SDL_Renderer* r){
    SDL_Rect rect;
    rect.x = pos.first;
    rect.y = pos.second;
    rect.h = height;
    rect.w = width;
    SDL_RenderCopy(r, sprites[frameIndex], NULL, &rect);
}






