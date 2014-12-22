#ifndef SELECTOR_HPP
#define SELECTOR_HPP

#include <SFML/Graphics.hpp>
#include "tile.hpp"
#include "textureholder.hpp"

class Selector
{
    public:
                Selector();
        void    update();
        void    draw(sf::RenderTarget &target);
        void    nextTexture();
        void    previousTexture();
        void    changeTexture(int modifier);

        int     getTextureId();

        sf::RectangleShape *getShape();
        sf::Texture getTexture();

    private:
        sf::RectangleShape mShape;
        int textureId;
};

#endif
