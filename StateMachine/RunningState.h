#pragma once
#include <string>
#include "CharacterState.h"

// 3.4. ‘–só‘Ô (MovingState‚Ìq)
class RunningState : public CharacterState
{
public:
    RunningState(Character* character) : CharacterState(character, "Running") {}

    void Enter() override;

    void Execute() override;

    void HandleInput(const std::string& input) override;
};

