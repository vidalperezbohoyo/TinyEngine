#include "Controller.hpp"

using namespace console;

Controller::Controller()
{
    callback_ = nullptr;
}

Controller::~Controller()
{

}

void Controller::handleEvent(AceButton* button, uint8_t eventType, uint8_t buttonState)
{
    callback_(button, eventType, buttonState); // Rebind to external class
}


void Controller::setPinout(const Pinout& pinout)
{
    pinout_ = pinout;
}


void Controller::check()
{
    for (auto& button : buttons_)
    {
        button.check();
    }
}

void Controller::setCallback(ControllerCallback cb)
{
    callback_ = cb;
}

void Controller::init()
{
    pinMode(pinout_.button_up, INPUT_PULLUP);
    pinMode(pinout_.button_down, INPUT_PULLUP);
    pinMode(pinout_.button_left, INPUT_PULLUP);
    pinMode(pinout_.button_right, INPUT_PULLUP);
    pinMode(pinout_.button_a, INPUT_PULLUP);
    pinMode(pinout_.button_b, INPUT_PULLUP);

    ButtonConfig* config = ButtonConfig::getSystemButtonConfig();
    config->setIEventHandler(this);
    config->setFeature(ButtonConfig::kFeatureClick);
    config->setFeature(ButtonConfig::kFeatureDoubleClick);
    config->setFeature(ButtonConfig::kFeatureLongPress);
    config->setFeature(ButtonConfig::kFeatureRepeatPress);

    buttons_[BUTTON_UP].init(pinout_.button_up, HIGH, BUTTON_UP);
    buttons_[BUTTON_DOWN].init(pinout_.button_down, HIGH, BUTTON_DOWN);
    buttons_[BUTTON_LEFT].init(pinout_.button_left, HIGH, BUTTON_LEFT);
    buttons_[BUTTON_RIGHT].init(pinout_.button_right, HIGH, BUTTON_RIGHT);
    buttons_[BUTTON_A].init(pinout_.button_a, HIGH, BUTTON_A);
    buttons_[BUTTON_B].init(pinout_.button_b, HIGH, BUTTON_B);

}
