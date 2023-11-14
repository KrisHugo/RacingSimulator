#ifndef __STATIC_MAPPING_CONFIG__
#define __STATIC_MAPPING_CONFIG__

/* GetAsyncKeyState °´¼üÓ³Éä
VK_LBUTTON             Êó±ê×ó¼ü                      0x01
VK_RBUTTON             Êó±êÓÒ¼ü                      0x02
VK_CANCEL              Ctrl + Break                  0x03
VK_MBUTTON             Êó±êÖÐ¼ü                      0x04

VK_BACK                Backspace ¼ü       0x08
VK_TAB                 Tab ¼ü                        0x09

VK_RETURN              »Ø³µ¼ü                        0x0D


VK_SHIFT               Shift ¼ü                      0x10
VK_CONTROL             Ctrl ¼ü                       0x11
VK_MENU                Alt ¼ü                 0x12
VK_PAUSE               Pause ¼ü                      0x13
VK_CAPITAL             Caps Lock ¼ü                  0x14

VK_ESCAPE              Esc ¼ü                        0x1B

VK_SPACE               ¿Õ¸ñ¼ü         0x20
VK_PRIOR               Page Up ¼ü                    0x21
VK_NEXT                Page Down ¼ü                  0x22
VK_END                 End ¼ü                        0x23
VK_HOME                Home ¼ü                       0x24
VK_LEFT                ×ó¼ýÍ·¼ü                      0x25
VK_UP                  ÉÏ¼ýÍ·¼ü                      0x26
VK_RIGHT               ÓÒ¼ýÍ·¼ü                      0x27
VK_DOWN                ÏÂ¼ýÍ·¼ü                      0x28
VK_SNAPSHOT            Print Screen ¼ü               0x2C
VK_Insert              Insert ¼ü                     0x2D
VK_Delete              Delete ¼ü                     0x2E

'0' ¨C '9'             Êý×Ö 0 - 9                    0x30 - 0x39
'A' ¨C 'Z'             ×ÖÄ¸ A - Z                    0x41 - 0x5A

VK_LWIN                ×óWinKey(104¼üÅÌ²ÅÓÐ)         0x5B
VK_RWIN                ÓÒWinKey(104¼üÅÌ²ÅÓÐ)         0x5C
VK_APPS                AppsKey(104¼üÅÌ²ÅÓÐ)          0x5D

VK_NUMPAD0            Ð¡¼üÅÌ 0 ¼ü                    0x60
VK_NUMPAD1            Ð¡¼üÅÌ 1 ¼ü                    0x61
VK_NUMPAD2            Ð¡¼üÅÌ 2 ¼ü                    0x62
VK_NUMPAD3            Ð¡¼üÅÌ 3 ¼ü                    0x63
VK_NUMPAD4            Ð¡¼üÅÌ 4 ¼ü                    0x64
VK_NUMPAD5            Ð¡¼üÅÌ 5 ¼ü                    0x65
VK_NUMPAD6            Ð¡¼üÅÌ 6 ¼ü                    0x66
VK_NUMPAD7            Ð¡¼üÅÌ 7 ¼ü                    0x67
VK_NUMPAD8            Ð¡¼üÅÌ 8 ¼ü                    0x68
VK_NUMPAD9            Ð¡¼üÅÌ 9 ¼ü                    0x69

VK_F1 - VK_F24        ¹¦ÄÜ¼üF1 ¨C F24               0x70 - 0x87

VK_NUMLOCK            Num Lock ¼ü                   0x90
VK_SCROLL             Scroll Lock ¼ü                0x91
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