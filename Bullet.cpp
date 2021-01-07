#include "Bullet.h"
#include "Constants.h"

#include <cmath>   


Bullet::Bullet(const sf::Vector2f& position, float directionAngel,
			   float speed, float time, float life_time)
	: mPosition(position), 
	  mDirectionAngel(Constants::MAX_ENGEL - directionAngel),
	  mSpeed(speed),
	  mTime(time),
	  mLifeTime(life_time)
{
}

Bullet::~Bullet()
{
}

void Bullet::actionUpColision()
{
}

void Bullet::update(float dt)
{
	mLifeTime -= dt;
	mTime -= dt;

	if (mTime > 0.f)
	{
		return;
	}

	mPosition.x = (mSpeed * 10 * dt) * cos(mDirectionAngel * Constants::PI / 180) + mPosition.x;
	mPosition.y = (mSpeed * 10 * dt) * sin(mDirectionAngel * Constants::PI / 180) + mPosition.y;
}

bool Bullet::isAlive() const
{
	return mLifeTime > 0.f;
}

bool Bullet::isOutOfRect(const sf::FloatRect& rect) const
{
	if (mPosition.x < rect.left - Constants::BULLET_RADIUS * 2)
		return true;

	if (mPosition.y < rect.top - Constants::BULLET_RADIUS * 2)
		return true;

	if (mPosition.x > rect.width + Constants::BULLET_RADIUS)
		return true;

	if (mPosition.y > rect.height + Constants::BULLET_RADIUS)
		return true;

	return false;
}

const sf::Vector2f& Bullet::getPosition() const
{
	return mPosition;
}

void Bullet::collisionTop()
{
	if (mDirectionAngel < 180)
	{
		return;
	}

	float angel = 180.f - mDirectionAngel;
	mDirectionAngel = angel + 180;
}

void Bullet::collisionSide()
{
	if (mDirectionAngel < 180)
	{
		mDirectionAngel = 180.f + mDirectionAngel;
	}
	else
	{
		mDirectionAngel = 180.f - mDirectionAngel;
	}
}
