#ifndef __object__
#define __object__
#include <unordered_set>
#include <vector>
#include "cusMath.h"
#define vector2 std::pair<double,double>
class Object{
protected:
    unsigned uid;

public:
    Object(unsigned _uid)
    {
        uid = _uid;
    }
    ~Object(){

    }
    unsigned getUid(){
        return uid;
    }
    // bool Interupt(unsigned _uid){
    //     if(events.find(_uid) == events.end())
    //         return false;
    //     // Singleton<EventSystem>::GetInstance().RunEvent(_uid);
    //     return true;
    // }
    
    void Update(){
        std::cout << "Update" << std::endl;
    }
};
class MenuObject : public Object{
protected:
    unsigned belongs;
    std::vector<unsigned> childs;
public:
    MenuObject(unsigned _uid, unsigned _belongs) : Object(_uid){
        belongs = _belongs;
    }
    void Update(){
        std::cout << "Update Menu" << std::endl;
    }
};
class GameObject : public Object{
protected:
    vector2 position;
    vector2 rotation;
    vector2 forward;
public:
    GameObject(unsigned _uid) : Object(_uid){
        position = {0.0, 0.0};
        rotation = {0.0, 0.0};
        forward = {1.0, 0.0};
    }
    void Update(){
        std::cout << "GameObject Update" << std::endl;
    }
    vector2 getPosition(){
        return position;
    }
    bool setPosition(double x, double y){
        position = {x,y};
        return true;
    }
    bool setPosition(vector2 _position){
        position = {_position.first, _position.second};
        return true;
    }
};

class Car : public GameObject{
private:
    double a = 1.0;
    vector2 speed;
public:
    Car(unsigned _uid) : GameObject(_uid){
        speed = {0.0, 0.0};
    }
    void Update(){
        
        if(Singleton<Actions>::GetInstance().GetKeyDown(ActionCode::Up)){
            std::cout << "Car Go Forward" << std::endl;
            speed.first += a;
            speed.second += a;
        }
        if(Singleton<Actions>::GetInstance().GetKeyDown(ActionCode::Down)){
            std::cout << "Car Go Backward" << std::endl;
            speed.first -= a * forward.first;
            speed.second -= a * forward.second;
        }
        return;
    }
    void moving(){
        if(normalize2D(speed) >= 0.1f){
            std::cout << "moving" << endl;
            position.first += speed.first;
            position.second += speed.second;
        }
    }
};
#endif