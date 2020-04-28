#pragma once

#include <Core/Utility/Policy.h>
#include <Core/CoreDefs.h>
#include <atomic>

template <class = DefaultThreadPolicy>
class CORE_API ReferenceCountable;

template <>
class CORE_API ReferenceCountable<DefaultThreadPolicy>
{
private:
	size_t counter = 1;
protected:
	virtual ~ReferenceCountable() = default;
public:
	using thread_policy = DefaultThreadPolicy;
public:
	void AddRef();
	void Release();
	[[nodiscard]] size_t Count() const;
};

template<>
class CORE_API ReferenceCountable<ThreadSafePolicy>
{
private:
	std::atomic_size_t counter;
protected:
	ReferenceCountable() { counter.store(1); }
	virtual ~ReferenceCountable() = default;
public:
	using thread_policy = ThreadSafePolicy;
public:
	void AddRef();
	void Release();
	size_t Count() const;
};