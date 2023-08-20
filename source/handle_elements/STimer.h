#pragma once

#include <SDL2/SDL.h>

class STimer final {
public:
    STimer();
    ~STimer() = default;

    void start();
    void stop();
    void pause();
    void unpause();

    int getTicks() const;

    bool isStarted() { return is_started_; }
    bool isPaused()  { return is_paused_;  }
private:
    int start_ticks_;
    int pause_ticks_;

    bool is_started_;
    bool is_paused_;
};
