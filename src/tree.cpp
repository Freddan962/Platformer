#include "tree.hpp"

void Tree::setTexture(int id)
{
    mSprite.setTexture(*Textureholder::getTreeT(id));
    int y = mSprite.getTexture()->getSize().y;
    mSprite.setOrigin(0, y);
}
