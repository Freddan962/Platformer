#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>

class Entity
{
    public:
                Entity();
        void    draw(sf::RenderTarget &target);

    public:
        sf::Texture     mTexture;
        sf::Sprite      mSprite;
};

#endif
