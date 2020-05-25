#pragma once

#include <Core/EventSystem/Event.h>
#include <Core/EventSystem/EventCaller.h>
#include <Core/Interfaces/PrototypeableInterface.h>
#include <Core/CoreDefs.h>
#include <Core/Consts/Enums.h>
#include <SFML/Graphics.hpp>
#include <string>

class EventCaller;

class CORE_API EventReceiver
{
public:
    EventReceiver(std::string&& inSid, ChannelEventType inChannelType, EventCaller* eventCaller);

    virtual ~EventReceiver() = default;
    [[nodiscard]] const std::string& GetSid() const;
    [[nodiscard]] const ChannelEventType& GetChannelType() const;
    [[nodiscard]] size_t GetOwnerUID() const;
    virtual void Receive(Event& inEvent);

private:
    std::string sid;
    ChannelEventType channelType = ChannelEventType::None;
    EventCaller* ownerEventCaller = nullptr;
};
