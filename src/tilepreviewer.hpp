#ifndef TILEPREVIEWER_HPP
#define TILEPREVIEWER_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "selector.hpp"

class TilePreviewer
{
    public:
             TilePreviewer();
        void update();
        void draw(sf::RenderTarget &target);

        void setSelector(Selector *nSelector);
        void setRelativePos(sf::Vector2f *pos);
    private:
        void updateTiles();
        void fillPreviewers(int nTop, int nBot);
        void positionPreviewers(int nTop, int nBot);
        void fixTexture();

        int  topTilesNeeded();
        int  botTilesNeeded();
        sf::RectangleShape createPreviewRect(int textureId);

    private:
        sf::Vector2f *relativePos;
        int oldTextureId;
        static const sf::Vector2f previewSize;
        sf::Vector2f border, rectSpace;
        sf::RectangleShape mShape;
        Selector *selector;

        std::vector<sf::RectangleShape> topPreviewers;
        std::vector<sf::RectangleShape> botPreviewers;
        sf::RectangleShape selectedRect;
};

#endif
