#include "editor.hpp"

const sf::Time Editor::TimePerFrame = sf::seconds(1.f/120.f);
const std::string Editor::NAME = "Platformer Editor";
const int Editor::WIDTH = 1400;
const int Editor::HEIGHT = 800;

Editor::Editor()
: mWindow(sf::VideoMode(WIDTH, HEIGHT), NAME)
, mScreen(0, 0)
, mScrollSpeed(250, 250)
{
    mWindow.setFramerateLimit(60);
    mView.reset(sf::FloatRect(0, 0, WIDTH, HEIGHT));
    mView.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));

    Tile::loadTextures();
    Decoration::loadTextures();
    Tree::loadTextures();

    mMap.loadMap("1");

    mLeft = mRight = mUp = mDown = false;

    mouseSelection.setSize(sf::Vector2f(50, 50));
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
        }
    }
}

void Editor::update()
{
    if(mLeft) mScreen.x += mScrollSpeed.x * TimePerFrame.asSeconds();
    if(mRight) mScreen.x -= mScrollSpeed.x * TimePerFrame.asSeconds();
    if(mUp) mScreen.y += mScrollSpeed.y * TimePerFrame.asSeconds();
    if(mDown) mScreen.y -= mScrollSpeed.y * TimePerFrame.asSeconds();
}

void Editor::render()
{
    mWindow.clear();
    mView.reset(sf::FloatRect(mScreen.x, mScreen.y, WIDTH, HEIGHT));
    mWindow.setView(mView);
    mMap.draw(mWindow);
    mWindow.setView(mWindow.getDefaultView());
    mWindow.display();
}

void Editor::handleUserInput(sf::Keyboard::Key key, bool isPressed)
{
    switch(key)
    {
        case sf::Keyboard::Left:
            mLeft = isPressed;
            break;
        case sf::Keyboard::Right:
            mRight = isPressed;
            break;
        case sf::Keyboard::Up:
            mUp = isPressed;
            break;
        case sf::Keyboard::Down:
            mDown = isPressed;
            break;
        case sf::Keyboard::R:
            reset();
            break;
        default:
            break;
    }
}

void Editor::reset()
{
    mScreen = sf::Vector2f(0, 0);
}

