#include "../../include/components/GraphicsComponent.h"
#include "../../include/entities/Entity.h"

void SpriteGraphicsComponent::init(const std::string& file)
{
	texture.loadFromFile(file);
	sprite.setTexture(texture);
	sprite.setScale(scale, scale);
}

void SpriteGraphicsComponent::update(const Entity& entity, float elapsed)
{
	sprite.setPosition(entity.getPosition().x, entity.getPosition().y);
}

void SpriteGraphicsComponent::draw(Window* window)
{
	window->draw(sprite);
}

const sf::Vector2f& SpriteGraphicsComponent::getSpriteScale() const
{
	return sprite.getScale();
}

const sf::Vector2i& SpriteGraphicsComponent::getTextureSize() const
{
	return { static_cast<int>(texture.getSize().x), static_cast<int>(texture.getSize().y) };

}

void SpriteGraphicsComponent::setAnimation(const std::string& animationName, bool play, bool loop)
{
	throw std::logic_error("Animation functions should not be called on a SpriteGraphicsComponent");
}

bool SpriteGraphicsComponent::isCurrentAnimation(const std::string& animationName) const
{
	throw std::logic_error("Animation functions should not be called on a SpriteGraphicsComponent");
}

const Direction SpriteGraphicsComponent::getSpriteDirection()
{
	throw std::logic_error("Animation functions should not be called on a SpriteGraphicsComponent");
}

void SpriteGraphicsComponent::setSpriteDirection(Direction d)
{
	throw std::logic_error("Animation functions should not be called on a SpriteGraphicsComponent");
}

bool SpriteGraphicsComponent::isAnimationPlaying() const
{
	throw std::logic_error("Animation functions should not be called on a SpriteGraphicsComponent");
}

bool SpriteGraphicsComponent::isAnimationInAction() const
{
	throw std::logic_error("Animation functions should not be called on a SpriteGraphicsComponent");
}

SpriteSheet* SpriteGraphicsComponent::getSpriteSheet()
{
	throw std::logic_error("Animation functions should not be called on a SpriteGraphicsComponent");
}

void SpriteSheetGraphicsComponent::init(const std::string& file)
{
	spriteSheet.loadSheet(file);
	spriteSheet.setAnimation("Idle", true, true);
}

void SpriteSheetGraphicsComponent::update(const Entity& entity, float elapsed)
{
	spriteSheet.setSpritePosition(sf::Vector2f(entity.getPosition().x, entity.getPosition().y));
	spriteSheet.update(elapsed);
}

void SpriteSheetGraphicsComponent::draw(Window* window)
{
	sf::Sprite* sp = &spriteSheet.getSprite();
	const sf::Vector2f pos = sp->getPosition();
	window->draw(spriteSheet.getSprite());
}

const sf::Vector2f& SpriteSheetGraphicsComponent::getSpriteScale() const
{
	return spriteSheet.getSpriteScale();
}

const sf::Vector2i& SpriteSheetGraphicsComponent::getTextureSize() const
{
	return spriteSheet.getSpriteSize();
}

void SpriteSheetGraphicsComponent::setAnimation(const std::string& animationName, bool play, bool loop)
{
	spriteSheet.setAnimation(animationName, play, loop);
}

bool SpriteSheetGraphicsComponent::isCurrentAnimation(const std::string& animationName) const
{
	return false;
}

const Direction SpriteSheetGraphicsComponent::getSpriteDirection()
{
	return Direction();
}

void SpriteSheetGraphicsComponent::setSpriteDirection(Direction d)
{
	spriteSheet.setSpriteDirection(d);
}

bool SpriteSheetGraphicsComponent::isAnimationPlaying() const
{
	return false;
}

bool SpriteSheetGraphicsComponent::isAnimationInAction() const
{
	return false;
}

SpriteSheet* SpriteSheetGraphicsComponent::getSpriteSheet()
{
	return &spriteSheet;
}
