#include "player.hpp"

Player::Player()
{
    mTexture.loadFromFile("./media/player.png");
    mSprite.setTexture(mTexture);
}
