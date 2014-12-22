#ifndef SELECTION_HPP
#define SELECTION_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

#include "tile.hpp"

class Selection
{
    public:
        Selection();
        void draw(sf::RenderTarget &target);
        void updateSelection();
        bool isActive();
        void reset();

        void setStartPos(sf::Vector2i start);
        void setEndPos(sf::Vector2i end);
        void setTexture(int id);

        sf::Vector2i *getStartPos();
        sf::Vector2i *getEndPos();
    private:
        std::vector<std::vector<sf::Sprite> > squares;

        sf::Vector2i startPos, endPos;

        int textureId;
};

#endif
