#ifndef EDITOR_HPP
#define EDITOR_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <string>

#include "physics.hpp"
#include "map.hpp"
#include "player.hpp"
#include "tile.hpp"

class Editor
{
    public:
                    Editor();
        void        run();

    private:
        void        processInput();
        void        update();
        void        render();
        void        handleUserInput(sf::Keyboard::Key key, bool isPressed);
        void        reset();

        void        moveLeft(bool isPressed);
        void        moveRight(bool isPressed);
        void        moveUp(bool isPressed);
        void        moveDown(bool isPressed);

        void        changeViewMode(bool isPressed);

    private:
        sf::RenderWindow            mWindow;
        sf::View                    mView;
        sf::Vector2f                mScreen;

        static const std::string    NAME;
        static const int            WIDTH;
        static const int            HEIGHT;
        static const sf::Time       TimePerFrame;

        Map                         mMap;
        sf::Vector2f                mScrollSpeed;
        bool                        mViewMode;
        bool                        mLeft, mRight, mUp, mDown;
        sf::RectangleShape          mouseSelection;
};

#endif
