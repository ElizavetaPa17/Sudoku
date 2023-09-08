#pragma once

#include "../resources/InitExitManager.h"
#include <memory>

class SChunkPlayer final {
public:
    struct Deleter {
        void operator()(Mix_Chunk* chunk) {
            Mix_FreeChunk(chunk);
        }
    };

    SChunkPlayer() = default;
    
    bool loadFromFile(const std::string& path);
    void play();

private:
    std::shared_ptr<Mix_Chunk> chunk_;
};
