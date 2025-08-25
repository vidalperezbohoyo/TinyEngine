#pragma once
#include "Arduino.h"
#include <vector>

namespace console
{


using Vibration = std::vector<uint16_t>; // Stores: time on, time off, time on, time off

const Vibration pulses = {700, 200};


class Haptics
{

public:

    void setPin(const int& pin);

    void stop();

    void check();

    void vibrate(); // Default vibration

    void vibrate(const Vibration& vibration, const bool& repeat = false);

private:
    int vibrator_pin_;

    bool vibrating_ = false;

};


};