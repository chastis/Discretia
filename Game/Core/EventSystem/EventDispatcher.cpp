#include <Core/EventSystem/EventDispatcher.h>
#include <Core/Interfaces/UIDInterface.h>

void EventDispatcher::DispatchFutureEvents()
{
    for (size_t i = 0; i < futureEvents.size(); ++i)
    {
        if (DispatchOnce(*futureEvents[i]))
        {
            futureEvents.erase(futureEvents.begin()+i);
            --i;
        }
    }
}

void EventDispatcher::Dispatch(Event& inEvent)
{
    std::map<ChannelEvent::Type, std::vector<EventReceiver*>> currentEvents;

    for (auto& eventChannel : events)
    {
        for (auto eventFunctionIt = eventChannel.second.begin(); eventFunctionIt != eventChannel.second.end(); ++eventFunctionIt)
        {
            if ((*eventFunctionIt)->bDirty)
            {
                eventFunctionIt = eventChannel.second.erase(eventFunctionIt);
                if (eventFunctionIt==eventChannel.second.end())
                    break;
            }
           
        }
    }

    for (auto& eventChannel : events)
    {
        for (auto& eventFunction : eventChannel.second)
        {
            currentEvents[eventChannel.first].emplace_back(eventFunction.get());
        }
    }

    for (auto& eventChannel : currentEvents)
    {
        for (auto& eventFunction : eventChannel.second)
        {
            if (eventFunction && !eventFunction->bDirty)
            {
                eventFunction->Receive(inEvent);
            }
        }
    }
}

bool EventDispatcher::DispatchOnce(Event& inEvent)
{
    std::map<ChannelEvent::Type, std::vector<EventReceiver*>> currentEvents;

    for (auto& eventChannel : events)
    {
        for (auto eventFunctionIt = eventChannel.second.begin(); eventFunctionIt != eventChannel.second.end(); ++eventFunctionIt)
        {
            if ((*eventFunctionIt)->bDirty)
            {
                eventFunctionIt = eventChannel.second.erase(eventFunctionIt);
                if (eventFunctionIt==eventChannel.second.end())
                    break;
            }
           
        }
    }

    for (auto& eventChannel : events)
    {
        for (auto& eventFunction : eventChannel.second)
        {
            currentEvents[eventChannel.first].emplace_back(eventFunction.get());
        }
    }

    for (auto& eventChannel : currentEvents)
    {
        for (auto& eventFunction : eventChannel.second)
        {
            if (eventFunction && !eventFunction->bDirty)
            {
                if (eventFunction->Receive(inEvent))
                    return true;
            }
        }
    }
    return false;
}

void EventDispatcher::JoinEvent(EventReceiver* NewEvent)
{
    if (NewEvent)
    {
        const ChannelEvent::Type NewEventType = NewEvent->GetChannelType();
        events[NewEventType].emplace_back(std::unique_ptr<EventReceiver>(NewEvent));
    }
}

void EventDispatcher::JoinEvent(std::unique_ptr<EventReceiver>&& NewEvent)
{
    if (NewEvent)
    {
        const ChannelEvent::Type NewEventType = NewEvent->GetChannelType();
        events[NewEventType].emplace_back(std::move(NewEvent));
    }
}

void EventDispatcher::RemoveEvent(EventCaller* eventCaller, const std::string& eventSID)
{
    auto UIDable = dynamic_cast<UIDInterface*>(eventCaller);
    if (UIDable)
    {
        RemoveEvent(UIDable->GetUID(), eventSID);
    }
}

void EventDispatcher::RemoveEvent(size_t ownerUID, const std::string& eventSID)
{
    for (auto& a : events)
    {
        for (auto& i : a.second)
        {
            if (i->GetOwnerUID() == ownerUID && i->GetSid() == eventSID)
            {
                i->bDirty = true;
            }
        }
    }
}

void EventDispatcher::LeaveChannel(ChannelEvent::Type channelType, size_t ownerUID)
{
    for (auto& a : events)
    {
        if (IsFlagOn(channelType, a.first))
        for (auto& i : a.second)
        {
            if (i && !i->bDirty && i->GetOwnerUID() == ownerUID)
            {
                i->bDirty = true;
            }
        }
    }
}

void EventDispatcher::AddFutureEvent(Event* futureEvent)
{
    futureEvents.emplace_back(std::unique_ptr<Event>(futureEvent));
}
