#pragma once

#define IsFlagOn(CheckedEnum, FlagValue) (static_cast<bool>(CheckedEnum&(FlagValue)))

#define AreAllFlagsOn(CheckedEnum, FlagValue) ((CheckedEnum&(FlagValue))==FlagValue)

#define SetFlagOn(EnumValue, FlagValue) (EnumValue |= FlagValue)

namespace ChannelEvent
{
    enum Type
    {
        None = 0,
        Application = 1 << 0,
        Keyboard = 1 << 1,
        Mouse = 1 << 2,
        Custom = 1 << 3,

        All = None | Application | Keyboard | Mouse | Custom
    };
}

enum class EntityTypes
{
    Core = 0,
    Basic,
    Advanced
};

enum class CollisionTypes
{
    None = 0,
    Box
};

enum class DiscreteOperations
{
    None = 0,
    Intersection = 1,
    Union = 2,
    Complement = 3,
    AbsoluteComplement = 4,
    SymmetricDifference = 5
};