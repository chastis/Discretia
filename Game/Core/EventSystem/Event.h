#pragma once

#include <Core/Consts/Enums.h>
#include <Core/CoreDefs.h>
#include <SFML/Graphics.hpp>

class CORE_API Event
{
public:
    virtual ~Event() = default;
    ChannelEventType channelType = ChannelEventType::None;
};

class CORE_API SFMLEvent : public Event, public sf::Event
{
public:
    SFMLEvent(sf::Event inEvent);
};