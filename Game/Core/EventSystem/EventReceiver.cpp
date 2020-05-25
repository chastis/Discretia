#include <Core/EventSystem/EventReceiver.h>
#include <Core/EventSystem/EventCaller.h>
#include <Core/Singletons/EntityManager.h>
#include <Core/Entity.h>
#include <Core/Interfaces/UIDInterface.h>

EventReceiver::EventReceiver(const std::string& inSid, ChannelEventType inChannelType, EventCaller* eventCaller) : sid(inSid), channelType(inChannelType), ownerEventCaller(eventCaller)
{}

const std::string& EventReceiver::GetSid() const
{
    return sid;
}

const ChannelEventType& EventReceiver::GetChannelType() const
{
    return channelType;
}

size_t EventReceiver::GetOwnerUID() const
{
    auto UIDableOwner = dynamic_cast<UIDInterface*>(ownerEventCaller);
    if (UIDableOwner)
    {
        return UIDableOwner->GetUID();
    }
    else
    {
        __debugbreak();
    }
    return -1;
}

void EventReceiver::Receive(Event& inEvent)
{
    if (ownerEventCaller)
    {
        ownerEventCaller->GetEventFunction(sid)(ownerEventCaller, inEvent);
    }
}
