#pragma once

enum class ChannelEventType
{
    None = 0,
    Application = 1 << 0,
    Keyboard = 1 << 1,
    Mouse = 1 << 2
};