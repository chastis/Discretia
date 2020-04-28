#pragma once

class Nonmoveable
{
	Nonmoveable() = default;
	~Nonmoveable() = default;
	Nonmoveable(const Nonmoveable&) = default;
	Nonmoveable(Nonmoveable&&) = delete;
	Nonmoveable& operator=(const Nonmoveable&) = default;
	Nonmoveable& operator=(Nonmoveable&&) = delete;
};

