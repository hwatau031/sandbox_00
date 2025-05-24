#pragma once
#include <string>
#include <memory>
#include "CharacterState.h"

// 3.2. 移動状態 (親状態)
class MovingState : public CharacterState
{
public:
    // MovingStateに入ったときに、デフォルトでWalkingStateに遷移する
    MovingState(Character* character);

    ~MovingState() override;

    void Enter() override;

    void Execute() override;

    void Update() override;

    void HandleInput(const std::string& input) override;

    // MovingState内部でのサブ状態変更
    void ChangeSubState(std::shared_ptr<CharacterState> newSubState);

    // サブ状態の取得（デバッグや特定のロジックで必要になる場合）
    CharacterState* GetCurrentSubState() const;

private:
    std::shared_ptr<CharacterState> m_currentSubState; // 現在のサブ状態
};

