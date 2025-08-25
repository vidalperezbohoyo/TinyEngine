#pragma once

#include <array>
#include <FastLED.h>

namespace console
{

class Display
{
public:

    Display();
    ~Display();

    void drawPixel(int x, int y, CRGB color, bool send_buffer = true);

    void drawLine(int x1, int y1, int x2, int y2, CRGB color);

    void drawRectangle(int x, int y, int width, int height, CRGB color);

    void drawFilledRectangle(int x, int y, int width, int height, CRGB color);

    void fill(const CRGB& color);

    void clear();

    void setBrightness(uint8_t brightness);

private:
    std::array<CRGB, 64> leds_;

};

}