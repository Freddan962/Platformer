#include "tree.hpp"

void Tree::setTexture(int id)
{
    if (id > Textureholder::NTREES)
        id -= Textureholder::TEXTURES_END - 6;

    mSprite.setTexture(*Textureholder::getTreeT(id));
    int y = mSprite.getTexture()->getSize().y;
    mSprite.setOrigin(0, y);
}
