#pragma once

#include <SFML/Graphics.hpp>
#include "../entities/Entity.h" 
#include "Components.h"

class VelocityComponent : public Component
{
public:
    virtual ComponentID getID() const override { return ComponentID::VELOCITY; }

    VelocityComponent(float speed = 1.f);
    const Vector2f& getVelocity() const { return velocity; }
    void setVelocity(float x, float y) { velocity.x = x; velocity.y = y; }


    void movePosition(Entity& entity, float elapsed);

private:
    Vector2f velocity;
    float speed;
};

