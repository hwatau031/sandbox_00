#pragma once
#include <iostream>
#include "Character.h"
#include "CharacterState.h"

// 現在の状態を設定
void Character::ChangeState(std::shared_ptr<CharacterState> newState)
{
	if (m_currentState) {
		m_currentState->Exit();
	}
	m_currentState = newState;
	if (m_currentState) {
		m_currentState->Enter();
	}
}

// 現在の状態を更新
void Character::Update()
{
	if (m_currentState) {
		m_currentState->Update(); // 親状態が子状態を管理できるようにUpdateを呼び出す
	}
}

// 現在の状態にインプットを渡す
void Character::HandleInput(const std::string& input)
{
	if (m_currentState) {
		m_currentState->HandleInput(input);
	}
}

// 現在の状態を取得 (デバッグ用)
CharacterState* Character::GetCurrentState() const
{
	return m_currentState.get();
}


