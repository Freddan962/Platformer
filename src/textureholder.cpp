#include "textureholder.hpp"

const int Textureholder::NTILES = 17; //0-16
const int Textureholder::NDECORATIONS = 13; //17-29
const int Textureholder::NTREES = 6; //30-35

const int Textureholder::TILES_END = NTILES - 1;
const int Textureholder::DECORATIONS_END = TILES_END + NDECORATIONS;
const int Textureholder::TREES_END = DECORATIONS_END + NTREES;

const int Textureholder::TEXTURES_END = TREES_END;

std::vector<sf::Texture> Textureholder::textures;

void Textureholder::loadTextures()
{
    loadTexture(NTILES, "");
    loadTexture(NDECORATIONS, "d");
    loadTexture(NTREES, "t");
}

void Textureholder::loadTexture(int size, std::string prefix)
{
    for (int i = 1; i <= size; i++)
    {
        sf::Texture tTexture;
        tTexture.loadFromFile("media/" + prefix + std::to_string(i) + ".png");
        tTexture.setSmooth(true);
        textures.push_back(tTexture);
    }
}


sf::Texture *Textureholder::getTexture(int id)
{
    return &textures.at(id);
}

sf::Texture *Textureholder::getTileT(int id)
{
    return &textures.at(id);
}

sf::Texture *Textureholder::getDecorationT(int id)
{
    return &textures.at(TILES_END + id);
}

sf::Texture *Textureholder::getTreeT(int id)
{
    return &textures.at(DECORATIONS_END + id);
}
