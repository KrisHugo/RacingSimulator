#ifndef __SINGLETON__
#define __SINGLETON__

template<typename T>
class Singleton{
private:
    static T* _singleton;
protected:
    Singleton() = default;
    virtual ~Singleton() = default;
public:
    static T& GetInstance()
    {
        static T instance;
        return instance;
    }
	//删除默认的移动、拷贝、赋值、取址
    Singleton(Singleton  &&) = delete;
    Singleton(const Singleton  &) = delete;
    void operator = (const Singleton  &) = delete;
    T *operator &() = delete;
};

#endif