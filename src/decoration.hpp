#ifndef DECORATION_HPP
#define DECORATION_HPP

#include <SFML/Graphics.hpp>
#include <vector>

#include "entity.hpp"
#include "textureholder.hpp"

class Decoration : public Entity
{
    public:
                    Decoration();
        void        setTexture(int id);
};

#endif
