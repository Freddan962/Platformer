#include "editor.hpp"

const sf::Time Editor::TimePerFrame = sf::seconds(1.f/120.f);
const std::string Editor::NAME = "Platformer Editor";
const int Editor::WIDTH = 1400;
const int Editor::HEIGHT = 800;

Editor::Editor()
: mWindow(sf::VideoMode(WIDTH, HEIGHT), NAME)
, mScreen(0.f, 0.f)
{
    mWindow.setFramerateLimit(60);
    mView.reset(sf::FloatRect(0, 0, WIDTH, HEIGHT));
    mView.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));

    Tile::loadTextures();
    Decoration::loadTextures();
    Tree::loadTextures();

    mMap.loadMap("1");
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
                handlePlayerInput(event.key.code, true);
                break;
            case sf::Event::KeyReleased:
                handlePlayerInput(event.key.code, false);
                break;
        }
    }
}

void Editor::update()
{
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

void Editor::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
    switch(key)
    {
        case sf::Keyboard::Left:
            if (isPressed) mScreen.x += 25;
            break;
        case sf::Keyboard::Right:
            if (isPressed) mScreen.x -= 25;
            break;
        case sf::Keyboard::Up:
            if (isPressed) mScreen.y += 25;
            break;
        case sf::Keyboard::Down:
            if (isPressed) mScreen.y -= 25;
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

