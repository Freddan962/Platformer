#ifndef TREE_HPP
#define TREE_HPP

#include <SFML/Graphics.hpp>
#include <vector>

#include "decoration.hpp"

class Tree : public Entity
{
    public:
        static void loadTextures();
        void        setTexture(int id);
    private:
        static const int nTextures;
        static std::vector<sf::Texture> textures;
};

#endif
