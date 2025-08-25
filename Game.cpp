#include "Game.hpp"

using namespace console;

Game* Game::instance_ = nullptr;

Game::Game()
{
    Game::instance_ = this;
}

Game::~Game()
{

}

void Game::run()
{
    // Check controller
    controller_->check();

    // Check timers
    for (auto& timer : timers_)
    {
        timer.check();
    }

    // Check sounds
    sound_->check();
}

void Game::setDisplay(Display* display)
{
    display_ = display;
    display_->clear();
}

void Game::setController(Controller* controller)
{
    controller_ = controller;

    controller_->setCallback(std::bind(&Game::onEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
    controller_->init();
}

void Game::setSound(Sound* sound)
{
    sound_ = sound;
    sound_->init();
}

Timer* Game::createTimer(unsigned long int period, std::function<void()> callback, bool one_shoot)
{
    timers_.push_back(Timer(period, callback, one_shoot));

    return &timers_.back();
}