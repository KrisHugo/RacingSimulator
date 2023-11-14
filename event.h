#ifndef __event__
#define __event__

#include <iostream>
#include <string>
#include "eventSystem.h"
#include "object.h"
class Event{
protected:
    unsigned uid;
    const std::string* name;

public:
    Event(const std::string* _name){
        name = _name;
        uid = 0;
        // uid = Singleton<EventSystem>::GetInstance().ResgisterEvent(this);
    };
    bool Run(){
        if(name->empty())
            return false;
        std::cout << (*name) << std::endl;
        return true;
    }
    std::string getEventName(){
        return (*name);
    }

};
class MenuEvent : public Event{
public:
    MenuEvent(const std::string* _name) : Event(_name){

    };

};

class GameObjectEvent : public Event{
public:
    GameObjectEvent(const std::string* _name) : Event(_name){

    };
    bool Run(){
        return true;
    }
};

#endif