#pragma once
#include <algorithm>
#include "Components.h"

class HealthComponent : public Component
{
protected:
    int currentHealth;
    int maxHealth;
public:
    virtual ComponentID getID() const override { return ComponentID::HEALTH; }
    HealthComponent(int startingHealth, int maxHealth)
        : currentHealth(startingHealth), maxHealth(maxHealth) {}

    int getHealth() const {
        return currentHealth;
    }

    void changeHealth(int delta) {
        currentHealth += delta;
        currentHealth = std::max(0, std::min(currentHealth, maxHealth));
    }
};
