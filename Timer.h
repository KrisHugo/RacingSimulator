#ifndef __GAME_TIME__
#define __GAME_TIME__
#include <Time.h>
#include "Singleton.h"
#define GameTimer Singleton<GameEngine::Timer>::GetInstance()
namespace GameEngine{
class Timer : Singleton<Timer>{
    friend class Singleton;
private:
    clock_t curTime;
    clock_t lastTime;
public:
    Timer() : Singleton(){
        curTime = 0;
        lastTime = curTime;
    }
    static clock_t getDeltaTime(){
        return GetInstance().curTime - GetInstance().lastTime;
    }
    static void updateTime(){
        GetInstance().lastTime = GetInstance().curTime;
        GetInstance().curTime = clock();
    }
};

}

#endif