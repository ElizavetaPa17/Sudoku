#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "resources/InitExitManager.h"
#include "handle_elements/STimer.h"
#include "renderer/STexture.h"

int main() {
    if (!InitExitManager::init(SDL_INIT_VIDEO | SDL_INIT_AUDIO, IMG_INIT_JPG | IMG_INIT_PNG)) {
        std::cerr << "Application error.\n";
        InitExitManager::exit();

        return -1;
    } else {
        SDL_Window* window = SDL_CreateWindow("Test texture", SDL_WINDOWPOS_UNDEFINED, 
                                              SDL_WINDOWPOS_UNDEFINED, 600, 500, SDL_WINDOW_SHOWN);
        SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        STexture texture;
        texture.loadFromFile(renderer, "picture/question.png");

        bool quit = false;
        SDL_Event event;
        SDL_Point point = { 300, 250 };

        while (!quit) {
            while(SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    quit = true;
                }
            }

            SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
            SDL_RenderClear(renderer);

            texture.render(renderer, 0, 0, nullptr, 30, &point);
            SDL_RenderPresent(renderer);
        }

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        InitExitManager::exit();
        return 0;
    }
}
