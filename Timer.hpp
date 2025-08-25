#pragma once

#include <functional>
#include "Arduino.h"

namespace console
{

class Timer
{
public:
    Timer(unsigned long int period, std::function<void()> callback, bool one_shoot = false);

    void check();

    void setPeriod(unsigned long int period);


private:

    unsigned long int last_trigger_millis_;
    unsigned long int period_;
    std::function<void()> callback_;
    bool one_shoot_;
    bool was_triggered_; // Using to implement "one_shoot" funtionality
};
}