#include "editor.hpp"

const sf::Time Editor::TimePerFrame = sf::seconds(1.f/120.f);
const std::string Editor::NAME = "Platformer Editor";
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

    Tile::loadTextures();
    Decoration::loadTextures();
    Tree::loadTextures();

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
            case sf::Event::MouseWheelMoved:
                selectBlock(event.mouseWheel);
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

    // Sets the selector's position only if within screen
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
}

void Editor::render()
{
    mWindow.clear();
    mView.reset(sf::FloatRect(mScreen.x, mScreen.y, WIDTH, HEIGHT));
    mWindow.setView(mView);
    mMap.draw(mWindow);
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

void Editor::selectBlock(sf::Event::MouseWheelEvent event)
{
    mSelector.changeTexture(event.delta);
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

