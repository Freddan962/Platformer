#ifndef MAP_HPP
#define MAP_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <typeinfo>

#include "tile.hpp"
#include "decoration.hpp"
#include "tree.hpp"

class Map
{
    public:
                    Map();
        void        draw(sf::RenderTarget &target);
        void        loadMap(std::string filepath);
        void        expand(sf::Vector2i size);

        sf::Sprite  *getBackground();
        std::vector<std::vector<Tile> > *getTiles();
        std::vector<std::vector<Decoration> > *getDecorations();
        std::vector<std::vector<Tree> > *getTrees();

        sf::Vector2i getTileSize();
        bool         mouseOutOfMap(sf::Vector2i mouseTilePos);
    private:
        template <class A>
        void    loadData(std::vector<std::vector<A> > &dVector, std::string filepath);

        template <class A>
        void    drawVector(sf::RenderTarget &target, std::vector<std::vector<A> > &dVector);

        template <class A>
        void    expandObjectVector(std::vector<std::vector<A> > &objectVector, sf::Vector2i size);

    private:
        std::vector<std::vector<Tile> > mTiles;
        std::vector<std::vector<Decoration> > mDecoration;
        std::vector<std::vector<Tree> > mTrees;

        sf::Sprite mBackground;
        sf::Texture mBackgroundTexture;

        sf::Vector2i mSize;
};

#endif
