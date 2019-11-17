// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Utils/TestUtils.hpp>
#include "gtest/gtest.h"

#include <Rosetta/Actions/ActionParams.hpp>
#include <Rosetta/Actions/Draw.hpp>
#include <Rosetta/Cards/Cards.hpp>
#include <Rosetta/Commons/DeckCode.hpp>
#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Games/GameConfig.hpp>
#include <Rosetta/Games/GameManager.hpp>
#include <Rosetta/Tasks/PlayerTasks/AttackTask.hpp>
#include <Rosetta/Tasks/PlayerTasks/EndTurnTask.hpp>
#include <Rosetta/Tasks/PlayerTasks/PlayCardTask.hpp>
#include <Rosetta/Views/Board.hpp>

#include <effolkronium/random.hpp>

using Random = effolkronium::random_static;

using namespace RosettaStone;
using namespace PlayerTasks;

class TestActionParams : public ActionParams
{
 public:
    TestActionParams() = default;

    TestActionParams(const TestActionParams&) = delete;
    TestActionParams(TestActionParams&&) noexcept = delete;

    TestActionParams& operator=(const TestActionParams&) = delete;
    TestActionParams& operator=(TestActionParams&&) noexcept = delete;

    void Init(const Board& board)
    {
        m_board = &board;
        Initialize(m_board->GetCurPlayerStateRefView().GetActionValidGetter());
    }

    std::size_t GetNumber(ActionType actionType, ActionChoices& choices) final
    {
        if (actionType != ActionType::MAIN_ACTION)
        {
            if (choices.Size() == 1)
            {
                return choices.Get(0);
            }
        }

        const std::size_t count = choices.Size();
        const auto randIdx = Random::get<std::size_t>(0, count - 1);
        const int result = static_cast<int>(randIdx);

        return result;
    }

 private:
    const Board* m_board = nullptr;
};

TEST(Game, RefCopyFrom)
{
    GameConfig config1;
    config1.player1Class = CardClass::WARRIOR;
    config1.player2Class = CardClass::ROGUE;
    config1.startPlayer = PlayerType::PLAYER1;
    config1.doFillDecks = true;
    config1.autoRun = true;

    GameConfig config2;
    config2.player1Class = CardClass::MAGE;
    config2.player2Class = CardClass::HUNTER;
    config2.startPlayer = PlayerType::PLAYER2;
    config2.doFillDecks = true;
    config2.autoRun = false;

    Game* game1 = new Game(config1);
    game1->step = Step::BEGIN_DRAW;
    game1->nextStep = Step::MAIN_ACTION;

    Game* game2 = new Game(config2);
    game2->step = Step::FINAL_WRAPUP;
    game2->nextStep = Step::MAIN_COMBAT;

    game1->RefCopyFrom(*game2);
    EXPECT_EQ(game1->step, Step::FINAL_WRAPUP);
    EXPECT_EQ(game1->nextStep, Step::MAIN_COMBAT);

    delete game1;
}

TEST(Game, GetPlayers)
{
    GameConfig config;
    config.player1Class = CardClass::WARRIOR;
    config.player2Class = CardClass::ROGUE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    const Game game(config);

    const Player* player1 = game.GetPlayer1();
    EXPECT_EQ(player1->playerType, PlayerType::PLAYER1);

    const Player* player2 = game.GetPlayer2();
    EXPECT_EQ(player2->playerType, PlayerType::PLAYER2);
}

TEST(Game, CurOpPlayer)
{
    GameConfig config;
    config.player1Class = CardClass::WARRIOR;
    config.player2Class = CardClass::ROGUE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game1;

    game1.SetCurrentPlayer(PlayerType::PLAYER2);
    EXPECT_EQ(game1.GetCurrentPlayer()->playerType, PlayerType::PLAYER2);
    EXPECT_EQ(game1.GetOpponentPlayer()->playerType, PlayerType::PLAYER1);

    const Game game2(config);

    EXPECT_EQ(game2.GetOpponentPlayer()->playerType, PlayerType::PLAYER2);

    config.startPlayer = PlayerType::PLAYER2;

    const Game game3(config);

    EXPECT_EQ(game3.GetOpponentPlayer()->playerType, PlayerType::PLAYER1);
}

TEST(Game, Turn)
{
    GameConfig config;
    config.player1Class = CardClass::WARRIOR;
    config.player2Class = CardClass::ROGUE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_START);

    auto* curPlayer = game.GetCurrentPlayer();
    auto* opPlayer = game.GetOpponentPlayer();

    EXPECT_EQ(game.GetTurn(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    EXPECT_EQ(game.GetTurn(), 2);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    EXPECT_EQ(game.GetTurn(), 3);

    game.SetTurn(30);
    EXPECT_EQ(game.GetTurn(), 30);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    EXPECT_EQ(game.GetTurn(), 31);
}

TEST(Game, GameOver_Player1Won)
{
    GameConfig config;
    config.player1Class = CardClass::WARRIOR;
    config.player2Class = CardClass::ROGUE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_START);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);
    opPlayer->GetHero()->SetDamage(29);

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, AttackTask(card1, opPlayer->GetHero()));

    EXPECT_EQ(game.state, State::COMPLETE);
    EXPECT_EQ(curPlayer->playState, PlayState::WON);
    EXPECT_EQ(opPlayer->playState, PlayState::LOST);
}

TEST(Game, GameOver_Player2Won)
{
    GameConfig config;
    config.player1Class = CardClass::WARRIOR;
    config.player2Class = CardClass::ROGUE;
    config.startPlayer = PlayerType::PLAYER2;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_START);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);
    opPlayer->GetHero()->SetDamage(29);

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, AttackTask(card1, opPlayer->GetHero()));

    EXPECT_EQ(game.state, State::COMPLETE);
    EXPECT_EQ(curPlayer->playState, PlayState::WON);
    EXPECT_EQ(opPlayer->playState, PlayState::LOST);
}

TEST(Game, GameOver_Tied)
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::ROGUE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_START);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);
    curPlayer->GetHero()->SetDamage(29);
    opPlayer->GetHero()->SetDamage(29);

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Hellfire"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));

    EXPECT_EQ(game.state, State::COMPLETE);
    EXPECT_EQ(curPlayer->playState, PlayState::TIED);
    EXPECT_EQ(opPlayer->playState, PlayState::TIED);
}

TEST(Game, PerformAction)
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::ROGUE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doShuffle = false;
    config.doFillDecks = false;
    config.skipMulligan = true;
    config.autoRun = true;

    const std::string INNKEEPER_EXPERT_WARLOCK =
        "AAEBAfqUAwAPMJMB3ALVA9AE9wTOBtwGkgeeB/sHsQjCCMQI9ggA";
    auto deck = DeckCode::Decode(INNKEEPER_EXPERT_WARLOCK).GetCardIDs();

    for (std::size_t j = 0; j < deck.size(); ++j)
    {
        config.player1Deck[j] = *Cards::FindCardByID(deck[j]);
        config.player2Deck[j] = *Cards::FindCardByID(deck[j]);
    }

    Game game(config);
    game.Start();
    game.MainReady();

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    while (game.state != State::COMPLETE)
    {
        TestActionParams params;
        Board board(game, game.GetCurrentPlayer()->playerType);

        params.Init(board);
        board.ApplyAction(params);
    }

    EXPECT_EQ(game.state, State::COMPLETE);
    EXPECT_TRUE(game.GetPlayer1()->playState == PlayState::WON ||
                game.GetPlayer1()->playState == PlayState::LOST);
    EXPECT_TRUE(game.GetPlayer2()->playState == PlayState::WON ||
                game.GetPlayer2()->playState == PlayState::LOST);
}

TEST(Game, CreateView)
{
    GameConfig config;
    config.player1Class = CardClass::WARRIOR;
    config.player2Class = CardClass::ROGUE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_START);

    const auto player1View = game.CreateView();
    EXPECT_EQ(player1View.GetMyHeroPower().cardID, "CS2_102");

    game.Process(game.GetCurrentPlayer(), EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    const auto player2View = game.CreateView();
    EXPECT_EQ(player2View.GetMyHeroPower().cardID, "CS2_083b");
}