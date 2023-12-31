#include "SGameEnvironment.h"

void SGameEnvironment::handleChildEvent(SWidget *child) {
    if (&closed_hint_button_ == child) {
        // closed_hint_button and closed_hint_button_ have the same 
        // position. So just switch the boolean and rendering button
        if (is_opened_hint_) {
            is_opened_hint_ = false;
            board_.setRenderInnerBoard(false);
        } else {
            is_opened_hint_ = true;
            board_.setRenderInnerBoard(true);
        }
    } else if (&quit_game_button_ == child) {
        timer_label_.pauseTimer();
        displ_exit_dialog_ = true;
    } else if (&exit_game_dialog_ == child && displ_exit_dialog_) {
        game_state_ = exit_game_dialog_.getGameState();

        if (game_state_ == SConstants::GameState::QUIT) {
            sendParentEvent();
        } else {
            timer_label_.unpauseTimer();
            displ_exit_dialog_ = false;
        }
    }
}

void SGameEnvironment::sendParentEvent() {
    parent_->handleChildEvent(this);
}

void SGameEnvironment::setUp(SWidget* parent, SDL_Renderer* renderer) {
    parent_ = parent;
    SChunkPlayer chunk_player;
    chunk_player.loadFromFile(SConstants::chunk_path);

    STexture buffer_texture;
    STexture additional_texture;
    
    buffer_texture.loadFromFile(renderer, "picture/board.png");
    board_.setTexture(buffer_texture);
    board_.setPosition({ 35, 35 });

    exit_game_dialog_.setUp(this, renderer);
    exit_game_dialog_.setPosition({ 230, 170 });

    buffer_texture.loadFromFile(renderer, "picture/score_board.png");        
    score_label_.setUp(renderer,buffer_texture);
    score_label_.setPosition({ 460, 35 });

    buffer_texture.loadFromFile(renderer, "picture/timer_board.png");
    timer_label_.setUp(renderer, buffer_texture);
    timer_label_.setPosition({ 460, 100 });

    SMusicPlayer music_player;
    if (!music_player.loadFromFile("audio/sudoku_music.wav")) {
        std::cerr << "Unable to load main music.\n";
    }


    buffer_texture.loadFromFile(renderer, "picture/voice_control_button.png");
    additional_texture.loadFromFile(renderer, "picture/stop_music.png");
    voice_button_.setUp(this, buffer_texture, additional_texture, chunk_player, music_player);
    voice_button_.setPosition({ 460, 230 });

    additional_texture.loadFromFile(renderer, "picture/rules_hint_menu.png");
    buffer_texture.loadFromFile(renderer, "picture/show_rules_button.png");

    rules_button_.setUp(this, buffer_texture, additional_texture, chunk_player);
    rules_button_.setPosition({ 525, 230 });

    buffer_texture.loadFromFile(renderer, "picture/show_hint_button.png");
    closed_hint_button_.setUp(this, buffer_texture, chunk_player);
    closed_hint_button_.setPosition({ 589, 230 });

    buffer_texture.loadFromFile(renderer, "picture/hide_hint_button.png");
    opened_hint_button_.setUp(this, buffer_texture, chunk_player);
    opened_hint_button_.setPosition({ 589, 230 });

    buffer_texture.loadFromFile(renderer, "picture/quit_game_button.png");
    quit_game_button_.setUp(this, buffer_texture, chunk_player);
    quit_game_button_.setPosition({ 653, 230 });
}

void SGameEnvironment::setGameLevel(SDL_Renderer* renderer, SConstants::GameLevel game_level) {
    game_level_label_.setUp(renderer, game_level);
    game_level_label_.setPosition({ 458, 165 });
}

void SGameEnvironment::render(SDL_Renderer *renderer) {
    board_.render(renderer);

    if (board_.getScoreStatus() == SConstants::ScoreStatus::ADD) {
        score_label_.addScore(renderer, 10);
    } else if (board_.getScoreStatus() ==  SConstants::ScoreStatus::SUB) {
        score_label_.subScore(renderer, 10);
    }
    
    score_label_.render(renderer);
    timer_label_.render(renderer);
    game_level_label_.render(renderer);

    voice_button_.render(renderer);
    rules_button_.render(renderer);

    if (is_opened_hint_) {
        opened_hint_button_.render(renderer);
    } else {
        closed_hint_button_.render(renderer);
    }

    quit_game_button_.render(renderer);

    if (displ_exit_dialog_) {
        exit_game_dialog_.render(renderer);
    }
}

void SGameEnvironment::handleEvents(SDL_Event &event) {
    if (displ_exit_dialog_) {
        exit_game_dialog_.handleEvents(event);
    } else {

        if (!is_blocked_score_changing_) {
            board_.handleEvents(event);
        }

        voice_button_.handleEvents(event);
        rules_button_.handleEvents(event);
        closed_hint_button_.handleEvents(event);
        opened_hint_button_.handleEvents(event);
        quit_game_button_.handleEvents(event);
    }
}

void SGameEnvironment::reset() {
    // reset timer
    timer_label_.stopTimer();
    timer_label_.startTimer();

    is_opened_hint_ = displ_exit_dialog_ = false;
    board_.generateNewBoard(game_level_label_.getGameLevel());
}

int SGameEnvironment::getPastTicks() {
    return timer_label_.getPastTicks();
}

SConstants::GameState SGameEnvironment::getGameState() {
    return game_state_;
}

void SGameEnvironment::setScoreBlocking(bool flag) {
    is_blocked_score_changing_ = flag;

    if (is_blocked_score_changing_ == false) {
        board_.setScoreStatus(SConstants::ScoreStatus::NO_CHANGES);
    }
}

void SGameEnvironment::setScore(SDL_Renderer* renderer, int value) {
   score_label_.setScore(renderer, value); 
   score_label_.render(renderer);
}

int SGameEnvironment::getScore() {
    return score_label_.getScore();
}
