#ifndef __SCENE_SYSTEM__
#define __SCENE_SYSTEM__
// ��Ҫ������عؿ��͹ؿ��ڵ�һ���������ʼ�������߼�
#include "Singleton.h"
#include "InputSystem.h"
#include "objectSystem.h"
class Scene{
public:
    std::vector<MenuObject*> menuObjects;
    std::vector<GameObject*> gameObjects;
    Scene(){
        menuObjects = {new MenuObject(1, 0)};
        gameObjects = {new Car(0)};
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
        Singleton<ObjectSystem>::GetInstance().Initialization(CurrentScene.menuObjects, CurrentScene.gameObjects);
    }
};
#endif