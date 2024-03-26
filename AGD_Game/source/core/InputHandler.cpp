#include "../../include/core/InputHandler.h"
#include "../../include/core/Command.h"
#include <iostream>

InputHandler::InputHandler() {
	pauseCommand = std::make_shared<PauseCommand>();
}

std::shared_ptr<Command> InputHandler::handleInput() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		return pauseCommand;
	}
	return nullptr;
}

PlayerInputHandler::PlayerInputHandler() {
	moveRightCommand = std::make_shared<MoveRightCommand>();
	moveLeftCommand = std::make_shared<MoveLeftCommand>();
	moveUpCommand = std::make_shared<MoveUpCommand>();
	moveDownCommand = std::make_shared<MoveDownCommand>();

	attackCommand = std::make_shared<AttackCommand>();
	shoutCommand = std::make_shared<ShoutCommand>();
}


std::vector<std::shared_ptr<Command>>& PlayerInputHandler::handleInput() {
	commands.clear();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		commands.push_back(moveRightCommand);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		commands.push_back(moveLeftCommand);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		commands.push_back(moveUpCommand);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		commands.push_back(moveDownCommand);
	}

	// Handle attack input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		commands.push_back(attackCommand);
	}

	// Handle shoot input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
		commands.push_back(shoutCommand);
	}
	return commands;
}