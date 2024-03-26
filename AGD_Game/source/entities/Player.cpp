#include "../../include/entities/Player.h"
#include "../../include/graphics/AnimBase.h"
#include "../../include/entities/Fire.h"
#include "../../include/core/Game.h"
#include "../../include/core/Command.h"
#include "../../include/core/InputHandler.h"
#include "../../include/components/InputComponent.h"
#include <iostream>


Player::Player() : Entity(EntityType::PLAYER), attacking(false), shouting(false), wood(0), shootCooldown(0.f)
{
	// Create the shared pointer to the PlayerInputHandler object
	input = std::make_shared<PlayerInputComponent>();

	// Create the health component and initialize it with startingHealth and maxHealth.
	healthComp = std::make_shared<HealthComponent>(startingHealth, maxHealth);

	// Create the velocity component and initialize it with playerSpeed.
	velocity = std::make_shared<VelocityComponent>(playerSpeed);

	addComponent(input);
	addComponent(healthComp);
	addComponent(velocity);
}


Player::~Player() {}

void Player::update(Game* game, float elapsed)
{
	// Reorder tasks VI and VII
	// Check if the player is attacking or shouting, and set the appropriate animation
	if (attacking) {
		spriteSheet.setAnimation("Attack", true);
		attacking = false;
	}
	else if (shouting) {
		spriteSheet.setAnimation("Shout", true);
		//  Create an Fire entity object (using Player::createFire()) and add it to the game (using Game::addEntity).
		//  Then, remove the shooting cost (Player::shootingCost) from the wood member variable of this class
		//  Finally, wrap the functionality below in an IF statement, so we only spawn fire when:
		if (spriteSheet.getCurrentAnim()->getCurrentFrame() ==  2 && wood >= shootingCost) {
			std::shared_ptr<Fire> fire = createFire();
			game->addEntity(fire);
			wood -= shootingCost;

			// Set the variable shootCooldown to the cooldown time (defined in shootCooldownTime).
			// Add another condition to the shooting IF statement that only allows shooting if shootCooldown <= 0.
			shootCooldown = shootCooldownTime;
		}
		shouting = false;
	}
	// If the player is not attacking or shouting, set the walking or idle animation as before
	else if (velocity->getVelocity().x < 0) {
		spriteSheet.setAnimation("Walk", true, true);
		spriteSheet.setSpriteDirection(Direction::Left);
	}
	else if (velocity->getVelocity().x > 0) {
		spriteSheet.setAnimation("Walk", true, true);
		spriteSheet.setSpriteDirection(Direction::Right);
	}
	else {
		spriteSheet.setAnimation("Idle", true, true);
	}
	Entity::update(game, elapsed);

	// Reduce the shoot cooldown counter by the elapsed time at every frame. 
	// Only do this if shoot cooldown is > 0
	if (shootCooldown > 0) {
		shootCooldown -= elapsed;
	}

}


std::shared_ptr<Fire> Player::createFire() const
{
	auto fireEntity = std::make_shared<Fire>();		

	Vector2f pos{ position->getPosition().x + getTextureSize().x * 0.5f,  position->getPosition().y + getTextureSize().y * 0.5f };

	auto velComp = fireEntity->getVelocityComp();
	fireEntity->init("img/fire.png", 1.0f);
	fireEntity->setPosition(pos.x, pos.y);
	Vector2f vel(fireSpeed, 0.f);
	if (spriteSheet.getSpriteDirection() == Direction::Left) vel.x = vel.x * -1.0f;
	velComp->setVelocity(vel.x, vel.y);


	return fireEntity;
}


void Player::addWood(int w)
{
	wood += w;
	if (wood > maxWood) wood = maxWood;
	if (wood < 0) wood = 0;
}


void Player::positionSprite(int row, int col, int spriteWH, float tileScale)
{
	sf::Vector2f scaleV2f = getSpriteScale();
	sf::Vector2i textureSize = getTextureSize();

	float x = col * spriteWH * tileScale;
	float y = (row)*spriteWH * tileScale;
	float spriteSizeY = scaleV2f.y * textureSize.y;
	float cntrFactorY = ((spriteWH * tileScale) - spriteSizeY);	// to align to lower side of the tile.
	float cntrFactorX = cntrFactorY * 0.5f;						//to center horizontally

	setPosition(x + cntrFactorX, y + cntrFactorY);
	velocity->setVelocity(0.0f, 0.0f);
}
