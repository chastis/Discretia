#include <Core/Singletons/PrototypeManager.h>
#include <Core/Prototypes/ApplicationPrototype.h>
#include <Core/Prototypes/TexturePrototype.h>
#include <Core/Prototypes/SpritePrototype.h>

void PrototypeManager::Init()
{
    ApplicationPrototypes::Init("ApplicationPrototypes");
    TexturePrototypes::Init("TexturePrototypes");
    SpritePrototypes::Init("SpritePrototypes");
}
