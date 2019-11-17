// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "gtest/gtest.h"

#include <Rosetta/Actions/Choose.hpp>
#include <Rosetta/Enums/CardEnums.hpp>
#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Zones/HandZone.hpp>

using namespace RosettaStone;

TEST(Choose, ChoiceMulligan)
{
    GameConfig config;
    config.player1Class = CardClass::ROGUE;
    config.player2Class = CardClass::PALADIN;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_START);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();

    const std::vector<std::size_t> curChoices, opChoices;

    Choice curChoice, opChoice;

    curChoice.choiceAction = ChoiceAction::HAND;
    curChoice.choices = curChoices;
    curChoice.choiceType = ChoiceType::MULLIGAN;

    opChoice.choiceAction = ChoiceAction::HAND;
    opChoice.choices = opChoices;
    opChoice.choiceType = ChoiceType::MULLIGAN;

    curPlayer->choice = curChoice;
    opPlayer->choice = opChoice;

    int curHandCount = curPlayer->GetHandZone()->GetCount();
    int opHandCount = opPlayer->GetHandZone()->GetCount();

    Generic::ChoiceMulligan(curPlayer, curChoices);
    Generic::ChoiceMulligan(opPlayer, opChoices);

    EXPECT_EQ(curHandCount, curPlayer->GetHandZone()->GetCount());
    EXPECT_EQ(opHandCount, opPlayer->GetHandZone()->GetCount());

    EXPECT_EQ(curPlayer->choice, std::nullopt);
    EXPECT_EQ(opPlayer->choice, std::nullopt);
}