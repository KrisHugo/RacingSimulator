#ifndef __GENERIC_INPUT__
#define __GENERIC_INPUT__
#include <conio.h>
#include <iostream>
#include <queue>
#include "staticMapping.h"
//负责接收键盘信息，并且将之转换成游戏内的输入信号
//意味着需要存储键盘和游戏输入执行的映射表，并负责存储所有的输入信息
//由于游戏内可能存在多键同步才映射到某个键位，因此需要更加做一个message信道来存储信息，并且需要存储与上一个信号之间的输入延迟，来确保与上一个信号是同一次的操作。
//signal, timeOffset
namespace GenericInput{

class Input{
private:
    std::unordered_set<SHORT> registeredHotKey;
    
    bool Insert(Signal newSignal){
        signals.push(newSignal);
        return true;
    }

    bool Insert(std::queue<Signal> newSignals){
        while (!newSignals.empty()) {
            signals.push(newSignals.front());
            newSignals.pop();
        }
        return true;
    }
    std::queue<Signal> CheckKeyboardInput(unsigned timeOffset){
        // std::cout << "hotkey check: " << registeredHotKey.size() << std::endl;
        std::queue<Signal> newSignals;
        for(auto hotkey : registeredHotKey){
            // std::cout << hotkey << std::endl;
            if(KEYDOWN(hotkey)){
                newSignals.push(Signal({KeyActionMapping[(KeyCode)hotkey], timeOffset}));
            }
        }
        return newSignals;
    }

public:
    unsigned allowOffset = 10;
    std::queue<Signal> signals;

    bool isEmpty(){
        return signals.empty();
    }
    Signal getLatestSignal(){
        if(isEmpty()){
            return GetNothingSignal();
        }
        Signal signal;
        signal = signals.front();
        signals.pop();
        return signal;
    }
    
    
    bool RegisterHotKey(SHORT keyCode){
        registeredHotKey.emplace(keyCode);
        return registeredHotKey.find(keyCode) != registeredHotKey.end();
    }

    bool UnregisterHotKey(SHORT keyCode){
        registeredHotKey.erase(keyCode);
        return registeredHotKey.find(keyCode) == registeredHotKey.end();
    }

    bool updateSignals(unsigned timeOffset){
        return Insert(CheckKeyboardInput(timeOffset));
    }

     Signal GetNothingSignal(){
        return {ActionCode::DoNothing, allowOffset};
    }
};
}

#endif