#include <Core/Singletons/UIDManager.h>

UIDManager UIDManager::Instance;

size_t UIDManager::Register()
{
    return nextUID++;
}

