#include <iostream>
#include <string>
#include <memory> // std::shared_ptr
#include <chrono>
#include <thread>
#include "Character.h"
#include "CharacterState.h"
#include "IdleState.h"
#include "RunningState.h"
#include "MovingState.h"
#include "WalkingState.h"

// ---------------------------------------------------
// メイン関数
// ---------------------------------------------------
int main() {
    Character player;

    // 初期状態をIdleに設定
    player.ChangeState(std::make_shared<IdleState>(&player));
    std::cout << "現在の状態: " << player.GetCurrentState()->GetName() << std::endl;

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cout << "\n--- 1秒経過 ---" << std::endl;
    player.Update(); // 状態更新
    std::cout << "現在の状態: " << player.GetCurrentState()->GetName() << std::endl;

    std::cout << "\n--- 'move' 入力 ---" << std::endl;
    player.HandleInput("move"); // Idle -> Moving (内部でWalkingへ)
    std::cout << "現在の状態: " << player.GetCurrentState()->GetName();
    if (auto movingState = dynamic_cast<MovingState*>(player.GetCurrentState())) {
        std::cout << " (サブ状態: " << movingState->GetCurrentSubState()->GetName() << ")";
    }
    // 上記のGetCurrentSubStateはprivateなので、ここでは親状態の名前だけ表示
    std::cout << std::endl;

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cout << "\n--- 1秒経過 ---" << std::endl;
    player.Update(); // 状態更新
    std::cout << "現在の状態: " << player.GetCurrentState()->GetName();
    // ここでサブ状態の名前も表示したいが、Characterクラスから直接アクセスできないので、
    // CharacterState::GetName() のみを表示する。
    // MovingStateの内部でサブ状態の名前を取得するロジックがあれば表示可能
    std::cout << std::endl;

    std::cout << "\n--- 'run' 入力 ---" << std::endl;
    player.HandleInput("run"); // Walking -> Running
    std::cout << "現在の状態: " << player.GetCurrentState()->GetName();
    std::cout << std::endl;

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cout << "\n--- 1秒経過 ---" << std::endl;
    player.Update(); // 状態更新
    std::cout << "現在の状態: " << player.GetCurrentState()->GetName();
    std::cout << std::endl;

    std::cout << "\n--- 'walk' 入力 ---" << std::endl;
    player.HandleInput("walk"); // Running -> Walking
    std::cout << "現在の状態: " << player.GetCurrentState()->GetName();
    std::cout << std::endl;

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cout << "\n--- 1秒経過 ---" << std::endl;
    player.Update(); // 状態更新
    std::cout << "現在の状態: " << player.GetCurrentState()->GetName();
    std::cout << std::endl;

    std::cout << "\n--- 'stop' 入力 ---" << std::endl;
    player.HandleInput("stop"); // Moving -> Idle
    std::cout << "現在の状態: " << player.GetCurrentState()->GetName() << std::endl;

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cout << "\n--- 1秒経過 ---" << std::endl;
    player.Update(); // 状態更新
    std::cout << "現在の状態: " << player.GetCurrentState()->GetName() << std::endl;

    std::cout << "\n--- 終了 ---" << std::endl;
    return 0;
}