#include "../../include/systems/Systems.h"

void TTLSystem::update(Game* game, Entity* entity, float dt) 
{
    {
        // Retrieve the shared pointer of the TTL Component
        std::shared_ptr<TTLComponent> ttlComp = entity->getTTLComp();
        // Verify if the returned pointer is not null
        if (ttlComp == nullptr) {
            // If it is null, throw an exception
            throw std::runtime_error("TTLComponent not found for entity");
        }
        else {
            // Decrease the TTL
            ttlComp->decreaseTTL();

            // Check if the value of the TTL counter is less or equal than 0
            if (ttlComp->getTTL() <= 0) {
                // If it is, delete the entity
                entity->deleteEntity();
            }
        }


        
    }
}
