#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "../resources/InitExitManager.h"
#include "../handle_elements/STimer.h"
#include "../renderer/STexture.h"
#include "../renderer/SFont.h"
#include "SChooseLevelDialog.h"
#include "SExitGameDialog.h"
#include "SGameEnvironment.h"
#include "../resources/constants.h"

// Singleton
class SApplication : public SWidget {
public:    
    static SApplication* getIntance();

    void handleChildEvent(SWidget* child) override;
    void sendParentEvent() override;

    // setup Application environment and resources
    bool init();

    // run the Application (loop)
    void run();

    // quit the Application and close all the environment, deleting resources
    void quit();

private:
    bool runChooseLevelDialog();
    bool runExitGameDialog();
    void runGame();

    SApplication() = default;

    static SApplication* instance_;

    SDL_Window*   window_;
    SDL_Renderer* renderer_;
    
    STexture      background_;
    SGameEnvironment game_environment_;
    SChooseLevelDialog choose_level_dialog_;

    bool displ_choose_dialog_ = false;
};
