#include "WallBlock.h"
#include <SFML\System\Vector2.hpp>

WallBlock::WallBlock(const sf::Vector2f& position, float width, float height)
	: mPosition(position),
	  mIsBroken(false),
	  mWidth(width),
	  mHeight(height)
{
}

WallBlock::~WallBlock()
{
}

bool WallBlock::isBroken() const
{
	return mIsBroken;
}

void WallBlock::setBroken(bool broken)
{
	mIsBroken = broken;
}

float WallBlock::getWidth() const
{
	return mWidth;
}

void WallBlock::setWidth(float width)
{
	mWidth = width;
}

float WallBlock::getHeight() const
{
	return mHeight;
}

void WallBlock::setHeight(float height)
{
	mHeight = height;
}

const sf::Vector2f& WallBlock::getPosition() const
{
	return mPosition;
}
