#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "resources/InitExitManager.h"
#include "handle_elements/STimer.h"
#include "renderer/STexture.h"
#include "renderer/SFont.h"
#include "handle_elements/SBoard.h"

int main() {
    if (!InitExitManager::init(SDL_INIT_VIDEO | SDL_INIT_AUDIO, IMG_INIT_JPG | IMG_INIT_PNG)) {
        std::cerr << "Application error.\n";
        InitExitManager::exit();
        
        return -1;
    } else {
        SDL_Window* window = SDL_CreateWindow("Test texture", SDL_WINDOWPOS_UNDEFINED, 
                                              SDL_WINDOWPOS_UNDEFINED, 1600, 1200, SDL_WINDOW_SHOWN);
        SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

        if (!InitExitManager::initCellFlyweight(renderer)) {
            InitExitManager::exit();

            return -1;
        }

        std::shared_ptr<STexture> texture = std::make_shared<STexture>();
        texture->loadFromFile(renderer, "picture/cells.jpg");
    
        SBoard board;
        board.setTexture(texture);

        bool quit = false;
        SDL_Event event;
        SDL_Point point = { 10, 10 };
        board.setPosition(point);

        while (!quit) {
            while(SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    quit = true;
                }

                board.handleEvents(event);
            }

            SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
            SDL_RenderClear(renderer);

            SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0xFF, 0xFF);
            board.render(renderer);

            SDL_RenderPresent(renderer);
        }

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
    }

    InitExitManager::exit();
    return 1;
}
