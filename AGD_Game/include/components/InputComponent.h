#pragma once

#include <memory>
#include "Components.h"

class Game;

class InputComponent : public Component
{
public:
    virtual ComponentID getID() const override { return ComponentID::INPUT; }
    virtual ~InputComponent() {}
    virtual void inputExecute(Game& game) = 0;
};

class PlayerInputHandler;

class PlayerInputComponent : public InputComponent {
public:
    PlayerInputComponent();
    virtual void inputExecute(Game& game) override;

private:
    std::unique_ptr<PlayerInputHandler> inputHandler;
};
