#pragma once
#include <string>
#include "Character.h"

// ---------------------------------------------------
// 1. 基底状態クラス (Abstract Base Class for all states)
// ---------------------------------------------------
class CharacterState
{
public:
    CharacterState(Character* character, const std::string& name)
        : m_character(character), m_name(name), m_parentState(nullptr) {}

    virtual ~CharacterState() = default;

    // 状態に入ったときに呼ばれる
    virtual void Enter();

    // 状態にいる間、毎フレーム（または定期的に）呼ばれる
    virtual void Execute();

    // 状態から出るときに呼ばれる
    virtual void Exit();

    // 入力を処理する（ここでは簡単な文字列として扱う）
    virtual void HandleInput(const std::string& input);

    // 階層型FSMの重要な部分：親状態から呼ばれる
    // 子状態が特定のイベントで別の状態に遷移する必要がある場合、ここで現在の状態を更新できる
    // または、単に Execute() を呼び出すだけでもよい
    virtual void Update();

    void SetParentState(CharacterState* parent);

    CharacterState* GetParentState() const;

    const std::string& GetName() const;

protected:
    Character* m_character; // キャラクターへのポインタ（状態がキャラクターを操作するため）
    std::string m_name;
    CharacterState* m_parentState; // 親状態へのポインタ
};

