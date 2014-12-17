#ifndef EDITOR_HPP
#define EDITOR_HPP

#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "textureholder.hpp"
#include "physics.hpp"
#include "map.hpp"
#include "player.hpp"
#include "tile.hpp"
#include "selector.hpp"
#include "tilepreviewer.hpp"

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

        void        onMouseClick(sf::Keyboard::Key key, bool isPressed);

        void        selectBlock(sf::Event::MouseWheelEvent event);
        void        reset();

        template<typename T>
        T          createMapObject(sf::Keyboard::Key key, sf::Vector2f position, int tModifier = 0);

        void        moveLeft(bool isPressed);
        void        moveRight(bool isPressed);
        void        moveUp(bool isPressed);
        void        moveDown(bool isPressed);

        void        changeViewMode(bool isPressed);
        std::string textureIdToC(int id);

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

        Selector                    mSelector;
        TilePreviewer               mTilePreviewer;
};
#endif
