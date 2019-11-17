// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Utils/TestUtils.hpp>
#include "gtest/gtest.h"

#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Models/Minion.hpp>
#include <Rosetta/Models/Weapon.hpp>
#include <Rosetta/Tasks/SimpleTasks/DestroyTask.hpp>
#include <Rosetta/Zones/FieldZone.hpp>

using namespace RosettaStone;
using namespace SimpleTasks;
using namespace TestUtils;

TEST(DestroyTask, Run)
{
    GameConfig config;
    config.player1Class = CardClass::SHAMAN;
    config.player2Class = CardClass::WARLOCK;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();

    Player* player1 = game.GetPlayer1();
    Player* player2 = game.GetPlayer2();

    auto& p1Field = *(player1->GetFieldZone());
    auto& p2Field = *(player2->GetFieldZone());

    auto card = GenerateMinionCard("minion1", 1, 1);
    const std::map<GameTag, int> tags;

    // Destroy Source Minion
    const auto minion1 = new Minion(player1, &card, tags);
    minion1->player = player1;
    p1Field.Add(minion1, 0);

    DestroyTask task1(EntityType::SOURCE);
    task1.SetPlayer(player1);
    task1.SetSource(p1Field[0]);

    TaskStatus result = task1.Run();
    game.ProcessDestroyAndUpdateAura();

    EXPECT_EQ(result, TaskStatus::COMPLETE);
    EXPECT_EQ(p1Field.GetCount(), 0);

    // Destroy Target Minion
    const auto minion2 = new Minion(player2, &card, tags);
    minion2->player = player2;
    p2Field.Add(minion2, 0);

    DestroyTask task2(EntityType::TARGET);
    task2.SetPlayer(player1);
    task2.SetTarget(p2Field[0]);

    TaskStatus result2 = task2.Run();
    game.ProcessDestroyAndUpdateAura();

    EXPECT_EQ(result2, TaskStatus::COMPLETE);
    EXPECT_EQ(p2Field.GetCount(), 0);

    // Destroy Target Weapon
    Card weaponCard;
    player2->GetHero()->weapon = new Weapon(player2, &weaponCard, tags);
    player2->GetWeapon().player = player2;

    DestroyTask task3(EntityType::ENEMY_WEAPON);
    task3.SetPlayer(player1);

    TaskStatus result3 = task3.Run();
    game.ProcessDestroyAndUpdateAura();

    EXPECT_EQ(result3, TaskStatus::COMPLETE);
    EXPECT_EQ(player2->GetHero()->HasWeapon(), false);
}
