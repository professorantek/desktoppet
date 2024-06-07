#include <SDL2/SDL_syswm.h>
#include <windows.h>
#include "Character.h"

#define TICKS_PER_FRAME (1000/60)

const int DISPLAYW = 1920, DISPLAYH = 1080;
const char* title = "WindowPet";
std::string animationPath = "animation.gif";
int lastTime = 0, x, y;
bool var = true, holding = false;
SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
Character c;

void CreateWindowAndRenderer(){
    SDL_SetMainReady();
    SDL_Init(SDL_INIT_EVERYTHING);
    Uint32 flags = SDL_WINDOW_BORDERLESS|SDL_WINDOW_SKIP_TASKBAR|SDL_WINDOW_TOOLTIP;
    window = SDL_CreateWindow(title, 0, 0, DISPLAYW, DISPLAYH, flags);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_RenderSetScale(renderer, 1,1);
}

bool MakeWindowTransparent(SDL_Window* window, COLORREF colorKey) {
    SDL_SysWMinfo wmInfo;
    SDL_VERSION(&wmInfo.version);
    SDL_GetWindowWMInfo(window, &wmInfo);
    HWND hWnd = wmInfo.info.win.window;
    SetWindowLong(hWnd, GWL_EXSTYLE, GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);
    return SetLayeredWindowAttributes(hWnd, colorKey, 0, LWA_COLORKEY);
}

void EventProcesser(){
    int x2,y2;
    SDL_Event event;
    if(SDL_PollEvent(&event)){
        if(event.type == SDL_KEYDOWN){
            switch(event.key.keysym.sym){
                case SDLK_ESCAPE:{
                    var = false;
                    break;
                }
            }
        }
        if(event.type == SDL_MOUSEBUTTONDOWN){
            switch(event.button.button){
                case SDL_BUTTON_LMASK:{
                    SDL_GetMouseState(&x, &y);
                    c.SetHoldPoint();
                    holding = true;
                    break;
                }
            }
        }
        if(event.type == SDL_MOUSEBUTTONUP){
            switch(event.button.button){
                case SDL_BUTTON_LMASK:{
                    holding = false;
                    break;
                }
            }
        }
        if(event.type == SDL_MOUSEMOTION){
            if(holding){
                SDL_GetMouseState(&x2, &y2);
                c.ForceMove(x, y, x2, y2);
            }
        }
    }
}

void Loop(){
    while(var){
        while(SDL_GetTicks64()-lastTime<TICKS_PER_FRAME){
            SDL_Delay(1);
        }
        lastTime = SDL_GetTicks64();
        EventProcesser();
        SDL_SetRenderDrawColor(renderer, 255,0,255,255);
        SDL_RenderClear(renderer);
        c.Animate(SDL_GetTicks64());
        if(rand()%20==0&&!holding){
            c.Move(DISPLAYW, DISPLAYH);
        }
        c.Display(renderer);
        SDL_RenderPresent(renderer);
    }
    
}

int main(){
    CreateWindowAndRenderer();
    MakeWindowTransparent(window, RGB(255,0,255));
    if(c.SetAnimation(animationPath ,renderer)){
        Loop();
    }
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}