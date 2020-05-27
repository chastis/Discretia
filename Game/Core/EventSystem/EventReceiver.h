#pragma once

#include <Core/EventSystem/Event.h>
#include <Core/EventSystem/EventCaller.h>
#include <Core/Interfaces/PrototypeableInterface.h>
#include <Core/CoreDefs.h>
#include <Core/Consts/Enums.h>
#include <SFML/Graphics.hpp>
#include <string>
#include <memory>

class EventCaller;

class CORE_API EventReceiver
{
    friend class EventDispatcher;
public:
    
    EventReceiver(const std::string& inSid, ChannelEvent::Type inChannelType, EventCaller* eventCaller);

    virtual ~EventReceiver() = default;
    [[nodiscard]] const std::string& GetSid() const;
    [[nodiscard]] const ChannelEvent::Type& GetChannelType() const;
    [[nodiscard]] EventCaller* GetOwner() const;
    [[nodiscard]] size_t GetOwnerUID() const;
    virtual bool Receive(Event& inEvent);
    virtual bool ReceiveCanceled(Event& inEvent);
private:
    std::string sid;
    ChannelEvent::Type channelType = ChannelEvent::Type::None;
    EventCaller* ownerEventCaller = nullptr;

    bool bDirty = false;
};