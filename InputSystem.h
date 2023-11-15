#ifndef __PLAYER_INPUT__
#define __PLAYER_INPUT__
// ���õ���genericInput�������źź󣬼�֪������Щ�����������ź�֮��
// ��֮ת���ɳ�������Ҫʶ���value, ����ӳ��� ��������ź�, �Լ����������¼��ź�, ����ִ�л����¼���
// ÿһ֡��event����value����¼֮��ֻ��Ҫ�����ж��¼��ж���Щobject��Ҫִ��(unordered_map<Signal?, Object>)
// Object����eventSystem��������event��value������Ҫ��ʲô���ݽ����޸ģ����޸ĳ�ʲô����
#include "Singleton.h"
#include "genericInput.h"
#include <iostream>
class Action
{
private:
    bool IsPressed;

public:
    Action()
    {
        IsPressed = false;
    }

    void Update(bool _isPressed)
    {
        IsPressed = _isPressed;
    }

    void clear()
    {
        Update(false);
    }
    bool GetPressed()
    {
        return IsPressed;
    }
};

class Actions : Singleton<Actions>
{
    friend class PlayerInput;

private:
    Action Up;
    Action Down;
    Action Left;
    Action Right;
    std::unordered_map<ActionCode, Action> actions = {{ActionCode::Up, Up},
                                                      {ActionCode::Down, Down},
                                                      {ActionCode::Left, Left},
                                                      {ActionCode::Right, Right}};

    void ClearActions()
    {
        for (auto &action : actions)
        {
            action.second.clear();
        }
    }

public:

    void UpdateKey(ActionCode code, bool _IsPressed)
    {
        actions[code].Update(_IsPressed);
        return;
    }
    bool GetKeyDown(ActionCode code)
    {
        return actions[code].GetPressed();
    }
    void GetKeyStatus()
    {
        std::cout << (GetKeyDown(ActionCode::Up) ? "up\n" : "");
        std::cout << (GetKeyDown(ActionCode::Down) ? "down\n" : "");
        std::cout << (GetKeyDown(ActionCode::Left) ? "left\n" : "");
        std::cout << (GetKeyDown(ActionCode::Right) ? "right\n" : "");
    }
};
class PlayerInput : Singleton<PlayerInput>
{
    friend class Singleton;

private:
    // Get All Keyboard Signal from input.
    GenericInput::Input input;
    // Update the GameInput By Signal per frame

    const unsigned maxDiff = 10;
    Signal signal, lastSignal;

public:
    PlayerInput() : Singleton()
    {
        lastSignal = signal;
    }

    void Initialization()
    {
        std::vector<SHORT> keyCodes({KeyCode::ESC, KeyCode::A, KeyCode::W, KeyCode::S, KeyCode::D});
        RegisterHotKeys(keyCodes);
        signal = input.GetNothingSignal();
    }

    bool RegisterHotKeys(std::vector<SHORT> keyCodes)
    {
        for (auto keyCode : keyCodes)
        {
            input.RegisterHotKey(keyCode);
        }
        return true;
    }

    bool UnregisterHotKeys(std::vector<SHORT> keyCodes)
    {
        for (auto keyCode : keyCodes)
        {
            input.UnregisterHotKey(keyCode);
        }
        return true;
    }
    void ClearControls()
    {
        // ���ԭ��button��״̬
        Singleton<Actions>::GetInstance().ClearActions();
    }

    // ������
    bool UpdateControl(clock_t timeOffset)
    {
        // ����button״̬
        input.updateSignals(timeOffset);
        while (!input.isEmpty())
        {
            lastSignal = signal;

            signal = input.getLatestSignal();
            ActionCode signalKey = signal.first;
            // ǿ�ƽ���ָ��
            if (signalKey == ActionCode::Exit)
            {
                return false;
            }
            else{
                Singleton<Actions>::GetInstance().UpdateKey(signalKey, true);
                // Singleton<Actions>::GetInstance().GetKeyStatus();
            }
            // ����ǰ֡������signalȫ��ת���ɰ�����Ϣ
        }
        return true;
    }
};
#endif