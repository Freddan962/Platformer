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
        sf::Sprite  *getBackground();
    private:
        template <class A>
        void    loadData(std::vector<std::vector<A> > &dVector, std::string filepath);

        template <class A>
        void    drawVector(sf::RenderTarget &target, std::vector<std::vector<A> > &dVector);

    private:
        std::vector<std::vector<Tile> > mTiles;
        std::vector<std::vector<Decoration> > mDecoration;
        std::vector<std::vector<Tree> > mTrees;

        sf::Sprite mBackground;
        sf::Texture mBackgroundTexture;
};

#endif
