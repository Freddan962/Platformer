#ifndef TILE_HPP
#define TILE_HPP

#include <SFML/Graphics.hpp>
#include <map>
#include <iostream>
#include <vector>

#include "entity.hpp"

class Tile : public Entity
{
    public:
                        Tile();

        static void     loadTextures();
        void            update();
        void            onCollide();

        void            setTexture(int id);
        void            setSolid(int isSolid);

        static sf::Texture *getTexture(int id);

    public:
        static const int NTEXTURES;
        static const int WIDTH;
        static const int HEIGHT;

    private:
        static std::vector<sf::Texture> textures;
        bool solid;
};

#endif
