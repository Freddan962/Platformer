#include "map.hpp"

Map::Map()
: mViewport()
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
        int type, j = 0;

        while(ss >> type)
        {
            A tObject;
            tObject.mSprite.setPosition(Tile::width * j, Tile::height * i);

            if (type != 0)
                tObject.setTexture(type-1);

            row.push_back(tObject);
            j++;
        }

        dVector.push_back(row);
        row.clear();
        i++;
    }
}
