#ifndef __PLAYER_INPUT__
#define __PLAYER_INPUT__
// ���õ���genericInput�������źź󣬼�֪������Щ�����������ź�֮��
// ��֮ת���ɳ�������Ҫʶ���value, ����ӳ��� ��������ź�, �Լ����������¼��ź�, ����ִ�л����¼���
// ÿһ֡��event����value����¼֮��ֻ��Ҫ�����ж��¼��ж���Щobject��Ҫִ��(unordered_map<Signal?, Object>)
// Object����eventSystem��������event��value������Ҫ��ʲô���ݽ����޸ģ����޸ĳ�ʲô����
#include "Singleton.h"
#include "genericInput.h"
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
        IsPressed = false;
    }
    bool GetPressed(){
        return IsPressed;
    }


};

class Actions : Singleton<PlayerInput>
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

    void ClearActions(){
        for(auto& action : actions){
            action.second.clear();
        }
    }
public:
    bool GetKeyDown(ActionCode code){
        return actions[code].GetPressed();
    }
};
class PlayerInput : Singleton<PlayerInput>
{
    friend class Singleton;

private:
    Actions actions;
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

    // ������
    bool UpdateControl(unsigned timeOffset)
    {
        // ���ԭ��button��״̬
        actions.ClearActions();
        // ����button״̬
        input.updateSignals(timeOffset);
        while (!input.isEmpty())
        {
            lastSignal = signal;

            signal = input.getLatestSignal();
            ActionCode signalKey = signal.first;
            std::cout << signalKey << std::endl;
            // ǿ�ƽ���ָ��
            if (signalKey == ActionCode::Exit)
            {
                return false;
            }
            switch (signalKey)
            {
            case ActionCode::Up:
                actions.Up.Update(true);
                break;
            case ActionCode::Down:
                actions.Down.Update(true);
                break;
            case ActionCode::Left:
                actions.Left.Update(true);
                break;
            case ActionCode::Right:
                actions.Right.Update(true);
                break;
            }
            // ����ǰ֡������signalȫ��ת���ɰ�����Ϣ
        }
        return true;
    }
};
#endif