#pragma once
#include "Entity.h"
#include "../components/PositionComponent.h"
#include "../components/ColliderComponent.h"


class Potion : public Entity
{
public:
	Potion() : Entity(EntityType::POTION) {}
	~Potion() {}

	void init(const std::string& textureFile, float scale) override
	{
		// Call the init() function in Entity to initalize this object
		Entity::init(textureFile, scale);
	}

	virtual void update(Game* game, float elapsed = 1.0f) override { }

	int getHealth() const { return potionHealth; }

protected:
	const int potionHealth = 10;
};


class Log : public Entity
{
public:
	Log() : Entity(EntityType::LOG) {}
	~Log() {}

	void init(const std::string& textureFile, float scale) override
	{
		// Call the init() function in Entity to initalize this object
		Entity::init(textureFile, scale);
	}

	virtual void update(Game* game, float elapsed = 1.0f) override {}

	int getWood() const { return woodAdded; }

protected:
	const int woodAdded = 15;
};