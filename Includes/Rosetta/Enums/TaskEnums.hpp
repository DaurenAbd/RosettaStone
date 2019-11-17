// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_TASK_ENUMS_HPP
#define ROSETTASTONE_TASK_ENUMS_HPP

namespace RosettaStone
{
//! \breif An enumerator for identifying power type.
enum class PowerType
{
    POWER,
    DEATHRATTLE,
    COMBO
};

//! \brief An enumerator for identifying entity type.
enum class EntityType
{
    EMPTY,
    SOURCE,
    TARGET,
    ALL,
    ALL_NOSOURCE,
    FRIENDS,
    ENEMIES,
    ENEMIES_NOTARGET,
    HERO,
    ENEMY_HERO,
    WEAPON,
    ENEMY_WEAPON,
    HAND,
    ENEMY_HAND,
    DECK,
    ENEMY_DECK,
    ALL_MINIONS,
    ALL_MINIONS_NOSOURCE,
    MINIONS,
    MINIONS_NOSOURCE,
    ENEMY_MINIONS,
    STACK,
    PLAYER,
    ENEMY_PLAYER
};

//! \brief An enumerator for evaluating the relation between primitive values
//! during game simulation.
enum class RelaSign
{
    EQ,   //!< Equal.
    GEQ,  //!< Greater equal.
    LEQ   //!< Lesser equal.
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_TASK_ENUMS_HPP
