#include "decoration.hpp"

Decoration::Decoration()
{
}

void Decoration::setTexture(int id)
{
    if (id > Textureholder::NDECORATIONS)
        id -= Textureholder::NDECORATIONS + 3;

    mSprite.setTexture(*Textureholder::getDecorationT(id));
    int y = mSprite.getTexture()->getSize().y;
    mSprite.setOrigin(0, y);
}
