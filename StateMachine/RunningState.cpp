#pragma once
#include <iostream>
#include "RunningState.h"
#include "MovingState.h"
#include "WalkingState.h"


void RunningState::Enter()
{
	CharacterState::Enter();
	std::cout << "    キャラクターは走り始めました！" << std::endl;
}

void RunningState::Execute()
{
	// 走行時の処理
	// std::cout << "    ダッシュ！！" << std::endl; // 頻繁なのでコメントアウト
}

void RunningState::HandleInput(const std::string& input)
{
	// 親状態（MovingState）にキャストしてサブ状態を変更
	if (input == "walk") {
		std::cout << "    入力 'walk' 受信 -> WalkingStateへ遷移" << std::endl;
		if (auto parentMovingState = dynamic_cast<MovingState*>(GetParentState())) {
			parentMovingState->ChangeSubState(std::make_shared<WalkingState>(m_character));
		}
	}
	else {
		CharacterState::HandleInput(input); // 親に委譲（MovingStateのHandleInputが呼ばれる）
	}
}

