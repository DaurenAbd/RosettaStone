// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_ATTACK_HPP
#define ROSETTASTONE_ATTACK_HPP

#include <Rosetta/Models/Player.hpp>

namespace RosettaStone::Generic
{
//! Source character attacks target character.
//! \param player An owner of source character.
//! \param source A pointer to source character.
//! \param target A pointer to target character.
void Attack(Player* player, Character* source, Character* target);
}  // namespace RosettaStone::Generic

#endif  // ROSETTASTONE_ATTACK_HPP
