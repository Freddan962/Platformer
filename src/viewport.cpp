#include "viewport.hpp"

Viewport::Viewport()
: viewModifier(0.f, 0.f)
{
}

void Viewport::moveLeft(float x)
{
    viewModifier.x += x;
}

void Viewport::moveRight(float x)
{
    viewModifier.x -= x;
}

void Viewport::moveUp(float y)
{
    viewModifier.y += y;
}

void Viewport::moveDown(float y)
{
    viewModifier.y -= y;
}

sf::Vector2f Viewport::getModifier()
{
    return viewModifier;
}
