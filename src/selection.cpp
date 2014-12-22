#include "selection.hpp"

Selection::Selection()
{
    startPos = sf::Vector2i(-1, -1);
    endPos = sf::Vector2i(0, 0);
}

void Selection::updateSelection()
{
    squares.clear();
    sf::Vector2i deltaPos = endPos - startPos;

    if (deltaPos.x > 0 || deltaPos.y > 0)
    {
        for (int y = 0; y < deltaPos.y + 1; y++)
        {
            std::vector<sf::Sprite> rectangleLine;
            for (int x = 0; x < deltaPos.x + 1; x++)
            {
                sf::Sprite rectSprite;
                if (textureId >= 0)
                {
                    rectSprite.setTexture(*Textureholder::getTexture(textureId));
                    rectSprite.setScale(sf::Vector2f((float)Tile::WIDTH / rectSprite.getTexture()->getSize().x,
                                                    (float)Tile::HEIGHT / rectSprite.getTexture()->getSize().y));
                }

                rectSprite.setColor(sf::Color(35, 201, 255, 155));
                rectSprite.setPosition(startPos.x * Tile::WIDTH + x * Tile::WIDTH, startPos.y * Tile::HEIGHT + y * Tile::HEIGHT);
                rectangleLine.push_back(rectSprite);
            }

            squares.push_back(rectangleLine);
        }
    }
}

void Selection::draw(sf::RenderTarget &target)
{
    for (int i = 0; i < squares.size(); i++)
        for (int j = 0; j < squares.at(i).size(); j++)
            target.draw(squares.at(i).at(j));
}

bool Selection::isActive()
{
    std::cout << startPos.x << " " << startPos.y << std::endl;
    if (startPos.x > -1 || startPos.y > -1)
        return true;

    return false;
}

void Selection::reset()
{
    startPos = endPos = sf::Vector2i(-1, -1);
}

void Selection::setStartPos(sf::Vector2i start)
{
    startPos = start;
}

void Selection::setEndPos(sf::Vector2i end)
{
    endPos = end;
}

void Selection::setTexture(int id)
{
    textureId = id;
}

sf::Vector2i *Selection::getStartPos()
{
    return &startPos;
}

sf::Vector2i *Selection::getEndPos()
{
    return &endPos;
}
