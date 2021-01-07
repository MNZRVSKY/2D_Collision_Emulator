#pragma once
class GameObject
{
	GameObject();
	virtual ~GameObject();

	virtual void update(float dt) = 0;
};

