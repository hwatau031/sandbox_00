#pragma once
#include <iostream>
#include "IdleState.h"
#include "RunningState.h"
#include "MovingState.h"
#include "WalkingState.h"


// MovingStateに入ったときに、デフォルトでWalkingStateに遷移する
MovingState::MovingState(Character* character)
	: CharacterState(character, "Moving")
{
	m_currentSubState = std::make_shared<WalkingState>(character);
	m_currentSubState->SetParentState(this); // 親を設定
}

MovingState::~MovingState()
{
	if (m_currentSubState) {
		m_currentSubState->Exit(); // サブ状態の終了を保証
	}
}

void MovingState::Enter()
{
	CharacterState::Enter();
	std::cout << "  キャラクターは移動を開始します。" << std::endl;
	if (m_currentSubState) {
		m_currentSubState->Enter(); // サブ状態もEnter
	}
}

void MovingState::Execute()
{
	// 移動状態全体に共通のロジック（例：移動速度の基本計算など）
}

void MovingState::Update()
{
	// 親状態のUpdateから、現在のアクティブなサブ状態のUpdateを呼び出す
	Execute(); // 親状態自身のExecute
	if (m_currentSubState) {
		m_currentSubState->Update(); // サブ状態の更新を委譲
	}
}

void MovingState::HandleInput(const std::string& input)
{
	if (input == "stop") {
		std::cout << "  入力 'stop' 受信 -> IdleStateへ遷移準備" << std::endl;
		m_character->ChangeState(std::make_shared<IdleState>(m_character));
		return;
	}

	// サブ状態がインプットを処理するかどうかを試す
	if (m_currentSubState) {
		// ここでサブ状態に直接インプットを渡すか、
		// サブ状態のロジック内で特定の入力に応じた遷移を行う
		// このサンプルではサブ状態も独自にHandleInputを持つ
		m_currentSubState->HandleInput(input);
		return; // サブ状態が処理したら親は処理しない
	}

	// サブ状態が処理しなかった場合、またはサブ状態がない場合、親のデフォルト処理
	CharacterState::HandleInput(input); // 親に委譲（ここではMovingStateが最上位なので効果なし）
}

// MovingState内部でのサブ状態変更
void MovingState::ChangeSubState(std::shared_ptr<CharacterState> newSubState)
{
	if (m_currentSubState) {
		m_currentSubState->Exit();
	}
	m_currentSubState = newSubState;
	if (m_currentSubState) {
		m_currentSubState->SetParentState(this); // 新しいサブ状態の親も設定
		m_currentSubState->Enter();
	}
}

// サブ状態の取得（デバッグや特定のロジックで必要になる場合）
CharacterState* MovingState::GetCurrentSubState() const
{
	return m_currentSubState.get();
}

