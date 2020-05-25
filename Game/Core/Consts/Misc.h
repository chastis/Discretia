#pragma once

#include <Core/Consts/Enums.h>
#include <SFML/Graphics.hpp>

namespace Misc
{
    ChannelEventType GetChannelTypeFromSFML(sf::Event::EventType SFMLType);
}