#pragma once

#include <Core/Consts/Enums.h>
#include <SFML/Graphics.hpp>

namespace Misc
{
    ChannelEvent::Type GetChannelTypeFromSFML(sf::Event::EventType SFMLType);
}