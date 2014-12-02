#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <string>

#include "physics.hpp"
#include "map.hpp"
#include "player.hpp"
#include "tile.hpp"

class Game
{
    public:
                    Game();
        void        run();

    private:
        void        processInput();
        void        update();
        void        render();
        void        handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
        void        reset();

    private:
        sf::RenderWindow            mWindow;
        sf::View                    mView;
        sf::Vector2f                mScreen;

        static const std::string    NAME;
        static const int            WIDTH;
        static const int            HEIGHT;
        static const sf::Time       TimePerFrame;

        Map                         mMap;
        Player                      player;
};

#endif
