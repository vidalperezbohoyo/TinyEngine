#include "Timer.hpp"

using namespace console;

Timer::Timer(unsigned long int period, std::function<void()> callback, bool one_shoot)
{
    last_trigger_millis_ = 0;
    period_ = period;
    callback_ = callback;
    one_shoot_ = one_shoot;
    was_triggered_ = false;
}

void Timer::check()
{
    if (one_shoot_ && was_triggered_)
    {
        return; 
    }

    if (millis() - period_ > last_trigger_millis_)
    {
        callback_();

        last_trigger_millis_ = millis();
        was_triggered_ = true;
    }
}

void Timer::setPeriod(unsigned long int period)
{
    period_ = period;
}
