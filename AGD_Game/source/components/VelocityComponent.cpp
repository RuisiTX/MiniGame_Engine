#include "../../include/components/VelocityComponent.h"
#include "../../include/components/PositionComponent.h"

VelocityComponent::VelocityComponent(float initialSpeed)
    : speed(initialSpeed), velocity(0.0f, 0.0f)
{
}

void VelocityComponent::movePosition(Entity& entity, float elapsed)
{
    entity.setPosition(entity.getPosition().x + velocity.x * speed * elapsed, entity.getPosition().y + velocity.y * speed * elapsed);

}
