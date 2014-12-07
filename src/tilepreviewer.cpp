#include "tilepreviewer.hpp"

const sf::Vector2f TilePreviewer::previewSize(30, 30);

TilePreviewer::TilePreviewer()
{
    mShape.setSize(sf::Vector2f(40, 800));
    mShape.setFillColor(sf::Color(46, 46, 44));

    selectedRect.setSize(previewSize);
    selectedRect.setOutlineThickness(2);
    selectedRect.setOutlineColor(sf::Color(35, 201, 255));

    border.x = 5;
    border.y = 175;
    rectSpace.y = 50;
}

void TilePreviewer::update(sf::Vector2f &relPos)
{
    relativePos = relPos;

    if (oldTextureId != selector->getTextureId())
        updateTiles();

    mShape.setPosition(relativePos);
    positionPreviewers(topPreviewers.size(), botPreviewers.size());

    oldTextureId = selector->getTextureId();
}

void TilePreviewer::updateTiles()
{
    topPreviewers.clear();
    botPreviewers.clear();

    int nTop = topTilesNeeded();
    int nBot = botTilesNeeded();

    fillPreviewers(nTop, nBot);
    positionPreviewers(nTop, nBot);
    fixTexture();
}

void TilePreviewer::draw(sf::RenderTarget &target)
{
    target.draw(mShape);

    for (int i = 0; i < topPreviewers.size(); i++)
        target.draw(topPreviewers.at(i));

    target.draw(selectedRect);

    for (int i = 0; i < botPreviewers.size(); i++)
        target.draw(botPreviewers.at(i));
}

void TilePreviewer::fillPreviewers(int nTop, int nBot)
{
    for (int i = nTop; i > 0; i--)
        topPreviewers.push_back(createPreviewRect(selector->getTextureId() - i));

    for (int i = 0; i < nBot; i++)
        botPreviewers.push_back(createPreviewRect(selector->getTextureId() + i + 1));
}

void TilePreviewer::positionPreviewers(int nTop, int nBot)
{
    int space = (3 - nTop) * rectSpace.y;
    for (int i = 0; i < topPreviewers.size(); i++)
        topPreviewers.at(i).setPosition(border.x + relativePos.x, border.y + rectSpace.y * i + space + relativePos.y);

    selectedRect.setPosition(sf::Vector2f(border.x + relativePos.x, border.y + rectSpace.y * nTop + space + relativePos.y));

    space = rectSpace.y * 2 + previewSize.y * 3;
    for (int i = 0; i < botPreviewers.size(); i++)
        botPreviewers.at(i).setPosition(border.x + relativePos.x, border.y + rectSpace.y * i + space + relativePos.y);
}

void TilePreviewer::fixTexture()
{
    for (int i = 0; i < topPreviewers.size(); i++)
    {
        sf::RectangleShape shape = topPreviewers.at(i);
        shape.setTextureRect(sf::IntRect(0, 0, shape.getTexture()->getSize().x, shape.getTexture()->getSize().y));
    }


    int textureId = selector->getTextureId() > -1 ? selector->getTextureId() : 0;
    selectedRect.setTexture(Textureholder::getTexture(textureId));

    if (selector->getTextureId() >= 0)
        selectedRect.setFillColor(sf::Color(255, 255, 255, 255));
    else
        selectedRect.setFillColor(sf::Color::Transparent);

    selectedRect.setTextureRect(sf::IntRect(0, 0, selectedRect.getTexture()->getSize().x, selectedRect.getTexture()->getSize().y));

    for (int i = 0; i < botPreviewers.size(); i++)
    {
        sf::RectangleShape shape = botPreviewers.at(i);
        shape.setTextureRect(sf::IntRect(0, 0, shape.getTexture()->getSize().x, shape.getTexture()->getSize().y));
    }
}

int TilePreviewer::topTilesNeeded()
{
    if (selector->getTextureId() > -1)
    {
        if (selector->getTextureId() > 4)
            return 4;
        else
            return selector->getTextureId();
    }
    else
        return 0;
}

int TilePreviewer::botTilesNeeded()
{
    if (selector->getTextureId() > Textureholder::TEXTURES_END - 4 - 1)
        return Textureholder::TEXTURES_END - selector->getTextureId();
    else
        return 4;
}

sf::RectangleShape TilePreviewer::createPreviewRect(int textureId)
{
    sf::RectangleShape shape(previewSize);
    shape.setTexture(Textureholder::getTexture(textureId));

    return shape;
}

void TilePreviewer::setSelector(Selector *nSelector)
{
    selector = nSelector;
}
