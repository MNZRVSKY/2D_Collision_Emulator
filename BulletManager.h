#pragma once
#include <list>
#include <vector>
#include <mutex>

class Bullet;
class WallBlock;

class BulletManager
{
public:
	BulletManager();
	~BulletManager();

	void test();

	void update(float dt);

	void fire(float x, float y, float directionAngel, float speed, float time, float lifeTime);

	const std::list<Bullet>& getBullets() const;

	void checkColisions(const std::vector<WallBlock>& blocks);

private:
	std::list<Bullet> mBullets;
	std::mutex mMutex;
};

