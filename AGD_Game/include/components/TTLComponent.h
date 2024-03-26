#pragma once
#include "Components.h"

class TTLComponent : public Component 
{
private:
    int ttl;

public:
    virtual ComponentID getID() const override { return ComponentID::TTL; }
    TTLComponent(int startTimeToLive) : ttl(startTimeToLive) {}
    void decreaseTTL() {
        if (ttl > 0) {
            ttl--;
        }
    }
    int getTTL() const { return ttl; }
};
