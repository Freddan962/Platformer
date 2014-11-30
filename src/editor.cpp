#include "editor.hpp"

const sf::Time Editor::timePerFrame = sf::seconds(1.f/120.f);
const std::string Editor::mName = "Platformer Editor";
const float Editor::mWidth = 1400;
const float Editor::mHeight = 800;

Editor::Editor()
: mWindow(sf::VideoMode(mWidth, mHeight), mName)
{
    mWindow.setFramerateLimit(60);
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
        while (timeSinceLastFrame >= timePerFrame)
        {
            processInput();
            update();
            timeSinceLastFrame -= timePerFrame;
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
    mMap.draw(mWindow);
    //player.draw(mWindow);
    mWindow.display();
}

void Editor::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
    switch(key)
    {
        default:
            break;
    }
}

void Editor::reset()
{

}

