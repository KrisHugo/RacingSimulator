#ifndef __object__
#define __object__
#include <iostream>
#include <unordered_set>
#include <vector>
#include "staticMapping.h"
#include "CustomMath.h"
#include "InputSystem.h"
#include "Timer.h"
class Object
{
protected:
    unsigned uid;

public:
    // 删除默认的移动、拷贝、赋值、取址
    Object(Object &&) = default;
    Object(const Object &) = default;

    Object(unsigned _uid)
    {
        uid = _uid;
    }
    ~Object()
    {
    }
    unsigned getUid()
    {
        return uid;
    }

    virtual void Update()
    {
        std::cout << "Update" << std::endl;
    }

    //TODO: this method should be a implement from renderSystem, and it will be control by any graphic card, which means its portable.
    //we try to use openGL, and the render component will be one of the paravariables.
    virtual void Render(){

    }
};
class MenuObject : public Object
{
protected:
    unsigned belongs;
    std::vector<unsigned> childs;

public:
    MenuObject(unsigned _uid, unsigned _belongs) : Object(_uid)
    {
        belongs = _belongs;
    }
    virtual void Update()
    {
        // std::cout << "Menu Update" << std::endl;
    }
};
class GameObject : public Object
{
protected:
    Vector2 position;
    Vector2 rotation;
    Vector2 forward;

public:
    GameObject(unsigned _uid) : Object(_uid)
    {
        position = {0.0, 0.0};
        rotation = {0.0, 0.0};
        forward = {1.0, 0.0};
    }
    virtual void Update()
    {
        // std::cout << "GameObject Update" << std::endl;
    }
    Vector2 getPosition()
    {
        return position;
    }
    bool setPosition(float x, float y)
    {
        position = {x, y};
        return true;
    }
    bool setPosition(Vector2 _position)
    {
        position = {_position.x, _position.y};
        return true;
    }
};
class Car : public GameObject
{
private:
    bool gear = true; // only forward or backward like autogear.
    float fraction = 1.0;
    float engineForce = 3;
    float breakForce = 4;
    float maxSpeed = 120;
    Vector2 speed;
    Vector2 a;

public:
    Car(unsigned _uid) : GameObject(_uid)
    {
        gear = true; // only forward or backward like autogear.
        fraction = 2;
        engineForce = 3;
        breakForce = 4;
        speed = {0.0, 0.0};
        a = {0.0, 0.0};
    }
    void Update()
    {
        // std::cout << "Car Update" << std::endl;
        // 每一时刻的加速度都需要根据当前的力情况重新计算
        //InputUpdate
        a = {0.0, 0.0};
        if (Singleton<Actions>::GetInstance().GetKeyDown(ActionCode::Up))
        {
            // std::cout << "Car Go" << std::endl;
            a.x += (gear ? 1 : -1) * engineForce * forward.x * GameTimer.getDeltaTime();
            a.y += (gear ? 1 : -1) * engineForce * forward.y * GameTimer.getDeltaTime();
        }
        // while we push the breaker, we always intend to stop the car, no matter what direction it moving now.
        if (Singleton<Actions>::GetInstance().GetKeyDown(ActionCode::Down))
        {
            // std::cout << "Car Stop" << std::endl;
            // 这里应该求二维向量speed 与 forward的夹角
            if(speed.Length >= 0.1f){
                a.x += -1 * breakForce * speed.x * GameTimer.getDeltaTime();
                a.y += -1 * breakForce * speed.y * GameTimer.getDeltaTime();
            }
        }
        // get actionCode left and right will change the car's forward.
        // if the power cant greater than fraction, than the car should just stop.
        if (speed.Length >= 0.1f)
        {
            a.x += -1 * std::min(speed.Length, fraction) * speed.x * GameTimer.getDeltaTime();
            a.y += -1 * std::min(speed.Length, fraction) * speed.y * GameTimer.getDeltaTime();
        }

        //Properties Updates
        // need to times the deltaTime as a static global singleton variable.
        speed.x += a.x * forward.x;
        speed.y += a.y * forward.y;
        //约束最大速度, 通过sin和cos分解出x,y值
        //maxSpeed * forward?
        //FIXME: we haven't limit the speed.
        if(speed.Length > maxSpeed){
            
        }
        updateEngineStatus();
        moving();
        return;
    }
    // dynamic changing the force from engine and break by speed and other status.
    void updateEngineStatus()
    {
    }
    void moving()
    {
        if (speed.Length >= 0.1f)
        {
            position.x += speed.x;
            position.y += speed.y;
            // std::cout << "a:" << a.first << "," << a.second << "\r";
            // std::cout << "moving:" << position.first << "," << position.second << std::endl;
        }
        //初始化
        else{
            speed.x = 0;
            speed.y = 0;
        }
        std::cout << "speed:" << speed.x << "," << speed.y << "\r";
    }
};
#endif