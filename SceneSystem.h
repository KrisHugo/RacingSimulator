#ifndef __SCENE_SYSTEM__
#define __SCENE_SYSTEM__
// 主要负责加载关卡和关卡内的一切物件并初始化所有逻辑
#include "Singleton.h"
#include "InputSystem.h"
#include "objectSystem.h"
class Scene{
public:
    std::vector<MenuObject> menuObject;
    std::vector<GameObject> gameObjects;
    Scene(){
        menuObject = {MenuObject(1, 0)};
        gameObjects = {Car(0)};
    }
};
class SceneSystem : Singleton<SceneSystem>
{
    friend class Singleton;

private:
    unsigned currentLevel = 0;
    Scene CurrentScene;
    //config path
    //
public:
    SceneSystem() : Singleton()
    {
    }
    void Initialization(unsigned level)
    {
        currentLevel = level;
        CurrentScene = Scene();
        Singleton<PlayerInput>::GetInstance().Initialization();
        Singleton<ObjectSystem>::GetInstance().Initialization(CurrentScene.menuObject, CurrentScene.gameObjects);
    }
};
#endif