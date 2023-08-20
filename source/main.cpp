#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "resources/InitExitManager.h"
#include "handle_elements/STimer.h"
#include "renderer/STexture.h"
#include "renderer/SFont.h"

int main() {
    if (!InitExitManager::init(SDL_INIT_VIDEO | SDL_INIT_AUDIO, IMG_INIT_JPG | IMG_INIT_PNG)) {
        std::cerr << "Application error.\n";
        InitExitManager::exit();

        return -1;
    } else {
        SDL_Window* window = SDL_CreateWindow("Test texture", SDL_WINDOWPOS_UNDEFINED, 
                                              SDL_WINDOWPOS_UNDEFINED, 600, 500, SDL_WINDOW_SHOWN);
        SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

        SFont font;
        font.loadFromFile("font/test_font.ttf", 30);
        
        SDL_Color color = { 0xFF, 0x00, 0xFF };
        STexture texture = font.createFontTexture(renderer, "It's working\n", color);
        texture.setAlpha(0xFF);

        SDL_Point pos = { 10, 10 };
        texture.setPosition(pos);

        color = { 0x00, 0xFF, 0xFF };
        pos = { 10, 100 };
        STexture texture2 = font.createFontTexture(renderer, "Hello", color);
        texture2.setPosition(pos);
        texture2.setAlpha(30);

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

            texture.render(renderer);
            texture2.render(renderer);

            SDL_RenderPresent(renderer);
        }

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
    }

    InitExitManager::exit();
    return 1;
}
