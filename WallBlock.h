#pragma once
#include <SFML\System\Vector2.hpp>
class WallBlock
{
public:
	WallBlock(const sf::Vector2f& position, float width, float height);
	~WallBlock();

	bool isBroken() const;
	void setBroken(bool broken);

	float getWidth() const;
	void setWidth(float width);

	float getHeight() const;
	void setHeight(float height);

	const sf::Vector2f& getPosition() const;

private:
	sf::Vector2f mPosition;
	bool mIsBroken;
	float mWidth;
	float mHeight;
};

