#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>

namespace UI
{
	class Slider : public sf::Drawable
	{
	public:
		Slider(sf::Vector2f position, std::string label);

		void create(int min, int max);
		float getValue() const;
		void input(sf::Event& e, const sf::Vector2i& position);

	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		sf::Text creatLabel(int x, int y, std::string text, int fontSize) const;

	private:
		sf::RectangleShape mHolder;
		sf::RectangleShape mAxis;
		sf::Font mFont;

		int mMinValue;
		int mMaxValue;
		int mXCord;
		int mYCord;
		int mAxisWidth;
		int mAxisHeight;
		int mHolderWidth;
		int mHolderHeight;
		float mHolderValue;
		std::string mLabel;

		const int PADDING = 4;
	};
}
