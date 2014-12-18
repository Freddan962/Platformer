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
    for (int i = 0; i < dVector.size(); i++)
        for (int j = 0; j < dVector.at(i).size(); j++)
            dVector.at(i).at(j).draw(target);
}

void Map::loadMap(std::string filepath)
{
    loadData(mTiles, filepath + ".tiles");
    loadData(mTrees, filepath + ".trees");
    loadData(mDecoration, filepath + ".decor");
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
    expandObjectVector<Tile>(mTiles, size);
    expandObjectVector<Decoration>(mDecoration, size);
    expandObjectVector<Tree>(mTrees, size);
}

template<class A>
void Map::expandObjectVector(std::vector<std::vector<A> > &objectVector, sf::Vector2i size)
{
    sf::Vector2i tileSize = getTileSize();

    if (size.x > objectVector.size() - 1)
    {
        int deltaX = size.x - objectVector.size() - 1;

        std::cout << deltaX << std::endl;
        for (int y = 0; y < objectVector.size(); y++)
        {
            for (int nTiles = 0; nTiles < deltaX; nTiles++)
            {
                A object;
                objectVector.at(y).push_back(object);
            }
        }
    }

    if (size.y > tileSize.y)
    {
        int deltaY = size.y - tileSize.y;
        std::cout << deltaY << "DY" << std::endl;
        for (int i = 0; i < deltaY; i++)
        {
            std::vector<A> newObjectLine;
            for (int j = 0; j < objectVector.at(0).size(); j++)
            {
                A object;
                newObjectLine.push_back(object);
            }

            objectVector.push_back(newObjectLine);
        }
    }

}

sf::Vector2i Map::getTileSize()
{
    sf::Vector2i size;

    size.x = mTiles.at(0).size() - 1;
    size.y = mTiles.size() - 1;

    return size;
}

bool Map::mouseOutOfMap(sf::Vector2i mouseTilePos)
{
    sf::Vector2i tileSize = getTileSize();
    return (mouseTilePos.x > getTileSize().x || mouseTilePos.y > getTileSize().y);
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
