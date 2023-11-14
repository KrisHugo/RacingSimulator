#ifndef __PLAYER_INPUT__
#define __PLAYER_INPUT__
// 当拿到了genericInput的输入信号后，即知道了那些按键有输入信号之后
// 将之转化成程序内需要识别的value, 例如映射成 方向控制信号, 以及其他独立事件信号, 例如执行互动事件等
// 每一帧的event及其value都记录之后，只需要根据中断事件判断哪些object需要执行(unordered_map<Signal?, Object>)
// Object根据eventSystem传过来的event和value来决定要对什么数据进行修改，又修改成什么样。
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

    // 输入检测
    bool UpdateControl(unsigned timeOffset)
    {
        // 清空原先button的状态
        actions.ClearActions();
        // 更新button状态
        input.updateSignals(timeOffset);
        while (!input.isEmpty())
        {
            lastSignal = signal;

            signal = input.getLatestSignal();
            ActionCode signalKey = signal.first;
            std::cout << signalKey << std::endl;
            // 强制结束指令
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
            // 将当前帧的所有signal全部转化成按键信息
        }
        return true;
    }
};
#endif