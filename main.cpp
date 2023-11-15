#include <iostream>
#include <time.h>
#include "staticMapping.h"
#include "SceneSystem.h"

//TO-DO ����Time��, ���ڻ�ȡdeltaTime

// �����е���ϵͳ���г�ʼ��
void GameInitialization()
{
    Singleton<SceneSystem>::GetInstance().Initialization(0);
}

int main()
{
    clock_t curTime = 0, lastTime;
    
    std::cout << "Game Start" << std::endl;
    std::cout << "Generate Scene" << std::endl;
    // ����Ļ�����ʼ��
    GameInitialization();

    while (true)
    {
        lastTime = curTime;
        curTime = clock();
        if (!Singleton<PlayerInput>::GetInstance().UpdateControl(curTime - lastTime))
            break;
        
        Singleton<ObjectSystem>::GetInstance().UpdateObjects();
        // ����ִ����ҵĲ���
        // ������Ϸ������ϵͳ�Զ�����
        // std::cout << "\033c";
        //����ж�����
        Singleton<PlayerInput>::GetInstance().ClearControls();
    }
    // �ͷ������˴�ռ��
    std::cout << "game is closed" << std::endl;
    // ��������

    return 0;
}