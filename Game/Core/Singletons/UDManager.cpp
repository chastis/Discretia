#include <Core/Singletons/UIDManager.h>

void UIDManager::Init()
{

}

size_t UIDManager::Register()
{
    return nextUID++;
}

