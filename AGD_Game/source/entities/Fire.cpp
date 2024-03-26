#include "../../include/entities/Fire.h"
#include <iostream>
#include "../../include/components/TTLComponent.h"


Fire::Fire() : Entity(EntityType::FIRE)
{
	// create shared pointers to components
	ttl = std::make_shared<TTLComponent>(startTimeToLive);
	velocity = std::make_shared<VelocityComponent>();

	// add components to component set
	addComponent(ttl);
	addComponent(velocity);

}


Fire::~Fire()
{}

void Fire::update(Game* game, float elapsed)
{
	// First, update the position of the Fire object by calling the parent Entity::update() function.
	Entity::update(game, elapsed);

	// Time to live (Fire::ttl member variable) needs to be reduced by 1 at every frame. If this gets
	// to 0, the entity must be deleted (here, just setting the deleted flag to true).
}

