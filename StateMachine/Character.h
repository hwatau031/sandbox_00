#pragma once
// 相互参照になるので前方宣言で回避する
class CharacterState;

// ---------------------------------------------------
// 2. キャラクタークラス (Context)
// ---------------------------------------------------
class Character
{
public:
    Character() : m_currentState(nullptr) {}

    // 現在の状態を設定
    void ChangeState(std::shared_ptr<CharacterState> newState);

    // 現在の状態を更新
    void Update();

    // 現在の状態にインプットを渡す
    void HandleInput(const std::string& input);

    // 現在の状態を取得 (デバッグ用)
    CharacterState* GetCurrentState() const;

private:
    std::shared_ptr<CharacterState> m_currentState; // 現在のキャラクターの状態
};

