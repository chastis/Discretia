#include <Core/Singletons/PrototypeManager.h>
#include <Core/Prototypes/ApplicationPrototype.h>

PrototypeManager PrototypeManager::Instance;

void PrototypeManager::Init()
{
    std::unique_ptr<ApplicationPrototypes> applicationPrototypes = std::make_unique<ApplicationPrototypes>();
    applicationPrototypes->Init("ApplicationPrototypes");
    //prototypes.push_back(std::move(applicationPrototypes));
}
