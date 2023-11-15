#ifndef __object__
#define __object__
#include <iostream>
#include <unordered_set>
#include <vector>
#include "staticMapping.h"
#include "CustomMath.h"
#include "InputSystem.h"
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
    vector2 position;
    vector2 rotation;
    vector2 forward;

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
    vector2 getPosition()
    {
        return position;
    }
    bool setPosition(double x, double y)
    {
        position = {x, y};
        return true;
    }
    bool setPosition(vector2 _position)
    {
        position = {_position.first, _position.second};
        return true;
    }
};
class Car : public GameObject
{
private:
    bool gear = true; // only forward or backward like autogear.
    double fraction = 1.0;
    double engineForce = 3;
    double breakForce = 4;
    double maxSpeed = 120;
    vector2 speed;
    vector2 a;

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
        a = {0.0, 0.0};
        if (Singleton<Actions>::GetInstance().GetKeyDown(ActionCode::Up))
        {
            // std::cout << "Car Go" << std::endl;
            a.first += (gear ? 1 : -1) * engineForce * forward.first;
            a.second += (gear ? 1 : -1) * engineForce * forward.second;
        }
        // while we push the breaker, we always intend to stop the car, no matter what direction it moving now.
        if (Singleton<Actions>::GetInstance().GetKeyDown(ActionCode::Down))
        {
            // std::cout << "Car Stop" << std::endl;
            // 这里应该求二维向量speed 与 forward的夹角
            if(normalize2D(speed) >= 0.1f){
                a.first += -1 * breakForce * speed.first;
                a.second += -1 * breakForce * speed.second;
            }
        }
        // get actionCode left and right will change the car's forward.
        // if the power cant greater than fraction, than the car should just stop.
        if (normalize2D(speed) >= 0.1f)
        {
            a.first += -1 * std::min(normalize2D(speed), fraction) * speed.first;
            a.second += -1 * std::min(normalize2D(speed), fraction) * speed.second;
        }
        // need to times the deltaTime as a static global singleton variable.
        speed.first += a.first * forward.first;
        speed.second += a.second * forward.second;
        //约束最大速度, 通过sin和cos分解出x,y值
        if(normalize2D(speed) >= maxSpeed){
            
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
        if (normalize2D(speed) >= 0.1f)
        {
            position.first += speed.first;
            position.second += speed.second;
            // std::cout << "a:" << a.first << "," << a.second << "\r";
            std::cout << "speed:" << speed.first << "," << speed.second << "\r";
            // std::cout << "moving:" << position.first << "," << position.second << std::endl;
        }
        //初始化
        else{
            speed.first = 0;
            speed.second = 0;
        }
    }
};
#endif