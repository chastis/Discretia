#pragma once

#include <Core/Utility/Noncopyable.h>
#include <Core/CoreDefs.h>

class UIDManager : public Noncopyable
{
public:
	static CORE_API UIDManager Instance;
	size_t CORE_API Register();
private:
	UIDManager() = default;
	~UIDManager() = default;
	size_t NextUID = 0;
};