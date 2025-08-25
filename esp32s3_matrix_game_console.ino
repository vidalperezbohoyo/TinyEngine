#include <sstream>

#include "TowerGame.hpp"

using namespace ace_button;

console::Controller controller;
console::Display display;
console::Sound sound;

console::TowerGame game;

void setup() 
{
  // Configure controller
  console::Pinout pinout;
  pinout.button_up = 4;
  pinout.button_down = 6;
  pinout.button_left = 7;
  pinout.button_right = 5;
  pinout.button_a = 38;
  pinout.button_b = 39;

  controller.setPinout(pinout);

  // Configure display
  display.setBrightness(2);
  display.clear();

  // Configure sound
  sound.setPin(37);

  // Configure game
  game.setController(&controller);
  game.setDisplay(&display);
  game.setSound(&sound);
}

void loop()
{
  game.run();
}