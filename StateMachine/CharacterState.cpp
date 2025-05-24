#pragma once
#include <iostream>
#include "CharacterState.h"


// 状態に入ったときに呼ばれる
void CharacterState::Enter()
{
	std::cout << "[" << m_name << "] Enter" << std::endl;
}

// 状態にいる間、毎フレーム（または定期的に）呼ばれる
void CharacterState::Execute()
{
	// std::cout << "[" << m_name << "] Execute" << std::endl; // 頻繁なのでコメントアウト
}

// 状態から出るときに呼ばれる
void CharacterState::Exit()
{
	std::cout << "[" << m_name << "] Exit" << std::endl;
}

// 入力を処理する（ここでは簡単な文字列として扱う）
void CharacterState::HandleInput(const std::string& input)
{
	// デフォルトでは何もしないか、親に委譲する
	if (m_parentState) {
		m_parentState->HandleInput(input);
	}
}

// 階層型FSMの重要な部分：親状態から呼ばれる
// 子状態が特定のイベントで別の状態に遷移する必要がある場合、ここで現在の状態を更新できる
// または、単に Execute() を呼び出すだけでもよい
void CharacterState::Update()
{
	Execute(); // デフォルトでは自身のExecuteを呼び出す
}

void CharacterState::SetParentState(CharacterState* parent)
{
	m_parentState = parent;
}

CharacterState* CharacterState::GetParentState() const
{
	return m_parentState;
}

const std::string& CharacterState::GetName() const
{
	return m_name;
}
