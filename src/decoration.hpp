#ifndef DECORATION_HPP
#define DECORATION_HPP

#include <SFML/Graphics.hpp>
#include <vector>

#include "entity.hpp"

class Decoration : public Entity
{
    public:
                    Decoration();
        static void loadTextures();
        void        setTexture(int id);
        static sf::Texture *getTexture(int id);
        static const int NTEXTURES;
    private:
        static std::vector<sf::Texture> textures;
};

#endif
