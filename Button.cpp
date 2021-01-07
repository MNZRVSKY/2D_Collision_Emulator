#include "button.h"
#include <iostream>

UI::Button::Button(sf::Vector2f position, std::string text)
    :mPosition(position),
    mState(UI::State::Normal),
    mTextColor(sf::Color(255, 255, 255)),
    mBackgroundNormal(sf::Color(0, 255, 255, 100)),
    mBackgroundHover(sf::Color(0, 200, 200, 100)),
    mBackgroundClicked(sf::Color(0, 150, 150)),
    mClickCallback([]() {})
{
    mFont.loadFromFile("Fonts\\Neon.ttf");

    //set up text
    mLabel = sf::Text(text, mFont, 26);
    mLabel.setOrigin(mLabel.getGlobalBounds().width / 2, mLabel.getGlobalBounds().height / 2);
    mLabel.setFillColor(mTextColor);

    //set some defauts
    mSize = sf::Vector2f(mLabel.getGlobalBounds().width * 1.5f, mLabel.getGlobalBounds().height * 1.5f);

    mButton = sf::RectangleShape(mSize);
    mButton.setFillColor(mBackgroundNormal);
    mButton.setOrigin(mButton.getGlobalBounds().width / 2, mButton.getGlobalBounds().height / 2);
    mButton.setPosition(mPosition);

    mLabel.setPosition(sf::Vector2f(mButton.getPosition().x, mButton.getPosition().y - mLabel.getGlobalBounds().height / 2));
}

UI::Button::~Button()
{
    
}

void UI::Button::input(sf::Event& e, const sf::Vector2i& position)
{
    //perform updates for settings from user
    mSize = sf::Vector2f(mLabel.getGlobalBounds().width * 1.5f, mLabel.getGlobalBounds().height * 1.75f);

    mButton = sf::RectangleShape(mSize);
    mButton.setFillColor(mBackgroundNormal);
    mButton.setOrigin(mButton.getGlobalBounds().width / 2, mButton.getGlobalBounds().height / 2);
    mButton.setPosition(mPosition);

    mLabel.setOrigin(mLabel.getGlobalBounds().width / 2, mLabel.getGlobalBounds().height / 2);
    mLabel.setPosition(sf::Vector2f(mButton.getPosition().x, mButton.getPosition().y - mLabel.getGlobalBounds().height / 2));
    mLabel.setFillColor(mTextColor);

    //perform updates for user mouse interactions
    bool mouseInButton = position.x >= mButton.getPosition().x - mButton.getGlobalBounds().width / 2
        && position.x <= mButton.getPosition().x + mButton.getGlobalBounds().width / 2
        && position.y >= mButton.getPosition().y - mButton.getGlobalBounds().height / 2
        && position.y <= mButton.getPosition().y + mButton.getGlobalBounds().height / 2;

    mState = UI::State::Normal;

    switch (e.type)
    {
        case sf::Event::MouseMoved:
            if (mouseInButton)  { mState = UI::State::Hover; }

        case sf::Event::MouseButtonPressed:
            if (e.mouseButton.button == sf::Mouse::Left)
            {
                if (mouseInButton) 
                { 
                    mState = UI::State::Clicked; 
                    mClickCallback();
                }
            }
            break;

        case sf::Event::MouseButtonReleased:
            if (e.mouseButton.button == sf::Mouse::Left)
            {
                if (mouseInButton)
                { 
                    mState = UI::State::Hover; 
                }
            }
            break;
    }

    switch (mState)
    {
        case UI::State::Normal:  mButton.setFillColor(mBackgroundNormal);  break;
        case UI::State::Hover:   mButton.setFillColor(mBackgroundHover);   break;
        case UI::State::Clicked: mButton.setFillColor(mBackgroundClicked); break;
    }
}

void UI::Button::setClickCallback(std::function<void(void)> clickCallback)
{
    mClickCallback = clickCallback;
}

void UI::Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mButton, states);
    target.draw(mLabel, states);
}