#include "WallManager.h"
#include "WallBlock.h"
#include "Bullet.h"
#include "Constants.h"

#include <SFML/Graphics/Rect.hpp>

WallManager::WallManager(int count, float blockWidth, float blockHeight)
{
	for (int i = 0; i < count; ++i)
	{
		mWallBlocks.push_back(WallBlock(sf::Vector2f(blockWidth * i, 0.f), blockWidth, blockHeight));
	}
}

WallManager::~WallManager()
{
}

const std::vector<WallBlock>& WallManager::getWallBlocks() const
{
	return mWallBlocks;
}

void WallManager::reset()
{
	for (auto it = mWallBlocks.begin(); it != mWallBlocks.end(); ++it)
	{
		it->setBroken(false);
	}
}

void WallManager::checkColisions(const std::list<Bullet>& bullets)
{
	for (auto bulletIter = bullets.begin(); bulletIter != bullets.end(); ++bulletIter)
	{
		for (auto blockIter = mWallBlocks.begin(); blockIter != mWallBlocks.end(); ++blockIter)
		{
			if (blockIter->isBroken())
				continue;

			sf::FloatRect bullet(bulletIter->getPosition(), sf::Vector2f(Constants::BULLET_RADIUS * 2, Constants::BULLET_RADIUS * 2));
			sf::FloatRect block(blockIter->getPosition(), sf::Vector2f(Constants::BLOCK_WIDTH, Constants::BLOCK_HEIGHT));

			if ( bullet.intersects(block) )
			{
				blockIter->setBroken(true);
			}
		}
	}
}
