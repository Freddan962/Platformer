#include "entity.hpp"
#include <iostream>

Entity::Entity()
{}

void Entity::draw(sf::RenderTarget &target)
{
    target.draw(mSprite);
}
