// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Utils/TestUtils.hpp>
#include "gtest/gtest.h"

#include <Rosetta/Cards/Cards.hpp>
#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Tasks/SimpleTasks/DamageTask.hpp>
#include <Rosetta/Zones/FieldZone.hpp>

using namespace RosettaStone;
using namespace SimpleTasks;
using namespace TestUtils;

TEST(DamageTask, Run)
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

    std::vector<Card> cards;
    cards.reserve(5);

    const std::string name = "test";
    for (std::size_t i = 0; i < 5; ++i)
    {
        const auto id = static_cast<char>(i + 0x30);
        cards.emplace_back(GenerateMinionCard(name + id, 1, 1));
        PlayMinionCard(player1, &cards[i]);
    }

    DamageTask damage(EntityType::FRIENDS, 1);
    damage.SetPlayer(player1);

    Entity tempEntity;

    damage.SetSource(&tempEntity);

    TaskStatus result = damage.Run();
    game.ProcessDestroyAndUpdateAura();

    EXPECT_EQ(result, TaskStatus::COMPLETE);
    EXPECT_EQ(player1->GetFieldZone()->GetCount(), 0);
}

TEST(DamageTask, SpellPower)
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
    auto& p1Field = *(player1->GetFieldZone());

    std::vector<Card> cards;
    cards.reserve(5);

    const std::string name = "test";
    for (std::size_t i = 0; i < 5; ++i)
    {
        const auto id = static_cast<char>(i + 0x30);
        cards.emplace_back(GenerateMinionCard(name + id, 1, 5));
        PlayMinionCard(player1, &cards[i]);
    }

    DamageTask damage1(EntityType::FRIENDS, 1, true);
    damage1.SetPlayer(player1);
    damage1.SetSource(p1Field[0]);

    TaskStatus result = damage1.Run();
    game.ProcessDestroyAndUpdateAura();

    EXPECT_EQ(result, TaskStatus::COMPLETE);
    for (std::size_t i = 0; i < 5; ++i)
    {
        EXPECT_EQ(p1Field[i]->GetHealth(), 4);
    }

    player1->currentSpellPower = 1;

    DamageTask damage2(EntityType::FRIENDS, 1, true);
    damage2.SetPlayer(player1);
    damage2.SetSource(p1Field[0]);

    result = damage2.Run();
    game.ProcessDestroyAndUpdateAura();

    EXPECT_EQ(result, TaskStatus::COMPLETE);
    for (std::size_t i = 0; i < 5; ++i)
    {
        EXPECT_EQ(p1Field[i]->GetHealth(), 2);
    }
}