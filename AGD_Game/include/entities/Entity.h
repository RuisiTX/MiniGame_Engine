#pragma once
#include "../graphics/Window.h"
#include "../graphics/SpriteSheet.h"
#include "../utils/Rectangle.h"
#include "../components/PositionComponent.h"
#include "../utils/Bitmask.h"
#include "../components/TTLComponent.h"
#include "../components/InputComponent.h"
//#include "../components/VelocityComponent.h"
//#include "../components/ColliderComponent.h"

using EntityID = unsigned int;
enum class EntityType
{
	UNDEFINED = -1,
	PLAYER = 0,
	POTION = 1,
	LOG = 2,
	FIRE = 3
};

//forward declaration
class Game; 
class BoxColliderComponent;
class PositionComponent;
class VelocityComponent;

class Entity
{
public:

	//Constructors and Desctrutors
	Entity();
	Entity(EntityType et);
	~Entity();

	//Init and update functions
	virtual void init(const std::string& textureFile, float scale);
	void initSpriteSheet(const std::string& spriteSheetFile);
	virtual void update(Game* game, float elapsed = 1.0f);
	void draw(Window* window);

	//Getters and Setters
	void setID(EntityID entId) { id = entId; }
	EntityID getID() const { return id; }

	//Replace position and velocity members with a unique pointer to PositionComponent.
	void setPosition(float x, float y);
	const Vector2f& getPosition() const;

	//Rectangle& getBoundingBox() { return boundingBox; };
	const sf::Vector2f& getSpriteScale() const;
	sf::Vector2i getTextureSize() const;
	EntityType getEntityType() const { return type; }
	const SpriteSheet* getSpriteSheet() const { return &spriteSheet; }
	//float getSpeed() const { return speed; }
	bool isSpriteSheetEntity() const { return isSpriteSheet; }

	
	// Add two helper functions. One that returns the value of the deleted flag, another one that 
	// "deletes" the entity by setting this flag to true. (Q: one of this functions should be "const", which one?).
	bool isDeleted() const { return deleted; }
	void deleteEntity() { deleted = true; } // This function is not "const" as it modifies the state of the object.

	//Bitmask for entities
	void addComponent(std::shared_ptr<Component> component)
	{
		componentSet.turnOnBit(static_cast<unsigned int>(component->getID()));
		components.push_back(component);
	}
	Bitmask getComponentSet() const { return componentSet; }  // new getter function
	bool hasComponent(Bitmask mask) const { return componentSet.contains(mask); }

	// Component set
	virtual std::shared_ptr<TTLComponent> getTTLComp() const;
	virtual std::shared_ptr<InputComponent> getInputComponent() const;
	virtual std::shared_ptr<VelocityComponent> getVelocityComp() const;
	virtual std::shared_ptr<PositionComponent> getPositionComp() const { return position; };
	virtual std::shared_ptr<BoxColliderComponent> getColliderComp() const { return collider; };

protected:

	EntityType type;
	EntityID id;

	//Replace position and velocity members with a unique pointer to PositionComponent.
	std::shared_ptr<PositionComponent> position;

	//Collision
	std::shared_ptr<BoxColliderComponent> collider;

	//Graphics-related variables.
	bool isSpriteSheet;
	SpriteSheet spriteSheet;
	sf::Texture texture;
	sf::Sprite sprite;
	//std::shared_ptr<GraphicsComponent> gc;

	// Add a bool member variable "deleted" to this class.
	bool deleted;

	//Bitmask for entities
	Bitmask componentSet; // bitmask representing the components that this entity owns
	std::vector<std::shared_ptr<Component>> components;
};