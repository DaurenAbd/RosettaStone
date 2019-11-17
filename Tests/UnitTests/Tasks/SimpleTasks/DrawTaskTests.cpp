// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "gtest/gtest.h"

#include <Rosetta/Cards/Cards.hpp>
#include <Rosetta/Commons/Utils.hpp>
#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Tasks/SimpleTasks/DrawTask.hpp>
#include <Rosetta/Zones/DeckZone.hpp>
#include <Rosetta/Zones/HandZone.hpp>

using namespace RosettaStone;
using namespace SimpleTasks;

TEST(DrawTask, Run)
{
    std::vector<Card*> cards;
    std::vector<Playable*> minions;

    GameConfig config;
    config.startPlayer = PlayerType::PLAYER1;
    Game game(config);

    Player* player = game.GetPlayer1();
    auto& playerHand = *(player->GetHandZone());
    auto& playerDeck = *(player->GetDeckZone());

    const auto Generate = [&](std::string&& id) -> Playable* {
        cards.emplace_back(new Card());

        Card* card = cards.back();
        card->id = std::move(id);
        const std::map<GameTag, int> tags;

        minions.emplace_back(new Minion(player, card, tags));

        return minions.back();
    };

    const std::string id = "card";
    for (char i = '0'; i < '3'; ++i)
    {
        playerDeck.Add(Generate(id + i));
    }

    DrawTask draw(3);
    draw.SetPlayer(player);

    TaskStatus result = draw.Run();
    EXPECT_EQ(result, TaskStatus::COMPLETE);
    EXPECT_EQ(playerHand.GetCount(), 3);

    for (std::size_t i = 0; i < 3; ++i)
    {
        EXPECT_EQ(playerHand[i]->card->id,
                  id + static_cast<char>(2 - i + 0x30));
    }

    for (Card* card : cards)
    {
        delete card;
    }
}

TEST(DrawTask, RunExhaust)
{
    GameConfig config;
    config.startPlayer = PlayerType::PLAYER1;
    Game game(config);

    Player* player = game.GetPlayer1();
    auto& playerHand = *(player->GetHandZone());
    auto& playerDeck = *(player->GetDeckZone());

    EXPECT_EQ(playerDeck.GetCount(), 0);

    DrawTask draw(3);
    draw.SetPlayer(game.GetPlayer1());

    TaskStatus result = draw.Run();
    EXPECT_EQ(result, TaskStatus::COMPLETE);
    EXPECT_EQ(playerHand.GetCount(), 0);
    EXPECT_EQ(playerDeck.GetCount(), 0);
    // Health: 30 - (1 + 2 + 3)
    EXPECT_EQ(player->GetHero()->GetHealth(), 24);

    Card card;
    card.id = "card1";
    const std::map<GameTag, int> tags;

    const auto minion = new Minion(player, &card, tags);
    playerDeck.Add(minion);

    result = draw.Run();
    EXPECT_EQ(result, TaskStatus::COMPLETE);
    EXPECT_EQ(playerHand.GetCount(), 1);
    EXPECT_EQ(playerHand[0]->card->id, "card1");
    EXPECT_EQ(playerDeck.GetCount(), 0);
    // Health: 30 - (1 + 2 + 3 + 4 + 5)
    EXPECT_EQ(player->GetHero()->GetHealth(), 15);
}

TEST(DrawTask, RunOverDraw)
{
    std::vector<Card*> cards;
    std::vector<Playable*> minions;

    GameConfig config;
    config.startPlayer = PlayerType::PLAYER1;
    Game game(config);

    Player* player = game.GetPlayer1();
    auto& playerHand = *(player->GetHandZone());
    auto& playerDeck = *(player->GetDeckZone());

    const auto Generate = [&](std::string&& id) -> Playable* {
        cards.emplace_back(new Card());

        Card* card = cards.back();
        card->id = std::move(id);
        const std::map<GameTag, int> tags;

        minions.emplace_back(new Minion(player, card, tags));

        return minions.back();
    };

    const std::string id = "card";
    for (char i = '0'; i <= '2'; ++i)
    {
        playerDeck.Add(Generate(id + i));
    }
    for (char i = '0'; i <= '9'; ++i)
    {
        playerHand.Add(Generate(id + i));
    }

    DrawTask draw(3);
    draw.SetPlayer(player);

    TaskStatus result = draw.Run();
    EXPECT_EQ(result, TaskStatus::COMPLETE);
    EXPECT_EQ(playerDeck.GetCount(), 0);
    EXPECT_EQ(playerHand.GetCount(), 10);

    for (Card* card : cards)
    {
        delete card;
    }
}

TEST(DrawTask, RunExhaustOverdraw)
{
    std::vector<Card*> cards;
    std::vector<Playable*> minions;

    GameConfig config;
    config.startPlayer = PlayerType::PLAYER1;
    Game game(config);

    Player* player = game.GetPlayer1();
    auto& playerHand = *(player->GetHandZone());
    auto& playerDeck = *(player->GetDeckZone());

    const auto Generate = [&](std::string&& id) -> Playable* {
        cards.emplace_back(new Card());

        Card* card = cards.back();
        card->id = std::move(id);
        const std::map<GameTag, int> tags;

        minions.emplace_back(new Minion(player, card, tags));
        return minions.back();
    };

    const std::string id = "card";
    for (char i = '0'; i <= '2'; ++i)
    {
        playerDeck.Add(Generate(id + i));
    }
    for (char i = '0'; i <= '8'; ++i)
    {
        playerHand.Add(Generate(id + i));
    }

    DrawTask draw(4);
    draw.SetPlayer(player);

    TaskStatus result = draw.Run();
    EXPECT_EQ(result, TaskStatus::COMPLETE);
    EXPECT_EQ(playerDeck.GetCount(), 0);
    EXPECT_EQ(playerHand.GetCount(), 10);
    EXPECT_EQ(playerHand[9]->card->id, "card2");

    for (Card* card : cards)
    {
        delete card;
    }
}