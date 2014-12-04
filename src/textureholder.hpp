#ifndef TEXTUREHOLDER_HPP
#define TEXTUREHOLDER_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Textureholder
{
    public:
        static void loadTextures();
        static sf::Texture *getTexture(int id);
        static sf::Texture *getTileT(int id);
        static sf::Texture *getDecorationT(int id);
        static sf::Texture *getTreeT(int id);

    private:
        static void loadTexture(int size, std::string prefix);

    public:
            static const int NTILES;
            static const int NDECORATIONS;
            static const int NTREES;

            static const int TILES_END;
            static const int DECORATIONS_END;
            static const int TREES_END;

            static const int TEXTURES_END;
    private:
        static std::vector<sf::Texture> textures;
};

#endif
