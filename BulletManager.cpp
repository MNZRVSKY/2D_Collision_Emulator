#include "BulletManager.h"
#include "Bullet.h"
#include "WallBlock.h"
#include "Constants.h"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include <iterator>

BulletManager::BulletManager()
{
}

BulletManager::~BulletManager()
{
	mBullets.clear();
}

void BulletManager::test()
{
}

void BulletManager::update(float dt)
{
	std::lock_guard<std::mutex> lock(mMutex);
	for (auto it = mBullets.begin(); it != mBullets.end(); ++it)
	{
		it->update(dt);
	}
	
	for (auto it = mBullets.begin(); it != mBullets.end();) 
	{
		if (!it->isAlive() || it->isOutOfRect( sf::FloatRect(0.f, 0.f, Constants::WINDOW_GAME_WIDTH, Constants::WINDOW_HEIGHT) ) )
		{
			it = mBullets.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void BulletManager::fire(float x, float y, float directionAngel, float speed, float time, float lifeTime)
{
	std::lock_guard<std::mutex> lock(mMutex);

	mBullets.push_back(Bullet(sf::Vector2f(x, y), directionAngel, speed, time, lifeTime));
}

const std::list<Bullet>& BulletManager::getBullets() const
{
	return mBullets;
}

void BulletManager::checkColisions(const std::vector<WallBlock>& blocks)
{
	for (auto bulletIter = mBullets.begin(); bulletIter != mBullets.end(); ++bulletIter)
	{
		for (auto blockIter = blocks.begin(); blockIter != blocks.end(); ++blockIter)
		{
			if ( blockIter->isBroken() )
				continue;

			sf::FloatRect bullet( bulletIter->getPosition(), sf::Vector2f(Constants::BULLET_RADIUS * 2, Constants::BULLET_RADIUS * 2) );
			sf::FloatRect block( blockIter->getPosition(), sf::Vector2f( Constants::BLOCK_WIDTH, Constants::BLOCK_HEIGHT) );

			float topBulletPosition = bulletIter->getPosition().y + Constants::BULLET_RADIUS / 2;
			float bottomBlockPosition = blockIter->getPosition().y + Constants::BLOCK_HEIGHT;

			if ( bullet.intersects(block) && topBulletPosition < bottomBlockPosition )
			{
				bulletIter->collisionSide();
				break;
			}

			if ( bullet.intersects(block) )
			{
				bulletIter->collisionTop();
				break;
			}
		}
	}
}
