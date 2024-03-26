#pragma once

#include "Components.h"
#include <SFML/System/Vector2.hpp>

class PositionComponent : public Component
{
public:
    virtual ComponentID getID() const override { return ComponentID::POSITION; }

    // Constructor to initialize the position to (0, 0)
    PositionComponent() : position(0.f, 0.f) {}

    // Getter for the position
    const Vector2f& getPosition() const { return position; }

    // Setter for the position
    void setPosition(float x, float y) { position.x = x; position.y = y; }

private:
    // Position vector
    Vector2f position;
};
