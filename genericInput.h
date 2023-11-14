#ifndef __GENERIC_INPUT__
#define __GENERIC_INPUT__
#include <conio.h>
#include <iostream>
#include <queue>
#include "staticMapping.h"
//������ռ�����Ϣ�����ҽ�֮ת������Ϸ�ڵ������ź�
//��ζ����Ҫ�洢���̺���Ϸ����ִ�е�ӳ���������洢���е�������Ϣ
//������Ϸ�ڿ��ܴ��ڶ��ͬ����ӳ�䵽ĳ����λ�������Ҫ������һ��message�ŵ����洢��Ϣ��������Ҫ�洢����һ���ź�֮��������ӳ٣���ȷ������һ���ź���ͬһ�εĲ�����
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