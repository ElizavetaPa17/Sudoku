#include "SApplication.h"

SApplication* SApplication::instance_ = nullptr;

SApplication* SApplication::getIntance() {
    if (!instance_) {
        instance_ = new SApplication();
    }

    return instance_;
}

bool SApplication::init() {
    if (!InitExitManager::init(SDL_INIT_VIDEO | SDL_INIT_AUDIO, IMG_INIT_JPG | IMG_INIT_PNG)) {
        std::cerr << "Application error.\n";
        InitExitManager::exit();
        
        return false;
    } else {
        window_ = SDL_CreateWindow("Sudoku", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                              SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

        renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);

        if (!InitExitManager::initCellFlyweight(renderer_)) {
            InitExitManager::exit();

            return false;
        }

        std::shared_ptr<STexture> texture = std::make_shared<STexture>();
        texture->loadFromFile(renderer_, "picture/board.png");
    
        board_;
        board_.setTexture(texture);
        board_.setPosition({ 35, 35 });

        return true;
    }
}

void SApplication::run() {
    bool quit = false;
        SDL_Event event;
        SDL_Point point = { 10, 10 };

        while (!quit) {
            while(SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    quit = true;
                }

                board_.handleEvents(event);
            }

            SDL_SetRenderDrawColor(renderer_, 0xFF, 0xFF, 0xFF, 0xFF);
            SDL_RenderClear(renderer_);

            SDL_SetRenderDrawColor(renderer_, 0x00, 0xFF, 0xFF, 0xFF);
            board_.render(renderer_);

            SDL_RenderPresent(renderer_);
        }
}

void SApplication::quit() {
    SDL_DestroyRenderer(renderer_);
    SDL_DestroyWindow(window_);

    InitExitManager::exit();
}
