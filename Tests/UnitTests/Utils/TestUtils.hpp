// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef UNIT_TESTS_TEST_UTILS_HPP
#define UNIT_TESTS_TEST_UTILS_HPP

#include <Rosetta/Cards/Card.hpp>

using namespace RosettaStone;

namespace TestUtils
{
Card GenerateMinionCard(std::string&& id, int attack, int health);
Card GenerateWeaponCard(std::string&& id, int attack, int durability);
Card GenerateEnchantmentCard(std::string&& id);

void PlayMinionCard(Player* player, Card* card);
void PlayWeaponCard(Player* player, Card* card);
void PlayEnchantmentCard(Player* player, Card* card, Entity* target);

void ExpectCardEqual(const Card& card1, const Card& card2);
}  // namespace TestUtils

#endif  // UNIT_TESTS_TEST_UTILS_HPP
