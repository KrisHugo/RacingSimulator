#ifndef __STATIC_MAPPING_CONFIG__
#define __STATIC_MAPPING_CONFIG__

/* GetAsyncKeyState ����ӳ��
VK_LBUTTON             ������                      0x01
VK_RBUTTON             ����Ҽ�                      0x02
VK_CANCEL              Ctrl + Break                  0x03
VK_MBUTTON             ����м�                      0x04

VK_BACK                Backspace ��       0x08
VK_TAB                 Tab ��                        0x09

VK_RETURN              �س���                        0x0D


VK_SHIFT               Shift ��                      0x10
VK_CONTROL             Ctrl ��                       0x11
VK_MENU                Alt ��                 0x12
VK_PAUSE               Pause ��                      0x13
VK_CAPITAL             Caps Lock ��                  0x14

VK_ESCAPE              Esc ��                        0x1B

VK_SPACE               �ո��         0x20
VK_PRIOR               Page Up ��                    0x21
VK_NEXT                Page Down ��                  0x22
VK_END                 End ��                        0x23
VK_HOME                Home ��                       0x24
VK_LEFT                ���ͷ��                      0x25
VK_UP                  �ϼ�ͷ��                      0x26
VK_RIGHT               �Ҽ�ͷ��                      0x27
VK_DOWN                �¼�ͷ��                      0x28
VK_SNAPSHOT            Print Screen ��               0x2C
VK_Insert              Insert ��                     0x2D
VK_Delete              Delete ��                     0x2E

'0' �C '9'             ���� 0 - 9                    0x30 - 0x39
'A' �C 'Z'             ��ĸ A - Z                    0x41 - 0x5A

VK_LWIN                ��WinKey(104���̲���)         0x5B
VK_RWIN                ��WinKey(104���̲���)         0x5C
VK_APPS                AppsKey(104���̲���)          0x5D

VK_NUMPAD0            С���� 0 ��                    0x60
VK_NUMPAD1            С���� 1 ��                    0x61
VK_NUMPAD2            С���� 2 ��                    0x62
VK_NUMPAD3            С���� 3 ��                    0x63
VK_NUMPAD4            С���� 4 ��                    0x64
VK_NUMPAD5            С���� 5 ��                    0x65
VK_NUMPAD6            С���� 6 ��                    0x66
VK_NUMPAD7            С���� 7 ��                    0x67
VK_NUMPAD8            С���� 8 ��                    0x68
VK_NUMPAD9            С���� 9 ��                    0x69

VK_F1 - VK_F24        ���ܼ�F1 �C F24               0x70 - 0x87

VK_NUMLOCK            Num Lock ��                   0x90
VK_SCROLL             Scroll Lock ��                0x91
*/
#include <Windows.h>
#include <unordered_map>
#include <unordered_set>

#define KEYDOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define KEYUP(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)

enum KeyCode
{
    SpaceBar = (SHORT)0x20,
    ESC = (SHORT)0x1B,
    LMOUSE = (SHORT)0x01,
    RMOUSE = (SHORT)0x02,
    A = (SHORT)0x41,
    D = (SHORT)0x44,
    E = (SHORT)0x45,
    S = (SHORT)0x53,
    W = (SHORT)0x57
};
enum ActionCode
{
    Exit,
    Up,
    Down,
    Left,
    Right,
    DoNothing
};
#define Signal std::pair<ActionCode, unsigned>

std::unordered_map<KeyCode, ActionCode> KeyActionMapping({{KeyCode::ESC, ActionCode::Exit},
                                                      {KeyCode::W, ActionCode::Up},
                                                      {KeyCode::S, ActionCode::Down},
                                                      {KeyCode::A, ActionCode::Left},
                                                      {KeyCode::D, ActionCode::Right}});
#endif