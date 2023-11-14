#ifndef __SCENE_SYSTEM__
#define __SCENE_SYSTEM__
// ��Ҫ������عؿ��͹ؿ��ڵ�һ���������ʼ�������߼�
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