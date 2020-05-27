#pragma once

#include <Core/EventSystem/EventReceiver.h>
#include <Core/Consts/Enums.h>
#include <Core/CoreDefs.h>
#include <SFML/Graphics.hpp>
#include <Core/Utility/Noncopyable.h>
#include <map>
#include <memory>
#include <set>

class CORE_API EventDispatcher: public Noncopyable
{
public:
    EventDispatcher() = default;
    EventDispatcher(const EventDispatcher&) = delete;
    EventDispatcher& operator=(const EventDispatcher&) = delete;
    void DispatchFutureEvents();
    void Dispatch(Event& inEvent);
    bool DispatchOnce(Event& inEvent);
    void JoinEvent(EventReceiver*);
    void JoinEvent(std::unique_ptr<EventReceiver>&&);
    void RemoveEvent(EventCaller* eventCaller, const std::string& eventSID);
    void RemoveEvent(size_t ownerUID, const std::string& eventSID);
    void LeaveChannel(ChannelEvent::Type channelType, size_t ownerUID);
    void AddFutureEvent(Event* futureEvent);
private:
    std::map<ChannelEvent::Type, std::vector<std::unique_ptr<EventReceiver>>> events;
    std::vector<std::unique_ptr<Event>> futureEvents;
};

