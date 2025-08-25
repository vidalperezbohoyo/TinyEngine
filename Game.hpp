#pragma once

#include "Controller.hpp"
#include "Display.hpp"
#include "Timer.hpp"
#include "Sound.hpp"

namespace console
{

class Game
{
public:
    Game();
    ~Game();

    void setDisplay(Display* display);

    void setController(Controller* controller);

    void setSound(Sound* sound);

    Timer* createTimer(unsigned long int period, std::function<void()> callback, bool one_shoot = false);

    //void onStart();

    virtual void onEvent(AceButton* btn, uint8_t event_type, uint8_t state) {}

    virtual void draw() {};

    void run();

protected:
    Display* display_;
    Sound* sound_;

private:
    Controller* controller_;

    static Game* instance_;

    std::vector<Timer> timers_;

};

}