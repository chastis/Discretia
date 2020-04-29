#pragma once 

#include <Core/Utility/Nonmoveable.h>
#include <Core/Utility/Noncopyable.h>
#include <Core/CoreDefs.h>

class CORE_API BaseSystem : public Noncopyable, public Nonmoveable
{
public:
	virtual void Update(float deltaTime) = 0;
	virtual ~BaseSystem() = default;
};