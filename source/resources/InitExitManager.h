#pragma once 

// main library
#include <SDL2/SDL.h>

// library for working with loading and formating image 
#include <SDL2/SDL_image.h>

// library for working with fonts
#include <SDL2/SDL_ttf.h>

// library for working with audio
#include <SDL2/SDL_mixer.h>

#include <iostream>

class InitExitManager {
public:
    static bool init(int sdl_flags, int img_flags);
    static void exit();
};
