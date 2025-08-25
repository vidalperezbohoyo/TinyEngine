#include "Game.hpp"

namespace console
{
class TowerGame : public Game
{
public:
    TowerGame();

    ~TowerGame();

    void moveBlocksCallback();

    void onEvent(AceButton* btn, uint8_t event_type, uint8_t state) override;

    void draw() override;

private:

    Timer* block_movement_timer_; ///< Timer for moving blocks

    uint8_t score_; ///< Current score of the game, starts in 1
    uint8_t block_size; ///< Can be 1 or 2. Depends on the previus block placement
    uint8_t cursor_x_; ///< Current cursor position in the X axis, can be 0-7
    uint8_t previous_block_mask_ [2]; ///< Can be 0,1 or 1,0 or 1,1 Used to place single blocks
};
}
