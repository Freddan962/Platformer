#include "selector.hpp"

Selector::Selector()
{
    mShape.setSize(sf::Vector2f(Tile::WIDTH, Tile::HEIGHT));
    mShape.setFillColor(sf::Color::Transparent);
    mShape.setOutlineColor(sf::Color::Black);
    mShape.setOutlineThickness(1.f);

    textureId = -1;
}

void Selector::update()
{
    if (mShape.getFillColor() == sf::Color::Transparent && textureId != -1)
        mShape.setFillColor(sf::Color(255, 255, 255, 255));
    else if (textureId == -1)
        mShape.setFillColor(sf::Color::Transparent);

    if (textureId >= 0)
        mShape.setTexture(Textureholder::getTexture(textureId));

    mShape.setTextureRect(sf::IntRect(0, 0, mShape.getTexture()->getSize().x, mShape.getTexture()->getSize().y));
}

void Selector::draw(sf::RenderTarget &target)
{
    target.draw(mShape);
}

void Selector::nextTexture()
{
    if (textureId <= Textureholder::TEXTURES_END)
    {
        textureId += 1;
        update();
    }
}

void Selector::previousTexture()
{
    if (textureId - 1 >= -1)
    {
        textureId -= 1;
        update();
    }
}

void Selector::changeTexture(int modifier)
{
    if (textureId + modifier <= Textureholder::TEXTURES_END && textureId + modifier >= -1)
    {
        textureId += modifier;
        update();
    }
}

sf::RectangleShape *Selector::getShape()
{
    return &mShape;
}

int Selector::getTextureId()
{
    return textureId;
}
