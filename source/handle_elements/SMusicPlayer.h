#pragma once

#include <memory>
#include "../resources/InitExitManager.h"

class SMusicPlayer final {
public:
    struct Deleter {
        void operator()(Mix_Music* music) {
            Mix_FreeMusic(music);
        }
    };

    SMusicPlayer() = default;
    bool loadFromFile(const std::string& path);

    void play() const;
    void stop() const;
    void pause() const;
    void unpause() const;

    bool isPlaying();

private: 
    std::shared_ptr<Mix_Music> music_;
};
