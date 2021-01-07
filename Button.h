#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <iostream>
#include <functional>

#include "SFML/Graphics.hpp"

namespace UI
{
    enum State
    {
        Normal = 0,
        Hover = 1,
        Clicked = 2
    };

    class Button : public sf::Drawable
    {
    public:
        Button(sf::Vector2f position, std::string text);
        ~Button();

        void input(sf::Event& e, const sf::Vector2i& position);

        void setClickCallback(std::function<void(void)> clickCallback);

    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        sf::Color mBackgroundNormal;
        sf::Color mBackgroundHover;
        sf::Color mBackgroundClicked;
        sf::Color mTextColor;

        sf::Vector2f mSize;
        sf::Vector2f mPosition;
        State mState;

        sf::RectangleShape mButton;
        sf::Font mFont;
        sf::Text mLabel;

        std::function<void(void)> mClickCallback;
    };
};
#endif // BUTTON_HPP