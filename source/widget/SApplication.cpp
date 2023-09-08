 #include "SApplication.h"
#include <math.h>

SApplication* SApplication::instance_ = nullptr;

SApplication* SApplication::getIntance() {
    if (!instance_) {
        instance_ = new SApplication();
    }

    return instance_;
}

// choose_level_dialog_ events are ignored (runChooseLevelDialog loop handles game level selection)
void SApplication::handleChildEvent(SWidget *child) {
    if (&game_environment_ == child) {
        switch (game_environment_.getGameState()) {
            case SConstants::GameState::QUIT : {
                displ_choose_dialog_ = true;
                choose_level_dialog_.reset();
            }
        }
    }
}

void SApplication::sendParentEvent() {
    SWidget::sendParentEvent();
}

bool SApplication::init() {
    if (!InitExitManager::init(SDL_INIT_VIDEO | SDL_INIT_AUDIO, IMG_INIT_JPG | IMG_INIT_PNG)) {
        std::cerr << "Application error.\n";
        InitExitManager::exit();
        
        return false;
    } else {
        window_ = SDL_CreateWindow("Sudoku", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                             SConstants::SCREEN_WIDTH, SConstants::SCREEN_HEIGHT, 
                                             SDL_WINDOW_SHOWN);

        renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);

        if (!InitExitManager::initCellFlyweight(renderer_)) {
            InitExitManager::exit();

            return false;
        }
        
        background_.loadFromFile(renderer_, "picture/background.png");

        choose_level_dialog_.setUp(this, renderer_);
        choose_level_dialog_.setPosition({ 140, 120 });
    

        game_environment_.setUp(this, renderer_);
        if (!music_.loadFromFile("audio/sudoku_music.wav")) {
            std::cerr << "Music can't be load!\n";
        }

        return true;
    }
}

void SApplication::run() {
    music_.play();
    do {
        if (runChooseLevelDialog()) {
            displ_choose_dialog_ = false;
            runGame();
        }

    } while (displ_choose_dialog_);

    quit();
}

bool SApplication::runChooseLevelDialog() {
    bool quit = false;
    SDL_Event event;
    
    while (!quit && (choose_level_dialog_.getGameLevel() == SConstants::GameLevel::NOT_SELECTED)) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }

            choose_level_dialog_.handleEvents(event);
        }

        SDL_SetRenderDrawColor(renderer_, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer_);

        background_.render(renderer_);
        choose_level_dialog_.render(renderer_);

        SDL_RenderPresent(renderer_);
    }

    if (quit) {
        return false;     
    } else { // the user choose game level 
        game_environment_.setGameLevel(renderer_, choose_level_dialog_.getGameLevel());
        return true;
    }
}

void SApplication::runGame() {
    bool quit = false;
    SDL_Event event;

    game_environment_.reset();

    while (!quit && !displ_choose_dialog_) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }

            game_environment_.handleEvents(event);
        }

        SDL_SetRenderDrawColor(renderer_, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer_);

        background_.render(renderer_);
        game_environment_.render(renderer_);

        SDL_RenderPresent(renderer_);
    }
}

void SApplication::quit() {
    SDL_DestroyRenderer(renderer_);
    SDL_DestroyWindow(window_);
    music_.stop();

    InitExitManager::exit();
}
