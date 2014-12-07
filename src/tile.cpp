#include "tile.hpp"

const int Tile::WIDTH = 100;
const int Tile::HEIGHT = 100;

Tile::Tile()
{
    solid = false;
    mSprite.setScale(0.78125, 0.78125);
}

void Tile::setTexture(int id)
{
    mSprite.setTexture(*Textureholder::getTileT(id));
    setSolid(true);
}

void Tile::setSolid(int isSolid)
{
    solid = isSolid;
}
