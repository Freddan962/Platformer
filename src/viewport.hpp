#ifndef VIEWPORT_HPP
#define VIEWPORT_HPP

#include "SFML/Graphics.hpp"

class Viewport
{
    public:

        Viewport();
        sf::Vector2f getModifier();

        void moveLeft(float x);
        void moveRight(float x);
        void moveUp(float y);
        void moveDown(float y);
    private:
        sf::Vector2f viewModifier;
};

#endif
