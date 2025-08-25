#include "TowerGame.hpp"

using namespace console;

TowerGame::TowerGame()
{
    block_movement_timer_ = createTimer(100, std::bind(&TowerGame::moveBlocksCallback, this));
}

TowerGame::~TowerGame()
{
    
}

void TowerGame::moveBlocksCallback()
{
    static bool moving_left = true; // Flag to alternate block movement direction

    // Move blocks left or right and reverse direction at edges
    if ((moving_left && cursor_x_ == 0) || (!moving_left && cursor_x_ == 7))
    {
        moving_left = !moving_left; // Reverse direction
    }
    else
    {
        cursor_x_ += moving_left ? -1 : 1;
    }

    // Draw screen to update the game state
    draw();
}

void TowerGame::onEvent(AceButton* btn, uint8_t event_type, uint8_t state)
{
    switch (event_type) 
    {
        case AceButton::kEventPressed:

        static int x = 4;
        static int y = 4;

        //display.clear();
        display_->drawPixel(x, y, CRGB(0, 0, 0)); // Clear previous pixel

        static auto color = CRGB(255, 255, 0);

        switch (btn->getId())
        {
            case console::BUTTON_UP:
                y--;
                break;

            case console::BUTTON_DOWN:
                y++;
                break;

            case console::BUTTON_LEFT:
                x--;
                break;

            case console::BUTTON_RIGHT:
                x++;
                break;

            case console::BUTTON_A:
                // Acción para botón A
                sound_->play(NOTE_F4, 1000);
                break;

            case console::BUTTON_B:
                // Acción para botón B
                sound_->play(TETRIS, TETRIS_SIZE);
                break;

            default:
                // Botón desconocido (opcional)
                break;
        }
        display_->drawPixel(x, y, color);

        break;
    };
}

void TowerGame::draw()
{
    // Display the game state, score, and blocks
    // Use Gfx methods to draw the game elements

    // Draw background
    //display_->fill(CRGB(0, 0, 80));

    // Draw tower blocks

    

    // Draw the new block to be placed
    display_->drawLine(0, 4, 7, 4, CRGB(0, 0, 0)); // Clear line
    display_->drawPixel(cursor_x_, 4, CRGB(0, 255, 0));
}