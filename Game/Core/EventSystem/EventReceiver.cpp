#include <Core/EventSystem/EventReceiver.h>
#include <Core/EventSystem/EventCaller.h>
#include <Core/Singletons/EntityManager.h>
#include <Core/Entity.h>
#include <Core/Interfaces/UIDInterface.h>

EventReceiver::EventReceiver(const std::string& inSid, ChannelEvent::Type inChannelType, EventCaller* eventCaller) : sid(inSid), channelType(inChannelType), ownerEventCaller(eventCaller)
{}

const std::string& EventReceiver::GetSid() const
{
    return sid;
}

const ChannelEvent::Type& EventReceiver::GetChannelType() const
{
    return channelType;
}

EventCaller* EventReceiver::GetOwner() const
{
    return ownerEventCaller;
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
        //__debugbreak();
    }
    return -1;
}

bool EventReceiver::Receive(Event& inEvent)
{
    if (ownerEventCaller)
    {
        return ownerEventCaller->GetEventFunction(sid)(ownerEventCaller, inEvent);
    }
    return false;
}

bool EventReceiver::ReceiveCanceled(class Event& inEvent)
{
    if (ownerEventCaller)
    {
        if (ownerEventCaller->IsFunctionExist("!"+sid))
        {
            return ownerEventCaller->GetEventFunction("!"+sid)(ownerEventCaller, inEvent);
        }
    }
    return false;
}