#pragma once
#include <AceButton.h>
#include "Arduino.h"

using namespace ace_button;

namespace console
{

struct Pinout
{
    int button_up;    ///< Pin for the "up" button
    int button_down;  ///< Pin for the "down" button
    int button_left;  ///< Pin for the "left" button
    int button_right; ///< Pin for the "right" button
    int button_a;     ///< Pin for the "A" button
    int button_b;     ///< Pin for the "B" button
};

enum Button
{
    BUTTON_UP = 0,
    BUTTON_DOWN,
    BUTTON_LEFT,
    BUTTON_RIGHT,
    BUTTON_A,
    BUTTON_B
};

using ControllerCallback = std::function<void(AceButton* btn, uint8_t event_type, uint8_t state)>;

class Controller : public IEventHandler
{
public:
    Controller();
    ~Controller();

    void setCallback(ControllerCallback cb);

    // Function from IEventHandler
    void handleEvent(AceButton* /* button */, uint8_t eventType, uint8_t buttonState) override;

    void setPinout(const Pinout& pinout);

    void init();

    void check();

private:
    Pinout pinout_;

    ControllerCallback callback_;

    AceButton buttons_[6];
};






}