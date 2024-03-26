#include "../../include/core/Game.h"
#include "../../include/core/InputHandler.h"
#include "../../include/core/Command.h"
#include "../../include/entities/Fire.h"
#include "../../include/entities/StaticEntities.h"
#include "../../include/entities/Entity.h"
#include <iostream>

// III.F Add the initialization (to 0) of the entity counter to the initalizers list of this constructor
Game::Game() : paused(false), entityCount(0)
{
	// V.B: Create the unique pointer to the Input Handler object.
	inputHandler = std::make_unique<InputHandler>();

	// initialize TTLSystem and add it to systems vector
	std::shared_ptr<System> ttlSystem = std::make_shared<TTLSystem>();
	systems.push_back(ttlSystem);
	// initialize InputSystem
	std::shared_ptr<System> inputSystem = std::make_shared<InputSystem>();
	systems.push_back(inputSystem);
	// initialize MovementSystem
	std::shared_ptr<System> movementSystem = std::make_shared<MovementSystem>();
	systems.push_back(movementSystem);
	// initialize ColliderSystem
	std::shared_ptr<System> colliderSystem = std::make_shared<ColliderSystem>();
	systems.push_back(colliderSystem);
}

Game::~Game()
{
}

template <typename T>
std::shared_ptr<T> Game::buildEntityAt(const std::string& filename, int col, int row)
{
	auto ent = std::make_shared<T>();
	float x = col * spriteWH * tileScale;
	float y = row * spriteWH * tileScale;
	float cntrFactor = (tileScale - itemScale) * spriteWH * 0.5f;

	ent->setPosition(x + cntrFactor, y + cntrFactor);
	ent->init(filename, itemScale);
	
	return ent;
}

void Game::buildBoard(size_t width, size_t height)
{
	// II.B Instantiate the unique pointer of type "Board". 
	//     Use the constructor of Board that receives the width and the height for the game grid.
	board = std::make_unique<Board>(width, height);
}

void Game::initWindow(size_t width, size_t height)
{
	int wdt = static_cast<int>(width * spriteWH * tileScale);
	int hgt = static_cast<int>(height * spriteWH * tileScale);
	window.setSize(sf::Vector2u(wdt, hgt));
	window.redraw();
}

void Game::init(std::vector<std::string> lines)
{
	// Make sure that the vector of lines is not emtpy. h is the number of lines (height of the level)
	size_t h = lines.size() - 1;
	if (h < 0)
		throw std::exception("No data in level file");
	size_t w = -1;

	// Load the font for the window and set its title
	window.loadFont("font/AmaticSC-Regular.ttf");
	window.setTitle("Mini-Game");
	
	auto it = lines.cbegin();
	int row = 0;
	while (it != lines.cend())
	{
		int col = 0;

		// First iteration: we determine the width of the level (w) by the number of symbols in the first line.
		if(w == -1)
		{
			//The size of the window must be equal to the number of tiles it has, factoring their dimensions.
			w = it->size();
			buildBoard(w, h);
			initWindow(w, h);		
		}
		
		std::string::const_iterator is = it->cbegin();
		while (is != it->cend())
		{
			switch (*is)
			{
			case '.':
			{
				// II.C (1/5) Use the function addTile from Board to add a CORRIDOR tile to this position.
				//      The parameters are the column (for x) and row (for y) where the tile is to be placed, the scale 
				//      of the tile (you can use the variable "tileScale") and the tile type. TileTypes are 
				//      defined in the enumerator TileType in Tile.h. You DON'T need to pass a filename parameter for the texture.
				board->addTile(col, row, tileScale, TileType::CORRIDOR);

				break;
			}
			case 'w':
			{
				// II.C (2/5) Use the function addTile from Board to add a WALL tile to this position.
				board->addTile(col, row, tileScale, TileType::WALL);

				break;
			}
			case 'x':
			{
				/// III.A Call the function "buildEntityAt" to create a Log pointer. The parameters are the filename to 
				///       the file with the sprite ("img/log.png"), the column and the row where the log should be place.
				///		  Then, uncomment the call to the funcion "addEntity" passing the pointer to the new entity as parameter.

				auto ent = buildEntityAt<Log>(("img/log.png"), col, row);
				addEntity(ent);			/// uncomment this (you may have to change "ent" for the name of the pointer you've just created above).
	
				//By default, entities stand on corridors
				// II.C (3/5) Use the function addTile from Board to add a CORRIDOR tile to this position.

				board->addTile(col, row, tileScale, TileType::CORRIDOR);

				break;
			}
			case 'p':
			{

				/// III.B Call the function "buildEntityAt" to create a Potion pointer. The parameters are the filename to 
				///       the file with the sprite ("img/potion.png"), the column and the row where the potion should be place.
				///		  Then, uncomment the call to the funcion "addEntity" passing the pointer to the new entity as parameter.
				
				auto ent = buildEntityAt<Potion>("img/potion.png", col, row);
				addEntity(ent);			/// uncomment this
	
				//By default, entities stand on corridors
				// II.C (4/5) Use the function addTile from Board to add a CORRIDOR tile to this position.
				
				board->addTile(col, row, tileScale, TileType::CORRIDOR);

				break;
			}
			case '*':
				{

				// IV.B (1/4): Create the player shared pointer.
				auto player = std::make_shared<Player>();

				// IV.B (2/4): Call the function that initializes the Sprite Sheet with a single parameter, a const std::string& filename.
				//			   This string should be "img/DwarfSpriteSheet_data.txt"
				player->initSpriteSheet("img/DwarfSpriteSheet_data.txt");

				// IV.B (3/4): Call the function that positions the sprite of the player in the board (Player::positionSprite). 
				//			   Parameters are the row and column where this object goes in the board, the sprite width and height (const int Game::spriteWH) 
				//			   and the scale for the tiles (const float Game::tileScale)
				player->positionSprite(row, col, Game::spriteWH, Game::tileScale);

				// IV.B (4/4): Call our function to add an entity to a game passing the player that has just been created.
				addEntity(player);
				this->player = player;

				//By default, entities stand on corridors:
				// II.C (5/5) Use the function addTile from Board to add a CORRIDOR tile to this position.
				
				board->addTile(col, row, Game::tileScale, TileType::CORRIDOR);

				break;
				}
			}

			col++; is++;
		}
		row++; it++;
	}
}

void Game::addEntity(std::shared_ptr<Entity> newEntity)
{
	
	// Increase the entity counter
	++entityCount;
	newEntity->setID(entityCount);

	// Add the entity to the vector
	entities.push_back(newEntity);

}

void Game::handleInput()
{
	// Call the fucntion that handles the input for the game and retrieve the command returned in a variable.
	// Then, call the "execute" method of the returned object to run this command.
	std::shared_ptr<Command> command = inputHandler->handleInput();
	if (command != nullptr) {
		command->execute(*this);
	}

}


void Game::update(float elapsed)
{
	// Call Game::bigArray() with the elapsed time
	// If this was the  end of our work, we would substitute this 
	// loop (iterates and updates all entities in the game) for our call to Game::bigArray().
	bigArray(elapsed);

	if (!isPaused()) {
		auto it = entities.begin();
		while (it != entities.end())
		{
			// Update each entity
			(*it)->update(this, elapsed);
			++it;
		}

		// Check for collisions between the player and other entities
		auto playerBB = player->getColliderComp()->getBoundingBox();
		auto it2 = entities.begin();
		while (it2 != entities.end())
		{
			// Only check collisions with entities that are not the player
			if ((*it2)->getEntityType() != EntityType::PLAYER) {
				auto entityBB = (*it2)->getColliderComp()->getBoundingBox();
				if (playerBB.intersects(entityBB)) {
					// Handle the collision based on the entity type
					switch ((*it2)->getEntityType()) {
					case EntityType::POTION:
					{
						// Handle collision with a potion entity
						std::cout << "You have collided with a potion that restores ";
						std::shared_ptr<Potion> potion = std::dynamic_pointer_cast<Potion>(*it2);
						std::cout << potion->getHealth() << " health." << std::endl;
						auto healthComp = player->getHealthComp();
						healthComp->changeHealth(potion->getHealth());
						std::cout << "Your health is now " << healthComp->getHealth() << std::endl;
						(*it2)->deleteEntity(); // mark the entity as deleted
						break;
					}
					break;
					case EntityType::LOG:
						if (player->getSpriteSheet()->getCurrentAnim()->isInAction() && player->getSpriteSheet()->getCurrentAnim()->getName() == "Attack"
							&& player->getSpriteSheet()->getCurrentAnim()->getCurrentFrame() == 4) {
							std::cout << "You have collected a log worth ";
							std::shared_ptr<Log> log = std::dynamic_pointer_cast<Log>(*it2);
							std::cout << log->getWood() << " wood." << std::endl;
							player->addWood(log->getWood());
							std::cout << "Your wood count is now " << player->getWood() << std::endl;
							(*it2)->deleteEntity();
						}
						break;
					}
				}
			}
			++it2;
		}

		// remove all entities marked as deleted
		it = entities.begin();
		while (it != entities.end()) {
			if ((*it)->isDeleted()) {
				it = entities.erase(it);
			}
			else {
				++it;
			}
		}

	}
	//Update the window for refreshing the graphics (leave this OUTSIDE the !paused block)
	window.update();
}

void Game::render(float elapsed)
{
	//Empty the screen
	window.beginDraw();

	// Call the draw method of the board object passing a pointer to the window.
	board->draw(&window);

	// Draw all units. Write a loop that iterates over all entities in this class's vector
	// and calls the "draw" method in the entities.
	for (auto& entity : entities) {
		entity->draw(&window);
	}


	//Draw FPS
	window.drawGUI(*this);

	//Close up for this frame.
	window.endDraw();
}


sf::Time Game::getElapsed() const { return gameClock.getElapsedTime(); }


void Game::setFPS(int FPS)
{
	std::string text("FPS: " + std::to_string(FPS));
	window.getFPSText().setString(text);
}

// Return the current ID counter.
EntityID Game::getIDCounter()
{
	return entityCount;
}

std::shared_ptr<Entity> Game::getEntity(unsigned int idx)
{
	// Return the pointer to the entity which is in position "idx" of the vector.
	// You must verify that the index is within the bounds of the vector.
	if (idx < entities.size()) {
		return entities[idx];
	}
	else {
		return nullptr;
	}
}

void Game::bigArray(float elapsed) 
{
    // Iterate through all systems
    for (auto systemIt = systems.begin(); systemIt != systems.end(); systemIt++) {
        auto system = *systemIt;

        // Iterate through all entities
        for (auto entityIt = entities.begin(); entityIt != entities.end(); entityIt++) {
            auto entity = *entityIt;

            // Check if entity is not deleted and if the system is valid for the entity
            if (!entity->isDeleted() && system->validate(entity.get())) {
                system->update(this, entity.get(), elapsed);
            }
        }
    }
}
