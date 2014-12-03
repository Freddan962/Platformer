#ifndef SELECTOR_HPP
#define SELECTOR_HPP

#include <SFML/Graphics.hpp>
#include "tile.hpp"
#include "decoration.hpp"
#include "tree.hpp"

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

    private:
        sf::RectangleShape mShape;
        int textureId;
        int tileStart, decorationStart, treeStart;
};

#endif
