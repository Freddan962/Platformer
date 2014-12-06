#ifndef TILEPREVIEWER_HPP
#define TILEPREVIEWER_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "selector.hpp"

class TilePreviewer
{
    public:
             TilePreviewer();
        void update(sf::Vector2f &relPos);
        void draw(sf::RenderTarget &target);
        void setSelector(Selector *nSelector);
    private:
        void updateTiles();
    private:
        static const sf::Vector2f previewSize;
        sf::Vector2f border, rectSpace;
        sf::RectangleShape mShape;
        Selector *selector;

        std::vector<sf::RectangleShape> rectPreviewers;
        std::vector<sf::RectangleShape> rectTopPreviewers;
        std::vector<sf::RectangleShape> rectBotPreviewers;
        sf::RectangleShape selectedRect;
};

#endif
