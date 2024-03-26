#include "../../include/core/Command.h"

void MoveRightCommand::execute(Game& game) {
    auto velocityComponent = game.getPlayer()->getVelocityComp();
    velocityComponent->setVelocity(1.0f, velocityComponent->getVelocity().y);
}

void MoveLeftCommand::execute(Game& game) {
    auto velocityComponent = game.getPlayer()->getVelocityComp();
    velocityComponent->setVelocity(-1.0f, velocityComponent->getVelocity().y);
}

void MoveUpCommand::execute(Game& game) {
    auto velocityComponent = game.getPlayer()->getVelocityComp();
    velocityComponent->setVelocity(velocityComponent->getVelocity().x, -1.0f);
}

void MoveDownCommand::execute(Game& game) {
    auto velocityComponent = game.getPlayer()->getVelocityComp();
    velocityComponent->setVelocity(velocityComponent->getVelocity().x, 1.0f);
}

void AttackCommand::execute(Game& game) {
    game.getPlayer()->setAttacking(true);
}

void ShoutCommand::execute(Game& game) {
    game.getPlayer()->setShouting(true);
}