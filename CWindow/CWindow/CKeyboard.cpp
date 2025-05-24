#include "CKeyboard.h"


bool CKeyboard::isKeyUp(int key_def)
{
    return !(GetKeyState(key_def) & 0x80);
}

bool CKeyboard::isKeyDown(int key_def)
{
    return (GetKeyState(key_def) & 0x80);
}

// キーボード入力
BOOL CKeyboard::GetKeyState(int key_def)
{
    BYTE KeyTbl[256];
    if (GetKeyboardState(KeyTbl))
    {
        return KeyTbl[key_def];
    }
    return 0;
}
