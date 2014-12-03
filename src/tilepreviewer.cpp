#include "tilepreviewer.hpp"

#include <iostream>

TilePreviewer::TilePreviewer()
{
    mShape.setSize(sf::Vector2f(40, 800));
    mShape.setFillColor(sf::Color(46, 46, 44));
}

void TilePreviewer::update(sf::Vector2f &relPos)
{
    mShape.setPosition(relPos);
}

void TilePreviewer::draw(sf::RenderTarget &target)
{
    target.draw(mShape);
}

void TilePreviewer::setSelector(Selector *nSelector)
{
    selector = nSelector;
}
