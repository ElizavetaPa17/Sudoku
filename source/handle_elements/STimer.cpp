#include "STimer.h"

STimer::STimer() : start_ticks_(0), pause_ticks_(0), is_started_(false), is_paused_(false)
{
}

// start the timer by reseting all the class members
void STimer::start() {
    is_started_ = true;
    is_paused_  = false;

    start_ticks_ = SDL_GetTicks();
    pause_ticks_ = 0;
}

// stop the timer by setting all the class members to default value
void STimer::stop() {
    is_started_ = false;
    is_paused_  = false;

    start_ticks_ = 0;
    pause_ticks_ = 0;
}

// pause timer. saving current time to pause_ticks and keeping it until unpause or stop
// if the timer has already stopped there's nothing to do
void STimer::pause() {
    if (is_started_ && !is_paused_) {
        is_paused_   = true;
        pause_ticks_ = SDL_GetTicks();
    }
}

// unpause timer. correct start_ticks to keep the time flow consequently
void STimer::unpause() { // 6
    if (is_started_ && is_paused_) {
        is_paused_   = false;
        start_ticks_ += SDL_GetTicks() - pause_ticks_;
        // pause_ticks_ = 0
    }
}

int STimer::getTicks() const {
    if (is_paused_) {
        return pause_ticks_ - start_ticks_;
    } else {
        return SDL_GetTicks() - start_ticks_;
    }
}

