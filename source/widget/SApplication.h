#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "../resources/InitExitManager.h"
#include "../handle_elements/STimer.h"
#include "../renderer/STexture.h"
#include "../renderer/SFont.h"
#include "../handle_elements/SBoard.h"

const int SCREEN_WIDTH  = 736;
const int SCREEN_HEIGHT = 474;

// Singleton
class SApplication final {
public:
    static SApplication* getIntance();

    // setup Application environment and resources
    bool init();

    // run the Application (loop)
    void run();

    // quit the Application and close all the environment, deleting resources
    void quit();

private:
    SApplication() = default;

    static SApplication* instance_;

    SDL_Window* window_;
    SDL_Renderer* renderer_;
    SBoard board_;
    STexture background_;
};
