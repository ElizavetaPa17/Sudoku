#include "SChunkPlayer.h"

bool SChunkPlayer::loadFromFile(const std::string& path) {
    Mix_Chunk* temp = Mix_LoadWAV(path.c_str());
    if (!temp) {
        std::cerr << "Unable to load music chunk. Path: " << path << 
                     ". Mix_Error: " << Mix_GetError() << '\n';
    } else {
        chunk_.reset(temp, Deleter());
    }

    return temp; // != nullptr
}

void SChunkPlayer::play() {
    Mix_PlayChannel(-1, chunk_.get(), 0);
}
