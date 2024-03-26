#include "../../include/components/InputComponent.h"
#include "../../include/core/Game.h"
#include "../../include/entities/Player.h"

PlayerInputComponent::PlayerInputComponent()
    : inputHandler(std::make_unique<PlayerInputHandler>())
{}

void PlayerInputComponent::inputExecute(Game& game) {
    std::vector<std::shared_ptr<Command>>& commands = inputHandler->handleInput();
    for (auto& cmd : commands) {
        cmd->execute(game);
    }
}
