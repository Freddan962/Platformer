#ifndef TILE_HPP
#define TILE_HPP

#include <SFML/Graphics.hpp>
#include <map>
#include <iostream>
#include <vector>

#include "entity.hpp"
#include "textureholder.hpp"

class Tile : public Entity
{
    public:
                        Tile();

        void            setTexture(int id);
        void            setSolid(int isSolid);

    public:
        static const int WIDTH;
        static const int HEIGHT;

    private:
        bool solid;
};

#endif
