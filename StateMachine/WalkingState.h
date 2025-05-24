#pragma once
#include <string>
#include "CharacterState.h"

// 3.3. •àsó‘Ô (MovingState‚Ìq)
class WalkingState : public CharacterState
{
public:
    WalkingState(Character* character) : CharacterState(character, "Walking") {}

    void Enter() override;

    void Execute() override;

    void HandleInput(const std::string& input) override;
};

