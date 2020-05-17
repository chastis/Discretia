#include <Core/Singletons/Application.h>
#include <Core/Prototypes/ApplicationPrototype.h>
#include <Core/Singletons/PrototypeManager.h>
#include <Core/Utility/Json.h>
#include <iostream>

void Application::Init()
{
	PrototypeManager::Instance.Init();
	ApplicationPrototype def = BasePrototypes<ApplicationPrototype>::GetDefault();
	std::cout << def.GetSID();
}
