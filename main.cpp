#include <iostream>
#include <time.h>
#include "staticMapping.h"
#include "SceneSystem.h"

using namespace std;

// �����е���ϵͳ���г�ʼ��
void GameInitialization()
{
    Singleton<SceneSystem>::GetInstance().Initialization(0);
}

int main()
{
    unsigned curTime = 0, lastTime;
    
    std::cout << "Game Start" << std::endl;
    std::cout << "Generate Scene" << std::endl;
    // ����Ļ�����ʼ��
    GameInitialization();

    while (true)
    {
        lastTime = curTime;
        curTime = (unsigned)clock();
        if (!Singleton<PlayerInput>::GetInstance().UpdateControl(curTime - lastTime))
            break;
        
        Singleton<ObjectSystem>::GetInstance().UpdateObjects();
        // ����ִ����ҵĲ���
        // ������Ϸ������ϵͳ�Զ�����
    }
    // �ͷ������˴�ռ��
    cout << "game is closed" << endl;
    // ��������

    return 0;
}