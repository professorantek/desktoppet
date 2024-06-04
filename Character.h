#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <time.h>
class Character{
    private:
        IMG_Animation* animation;
        char* antimationPath;
        std::pair<int, int> pos;
        const int width = 100, height= 100;
        int frameIndex;
        int lastTime;
    public:
        /**
         * Function to set the path for the animation files
         * \param path  - const char* containing path to an animation file
         * \param Delays - int* of millisecond delay between animations frame
         * \returns true - if the path was set and animation was initialized; false - if one of them was not 
        */
        bool SetAnimation(const char* path, int *Delays);
        /**
         * Function that moves the character around the screen
        */
        void Move();
        /**
         * Function to set the right frame of the animation
         * \param now - int of current time
        */
        void Animate(int now);
        /**
         * Function displays the character on the screen
         * \param r - SDL_Renderer*
        */
        void Display(SDL_Renderer* r);
        
        
        
};
