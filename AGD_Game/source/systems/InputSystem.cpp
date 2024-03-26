#include "../../include/systems/Systems.h"

void InputSystem::update(Game* game, Entity* entity, float dt) {
    // Reset velocity
    std::shared_ptr<VelocityComponent> velocityComponent = entity->getVelocityComp();
    if (velocityComponent != nullptr) {
        velocityComponent->setVelocity(0.f, 0.f); 
    }
    else {
		throw std::runtime_error("VelocityComponent not found for entity");
	}

    // Check input and execute commands
    std::shared_ptr<InputComponent> inputComponent = entity->getInputComponent();
    if (inputComponent != nullptr) {
        inputComponent->inputExecute(*game);
    }
    else {
        throw std::runtime_error("InputComponent not found for entity");
    }
}