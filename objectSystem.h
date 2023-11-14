#ifndef __OBJECT_SYSTEM__
#define __OBJECT_SYSTEM__
#include <vector>
#include "Singleton.h"
#include "object.h"
/*
注册所有的object, 并使object能够执行start, update, even fixed update
*/
class ObjectSystem : public Singleton<ObjectSystem>
{
    friend class Singleton;

private:
    unsigned counter;
    
    std::vector<MenuObject> menuObjects;
    std::vector<GameObject> gameObjects;
    ObjectSystem()
    {
        counter = 0;
    }

public:
    bool Initialization(std::vector<MenuObject> _menuObjects, std::vector<GameObject> _gameObjects)
    {
        counter = 0;
        menuObjects = _menuObjects;
        gameObjects = _gameObjects;
        return true;
    }

    void UpdateObjects()
    {
        for (auto object : menuObjects)
        {
            object.Update();
        }
        for (auto object : gameObjects)
        {
            object.Update();
        }
    }
    bool RegisterGameObject(GameObject object)
    {
        gameObjects.push_back(object);
        return true;
    }

    bool RegisterMenuObject(MenuObject object)
    {
        menuObjects.push_back(object);
        return true;
    }
    bool UnregisterGameObject(unsigned uid)
    {
        for (auto object = gameObjects.begin(); object != gameObjects.end(); object++)
        {
            if (object->getUid() == uid)
            {
                gameObjects.erase(object);
            }
        }
        return true;
    }
};

#endif