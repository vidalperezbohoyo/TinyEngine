#include "Display.hpp"

using namespace console;

Display::Display()
{
    FastLED.addLeds<WS2812, 14, GRB>(leds_.data(), 64);
}

Display::~Display()
{

}

void Display::drawPixel(int x, int y, CRGB color, bool send_buffer)
{
    
    if (x < 0 || x >= 8 || y < 0 || y >= 8)
    {
        return; // Invalid pixel
    }

    int index = y * 8 + x;

    leds_[index] = color;

    if (send_buffer)
    {
        FastLED.show();
    }
}

void Display::drawLine(int x1, int y1, int x2, int y2, CRGB color)
{
    int dx = abs(x2 - x1);
    int dy = -abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx + dy;

    while (true)
    {
        drawPixel(x1, y1, color, false);

        if (x1 == x2 && y1 == y2)
            break;

        int e2 = 2 * err;
        if (e2 >= dy)
        {
            err += dy;
            x1 += sx;
        }
        if (e2 <= dx)
        {
            err += dx;
            y1 += sy;
        }
    }
    FastLED.show();
}

void Display::drawRectangle(int x, int y, int width, int height, CRGB color)
{
    // Top and bottom edges
    for (int i = x; i < x + width; ++i)
    {
        drawPixel(i, y, color, false);               // Top edge
        drawPixel(i, y + height - 1, color, false);  // Bottom edge
    }

    // Left and right edges
    for (int i = y; i < y + height; ++i)
    {
        drawPixel(x, i, color, false);               // Left edge
        drawPixel(x + width - 1, i, color, false);   // Right edge
    }
    FastLED.show();
}

void Display::drawFilledRectangle(int x, int y, int width, int height, CRGB color)
{
    for (int j = y; j < y + height; ++j)
    {
        for (int i = x; i < x + width; ++i)
        {
            drawPixel(i, j, color, false);
        }
    }
    FastLED.show();
}

void Display::fill(const CRGB& color)
{
    leds_.fill(color);
    FastLED.show();
}

void Display::clear()
{
    leds_.fill(CRGB(0, 0, 0));
    FastLED.show();
}

void Display::setBrightness(uint8_t brightness)
{
    FastLED.setBrightness(brightness);
}

