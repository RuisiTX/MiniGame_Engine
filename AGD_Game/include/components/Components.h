#pragma once
enum class ComponentID
{
	UNDEFINED = -1, // Good to have a default value .
	INPUT = 0,
	POSITION = 1,
	VELOCITY = 2,
	TTL = 3,
	HEALTH = 4,
	COLLIDER = 5,
	// ... Complete with all components you ¡¯ve implemented . If your components
	// use inheritance , pick the base class as the type (i.e. Logic , Graphics ).

};


class Component
{
public:
	virtual ComponentID getID() const = 0;
};
