#include "Slider.h"


UI::Slider::Slider(sf::Vector2f position, std::string label)
	: mXCord(position.x), mYCord(position.y),
	  mAxisHeight(30), mAxisWidth(200),
	  mHolderWidth(10), mHolderHeight(26), mHolderValue(0.f),
	  mMinValue(0.f), mMaxValue(0.f),
	  mLabel(label)
{
	mFont.loadFromFile("Fonts\\Neon.ttf");

	mAxis.setPosition(position.x - (mHolderWidth + PADDING) / 2, position.y);
	mAxis.setOrigin(0, mAxisHeight / 2);
	mAxis.setSize(sf::Vector2f(mAxisWidth + mHolderWidth + PADDING, mAxisHeight));
	mAxis.setFillColor(sf::Color(17, 111, 189));

	mHolder.setPosition(position);
	mHolder.setOrigin(mHolderWidth / 2, mHolderHeight / 2);
	mHolder.setSize(sf::Vector2f(mHolderWidth, mHolderHeight));
	mHolder.setFillColor(sf::Color(219, 57, 57));
}

void UI::Slider::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mAxis, states);
	target.draw(mHolder, states);

	sf::Text label = creatLabel(mAxis.getPosition().x + mAxisWidth / 2, mAxis.getPosition().y + mAxisHeight / 2,
		mLabel + " " + std::to_string((int)mHolderValue), 20);
	target.draw(label, states);
}

sf::Text UI::Slider::creatLabel(int x, int y, std::string text, int fontSize) const
{
	sf::Text label(text, mFont, fontSize);
	label.setFillColor(sf::Color::White);
	label.setPosition(x - label.getGlobalBounds().width / 2, y - mAxisHeight);
	
	return label;
}

void UI::Slider::create(int min, int max)
{
	mHolderValue = min;
	mMinValue = min;
	mMaxValue = max;
}

void UI::Slider::input(sf::Event& e, const sf::Vector2i& position)
{
	if ( !mHolder.getGlobalBounds().contains(position.x, position.y) )
	{
		return;
	}

	if ( !sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) )
	{
		return;
	}

	if (position.x >= mXCord && position.x <= mXCord + mAxisWidth)
	{
		mHolder.setPosition(position.x, mYCord);
		mHolderValue = (mMinValue + ((mHolder.getPosition().x - mXCord) / mAxisWidth * (mMaxValue - mMinValue)));
	}
}

float UI::Slider::getValue() const
{
	return mHolderValue;
}

