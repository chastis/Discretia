#include <Core/EventSystem/EventCaller.h>

size_t EventCaller::maxPriority = 1;

const EventFunction& EventCaller::GetEventFunction(const std::string& functionSID) const
{
    if (eventFunctions)
    {
        const auto it = eventFunctions->find(functionSID);
        if (it != eventFunctions->end())
        {
            return it->second;
        }
    }
    __debugbreak();
    return EventFunctionHandler<EventCaller>::GetDefault();
}

bool EventCaller::IsFunctionExist(const std::string& functionSID)
{
    if (eventFunctions)
    {
        return eventFunctions->find(functionSID) != eventFunctions->end();
    }
    __debugbreak();
    return false;
}

void EventCaller::ChangePriorityToMax()
{
    if (priority!=maxPriority)
    {
        priority = maxPriority++;
    }
}

