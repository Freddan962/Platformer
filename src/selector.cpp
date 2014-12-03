#include "selector.hpp"

Selector::Selector()
{
    mShape.setSize(sf::Vector2f(Tile::WIDTH, Tile::HEIGHT));
    mShape.setFillColor(sf::Color::Transparent);
    mShape.setOutlineColor(sf::Color::Black);
    mShape.setOutlineThickness(1.f);

    textureId = 0;

    tileStart = 1;
    decorationStart = Tile::NTEXTURES;
    treeStart = decorationStart + Tree::NTEXTURES;
}

void Selector::update()
{
    if (mShape.getFillColor() == sf::Color::Transparent && textureId != 0)
        mShape.setFillColor(sf::Color(255, 255, 255, 255));
    else if (textureId == 0)
        mShape.setFillColor(sf::Color::Transparent);

    if (textureId > 0 && textureId < decorationStart)
        mShape.setTexture(Tile::getTexture(textureId));
    else if (textureId >= decorationStart && textureId < treeStart)
        mShape.setTexture(Decoration::getTexture(textureId - decorationStart));
    else if (textureId >= treeStart)
        mShape.setTexture(Tree::getTexture(textureId - treeStart));
}

void Selector::draw(sf::RenderTarget &target)
{
    target.draw(mShape);
}

void Selector::nextTexture()
{
    textureId += 1;
    update();
}

void Selector::previousTexture()
{
    if (textureId > 0)
    {
        update();
        textureId += 1;
    }
}

void Selector::changeTexture(int modifier)
{
    if (textureId + modifier < treeStart + Tree::NTEXTURES && textureId + modifier >= 0)
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
