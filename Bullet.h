#pragma once
#include "Point.h"
#include <SFML\System\Vector2.hpp>
#include <SFML\Graphics\Rect.hpp>

class Bullet
{
public:
	Bullet(const sf::Vector2f& position, float directionAngel, float speed, float time, float life_time);
	virtual ~Bullet();

	void actionUpColision();

	void update(float dt);

	bool isAlive() const;
	bool isOutOfRect(const sf::FloatRect & rect) const;

	const sf::Vector2f& getPosition() const;

	void collisionTop();
	void collisionSide();

private:
	sf::Vector2f mPosition;
	float mDirectionAngel;
	float mSpeed;
	float mTime;
	float mLifeTime;
};

