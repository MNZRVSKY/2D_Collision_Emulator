#pragma once
#include <vector>
#include <list>

class Bullet;
class WallBlock;

class WallManager
{
public:
	WallManager(int count, float blockWidth, float blockHeight);
	virtual ~WallManager();

	const std::vector<WallBlock>& getWallBlocks() const;

	void reset();

	void checkColisions(const std::list<Bullet>& bullets);

private:
	std::vector<WallBlock> mWallBlocks;

};

