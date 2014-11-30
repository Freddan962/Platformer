#include <SFML/Graphics.hpp>
#include <vector>

namespace physics
{
    bool    isRectColliding(sf::RectangleShape rectShape, sf::RectangleShape rectShape2);
    bool    isRectColliding(sf::RectangleShape rectShape, std::vector<sf::RectangleShape> body);
};
