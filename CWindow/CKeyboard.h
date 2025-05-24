#pragma once
#include <windows.h>

class CKeyboard
{
public:
	CKeyboard() {};
	~CKeyboard() {};

	bool isKeyUp(int key_def);
	bool isKeyDown(int key_def);

private:
	// キーボード入力
	BOOL GetKeyState(int key);
};

