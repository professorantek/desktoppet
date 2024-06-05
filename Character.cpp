#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <time.h>

class Character{
    private :
        IMG_Animation* animation = nullptr;
        std::vector<SDL_Texture*> sprites;
        const char* animationPath = nullptr;
        std::pair<int, int> pos = {1500, 800};
        int x3, y3;
        const int width = 32, height = 32;
        int frameIndex = 0;
        int lastTime = 0;

    public:
        bool SetAnimation(const char* path, SDL_Renderer *r){
            animationPath = path;
            if(animationPath == nullptr){
                return false;
            }
            animation = IMG_LoadAnimation(animationPath);
            if(animation == nullptr){
                return false;
            }
            for(int i=0; i<animation->count; i++){
                SDL_Texture* tex = SDL_CreateTextureFromSurface(r, animation->frames[i]); 
                sprites.push_back(tex);
            }
            
            return true;
        }
        void Move(int w, int h){
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
        void SetHoldPoint(){
            x3 = pos.first;
            y3 = pos.second;
        }
        void ForceMove(int x1, int y1, int x2, int y2){
            pos.first = x2-(x1-x3);
            pos.second = y2-(y1-y3);
            return;
        }
        void Animate(int now){
            if(now - lastTime>=*animation->delays){
                frameIndex = (frameIndex+1)%animation->count;
                lastTime = now;
            }
            
        }
        void Display(SDL_Renderer* r){
            SDL_Rect rect;
            rect.x = pos.first;
            rect.y = pos.second;
            rect.h = width;
            rect.w = height;
            SDL_RenderCopy(r, sprites[frameIndex], NULL, &rect);
        }
};





