#pragma once

#include <Core/Utility/Noncopyable.h>
#include <Core/CoreDefs.h>

class UIDManager : public Noncopyable
{
public:
	static CORE_DLL UIDManager Instance;
	size_t CORE_DLL Register();
private:
	UIDManager() = default;
	~UIDManager() = default;
	size_t NextUID = 0;
};