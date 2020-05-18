#pragma once

#include <Core/Utility/Noncopyable.h>
#include <Core/Utility/Nonmoveable.h>
#include <Core/CoreDefs.h>

template <class T>
class CORE_API BaseSingleton : public Noncopyable, public Nonmoveable
{
public:

    static void CreateInstance()
    {
        instance = new T;
    }

    static void DestroyInstance()
    {
        delete instance;
    }

    static T& GetInstance()
    {
        if (!instance)
        {
            CreateInstance();
        }
        return *instance;
    }
    
    virtual void Init() = 0;

protected:
    BaseSingleton() = default;
    virtual ~BaseSingleton() = default;
    static T* instance;
};

template <class T>
T* BaseSingleton<T>::instance = nullptr;