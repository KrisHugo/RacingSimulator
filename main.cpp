#include <iostream>
#include <time.h>
#include "staticMapping.h"
#include "SceneSystem.h"

//TO-DO 生成Time类, 用于获取deltaTime

// 将所有单例系统进行初始化
void GameInitialization()
{
    Singleton<SceneSystem>::GetInstance().Initialization(0);
}

int main()
{
    clock_t curTime = 0, lastTime;
    
    std::cout << "Game Start" << std::endl;
    std::cout << "Generate Scene" << std::endl;
    // 程序的基本初始化
    GameInitialization();

    while (true)
    {
        lastTime = curTime;
        curTime = clock();
        if (!Singleton<PlayerInput>::GetInstance().UpdateControl(curTime - lastTime))
            break;
        
        Singleton<ObjectSystem>::GetInstance().UpdateObjects();
        // 首先执行玩家的操作
        // 进行游戏的其他系统自动工作
        // std::cout << "\033c";
        //清空中断数据
        Singleton<PlayerInput>::GetInstance().ClearControls();
    }
    // 释放所有运存占用
    std::cout << "game is closed" << std::endl;
    // 结束程序

    return 0;
}