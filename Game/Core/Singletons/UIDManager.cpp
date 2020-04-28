#include <Core/Singletons/UIDManager.h>

size_t UIDManager::Register()
{
	return NextUID++;
}

