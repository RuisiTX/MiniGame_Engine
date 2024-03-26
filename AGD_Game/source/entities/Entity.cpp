#include "../../include/entities/Entity.h"
#include "../../include/graphics/Window.h"
#include "../../include/components/PositionComponent.h"
#include "../../include/components/ColliderComponent.h"
#include <iostream>


Entity::Entity() :
	isSpriteSheet(false),
	id(0),
	type(EntityType::UNDEFINED),
	// Add the initialization the deleted flag to false
	deleted(false)
{
	position = std::make_shared<PositionComponent>();
	addComponent(position);
	collider = std::make_shared<BoxColliderComponent>();
	addComponent(collider);
}

Entity::Entity(EntityType et) : 
	isSpriteSheet(false),
	id(0),
	type (et),
	// Add the initialization the deleted flag to false
	deleted(false)
{
	position = std::make_shared<PositionComponent>();
	addComponent(position);
	collider = std::make_shared<BoxColliderComponent>();
	addComponent(collider);
}

Entity::~Entity()
{
}

void Entity::update(Game* game, float elapsed)
{
	// If the entity has a spritesheet, set its position to the position of this entity, and call update
	// on the spritesheet, passing the delta time of this update call. Otherwise, set the position of the
	// sprite variable to the position vector.
	if (isSpriteSheet) {
		spriteSheet.setSpritePosition(sf::Vector2f(position->getPosition().x, position->getPosition().y));
		spriteSheet.update(elapsed);
	}
	else {
		sprite.setPosition(position->getPosition().x, position->getPosition().y);
	}

}



void Entity::draw(Window* window)
{
	if (isSpriteSheet)
	{
		sf::Sprite* sp = &spriteSheet.getSprite();
		const sf::Vector2f pos = sp->getPosition();
		window->draw(spriteSheet.getSprite());
	}
	else
		window->draw(sprite); 

	// Draw the bounding box by retrieving a drawable rect from the bounding box Rectangle.
	
	collider->draw(window);
}

void Entity::init(const std::string& textureFile, float scale)
{
	texture.loadFromFile(textureFile);
	sprite.setTexture(texture);
	sprite.setScale(scale, scale);

	collider->init(Vector2f(texture.getSize().x * scale, texture.getSize().y * scale));
}

void Entity::initSpriteSheet(const std::string& spriteSheetFile)
{
	spriteSheet.loadSheet(spriteSheetFile);
	isSpriteSheet = true;
	spriteSheet.setAnimation("Idle", true, true);

	collider->init(Vector2f(spriteSheet.getSpriteSize().x * spriteSheet.getSpriteScale().x, spriteSheet.getSpriteSize().y * spriteSheet.getSpriteScale().y));
}

void Entity::setPosition(float x, float y)
{
	position->setPosition(x, y);
	if(isSpriteSheet)
		spriteSheet.getSprite().setPosition(x, y);
	else
		sprite.setPosition(x, y);
}	

const::Vector2f& Entity::getPosition() const
{
	return position->getPosition();
}

const sf::Vector2f& Entity::getSpriteScale() const
{
	if (isSpriteSheet)
	{
		return spriteSheet.getSpriteScale();
	}

	return sprite.getScale();
}

sf::Vector2i Entity::getTextureSize() const
{
	if (isSpriteSheet)
	{
		return spriteSheet.getSpriteSize();
	}

	return { static_cast<int>(texture.getSize().x), static_cast<int>(texture.getSize().y) };
}

std::shared_ptr<TTLComponent> Entity::getTTLComp() const
{
	return nullptr;
}

std::shared_ptr<InputComponent> Entity::getInputComponent() const
{
	return nullptr;
}

std::shared_ptr<VelocityComponent> Entity::getVelocityComp() const
{
	return nullptr;
}