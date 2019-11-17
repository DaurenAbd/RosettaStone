// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Utils/TestUtils.hpp>
#include "gtest/gtest.h"

#include <Rosetta/Cards/Cards.hpp>
#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Tasks/SimpleTasks/IncludeTask.hpp>
#include <Rosetta/Zones/FieldZone.hpp>

using namespace RosettaStone;
using namespace SimpleTasks;
using namespace TestUtils;

TEST(IncludeTask, Run_NonConst)
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::PALADIN;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_START);

    Player* player1 = game.GetPlayer1();
    Player* player2 = game.GetPlayer2();

    auto& player1Field = *(player1->GetFieldZone());
    auto& player2Field = *(player2->GetFieldZone());

    const auto weapon1 = dynamic_cast<Weapon*>(
        Entity::GetFromCard(player1, Cards::FindCardByName("Fiery War Axe")));
    player1->GetHero()->AddWeapon(*weapon1);

    const auto weapon2 = dynamic_cast<Weapon*>(
        Entity::GetFromCard(player2, Cards::FindCardByName("Arcanite Reaper")));
    player2->GetHero()->AddWeapon(*weapon2);

    for (std::size_t i = 0; i < 6; ++i)
    {
        Playable* playable1 =
            Entity::GetFromCard(player1, Cards::FindCardByName("Flame Imp"),
                                std::nullopt, player1->GetFieldZone());
        player1->GetFieldZone()->Add(playable1);
    }

    for (std::size_t i = 0; i < 4; ++i)
    {
        Playable* playable2 =
            Entity::GetFromCard(player2, Cards::FindCardByName("Worthless Imp"),
                                std::nullopt, player2->GetFieldZone());
        player2->GetFieldZone()->Add(playable2);
    }

    const auto entities1 =
        IncludeTask::GetEntities(EntityType::SOURCE, player1, player1Field[0]);
    EXPECT_EQ(entities1.size(), 1u);
    EXPECT_EQ(entities1[0]->card->name, "Flame Imp");

    const auto entities2 = IncludeTask::GetEntities(EntityType::TARGET, player1,
                                                    nullptr, player2Field[0]);
    EXPECT_EQ(entities2.size(), 1u);
    EXPECT_EQ(entities2[0]->card->name, "Worthless Imp");

    const auto entities3 = IncludeTask::GetEntities(EntityType::ALL, player1);
    EXPECT_EQ(entities3.size(), 12u);

    const auto entities4_1 = IncludeTask::GetEntities(EntityType::ALL_NOSOURCE,
                                                      player1, player1Field[0]);
    EXPECT_EQ(entities4_1.size(), 11u);

    const auto entities4_2 = IncludeTask::GetEntities(EntityType::ALL_NOSOURCE,
                                                      player1, player2Field[0]);
    EXPECT_EQ(entities4_2.size(), 11u);

    const auto entities5 =
        IncludeTask::GetEntities(EntityType::FRIENDS, player1);
    EXPECT_EQ(entities5.size(), 7u);

    const auto entities6 =
        IncludeTask::GetEntities(EntityType::ENEMIES, player1);
    EXPECT_EQ(entities6.size(), 5u);

    const auto entities7_1 = IncludeTask::GetEntities(
        EntityType::ENEMIES_NOTARGET, player1, nullptr, player2->GetHero());
    EXPECT_EQ(entities7_1.size(), 4u);

    const auto entities7_2 = IncludeTask::GetEntities(
        EntityType::ENEMIES_NOTARGET, player1, nullptr, player2->GetHero());
    EXPECT_EQ(entities7_2.size(), 4u);

    const auto entities8 = IncludeTask::GetEntities(EntityType::HERO, player1);
    EXPECT_EQ(entities8.size(), 1u);
    EXPECT_EQ(entities8[0]->card->GetCardClass(), CardClass::WARLOCK);

    const auto entities9 =
        IncludeTask::GetEntities(EntityType::ENEMY_HERO, player1);
    EXPECT_EQ(entities9.size(), 1u);
    EXPECT_EQ(entities9[0]->card->GetCardClass(), CardClass::PALADIN);

    const auto entities10 =
        IncludeTask::GetEntities(EntityType::WEAPON, player1);
    EXPECT_EQ(entities10.size(), 1u);
    EXPECT_EQ(entities10[0]->card->name, "Fiery War Axe");

    const auto entities11 =
        IncludeTask::GetEntities(EntityType::ENEMY_WEAPON, player1);
    EXPECT_EQ(entities11.size(), 1u);
    EXPECT_EQ(entities11[0]->card->name, "Arcanite Reaper");

    const auto entities12 = IncludeTask::GetEntities(EntityType::HAND, player1);
    EXPECT_EQ(entities12.size(), 4u);

    const auto entities13 =
        IncludeTask::GetEntities(EntityType::ENEMY_HAND, player1);
    EXPECT_EQ(entities13.size(), 5u);

    const auto entities14 = IncludeTask::GetEntities(EntityType::DECK, player1);
    EXPECT_EQ(entities14.size(), 5u);

    const auto entities15 =
        IncludeTask::GetEntities(EntityType::ENEMY_DECK, player1);
    EXPECT_EQ(entities15.size(), 5u);

    const auto entities16 =
        IncludeTask::GetEntities(EntityType::ALL_MINIONS, player1);
    EXPECT_EQ(entities16.size(), 10u);

    const auto entities17 = IncludeTask::GetEntities(
        EntityType::ALL_MINIONS_NOSOURCE, player1, player1Field[0]);
    EXPECT_EQ(entities17.size(), 9u);

    const auto entities18 =
        IncludeTask::GetEntities(EntityType::MINIONS, player1);
    EXPECT_EQ(entities18.size(), 6u);

    const auto entities19 = IncludeTask::GetEntities(
        EntityType::MINIONS_NOSOURCE, player1, player1Field[0]);
    EXPECT_EQ(entities19.size(), 5u);

    const auto entities20 =
        IncludeTask::GetEntities(EntityType::ENEMY_MINIONS, player1);
    EXPECT_EQ(entities20.size(), 4u);

    const auto entities21 =
        IncludeTask::GetEntities(EntityType::STACK, player1);
    EXPECT_EQ(entities21.size(), 0u);

    EXPECT_THROW(IncludeTask::GetEntities(EntityType::EMPTY, player1),
                 std::invalid_argument);
}

TEST(IncludeTask, Run_Const)
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::PALADIN;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_START);

    const Player* player1 = game.GetPlayer1();
    const Player* player2 = game.GetPlayer2();

    auto& player1Field = *(player1->GetFieldZone());
    auto& player2Field = *(player2->GetFieldZone());

    const auto weapon1 = dynamic_cast<Weapon*>(Entity::GetFromCard(
        const_cast<Player*>(player1), Cards::FindCardByName("Fiery War Axe")));
    player1->GetHero()->AddWeapon(*weapon1);

    const auto weapon2 = dynamic_cast<Weapon*>(
        Entity::GetFromCard(const_cast<Player*>(player2),
                            Cards::FindCardByName("Arcanite Reaper")));
    player2->GetHero()->AddWeapon(*weapon2);

    std::vector<Card> player1Cards, player2Cards;
    player1Cards.reserve(6);
    player2Cards.reserve(4);

    for (std::size_t i = 0; i < 6; ++i)
    {
        Playable* playable1 = Entity::GetFromCard(
            const_cast<Player*>(player1), Cards::FindCardByName("Flame Imp"),
            std::nullopt, player1->GetFieldZone());
        player1->GetFieldZone()->Add(playable1);
    }

    for (std::size_t i = 0; i < 4; ++i)
    {
        Playable* playable2 =
            Entity::GetFromCard(const_cast<Player*>(player2),
                                Cards::FindCardByName("Worthless Imp"),
                                std::nullopt, player2->GetFieldZone());
        player2->GetFieldZone()->Add(playable2);
    }

    const auto entities1 =
        IncludeTask::GetEntities(EntityType::SOURCE, player1, player1Field[0]);
    EXPECT_EQ(entities1.size(), 1u);
    EXPECT_EQ(entities1[0]->card->name, "Flame Imp");

    const auto entities2 = IncludeTask::GetEntities(EntityType::TARGET, player1,
                                                    nullptr, player2Field[0]);
    EXPECT_EQ(entities2.size(), 1u);
    EXPECT_EQ(entities2[0]->card->name, "Worthless Imp");

    const auto entities3 = IncludeTask::GetEntities(EntityType::ALL, player1);
    EXPECT_EQ(entities3.size(), 12u);

    const auto entities4_1 = IncludeTask::GetEntities(EntityType::ALL_NOSOURCE,
                                                      player1, player1Field[0]);
    EXPECT_EQ(entities4_1.size(), 11u);

    const auto entities4_2 = IncludeTask::GetEntities(EntityType::ALL_NOSOURCE,
                                                      player1, player2Field[0]);
    EXPECT_EQ(entities4_2.size(), 11u);

    const auto entities5 =
        IncludeTask::GetEntities(EntityType::FRIENDS, player1);
    EXPECT_EQ(entities5.size(), 7u);

    const auto entities6 =
        IncludeTask::GetEntities(EntityType::ENEMIES, player1);
    EXPECT_EQ(entities6.size(), 5u);

    const auto entities7_1 = IncludeTask::GetEntities(
        EntityType::ENEMIES_NOTARGET, player1, nullptr, player2->GetHero());
    EXPECT_EQ(entities7_1.size(), 4u);

    const auto entities7_2 = IncludeTask::GetEntities(
        EntityType::ENEMIES_NOTARGET, player1, nullptr, player2->GetHero());
    EXPECT_EQ(entities7_2.size(), 4u);

    const auto entities8 = IncludeTask::GetEntities(EntityType::HERO, player1);
    EXPECT_EQ(entities8.size(), 1u);
    EXPECT_EQ(entities8[0]->card->GetCardClass(), CardClass::WARLOCK);

    const auto entities9 =
        IncludeTask::GetEntities(EntityType::ENEMY_HERO, player1);
    EXPECT_EQ(entities9.size(), 1u);
    EXPECT_EQ(entities9[0]->card->GetCardClass(), CardClass::PALADIN);

    const auto entities10 =
        IncludeTask::GetEntities(EntityType::WEAPON, player1);
    EXPECT_EQ(entities10.size(), 1u);
    EXPECT_EQ(entities10[0]->card->name, "Fiery War Axe");

    const auto entities11 =
        IncludeTask::GetEntities(EntityType::ENEMY_WEAPON, player1);
    EXPECT_EQ(entities11.size(), 1u);
    EXPECT_EQ(entities11[0]->card->name, "Arcanite Reaper");

    const auto entities12 = IncludeTask::GetEntities(EntityType::HAND, player1);
    EXPECT_EQ(entities12.size(), 4u);

    const auto entities13 =
        IncludeTask::GetEntities(EntityType::ENEMY_HAND, player1);
    EXPECT_EQ(entities13.size(), 5u);

    const auto entities14 = IncludeTask::GetEntities(EntityType::DECK, player1);
    EXPECT_EQ(entities14.size(), 5u);

    const auto entities15 =
        IncludeTask::GetEntities(EntityType::ENEMY_DECK, player1);
    EXPECT_EQ(entities15.size(), 5u);

    const auto entities16 =
        IncludeTask::GetEntities(EntityType::ALL_MINIONS, player1);
    EXPECT_EQ(entities16.size(), 10u);

    const auto entities17 = IncludeTask::GetEntities(
        EntityType::ALL_MINIONS_NOSOURCE, player1, player1Field[0]);
    EXPECT_EQ(entities17.size(), 9u);

    const auto entities18 =
        IncludeTask::GetEntities(EntityType::MINIONS, player1);
    EXPECT_EQ(entities18.size(), 6u);

    const auto entities19 = IncludeTask::GetEntities(
        EntityType::MINIONS_NOSOURCE, player1, player1Field[0]);
    EXPECT_EQ(entities19.size(), 5u);

    const auto entities20 =
        IncludeTask::GetEntities(EntityType::ENEMY_MINIONS, player1);
    EXPECT_EQ(entities20.size(), 4u);

    const auto entities21 =
        IncludeTask::GetEntities(EntityType::STACK, player1);
    EXPECT_EQ(entities21.size(), 0u);

    EXPECT_THROW(IncludeTask::GetEntities(EntityType::EMPTY, player1),
                 std::invalid_argument);
}
