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
        static const std::string    mName;
        static const float          mWidth;
        static const float          mHeight;
        static const sf::Time       timePerFrame;

        Map                         mMap;
        Player                      player;
};

#endif
