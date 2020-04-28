#pragma once

#include <Core/Utility/Noncopyable.h>

class UIDManager : public Noncopyable
{
public:
	static UIDManager Instance;
	size_t Register();
private:
	UIDManager() = default;
	~UIDManager() = default;
	size_t NextUID = 0;
};