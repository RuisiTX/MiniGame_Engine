#pragma once
#include "../utils/Bitmask.h"
#include "../entities/Entity.h"
#include "../core/Game.h"

class System {
protected:
	Bitmask componentMask;

public:
	virtual ~System() {}

	virtual void update(Game* game, Entity* entity, float deltaTime) = 0;

	bool validate(Entity* entity) {
		return entity->hasComponent(componentMask);
	}
};

class TTLSystem : public System {
public:
	TTLSystem() {
		componentMask.turnOnBit(static_cast<int>(ComponentID::TTL));
	}
	void update(Game* game, Entity* entity, float deltaTime) override;
};

class InputSystem : public System {
public:
	InputSystem() {
		componentMask.turnOnBit(static_cast<int>(ComponentID::INPUT));
		componentMask.turnOnBit(static_cast<int>(ComponentID::VELOCITY));
	}
	void update(Game* game, Entity* entity, float deltaTime) override;
};

class MovementSystem : public System {
public:
	MovementSystem() {
		componentMask.turnOnBit(static_cast<int>(ComponentID::VELOCITY));
		componentMask.turnOnBit(static_cast<int>(ComponentID::POSITION));
	}
	void update(Game* game, Entity* entity, float deltaTime) override;
};

class ColliderSystem : public System {
public:
	ColliderSystem() {
		componentMask.turnOnBit(static_cast<int>(ComponentID::COLLIDER));
		componentMask.turnOnBit(static_cast<int>(ComponentID::POSITION));
	}
	void update(Game* game, Entity* entity, float deltaTime) override;

};;