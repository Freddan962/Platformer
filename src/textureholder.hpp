#ifndef TEXTUREHOLDER_HPP
#define TEXTUREHOLDER_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

class Textureholder
{
    public:
        static void loadTextures();
        static sf::Texture *getTexture(int id);
    private:
        static void loadTexture(int size, std::string prefix);
        static sf::Texture *getTile(int id);
        static sf::Texture *getDecoration(int id);
        static sf::Texture *getTree(int id);
    public:
            static const int NTILES;
            static const int NDECORATIONS;
            static const int NTREES;

            static const int TILES_END;
            static const int DECORATIONS_END;
            static const int TREES_END;
    private:
        static std::vector<sf::Texture> textures;
};

#endif
