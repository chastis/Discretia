#include <Core/Consts/Misc.h>

ChannelEvent::Type Misc::GetChannelTypeFromSFML(sf::Event::EventType SFMLType)
{
    switch (SFMLType)
    {
    case sf::Event::Closed:
    case sf::Event::Resized:
    case sf::Event::LostFocus:
    case sf::Event::GainedFocus:
    case sf::Event::TextEntered:
    {
        return ChannelEvent::Type::Application;
    }
    case sf::Event::KeyPressed:
    case sf::Event::KeyReleased:
    {
        return ChannelEvent::Type::Keyboard;
    }
    case sf::Event::MouseWheelMoved:
    case sf::Event::MouseWheelScrolled:
    case sf::Event::MouseButtonPressed:
    case sf::Event::MouseButtonReleased:
    case sf::Event::MouseMoved:
    case sf::Event::MouseEntered:
    case sf::Event::MouseLeft:
    {
        return ChannelEvent::Type::Mouse;
    }
    case sf::Event::JoystickButtonPressed:
    case sf::Event::JoystickButtonReleased:
    case sf::Event::JoystickMoved:
    case sf::Event::JoystickConnected:
    case sf::Event::JoystickDisconnected:
    case sf::Event::TouchBegan:
    case sf::Event::TouchMoved:
    case sf::Event::TouchEnded:
    case sf::Event::SensorChanged:
    case sf::Event::Count:
    default:
    {
        return ChannelEvent::Type::None;
    }
    }
}

