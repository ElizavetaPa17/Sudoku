#include "SMusicPlayer.h"

bool SMusicPlayer::loadFromFile(const std::string& path) {
    Mix_Music* temp = Mix_LoadMUS(path.c_str());
    if (!temp) {
        std::cerr << "Unable to laod music. Path: " << path << 
                     ". SDL_Mixer Error: " << Mix_GetError() << '\n';
    } else {
        music_.reset(temp, Deleter());
    }

    return temp; // != nullptr
}

void SMusicPlayer::play() const {
    Mix_PlayMusic(music_.get(), -1); // -1 is number of repetition (equals infinity)
}

void SMusicPlayer::stop() const {
    Mix_HaltMusic();
}

void SMusicPlayer::pause() const {
    Mix_PauseMusic();
}

void SMusicPlayer::unpause() const {
    Mix_ResumeMusic();
}
