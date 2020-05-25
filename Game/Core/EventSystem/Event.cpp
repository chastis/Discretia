#include <Core/EventSystem/Event.h>
#include <Core/Consts/Misc.h>

SFMLEvent::SFMLEvent(sf::Event inEvent)
{
    auto thisSFML = dynamic_cast<sf::Event*>(this);
    *thisSFML = inEvent;
    channelType = Misc::GetChannelTypeFromSFML(inEvent.type);
}
