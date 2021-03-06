#include "editor.hpp"

const sf::Time Editor::TimePerFrame = sf::seconds(1.f/120.f);
const std::string Editor::NAME = "Platform Editor";
const int Editor::WIDTH = 1400;
const int Editor::HEIGHT = 800;

Editor::Editor()
: mWindow(sf::VideoMode(WIDTH, HEIGHT), NAME)
, mScreen(0, 0)
, mScrollSpeed(300, 300)
{
    mWindow.setFramerateLimit(60);
    mView.reset(sf::FloatRect(0, 0, WIDTH, HEIGHT));
    mView.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));

    Textureholder::loadTextures();

    mMap.loadMap("1");

    mViewMode = true;
    mLeft = mRight = mUp = mDown = false;
    mTilePreviewer.setSelector(&mSelector);
}

void Editor::run()
{
    sf::Clock frameTimer;
    sf::Time timeSinceLastFrame = sf::Time::Zero;

    while (mWindow.isOpen())
    {
        timeSinceLastFrame += frameTimer.restart();
        while (timeSinceLastFrame >= TimePerFrame)
        {
            processInput();
            update();
            timeSinceLastFrame -= TimePerFrame;
        }

        processInput();
        render();
    }
}

void Editor::processInput()
{
    sf::Event event;

    while (mWindow.pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::Closed:
                mWindow.close();
                break;
            case sf::Event::KeyPressed:
                handleUserInput(event.key.code, true);
                break;
            case sf::Event::KeyReleased:
                handleUserInput(event.key.code, false);
                break;
            case sf::Event::MouseWheelMoved:
                selectBlock(event.mouseWheel);
                break;
            case sf::Event::MouseButtonPressed:
                onMouseClick(event.mouseButton.button, true);
                break;
            case sf::Event::MouseButtonReleased:
                onMouseClick(event.mouseButton.button, false);
                break;
            default:
                break;
        }
    }
}

void Editor::update()
{
    if(mLeft) mScreen.x -= mScrollSpeed.x * TimePerFrame.asSeconds();
    if(mRight) mScreen.x += mScrollSpeed.x * TimePerFrame.asSeconds();
    if(mUp) mScreen.y -= mScrollSpeed.y * TimePerFrame.asSeconds();
    if(mDown) mScreen.y += mScrollSpeed.y * TimePerFrame.asSeconds();

    // Sets the selector's position only if within map boundaries
    sf::Vector2i mousePos = sf::Mouse::getPosition(mWindow);
    int tileCol = mSelector.getShape()->getPosition().x/100;
    int tileRow = mSelector.getShape()->getPosition().y/100;

    if (mousePos.x + mScreen.x > 0)
        tileCol = (mousePos.x + mScreen.x) / Tile::WIDTH;

    if (mousePos.y + mScreen.y > 0)
        tileRow = (mousePos.y + mScreen.y) / Tile::HEIGHT;

    sf::Vector2f mouseTilePos(tileCol * Tile::WIDTH, tileRow * Tile::HEIGHT);
    mSelector.getShape()->setPosition(mouseTilePos.x, mouseTilePos.y);

    mTilePreviewer.update(mScreen);
    mMap.getBackground()->setPosition(mScreen);

    if (mSelection.isActive() && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    {
        mSelection.setEndPos(getMouseTilePos());
        mSelection.updateSelection();
    }
}

void Editor::render()
{
    mWindow.clear();
    mView.reset(sf::FloatRect(mScreen.x, mScreen.y, WIDTH, HEIGHT));
    mWindow.setView(mView);
    mMap.draw(mWindow);
    mSelection.draw(mWindow);
    mSelector.draw(mWindow);
    mTilePreviewer.draw(mWindow);
    mWindow.setView(mWindow.getDefaultView());
    mWindow.display();
}

void Editor::handleUserInput(sf::Keyboard::Key key, bool isPressed)
{
    switch(key)
    {
        case sf::Keyboard::Left:
            moveLeft(isPressed);
            break;
        case sf::Keyboard::Right:
            moveRight(isPressed);
            break;
        case sf::Keyboard::Up:
            moveUp(isPressed);
            break;
        case sf::Keyboard::Down:
            moveDown(isPressed);
            break;
        case sf::Keyboard::R:
            reset();
            break;
        case sf::Keyboard::M:
            changeViewMode(isPressed);
            break;
        default:
            break;
    }
}

void Editor::onMouseClick(sf::Mouse::Button button, bool isPressed)
{
    if (isPressed)
    {
        if (button == sf::Mouse::Left)
            mSelection.setStartPos(getMouseTilePos());

        if (mMap.mouseOutOfMap(getMouseTilePos()))
            mMap.expand(getMouseTilePos());
    }
    else
    {
        std::string textureClassName = textureIdToC(mSelector.getTextureId());
        sf::Vector2f position = mSelector.getShape()->getPosition();

        if (button == sf::Mouse::Left)
        {
            mSelection.setEndPos(getMouseTilePos());
            mSelection.updateSelection();

          if (textureClassName == "Tile")
                mMap.fillStuff(*mSelection.getStartPos(), *mSelection.getEndPos(), createMapObject<Tile>(button, position, 1), textureClassName);
            else if(textureClassName == "Decoration")
                mMap.fillStuff(*mSelection.getStartPos(), *mSelection.getEndPos(), createMapObject<Decoration>(button, position), textureClassName);
            else if(textureClassName == "Tree")
                mMap.fillStuff(*mSelection.getStartPos(), *mSelection.getEndPos(), createMapObject<Tree>(button, position), textureClassName);
            mSelection.reset();
        }

        if (button == sf::Mouse::Left || button == sf::Mouse::Right)
        {
            if (textureClassName == "Tree" || textureClassName == "Decoration")
                position.y += Tile::HEIGHT;

            sf::Vector2u tilePosition = sf::Vector2u(position.x/Tile::WIDTH, position.y/Tile::HEIGHT);

            if (textureClassName == "Tile")
                mMap.getTiles()->at(tilePosition.y).at(tilePosition.x) = createMapObject<Tile>(button, position, 1);
            else if (textureClassName == "Decoration")
                mMap.getDecorations()->at(tilePosition.y).at(tilePosition.x) = createMapObject<Decoration>(button, position);
            else if (textureClassName == "Tree")
                mMap.getTrees()->at(tilePosition.y).at(tilePosition.x) = createMapObject<Tree>(button, position);
        }
    }
}

template<typename T>
T Editor::createMapObject(sf::Mouse::Button button, sf::Vector2f position, int tModifier)
{
    T mapObject;

    if (mSelector.getTextureId() >= 0 && button == sf::Mouse::Left)
        mapObject.setTexture(mSelector.getTextureId() + tModifier);

    mapObject.mSprite.setPosition(position);
    return mapObject;
}

std::string Editor::textureIdToC(int id)
{
    if (id <= Textureholder::TILES_END)
        return "Tile";
    else if(id > Textureholder::TILES_END &&  id <= Textureholder::DECORATIONS_END)
        return "Decoration";
    else if(id > Textureholder::DECORATIONS_END)
        return "Tree";
}

sf::Vector2i Editor::getMouseTilePos()
{
    sf::Vector2i mouseTilePos;

    sf::Vector2i mousePos = sf::Mouse::getPosition(mWindow);

    mouseTilePos.x = (mousePos.x + mScreen.x) / Tile::WIDTH;
    mouseTilePos.y = (mousePos.y + mScreen.y) / Tile::HEIGHT;

    return mouseTilePos;
}

void Editor::selectBlock(sf::Event::MouseWheelEvent event)
{
    if (mSelector.getTextureId() + event.delta >= -1)
    {
        mSelector.changeTexture(event.delta);
        mSelection.setTexture(mSelector.getTextureId());
    }
}

void Editor::reset()
{
    mScreen = sf::Vector2f(0, 0);
    mLeft = mRight = mUp = mDown = false;
}

void Editor::moveLeft(bool isPressed)
{
    if (mViewMode) mLeft = isPressed;
    else if(isPressed) mScreen.x -= mScrollSpeed.x;
}

void Editor::moveRight(bool isPressed)
{
    if (mViewMode) mRight = isPressed;
    else if(isPressed) mScreen.x += mScrollSpeed.x;
}

void Editor::moveUp(bool isPressed)
{
    if (mViewMode) mUp = isPressed;
    else if(isPressed) mScreen.y -= mScrollSpeed.y;
}

void Editor::moveDown(bool isPressed)
{
    if (mViewMode) mDown = isPressed;
    else if(isPressed) mScreen.y += mScrollSpeed.y;
}

void Editor::changeViewMode(bool isPressed)
{
    if (isPressed) mViewMode = !mViewMode;
}

