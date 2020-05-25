#include <Core/EventSystem/EventCaller.h>


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
