#include "game.hpp"

const sf::Time Game::timePerFrame = sf::seconds(1.f/120.f);
const std::string Game::mName = "Platformer Evolution";
const float Game::mWidth = 1400;
const float Game::mHeight = 800;

Game::Game()
: mWindow(sf::VideoMode(mWidth, mHeight), mName)
{
    mWindow.setFramerateLimit(60);
    Tile::loadTextures();
    Decoration::loadTextures();
    Tree::loadTextures();

    mMap.loadMap("1");
}

void Game::run()
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

void Game::processInput()
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

void Game::update()
{
}

void Game::render()
{
    mWindow.clear();
    mMap.draw(mWindow);
    //player.draw(mWindow);
    mWindow.display();
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
    switch(key)
    {
        default:
            break;
    }
}

void Game::reset()
{

}
