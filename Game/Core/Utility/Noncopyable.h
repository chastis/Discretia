#pragma once

#include <Core/CoreDefs.h>

class CORE_DLL Noncopyable
{
	Noncopyable() = default;
	~Noncopyable() = default;
	Noncopyable(const Noncopyable&) = delete;
	Noncopyable(Noncopyable&&) = default;
	Noncopyable& operator=(const Noncopyable&) = delete;
	Noncopyable& operator=(Noncopyable&&) = default;
};

