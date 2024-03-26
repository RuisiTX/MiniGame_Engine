#pragma once
#include "Entity.h"
#include "../components/TTLComponent.h"
#include "../components/VelocityComponent.h"

class Fire : public Entity
{
public:
	const int startTimeToLive = 150; //frames

	Fire();
	~Fire();

	virtual void update(Game* game, float elapsed = 1.0f) override;

	// int getTTL() const { return ttl; }

	std::shared_ptr<TTLComponent> getTTLComp() const { return ttl; }
	std::shared_ptr<VelocityComponent> getVelocityComp() const { return velocity; }
	int getTTL() const { return ttl->getTTL(); }

private:
	// int ttl;
	// std::unique_ptr<TTLComponent> ttl;
	std::shared_ptr<TTLComponent> ttl;
	std::shared_ptr<VelocityComponent> velocity;

};

