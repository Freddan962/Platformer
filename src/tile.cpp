#include "tile.hpp"

std::vector<sf::Texture> Tile::textures;

const int Tile::NTEXTURES = 17;
const int Tile::WIDTH = 100;
const int Tile::HEIGHT = 100;

Tile::Tile()
{
    solid = false;
    mSprite.setScale(0.78125, 0.78125);
}

void Tile::loadTextures()
{
    for (int i = 1; i <= NTEXTURES; i++)
    {
        sf::Texture tTexture;
        tTexture.loadFromFile("media/" + std::to_string(i) + ".png");
        tTexture.setSmooth(true);
        textures.push_back(tTexture);
    }
}

void Tile::setTexture(int id)
{
    mSprite.setTexture(textures.at(id));
    setSolid(true);
}

void Tile::setSolid(int isSolid)
{
    solid = isSolid;
}
