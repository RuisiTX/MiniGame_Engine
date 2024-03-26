#include "../../include/systems/Systems.h"
#include "../../include/components/ColliderComponent.h"

void ColliderSystem::update(Game* game, Entity* entity, float dt) 
{
	std::shared_ptr<BoxColliderComponent> colliderComp = entity->getColliderComp();
	if (colliderComp != nullptr) {
		// Update the collider component with the entity's position and size.
		colliderComp -> update(*entity);
		colliderComp -> setBoundingBox(entity->getPosition(), entity->getPosition() + entity->getColliderComp()->getSize());
	}
	else {
		throw std::runtime_error("BoxColliderComponent not found for entity");
	}
}