#include "../../include/systems/Systems.h"

void MovementSystem::update(Game* game, Entity* entity, float dt)
{
	std::shared_ptr<VelocityComponent> velocityComp  = entity->getVelocityComp();
	if (velocityComp) {
		// Update the entity's position based on its velocity component.
		velocityComp->movePosition(*entity, dt);
	}
	else {
		throw std::runtime_error("VelocityComponent not found for entity");
	}
}