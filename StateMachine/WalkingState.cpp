#pragma once
#include <iostream>
#include "WalkingState.h"
#include "MovingState.h"
#include "RunningState.h"


void WalkingState::Enter()
{
    CharacterState::Enter();
    std::cout << "    キャラクターは歩き始めました。" << std::endl;
}

void WalkingState::Execute()
{
    // 歩行時の処理
    // std::cout << "    てくてく..." << std::endl; // 頻繁なのでコメントアウト
}

void WalkingState::HandleInput(const std::string& input)
{
    // 親状態（MovingState）にキャストしてサブ状態を変更
    if (input == "run") {
        std::cout << "    入力 'run' 受信 -> RunningStateへ遷移" << std::endl;
        if (auto parentMovingState = dynamic_cast<MovingState*>(GetParentState())) {
            parentMovingState->ChangeSubState(std::make_shared<RunningState>(m_character));
        }
    }
    else {
        CharacterState::HandleInput(input); // 親に委譲（MovingStateのHandleInputが呼ばれる）
    }
}

