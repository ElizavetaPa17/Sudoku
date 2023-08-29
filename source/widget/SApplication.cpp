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

        background_.loadFromFile(renderer_, "picture/background.png");
        background_.setPosition({ 0, 0 });

        std::shared_ptr<STexture> board_texture = std::make_shared<STexture>();
        board_texture->loadFromFile(renderer_, "picture/board.png");

        board_.setTexture(board_texture);
        board_.setPosition({ 35, 35 });

        STexture score_background;
        score_background.loadFromFile(renderer_, "picture/score_board.png");        
        score_label_.setUp(renderer_, score_background);
        score_label_.setPosition({ 458, 35 });

        STexture timer_background;
        timer_background.loadFromFile(renderer_, "picture/timer_board.png");
        timer_label_.setUp(renderer_, timer_background);
        timer_label_.setPosition({ 458, 100 });

        return true;
    }
}

void SApplication::run() {
    bool quit = false;
        SDL_Event event;
        SDL_Point point = { 10, 10 };
        timer_label_.startTimer();

        while (!quit) {
            while(SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    quit = true;
                }

                board_.handleEvents(event);
            }

            SDL_SetRenderDrawColor(renderer_, 0xFF, 0xFF, 0xFF, 0xFF);
            SDL_RenderClear(renderer_);
            
            background_.render(renderer_);
            board_.render(renderer_);
            score_label_.render(renderer_);
            timer_label_.render(renderer_);

            SDL_RenderPresent(renderer_);
        }
}

void SApplication::quit() {
    SDL_DestroyRenderer(renderer_);
    SDL_DestroyWindow(window_);

    InitExitManager::exit();
}
