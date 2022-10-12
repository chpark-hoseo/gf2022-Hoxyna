#pragma once
#include <SDL2/SDL.h> 
class Singleton
{
private:
    Singleton() {};
    static Singleton* instance;

public:
    static Singleton* GetInstance()
    {
        if (instance == NULL)
            instance = new Singleton();
        return instance;
    }
};

Singleton* Singleton::instance = NULL;
