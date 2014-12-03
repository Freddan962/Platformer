#ifndef TILEPREVIEWER_HPP
#define TILEPREVIEWER_HPP

#include <SFML/Graphics.hpp>
#include "selector.hpp"

class TilePreviewer
{
    public:
             TilePreviewer();
        void update(sf::Vector2f &relPos);
        void draw(sf::RenderTarget &target);
        void setSelector(Selector *nSelector);
    private:
        sf::RectangleShape mShape;
        Selector *selector;
};

#endif
