#pragma once

class Entity;

class BaseComponent
{
public:
	void Init(Entity* InOwner);

private:
	Entity* Owner = nullptr;
};