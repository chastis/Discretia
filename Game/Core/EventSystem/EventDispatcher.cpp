#include <Core/EventSystem/EventDispatcher.h>

void EventDispatcher::Dispatch(Event& inEvent)
{
    // todo gamnokod
    for (auto& a : events)
    {
        for (auto& b : a.second)
        {
            if (b)
                b->Receive(inEvent);
        }
    }
}

void EventDispatcher::JoinEvent(EventReceiver* NewEvent)
{
    if (NewEvent)
    {
        const ChannelEventType NewEventType = NewEvent->GetChannelType();
        events[NewEventType].emplace_back(std::unique_ptr<EventReceiver>(NewEvent));
    }
}

void EventDispatcher::JoinEvent(std::unique_ptr<EventReceiver>&& NewEvent)
{
    if (NewEvent)
    {
        const ChannelEventType NewEventType = NewEvent->GetChannelType();
        events[NewEventType].emplace_back(std::move(NewEvent));
    }
}
