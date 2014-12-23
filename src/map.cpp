#include "map.hpp"

Map::Map()
{
    mBackgroundTexture.loadFromFile("media/background.jpg");
    mBackground.setTexture(mBackgroundTexture);
}

void Map::draw(sf::RenderTarget &target)
{
    target.draw(mBackground);
    drawVector(target, mTiles);
    drawVector(target, mTrees);
    drawVector(target, mDecoration);
}

template <class A>
void Map::drawVector(sf::RenderTarget &target, std::vector<std::vector<A> > &dVector)
{
    for (unsigned int i = 0; i < dVector.size(); i++)
        for (unsigned int j = 0; j < dVector.at(i).size(); j++)
            dVector.at(i).at(j).draw(target);
}

void Map::loadMap(std::string filepath)
{
    loadData(mTiles, filepath + ".tiles");
    loadData(mTrees, filepath + ".trees");
    loadData(mDecoration, filepath + ".decor");

    mSize.x = mTiles.at(0).size() - 1;
    mSize.y = mTiles.size() - 1;
}

template <class A>
void Map::loadData(std::vector<std::vector<A> > &dVector, std::string filepath)
{
    std::ifstream file("maps/" + filepath);
    std::string line;
    std::stringstream ss;

    int i = 0;
    while (std::getline(file, line))
    {
        ss.clear();
        ss.str(line);

        std::vector<A> row;
        int id, j = 0;

        while(ss >> id)
        {
            A tObject;
            tObject.mSprite.setPosition(Tile::WIDTH * j, Tile::HEIGHT * i);

            if (id != 0)
                tObject.setTexture(id);

            row.push_back(tObject);
            j++;
        }

        dVector.push_back(row);
        row.clear();
        i++;
    }
}

void Map::expand(sf::Vector2i size)
{
    if (size.x > mSize.x)
    {
        expandObjectVectorX<Tile>(mTiles, size);
        expandObjectVectorX<Decoration>(mDecoration, size, 1);
        expandObjectVectorX<Tree>(mTrees, size, 1);

        mSize.x += size.x - mSize.x;
    }

    if (size.y > mSize.y)
    {
        expandObjectVectorY<Tile>(mTiles, size);
        expandObjectVectorY<Decoration>(mDecoration, size, 1);
        expandObjectVectorY<Tree>(mTrees, size, 1);

        mSize.y += size.y - mSize.y;
    }
}

template<class A>
void Map::expandObjectVectorX(std::vector<std::vector<A> > &objectVector, sf::Vector2i size, int modifier)
{
    int deltaX = size.x - mSize.x;

    for (int y = 0; y <= mSize.y + modifier; y++)
    {
        for (int nTiles = 0; nTiles < deltaX; nTiles++)
        {
            A object;
            object.mSprite.setPosition(mSize.x * Tile::WIDTH + nTiles * Tile::WIDTH + Tile::WIDTH, y * Tile::HEIGHT);
            objectVector.at(y).push_back(object);
        }
    }
}

template<class A>
void Map::expandObjectVectorY(std::vector<std::vector<A> > &objectVector, sf::Vector2i size, int modifier)
{
    int deltaY = size.y - mSize.y;
    for (int i = 0; i < deltaY; i++)
    {
        std::vector<A> newObjectLine;
        for (int j = 0; j <= mSize.x + modifier; j++)
        {
            A object;
            object.mSprite.setPosition(sf::Vector2f(Tile::WIDTH * j, Tile::HEIGHT * mSize.y + Tile::HEIGHT * i + Tile::HEIGHT));
            newObjectLine.push_back(object);
        }

        objectVector.push_back(newObjectLine);
    }
}


template <class A>
void Map::fillStuff(sf::Vector2i startPos, sf::Vector2i endPos, A entity, std::string type)
{
    sf::Vector2i deltaPos = endPos - startPos;
    for (int y = 0; y < deltaPos.y; y++)
    {
        for (int x = 0; x < deltaPos.x; x++)
        {

            if (type == "Tile")
                mTiles.at(y).at(x) = entity;

            if (type == "Decoration")
                mDecoration.at(y).at(x) = entity;

            if (type == "Tree")
                mTrees.at(y).at(x) = entity;
        }
    }
}

sf::Vector2i Map::getTileSize()
{
    return mSize;
}

bool Map::mouseOutOfMap(sf::Vector2i mouseTilePos)
{
    sf::Vector2i tileSize = getTileSize();
    return (mouseTilePos.x > tileSize.x || mouseTilePos.y > tileSize.y);
}

sf::Sprite *Map::getBackground()
{
    return &mBackground;
}

std::vector<std::vector<Tile> > *Map::getTiles()
{
    return &mTiles;
}
std::vector<std::vector<Decoration> > *Map::getDecorations()
{
    return &mDecoration;
}
std::vector<std::vector<Tree> > *Map::getTrees()
{
    return &mTrees;
}
