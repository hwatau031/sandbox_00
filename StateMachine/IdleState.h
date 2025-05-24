#pragma once
#include <string>
#include "CharacterState.h"

#// 3.1. ƒAƒCƒhƒ‹ó‘Ô
class IdleState : public CharacterState
{
public:
    IdleState(Character* character) : CharacterState(character, "Idle") {}

    void Enter() override;

    void Execute() override;

    void HandleInput(const std::string& input) override;
};

