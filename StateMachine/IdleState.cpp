#pragma once
#include <iostream>
#include "CharacterState.h"
#include "IdleState.h"
#include "MovingState.h"


void IdleState::Enter()
{
	CharacterState::Enter();
	std::cout << "  キャラクターは静かに立っています。" << std::endl;
}

void IdleState::Execute()
{
	// 何もせず待機
}

void IdleState::HandleInput(const std::string& input)
{
	if (input == "move") {
		// アイドル状態からMovingStateへ直接遷移（MovingStateがサブ状態を持つ親なので、まず親に）
		// ここでは簡易的に、CharacterのChangeStateを通じて新しい状態インスタンスを生成
		std::cout << "  入力 'move' 受信 -> MovingStateへ遷移準備" << std::endl;
		m_character->ChangeState(std::make_shared<MovingState>(m_character));
	}
	else {
		CharacterState::HandleInput(input); // 親に委譲（ここではIdleStateが最上位なので効果なし）
	}
}

