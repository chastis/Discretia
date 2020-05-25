#pragma once

#include <Core/EventSystem/Event.h>
#include <Core/Interfaces/PrototypeableInterface.h>
#include <Core/CoreDefs.h>
#include <SFML/Graphics.hpp>
#include <map>

class EventCaller;

using EventFunction = std::function<void(EventCaller*, Event&)>;
using EventFunctionsMap = std::map<std::string, EventFunction>;

template<class T>
class EventFunctionHandler
{
public:
    EventFunctionHandler();
    [[nodiscard]] static EventFunctionsMap* GetEventFunctions();
    [[nodiscard]] static const EventFunction& GetDefault();
    [[nodiscard]] static const EventFunction& GetFunction(const std::string& functionSID);
protected:
    static EventFunctionsMap eventFunctions;
};

template<class T>
EventFunctionsMap EventFunctionHandler<T>::eventFunctions;

template <class T>
EventFunctionHandler<T>::EventFunctionHandler()
{
    eventFunctions.emplace("default", [](EventCaller* eventCaller, Event& inEvent) { __debugbreak(); });
}

template <class T>
EventFunctionsMap* EventFunctionHandler<T>::GetEventFunctions()
{
    return &eventFunctions;
}

template <class T>
const EventFunction& EventFunctionHandler<T>::GetDefault()
{
    auto eventFunctionIt = eventFunctions.find("default");
    if (eventFunctionIt == eventFunctions.end())
    {
        eventFunctions.emplace("default", [](EventCaller* eventCaller, Event& inEvent) { __debugbreak(); });
        eventFunctionIt = eventFunctions.find("default");
    }
    return eventFunctionIt->second;
}

template <class T>
const EventFunction& EventFunctionHandler<T>::GetFunction(const std::string& functionSID)
{
    auto eventFunctionIt = eventFunctions.find(functionSID);
    if (eventFunctionIt == eventFunctions.end())
    {
        eventFunctionIt = eventFunctions.begin();
        __debugbreak();
    }
    return GetDefault();
}

class CORE_API EventCaller
{
public:
    virtual ~EventCaller() = default;
    [[nodiscard]] const EventFunction& GetEventFunction(const std::string& functionSID) const;
    virtual void InitEventFunctions() = 0;

protected:
    EventFunctionsMap* eventFunctions = nullptr;
};
