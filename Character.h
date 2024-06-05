#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <time.h>
class Character{
    private:
        IMG_Animation* animation;
        std::vector<SDL_Texture*> sprites;
        char* antimationPath;
        std::pair<int, int> pos;
        const int width = 100, height= 100;
        int frameIndex;
        int lastTime;
    public:
        /**
         * Function to set the path for the animation files
         * \param path const char* containing path to an animation file
         * \param r  SDL_Renderer*
         * \returns true - if the path was set and animation was initialized; false - if one of them was not 
        */
        bool SetAnimation(const char* path, SDL_Renderer *r);
        /**
         * Function that moves the character around the screen
        */
        void Move();
        void SetHoldPoint();
        /**
         * Function to move the character to a defined position
         * \param x1,y1 position of the mouse at SetHoldPoint() - used to calculate the right position after moving
         * \param x2,y2 current position of the mouse
        */
        void ForceMove(int x1, int y1, int x2, int y2);
        /**
         * Function to set the right frame of the animation
         * \param now int of current time
        */
        void Animate(int now);
        /**
         * Function displays the character on the screen
         * \param r SDL_Renderer*
        */
        void Display(SDL_Renderer* r);
        
        
        
};
