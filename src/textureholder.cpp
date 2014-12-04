#include "textureholder.hpp"

const int Textureholder::NTILES = 17; //0-16
const int Textureholder::NDECORATIONS = 13; //17-29
const int Textureholder::NTREES = 6; //30-35

const int Textureholder::TILES_END = NTILES - 1;
const int Textureholder::DECORATIONS_END = TILES_END + NDECORATIONS;
const int Textureholder::TREES_END = DECORATIONS_END + NTREES;

std::vector<sf::Texture> Textureholder::textures;

void Textureholder::loadTextures()
{
    loadTexture(NTILES, "");
    loadTexture(NDECORATIONS, "d");
    loadTexture(NTREES, "t");

    std::cout << "TE : " << TILES_END << " DE : " << DECORATIONS_END << " TE : " << TREES_END;
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
    if(id >= 0 && id <= TILES_END)
        return getTile(id);
    else if(id > TILES_END & id <= DECORATIONS_END)
        return getDecoration(id);
    else if(id > DECORATIONS_END && id <= TREES_END)
        return getTree(id);
    else
        std::cout << "ERROR: Textureholder::getTexture Id out of scope!";
}

sf::Texture *Textureholder::getTile(int id)
{
    return &textures.at(id+1);
}

sf::Texture *Textureholder::getDecoration(int id)
{
    return &textures.at(TILES_END + id);
}

sf::Texture *Textureholder::getTree(int id)
{
    return &textures.at(DECORATIONS_END + id);
}
