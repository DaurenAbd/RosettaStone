﻿// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Utils/CardSetUtils.hpp>

#include <Rosetta/Actions/Draw.hpp>
#include <Rosetta/Cards/Cards.hpp>
#include <Rosetta/Zones/FieldZone.hpp>
#include <Rosetta/Zones/HandZone.hpp>

using namespace RosettaStone;
using namespace PlayerTasks;
using namespace SimpleTasks;

// ------------------------------------------ SPELL - DRUID
// [EX1_161] Naturalize - COST:1
// - Faction: Neutral, Set: HoF, Rarity: Common
// --------------------------------------------------------
// Text: Destroy a minion.
//       Your opponent draws 2 cards.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST(DruidHoFTest, EX1_161_Naturalize)
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
    config.player2Class = CardClass::DRUID;
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

    const auto card1 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Naturalize"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Magma Rager"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    const auto curHandCount = curPlayer->GetHandZone()->GetCount();
    game.Process(opPlayer, PlayCardTask::SpellTarget(card1, card2));

    EXPECT_EQ(curPlayer->GetHandZone()->GetCount(), curHandCount + 2);
    EXPECT_EQ(curPlayer->GetFieldZone()->GetCount(), 0);
}

// ------------------------------------------- SPELL - MAGE
// [CS2_031] Ice Lance - COST:1
// - Faction: Neutral, Set: HoF, Rarity: Common
// --------------------------------------------------------
// Text: <b>Freeze</b> a character. If it was already <b>Frozen</b>,
//       deal 4 damage instead.
// --------------------------------------------------------
// GameTag:
// - FREEZE = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// --------------------------------------------------------
TEST(MageHoFTest, CS2_031_IceLance)
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
    config.player2Class = CardClass::DRUID;
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

    const auto card1 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Ice Lance"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Ice Lance"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Ice Lance"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Ice Lance"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Bloodmage Thalnos"));
    const auto card6 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Ancient Watcher"));
    const auto card7 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Ancient Watcher"));

    game.Process(curPlayer, PlayCardTask::Minion(card6));
    game.Process(curPlayer, PlayCardTask::Minion(card7));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card1, card6));
    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, card7));

    EXPECT_EQ(card6->GetGameTag(GameTag::FROZEN), 1);
    EXPECT_EQ(card7->GetGameTag(GameTag::FROZEN), 1);
    EXPECT_EQ(card6->GetGameTag(GameTag::DAMAGE), 0);
    EXPECT_EQ(card7->GetGameTag(GameTag::DAMAGE), 0);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card3, card6));

    EXPECT_EQ(card6->GetGameTag(GameTag::DAMAGE), 4);

    game.Process(opPlayer, PlayCardTask::Minion(card5));
    game.Process(opPlayer, PlayCardTask::SpellTarget(card4, card7));

    EXPECT_EQ(card7->isDestroyed, true);
}

// ----------------------------------------- SPELL - PRIEST
// [DS1_233] Mind Blast - COST:2
// - Faction: Neutral, Set: HoF, Rarity: Free
// --------------------------------------------------------
// Text: Deal 5 damage to the enemy hero.
// --------------------------------------------------------
TEST(PriestHoFTest, DS1_233_MindBlast)
{
    GameConfig config;
    config.player1Class = CardClass::PRIEST;
    config.player2Class = CardClass::PALADIN;
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Mind Blast"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    EXPECT_EQ(opPlayer->GetHero()->GetHealth(), 25);
}

// ------------------------------------------ SPELL - ROGUE
// [NEW1_004] Vanish - COST:6
// - Set: HoF, Rarity: Free
// --------------------------------------------------------
// Text: Return all minions to their owner's hand.
// --------------------------------------------------------
TEST(RogueHoFTest, NEW1_004_Vanish)
{
    GameConfig config;
    config.player1Class = CardClass::ROGUE;
    config.player2Class = CardClass::WARRIOR;
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

    auto& curField = *(curPlayer->GetFieldZone());
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Vanish"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Voidwalker"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    EXPECT_EQ(curPlayer->GetHandZone()->GetCount(), 5);
    EXPECT_EQ(curField.GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    EXPECT_EQ(opPlayer->GetHandZone()->GetCount(), 6);
    EXPECT_EQ(opField.GetCount(), 1);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    EXPECT_EQ(curPlayer->GetHandZone()->GetCount(), 6);
    EXPECT_EQ(curField.GetCount(), 0);
    EXPECT_EQ(opPlayer->GetHandZone()->GetCount(), 7);
    EXPECT_EQ(opField.GetCount(), 0);
}

// --------------------------------------- MINION - WARLOCK
// [EX1_310] Doomguard - COST:5 [ATK:5/HP:7]
// - Race: Demon, Set: HoF, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Charge</b>. <b>Battlecry:</b> Discard two random cards.
// --------------------------------------------------------
// GameTag:
// - CHARGE = 1
// - BATTLECRY = 1
// --------------------------------------------------------
TEST(WarlockHoFTest, EX1_310_Doomguard)
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::WARRIOR;
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Doomguard"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Acidic Swamp Ooze"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    EXPECT_EQ(curPlayer->GetHandZone()->GetCount(), 2);

    game.Process(curPlayer, AttackTask(card1, opPlayer->GetHero()));
    EXPECT_EQ(opPlayer->GetHero()->GetHealth(), 25);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    EXPECT_EQ(opPlayer->GetHandZone()->GetCount(), 6);
}

// ---------------------------------------- SPELL - WARLOCK
// [EX1_316] Power Overwhelming - COST:1
// - Faction: Neutral, Set: HoF, Rarity: Common
// --------------------------------------------------------
// Text: Give a friendly minion +4/+4 until end of turn.
//       Then, it dies. Horribly.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// - REQ_FRIENDLY_TARGET = 0
// --------------------------------------------------------
TEST(WarlockHoFTest, EX1_316_PowerOverwhelming)
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::WARRIOR;
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

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Power Overwhelming"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Goldshire Footman"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("King Mukla"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    game.Process(opPlayer, PlayCardTask::Minion(card3));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card2));
    game.Process(curPlayer, AttackTask(card2, card3));

    EXPECT_EQ(curField[0]->GetHealth(), 1);
    EXPECT_EQ(opPlayer->GetFieldZone()->GetCount(), 0);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    EXPECT_EQ(curPlayer->GetFieldZone()->GetCount(), 0);
}

// --------------------------------------- MINION - NEUTRAL
// [EX1_016] Sylvanas Windrunner - COST:6 [ATK:5/HP:5]
// - Set: HoF, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> Take control of a random enemy minion.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST(NeutralHoFTest, EX1_016_SylvanasWindrunner)
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
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Sylvanas Windrunner"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Magma Rager"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Oasis Snapjaw"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    game.Process(opPlayer, PlayCardTask::Minion(card3));
    game.Process(opPlayer, PlayCardTask::Minion(card4));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    game.Process(curPlayer, AttackTask(card1, card2));
    EXPECT_EQ(curPlayer->GetFieldZone()->GetCount(), 1);
    EXPECT_EQ(opPlayer->GetFieldZone()->GetCount(), 1);
}

// --------------------------------------- MINION - NEUTRAL
// [EX1_050] Coldlight Oracle - COST:3 [ATK:2/HP:2]
// - Faction: Neutral, Set: HoF, Rarity: Free
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Each player draws 2 cards.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST(NeutralHoFTest, EX1_050_ColdlightOracle)
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
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    const auto card =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Coldlight Oracle"));
    EXPECT_EQ(curPlayer->GetHandZone()->GetCount(), 5);

    game.Process(curPlayer, PlayCardTask::Minion(card));
    EXPECT_EQ(curPlayer->GetHandZone()->GetCount(), 6);
    EXPECT_EQ(opPlayer->GetHandZone()->GetCount(), 7);
}

// --------------------------------------- MINION - NEUTRAL
// [EX1_284] Azure Drake - COST:5 [ATK:4/HP:4]
// - Race: Dragon, Faction: Neutral, Set: HoF, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Spell Damage +1</b>
//       <b>Battlecry:</b> Draw a card.
// --------------------------------------------------------
// GameTag:
// - SPELLPOWER = 1
// - BATTLECRY = 1
// --------------------------------------------------------
TEST(NeutralHoFTest, EX1_284_AzureDrake)
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
    config.player2Class = CardClass::PALADIN;
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Azure Drake"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Archmage"));

    const auto curHandCount = curPlayer->GetHandZone()->GetCount();

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    EXPECT_EQ(curPlayer->GetHandZone()->GetCount(), curHandCount);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    game.Process(opPlayer, PlayCardTask::Minion(card3));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card2, card3));

    EXPECT_EQ(curPlayer->GetFieldZone()->GetCount(), 1);
    EXPECT_EQ(opPlayer->GetFieldZone()->GetCount(), 0);
}