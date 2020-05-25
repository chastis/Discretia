#pragma once

#include <Core/EventSystem/EventReceiver.h>
#include <Core/Consts/Enums.h>
#include <Core/CoreDefs.h>
#include <SFML/Graphics.hpp>
#include <Core/Utility/Noncopyable.h>
#include <map>
#include <memory>

class CORE_API EventDispatcher: public Noncopyable
{
public:
    EventDispatcher() = default;
    EventDispatcher(const EventDispatcher&) = delete;
    EventDispatcher& operator=(const EventDispatcher&) = delete;
    void Dispatch(Event& inEvent);
    void JoinEvent(EventReceiver*);
    void JoinEvent(std::unique_ptr<EventReceiver>&&);
    void LeaveChannel(ChannelEventType channelType, size_t ownerUID);
    void RemoveEvent(size_t ownerUID, const std::string& eventSID);
private:
    std::map<ChannelEventType, std::vector<std::unique_ptr<EventReceiver>>> events;
};

