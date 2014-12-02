#include "game.hpp"

const sf::Time Game::TimePerFrame = sf::seconds(1.f/120.f);
const std::string Game::NAME = "Platformer";
const int Game::WIDTH = 1400;
const int Game::HEIGHT = 800;

Game::Game()
: mWindow(sf::VideoMode(WIDTH, HEIGHT), NAME)
{
    mWindow.setFramerateLimit(60);
    mView.reset(sf::FloatRect(0, 0, WIDTH, HEIGHT));
    mView.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));

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
    mView.reset(sf::FloatRect(mScreen.x, mScreen.y, WIDTH, HEIGHT));
    mWindow.setView(mView);
    mMap.draw(mWindow);
    //player.draw(mWindow);
    mWindow.setView(mWindow.getDefaultView());
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
