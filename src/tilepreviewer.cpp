#include "tilepreviewer.hpp"

const sf::Vector2f TilePreviewer::previewSize(30, 30);

TilePreviewer::TilePreviewer()
{
    mShape.setSize(sf::Vector2f(40, 800));
    mShape.setFillColor(sf::Color(46, 46, 44));

    border.x = 5;
    border.y = 175;

    rectSpace.y = 50;

    for (int i = 0; i < 9; i++)
    {
        sf::RectangleShape shape(previewSize);
        shape.setPosition(border.x, border.y + rectSpace.y * i);
        rectPreviewers.push_back(shape);
    }
}

void TilePreviewer::update(sf::Vector2f &relPos)
{
    mShape.setPosition(relPos);

    for (int i = 0; i < 9; i++)
        rectPreviewers.at(i).setPosition(border.x + relPos.x, relPos.y + border.y + rectSpace.y * i);
}

void TilePreviewer::draw(sf::RenderTarget &target)
{
    target.draw(mShape);

    for (int i = 0; i < rectPreviewers.size(); i++)
        target.draw(rectPreviewers.at(i));
}

void TilePreviewer::setSelector(Selector *nSelector)
{
    selector = nSelector;
}
