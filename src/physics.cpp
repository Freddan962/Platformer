#include "physics.hpp"
#include <iostream>

bool physics::isRectColliding(sf::RectangleShape rectShape, sf::RectangleShape rectShape2)
{
    return ((rectShape.getPosition().x / 16 == rectShape2.getPosition().x / 16) &&
            (rectShape.getPosition().y / 16 == rectShape2.getPosition().y / 16));
}

bool physics::isRectColliding(sf::RectangleShape rectShape, std::vector<sf::RectangleShape> body)
{
    for (std::vector<sf::RectangleShape>::iterator it = body.begin(); it != body.end(); it++)
        if (isRectColliding(rectShape, *it))
            return true;
}
