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
    mShape.setPosition(relPos);

    for (int i = 0; i < rectPreviewers.size(); i++)
        rectPreviewers.at(i).setPosition(border.x + relPos.x, relPos.y + border.y + rectSpace.y * i);

    updateTiles();
}

void TilePreviewer::draw(sf::RenderTarget &target)
{
    target.draw(mShape);

    for (int i = 0; i < rectTopPreviewers.size(); i++)
        target.draw(rectTopPreviewers.at(i));

    target.draw(selectedRect);

    for (int i = 0; i < rectBotPreviewers.size(); i++)
        target.draw(rectBotPreviewers.at(i));
}

void TilePreviewer::updateTiles()
{
    rectPreviewers.clear();
    rectTopPreviewers.clear();
    rectBotPreviewers.clear();

    int nBottomTiles;
    if (selector->getTextureId() > Textureholder::TEXTURES_END - 5)
        nBottomTiles = Textureholder::TEXTURES_END - selector->getTextureId();
    else
        nBottomTiles = 4;

    int nTopTiles;
    if (selector->getTextureId() > -1)
    {
        nTopTiles = selector->getTextureId();

        if (nTopTiles > 4)
            nTopTiles = 4;
    }
    else
        nTopTiles = 0;

    std::cout << nBottomTiles << " t: " << nTopTiles << std::endl;

    for (int i = nTopTiles; i > 0; i--)
    {
        sf::RectangleShape shape(previewSize);
        shape.setTexture(Textureholder::getTexture(selector->getTextureId() - i));
        rectTopPreviewers.push_back(shape);
    }

    int nExtraSpace = (3 - nTopTiles) * rectSpace.y;
    for (int i = 0; i < rectTopPreviewers.size(); i++)
        rectTopPreviewers.at(i).setPosition(border.x, border.y + rectSpace.y * i + nExtraSpace);

    for (int i = 0; i < nBottomTiles; i++)
    {
        sf::RectangleShape shape(previewSize);

        int textureId = selector->getTextureId() == -1 ? 1 + selector->getTextureId() + i : selector->getTextureId() + i + 1;
        shape.setTexture(Textureholder::getTexture(textureId));
        rectBotPreviewers.push_back(shape);
    }

    int textureId = selector->getTextureId() > -1 ? selector->getTextureId() : 0;
    selectedRect.setTexture(Textureholder::getTexture(textureId));
    selectedRect.setPosition(sf::Vector2f(border.x, border.y + rectSpace.y * nTopTiles + nExtraSpace));

    if (selector->getTextureId() >= 0)
        selectedRect.setFillColor(sf::Color(255, 255, 255, 255));
    else
        selectedRect.setFillColor(sf::Color::Transparent);

    nExtraSpace = rectSpace.y * 2 + previewSize.y * 3;
    for (int i = 0; i < rectBotPreviewers.size(); i++)
        rectBotPreviewers.at(i).setPosition(border.x, border.y + rectSpace.y * i + nExtraSpace);


    for (int i = 0; i < rectTopPreviewers.size(); i++)
    {
        sf::RectangleShape shape = rectTopPreviewers.at(i);
        shape.setTextureRect(sf::IntRect(0, 0, shape.getTexture()->getSize().x, shape.getTexture()->getSize().y));
    }

    selectedRect.setTextureRect(sf::IntRect(0, 0, selectedRect.getTexture()->getSize().x, selectedRect.getTexture()->getSize().y));

    for (int i = 0; i < rectBotPreviewers.size(); i++)
    {
        sf::RectangleShape shape = rectBotPreviewers.at(i);
        shape.setTextureRect(sf::IntRect(0, 0, shape.getTexture()->getSize().x, shape.getTexture()->getSize().y));
    }
}

void TilePreviewer::setSelector(Selector *nSelector)
{
    selector = nSelector;
}
