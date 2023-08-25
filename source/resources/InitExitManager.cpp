#include "InitExitManager.h"
#include <SDL2/SDL_ttf.h>

bool InitExitManager::init(int sdl_flags, int img_flags) {
    bool success = true;
    if (SDL_Init(sdl_flags) != 0) {
        std::cerr << "Unable to init SDL. SDL_Error: " << SDL_GetError << '\n';
        success = false;
    }
    // IMG_Init return all successful flags. XOR identify unsuccessful ones
    if (IMG_Init(img_flags) ^ (img_flags)) {
        std::cerr << "Unable to init SDL_image. IMG_Error: " << IMG_GetError() << '\n';
        success = false;
    }

    // Mix_OpenAudio open default audio device for playback
    if (Mix_OpenAudio(44800, MIX_DEFAULT_FORMAT, 2, 2048) != 0) {
        std::cerr << "Unable to init SDL_mixer. Mix_Error: " << Mix_GetError() << '\n';
        success = false;
    }

    // Initialize SDL_ttf 
    if (TTF_Init() != 0) {
        std::cerr << "Unable to init SDL_ttf. TTF_Error: " << TTF_GetError() << '\n';
        success = false;
    }
    
    return success;
}

bool InitExitManager::initCellFlyweight(SDL_Renderer *renderer) {
    if (!SCellFlyweight::init(renderer)) {
        std::cerr << "Unable to init SCellFlyweight\n";
        return false;
    } else {
        return true;
    }
}

void InitExitManager::exit() {
    TTF_Quit();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}
