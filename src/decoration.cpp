#include "decoration.hpp"

std::vector<sf::Texture> Decoration::textures;
const int Decoration::nTextures = 13;

Decoration::Decoration()
{
}

void Decoration::loadTextures()
{
    for (int i = 1; i <= nTextures; i++)
    {
        sf::Texture tTexture;
        tTexture.loadFromFile("media/d" + std::to_string(i) + ".png");
        tTexture.setSmooth(true);
        textures.push_back(tTexture);
    }
}

void Decoration::setTexture(int id)
{
    mSprite.setTexture(textures.at(id));
    int y = mSprite.getTexture()->getSize().y;
    mSprite.setOrigin(0, y);
}
