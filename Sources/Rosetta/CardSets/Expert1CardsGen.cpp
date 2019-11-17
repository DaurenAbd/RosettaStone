﻿// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Auras/AdaptiveCostEffect.hpp>
#include <Rosetta/Auras/AdaptiveEffect.hpp>
#include <Rosetta/Auras/AdjacentAura.hpp>
#include <Rosetta/Auras/EnrageEffect.hpp>
#include <Rosetta/Auras/SwitchingAura.hpp>
#include <Rosetta/CardSets/Expert1CardsGen.hpp>
#include <Rosetta/Cards/Cards.hpp>
#include <Rosetta/Enchants/Effects.hpp>
#include <Rosetta/Enchants/Enchants.hpp>
#include <Rosetta/Enchants/Triggers.hpp>
#include <Rosetta/Tasks/SimpleTasks/AddAuraEffectTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/AddCardTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/AddEnchantmentTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/AddStackToTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/ArmorTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/ChanceTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/ChangeAttackingTargetTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/ChangeHeroPowerTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/ConditionTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/ControlTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/CopyTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/CountTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/DamageNumberTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/DamageTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/DestroyTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/DrawNumberTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/DrawStackTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/DrawTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/EnqueueTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/FilterStackTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/FlagTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/FuncPlayableTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/GetEventNumberTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/GetGameTagTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/HealTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/IncludeAdjacentTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/IncludeTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/ManaCrystalTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/MathNumberIndexTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/MoveToGraveyardTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/MoveToSetasideTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/RandomCardTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/RandomEntourageTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/RandomTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/RemoveDurabilityTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/RemoveEnchantmentTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/RemoveHandTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/ReturnHandTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/SetGameTagTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/SilenceTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/SummonOpTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/SummonTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/SwapAttackHealthTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/TransformCopyTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/TransformTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/WeaponTask.hpp>
#include <Rosetta/Zones/HandZone.hpp>

using namespace RosettaStone::SimpleTasks;

namespace RosettaStone
{
void Expert1CardsGen::AddHeroes(std::map<std::string, Power>& cards)
{
    (void)cards;
}

void Expert1CardsGen::AddHeroPowers(std::map<std::string, Power>& cards)
{
    Power power;

    // ------------------------------------ HERO_POWER - PRIEST
    // [EX1_625t] Mind Spike (*) - COST:2
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: <b>Hero Power</b>
    //       Deal $2 damage.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new DamageTask(EntityType::TARGET, 2));
    cards.emplace("EX1_625t", power);

    // ------------------------------------ HERO_POWER - PRIEST
    // [EX1_625t2] Mind Shatter (*) - COST:2
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: <b>Hero Power</b>
    //       Deal $3 damage.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new DamageTask(EntityType::TARGET, 3));
    cards.emplace("EX1_625t2", power);
}

void Expert1CardsGen::AddDruid(std::map<std::string, Power>& cards)
{
    Power power;

    // ------------------------------------------ SPELL - DRUID
    // [EX1_154] Wrath - COST:2
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Choose One -</b>
    //       Deal $3 damage to a minion; or $1 damage
    //       and draw a card.
    // --------------------------------------------------------
    // GameTag:
    // - CHOOSE_ONE = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("EX1_154", power);

    // ------------------------------------------ SPELL - DRUID
    // [EX1_155] Mark of Nature - COST:3
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Choose One -</b> Give a minion +4 Attack;
    //       or +4 Health and <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - CHOOSE_ONE = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("EX1_155", power);

    // ------------------------------------------ SPELL - DRUID
    // [EX1_158] Soul of the Forest - COST:4
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: Give your minions "<b>Deathrattle:</b> Summon a 2/2 Treant."
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new AddEnchantmentTask("EX1_158e", EntityType::MINIONS));
    cards.emplace("EX1_158", power);

    // ------------------------------------------ SPELL - DRUID
    // [EX1_160] Power of the Wild - COST:2
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Choose One -</b> Give your minions +1/+1;
    //       or Summon a 3/2 Panther.
    // --------------------------------------------------------
    // GameTag:
    // - CHOOSE_ONE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("EX1_160", power);

    // ------------------------------------------ SPELL - DRUID
    // [EX1_164] Nourish - COST:6
    // - Faction: Neutral, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Choose One -</b> Gain 2 Mana Crystals; or Draw 3 cards.
    // --------------------------------------------------------
    // GameTag:
    // - CHOOSE_ONE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("EX1_164", power);

    // ----------------------------------------- MINION - DRUID
    // [EX1_165] Druid of the Claw - COST:5 [ATK:4/HP:4]
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Choose One -</b> Transform into a 4/4 with <b>Charge</b>;
    //       or a 4/6 with <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - CHOOSE_ONE = 1
    // --------------------------------------------------------
    // RefTag:
    // - CHARGE = 1
    // - TAUNT = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("EX1_165", power);

    // ----------------------------------------- MINION - DRUID
    // [EX1_178] Ancient of War - COST:7 [ATK:5/HP:5]
    // - Faction: Neutral, Set: Expert1, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Choose One -</b>+5 Attack; or +5 Health and <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - CHOOSE_ONE = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("EX1_178", power);

    // ------------------------------------------- SPELL - DRUID
    // [EX1_570] Bite - COST:4
    // - Faction: Neutral, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: Give your hero +4 Attack this turn. Gain 4 Armor.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new AddEnchantmentTask("EX1_570e", EntityType::HERO));
    power.AddPowerTask(new ArmorTask(4));
    cards.emplace("EX1_570", power);

    // ------------------------------------------ SPELL - DRUID
    // [EX1_571] Force of Nature - COST:5
    // - Faction: Neutral, Set: Expert1, Rarity: Epic
    // --------------------------------------------------------
    // Text: Summon three 2/2 Treants.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new SummonTask("EX1_tk9", 3));
    cards.emplace("EX1_571", power);
}

void Expert1CardsGen::AddDruidNonCollect(std::map<std::string, Power>& cards)
{
    Power power;

    // ------------------------------------------ SPELL - DRUID
    // [EX1_154a] Wrath (*) - COST:0
    // - Faction: Neutral, Set: Expert1
    // --------------------------------------------------------
    // Text: Deal $3 damage to a minion.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new DamageTask(EntityType::TARGET, 3, true));
    cards.emplace("EX1_154a", power);

    // ------------------------------------------ SPELL - DRUID
    // [EX1_154b] Wrath (*) - COST:0
    // - Faction: Neutral, Set: Expert1
    // --------------------------------------------------------
    // Text: Deal $1 damage to a minion. Draw a card.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new DamageTask(EntityType::TARGET, 1, true));
    power.AddPowerTask(new DrawTask(1));
    cards.emplace("EX1_154b", power);

    // ------------------------------------------ SPELL - DRUID
    // [EX1_155a] Tiger's Fury (*) - COST:0
    // - Faction: Neutral, Set: Expert1
    // --------------------------------------------------------
    // Text: +4 Attack.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new AddEnchantmentTask("EX1_155ae", EntityType::TARGET));
    cards.emplace("EX1_155a", power);

    // ------------------------------------------ SPELL - DRUID
    // [EX1_155ae] Mark of Nature (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: This minion has +4 Attack.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(Enchants::GetEnchantFromText("EX1_155ae"));
    cards.emplace("EX1_155ae", power);

    // ------------------------------------------ SPELL - DRUID
    // [EX1_155b] Thick Hide (*) - COST:0
    // - Faction: Neutral, Set: Expert1
    // --------------------------------------------------------
    // Text: +4 Health and <b>Taunt</b>.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new AddEnchantmentTask("EX1_155be", EntityType::TARGET));
    cards.emplace("EX1_155b", power);

    // ------------------------------------------ SPELL - DRUID
    // [EX1_155be] Mark of Nature (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: This minion has +4 Health and <b>Taunt</b>.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(Enchants::GetEnchantFromText("EX1_155be"));
    cards.emplace("EX1_155be", power);

    // ------------------------------------ ENCHANTMENT - DRUID
    // [EX1_158e] Soul of the Forest (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: Deathrattle: Summon a 2/2 Treant.
    // --------------------------------------------------------
    power.ClearData();
    power.AddDeathrattleTask(new SummonTask("EX1_158t", SummonSide::DEFAULT));
    cards.emplace("EX1_158e", power);

    // ----------------------------------------- MINION - DRUID
    // [EX1_158t] Treant (*) - COST:2 [ATK:2/HP:2]
    // - Faction: Neutral, Set: Expert1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("EX1_158t", power);

    // ------------------------------------------ SPELL - DRUID
    // [EX1_160a] Summon a Panther (*) - COST:2
    // - Faction: Neutral, Set: Expert1
    // --------------------------------------------------------
    // Text: Summon a 3/2 Panther.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new SummonTask("EX1_160t", SummonSide::SPELL));
    cards.emplace("EX1_160a", power);

    // ------------------------------------------ SPELL - DRUID
    // [EX1_160b] Leader of the Pack (*) - COST:2
    // - Faction: Neutral, Set: Expert1
    // --------------------------------------------------------
    // Text: Give your minions +1/+1.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        new AddEnchantmentTask("EX1_160be", EntityType::MINIONS));
    cards.emplace("EX1_160b", power);

    // ------------------------------------ ENCHANTMENT - DRUID
    // [EX1_160be] Leader of the Pack (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(Enchants::GetEnchantFromText("EX1_160be"));
    cards.emplace("EX1_160be", power);

    // ----------------------------------------- MINION - DRUID
    // [EX1_160t] Panther (*) - COST:2 [ATK:3/HP:2]
    // - Race: Beast, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("EX1_160t", power);

    // ------------------------------------------ SPELL - DRUID
    // [EX1_164a] Rampant Growth (*) - COST:6
    // - Faction: Neutral, Set: Expert1
    // --------------------------------------------------------
    // Text: Gain 2 Mana Crystals.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new ManaCrystalTask(2, true));
    cards.emplace("EX1_164a", power);

    // ------------------------------------------ SPELL - DRUID
    // [EX1_164b] Enrich (*) - COST:6
    // - Faction: Neutral, Set: Expert1
    // --------------------------------------------------------
    // Text: Draw 3 cards.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new DrawTask(3));
    cards.emplace("EX1_164b", power);

    // ----------------------------------------- MINION - DRUID
    // [EX1_165a] Cat Form (*) - COST:5 [ATK:4/HP:4]
    // - Faction: Neutral, Set: Expert1
    // --------------------------------------------------------
    // Text: <b>Charge</b>
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new TransformTask(EntityType::SOURCE, "EX1_165t1"));
    cards.emplace("EX1_165a", power);

    // ----------------------------------------- MINION - DRUID
    // [EX1_165b] Bear Form (*) - COST:5 [ATK:4/HP:6]
    // - Faction: Neutral, Set: Expert1
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new TransformTask(EntityType::SOURCE, "EX1_165t2"));
    cards.emplace("EX1_165b", power);

    // ----------------------------------------- MINION - DRUID
    // [EX1_165t1] Druid of the Claw (*) - COST:5 [ATK:4/HP:4]
    // - Race: Beast, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Charge</b>
    // --------------------------------------------------------
    // GameTag:
    // - CHARGE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("EX1_165t1", power);

    // ----------------------------------------- MINION - DRUID
    // [EX1_165t2] Druid of the Claw (*) - COST:5 [ATK:4/HP:6]
    // - Race: Beast, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("EX1_165t2", power);

    // ------------------------------------------ SPELL - DRUID
    // [EX1_178a] Rooted (*) - COST:7
    // - Faction: Neutral, Set: Expert1
    // --------------------------------------------------------
    // Text: +5 Health and <b>Taunt</b>.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new AddEnchantmentTask("EX1_178ae", EntityType::SOURCE));
    cards.emplace("EX1_178a", power);

    // ------------------------------------ ENCHANTMENT - DRUID
    // [EX1_178ae] Rooted (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: +5 Health and <b>Taunt</b>
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(Enchants::GetEnchantFromText("EX1_178ae"));
    cards.emplace("EX1_178ae", power);

    // ------------------------------------------ SPELL - DRUID
    // [EX1_178b] Uproot (*) - COST:7
    // - Faction: Neutral, Set: Expert1
    // --------------------------------------------------------
    // Text: +5 Attack.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new AddEnchantmentTask("EX1_178be", EntityType::SOURCE));
    cards.emplace("EX1_178b", power);

    // ------------------------------------ ENCHANTMENT - DRUID
    // [EX1_178be] Uprooted (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: +5 Attack.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(Enchants::GetEnchantFromText("EX1_178be"));
    cards.emplace("EX1_178be", power);

    // ------------------------------------ ENCHANTMENT - DRUID
    // [EX1_570e] Bite - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: +4 Attack this turn.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(Enchants::GetEnchantFromText("EX1_570e"));
    cards.emplace("EX1_570e", power);

    // ----------------------------------------- MINION - DRUID
    // [EX1_tk9] Treant (*) - COST:2 [ATK:2/HP:2]
    // - Faction: Neutral, Set: Expert1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("EX1_tk9", power);
}

void Expert1CardsGen::AddHunter(std::map<std::string, Power>& cards)
{
    Power power;

    // ---------------------------------------- WEAPON - HUNTER
    // [DS1_188] Gladiator's Longbow - COST:7 [ATK:5/HP:0]
    // - Faction: Neutral, Set: Expert1, Rarity: Epic
    // --------------------------------------------------------
    // Text: Your hero is <b>Immune</b> while attacking.
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 2
    // --------------------------------------------------------
    // RefTag:
    // - IMMUNE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(new Trigger(TriggerType::TARGET));
    power.GetTrigger()->triggerSource = TriggerSource::HERO;
    power.GetTrigger()->tasks = { new AddEnchantmentTask("DS1_188e",
                                                         EntityType::HERO) };
    cards.emplace("DS1_188", power);

    // ---------------------------------------- MINION - HUNTER
    // [EX1_543] King Krush - COST:9 [ATK:8/HP:8]
    // - Race: Beast, Faction: Neutral, Set: Expert1, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Charge</b>
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - CHARGE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("EX1_543", power);

    // ----------------------------------------- SPELL - HUNTER
    // [EX1_609] Snipe - COST:2
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Secret:</b> After your opponent plays a minion,
    //       deal $4 damage to it.
    // --------------------------------------------------------
    // GameTag:
    // - SECRET = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(new Trigger(TriggerType::AFTER_PLAY_MINION));
    power.GetTrigger()->triggerSource = TriggerSource::ENEMY_MINIONS;
    power.GetTrigger()->tasks = {
        new ConditionTask(EntityType::TARGET, { SelfCondition::IsNotDead() }),
        new FlagTask(true, { new DamageTask(EntityType::TARGET, 4, true),
                             new SetGameTagTask(EntityType::SOURCE,
                                                GameTag::REVEALED, 1),
                             new MoveToGraveyardTask(EntityType::SOURCE) })
    };
    cards.emplace("EX1_609", power);

    // ----------------------------------------- SPELL - HUNTER
    // [EX1_617] Deadly Shot - COST:3
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: Destroy a random enemy minion.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINIMUM_ENEMY_MINIONS = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new RandomTask(EntityType::ENEMY_MINIONS, 1));
    power.AddPowerTask(new DestroyTask(EntityType::STACK));
    cards.emplace("EX1_617", power);

    // ---------------------------------------- MINION - HUNTER
    // [EX1_534] Savannah Highmane - COST:6 [ATK:6/HP:5]
    // - Race: Beast, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon two 2/2 Hyenas.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddDeathrattleTask(
        new EnqueueTask({ new SummonTask(SummonSide::DEATHRATTLE,
                                         Cards::FindCardByID("EX1_534t")) },
                        2));
    cards.emplace("EX1_534", power);
}

void Expert1CardsGen::AddHunterNonCollect(std::map<std::string, Power>& cards)
{
    Power power;

    // ----------------------------------- ENCHANTMENT - HUNTER
    // [DS1_188e] Gladiator's Longbow enchantment (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(new Enchant(Effects::Immune));
    power.AddTrigger(new Trigger(TriggerType::AFTER_ATTACK));
    power.GetTrigger()->triggerSource = TriggerSource::HERO;
    power.GetTrigger()->tasks = { new RemoveEnchantmentTask() };
    cards.emplace("DS1_188e", power);

    // ---------------------------------------- MINION - HUNTER
    // [EX1_534t] Hyena (*) - COST:2 [ATK:2/HP:2]
    // - Race: Beast, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("EX1_534t", power);
}

void Expert1CardsGen::AddMage(std::map<std::string, Power>& cards)
{
    Power power;

    // ------------------------------------------- SPELL - MAGE
    // [CS2_028] Blizzard - COST:6
    // - Faction: Neutral, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: Deal $2 damage to all enemy minions and <b>Freeze</b> them.
    // --------------------------------------------------------
    // GameTag:
    // - FREEZE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new DamageTask(EntityType::ENEMY_MINIONS, 2, true));
    power.AddPowerTask(
        new SetGameTagTask(EntityType::ENEMY_MINIONS, GameTag::FROZEN, 1));
    cards.emplace("CS2_028", power);

    // ------------------------------------------- SPELL - MAGE
    // [EX1_179] Icicle - COST:2
    // - Set: Expert1, Rarity: Epic
    // --------------------------------------------------------
    // Text: Deal $2 damage to a minion.
    //       If it's <b>Frozen</b>, draw a card.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    // RefTag:
    // - FREEZE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new DamageTask(EntityType::TARGET, 2, true));
    power.AddPowerTask(
        new ConditionTask(EntityType::TARGET, { SelfCondition::IsFrozen() }));
    power.AddPowerTask(new FlagTask(true, { new DrawTask(1) }));
    cards.emplace("EX1_179", power);

    // ------------------------------------------- SPELL - MAGE
    // [EX1_180] Tome of Intellect - COST:1
    // - Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: Add a random Mage spell to your hand.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new RandomCardTask(CardType::SPELL, CardClass::MAGE));
    power.AddPowerTask(new AddStackToTask(EntityType::HAND));
    cards.emplace("EX1_180", power);

    // ------------------------------------------ MINION - MAGE
    // [EX1_274] Ethereal Arcanist - COST:4 [ATK:3/HP:3]
    // - Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: If you control a <b>Secret</b> at the end
    //       of your turn, gain +2/+2.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    // RefTag:
    // - SECRET = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(new Trigger(TriggerType::TURN_END));
    power.GetTrigger()->condition =
        new SelfCondition(SelfCondition::IsControllingSecret());
    power.GetTrigger()->tasks = { new AddEnchantmentTask("EX1_274e",
                                                         EntityType::SOURCE) };
    cards.emplace("EX1_274", power);

    // ------------------------------------------- SPELL - MAGE
    // [EX1_279] Pyroblast - COST:10
    // - Faction: Neutral, Set: Expert1, Rarity: Epic
    // --------------------------------------------------------
    // Text: Deal $10 damage.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new DamageTask(EntityType::TARGET, 10, true));
    cards.emplace("EX1_279", power);

    // ------------------------------------------- SPELL - MAGE
    // [EX1_287] Counterspell - COST:3
    // - Faction: Neutral, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Secret:</b> When your opponent casts a spell, <b>Counter</b> it.
    // --------------------------------------------------------
    // GameTag:
    // - SECRET = 1
    // --------------------------------------------------------
    // RefTag:
    // - COUNTER = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(new Trigger(TriggerType::CAST_SPELL));
    power.GetTrigger()->triggerSource = TriggerSource::ENEMY_SPELLS;
    power.GetTrigger()->tasks = {
        new SetGameTagTask(EntityType::TARGET, GameTag::CANT_PLAY, 1),
        new SetGameTagTask(EntityType::SOURCE, GameTag::REVEALED, 1),
        new MoveToGraveyardTask(EntityType::SOURCE)
    };
    power.GetTrigger()->fastExecution = true;
    cards.emplace("EX1_287", power);

    // ------------------------------------------ MINION - MAGE
    // [EX1_608] Sorcerer's Apprentice - COST:2 [ATK:3/HP:2]
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: Your spells cost (1) less.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddAura(new Aura(AuraType::HAND, { Effects::ReduceCost(1) }));
    {
        const auto aura = dynamic_cast<Aura*>(power.GetAura());
        aura->condition = new SelfCondition(SelfCondition::IsSpell());
    }
    cards.emplace("EX1_608", power);

    // ------------------------------------------ MINION - MAGE
    // [NEW1_012] Mana Wyrm - COST:2 [ATK:1/HP:3]
    // - Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: Whenever you cast a spell, gain +1 Attack.
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(new Trigger(TriggerType::CAST_SPELL));
    power.GetTrigger()->triggerSource = TriggerSource::FRIENDLY;
    power.GetTrigger()->tasks = { new AddEnchantmentTask("NEW1_012o",
                                                         EntityType::SOURCE) };
    cards.emplace("NEW1_012", power);
}

void Expert1CardsGen::AddMageNonCollect(std::map<std::string, Power>& cards)
{
    Power power;

    // ------------------------------------- ENCHANTMENT - MAGE
    // [EX1_274e] Raw Power! (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: Increased stats.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(new Enchant(Effects::AttackHealthN(2)));
    cards.emplace("EX1_274e", power);

    // ------------------------------------- ENCHANTMENT - MAGE
    // [NEW1_012o] Mana Gorged (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: Increased attack.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(new Enchant(Effects::AttackN(1)));
    cards.emplace("NEW1_012o", power);
}

void Expert1CardsGen::AddPaladin(std::map<std::string, Power>& cards)
{
    Power power;

    // ---------------------------------------- SPELL - PALADIN
    // [EX1_130] Noble Sacrifice - COST:1
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Secret:</b> When an enemy attacks,
    //       summon a 2/1 Defender as the new target.
    // --------------------------------------------------------
    // GameTag:
    // - SECRET = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(new Trigger(TriggerType::ATTACK));
    power.GetTrigger()->triggerSource = TriggerSource::ENEMY;
    power.GetTrigger()->tasks = {
        new SummonTask("EX1_130a", SummonSide::SPELL, true),
        new ChangeAttackingTargetTask(EntityType::TARGET, EntityType::STACK),
        new SetGameTagTask(EntityType::SOURCE, GameTag::REVEALED, 1),
        new MoveToGraveyardTask(EntityType::SOURCE)
    };
    cards.emplace("EX1_130", power);

    // ---------------------------------------- SPELL - PALADIN
    // [EX1_132] Eye for an Eye - COST:1
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Secret:</b> When your hero takes damage,
    //       deal that much damage to the enemy hero.
    // --------------------------------------------------------
    // GameTag:
    // - SECRET = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(new Trigger(TriggerType::TAKE_DAMAGE));
    power.GetTrigger()->triggerSource = TriggerSource::HERO;
    power.GetTrigger()->tasks = {
        new GetEventNumberTask(),
        new DamageNumberTask(EntityType::ENEMY_HERO, true),
        new SetGameTagTask(EntityType::SOURCE, GameTag::REVEALED, 1),
        new MoveToGraveyardTask(EntityType::SOURCE)
    };
    cards.emplace("EX1_132", power);

    // ---------------------------------------- SPELL - PALADIN
    // [EX1_136] Redemption - COST:1
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Secret:</b> When a friendly minion dies,
    //       return it to life with 1 Health.
    // --------------------------------------------------------
    // GameTag:
    // - SECRET = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(new Trigger(TriggerType::DEATH));
    power.GetTrigger()->triggerSource = TriggerSource::MINIONS;
    power.GetTrigger()->tasks = {
        new CopyTask(EntityType::TARGET, ZoneType::PLAY, 1, true),
        new FuncPlayableTask([=](const std::vector<Playable*>& playables) {
            auto target = dynamic_cast<Minion*>(playables[0]);
            if (target == nullptr)
            {
                return std::vector<Playable*>{};
            }

            target->SetDamage(target->GetHealth() - 1);
            return std::vector<Playable*>{ target };
        }),
        new SetGameTagTask(EntityType::SOURCE, GameTag::REVEALED, 1),
        new MoveToGraveyardTask(EntityType::SOURCE)
    };
    power.GetTrigger()->removeAfterTriggered = true;
    cards.emplace("EX1_136", power);

    // ---------------------------------------- SPELL - PALADIN
    // [EX1_354] Lay on Hands - COST:8
    // - Faction: Neutral, Set: Expert1, Rarity: Epic
    // --------------------------------------------------------
    // Text: Restore #8 Health. Draw 3 cards.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new HealTask(EntityType::TARGET, 8));
    power.AddPowerTask(new DrawTask(3));
    cards.emplace("EX1_354", power);

    // ---------------------------------------- SPELL - PALADIN
    // [EX1_355] Blessed Champion - COST:5
    // - Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: Double a minion's Attack.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new AddEnchantmentTask("EX1_355e", EntityType::TARGET));
    cards.emplace("EX1_355", power);

    // --------------------------------------- MINION - PALADIN
    // [EX1_362] Argent Protector - COST:2 [ATK:2/HP:2]
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give a friendly minion <b>Divine Shield</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_FRIENDLY_TARGET = 0
    // - REQ_NONSELF_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - DIVINE_SHIELD = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        new SetGameTagTask(EntityType::TARGET, GameTag::DIVINE_SHIELD, 1));
    cards.emplace("EX1_362", power);

    // ------------------------------------------ SPELL - PALADIN
    // [EX1_365] Holy Wrath - COST:5
    // - Faction: Neutral, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: Draw a card and deal damage equal to its Cost.
    // --------------------------------------------------------
    // GameTag:
    // - AFFECTED_BY_SPELL_POWER = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new DrawTask(1, true));
    power.AddPowerTask(new GetGameTagTask(EntityType::STACK, GameTag::COST));
    power.AddPowerTask(new DamageNumberTask(EntityType::TARGET, true));
    cards.emplace("EX1_365", power);

    // --------------------------------------- MINION - PALADIN
    // [EX1_382] Aldor Peacekeeper - COST:3 [ATK:3/HP:3]
    // - Faction: Neutral, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Change an enemy minion's Attack to 1.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_ENEMY_TARGET = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_TARGET_IF_AVAILABLE = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new AddEnchantmentTask("EX1_382e", EntityType::TARGET));
    cards.emplace("EX1_382", power);

    // --------------------------------------- MINION - PALADIN
    // [EX1_383] Tirion Fordring - COST:8 [ATK:6/HP:6]
    // - Faction: Neutral, Set: Expert1, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b><b>Divine Shield</b>,</b> <b>Taunt</b>
    //       <b>Deathrattle:</b> Equip a 5/3 Ashbringer.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DIVINE_SHIELD = 1
    // - TAUNT = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddDeathrattleTask(new WeaponTask("EX1_383t"));
    cards.emplace("EX1_383", power);

    // ---------------------------------------- SPELL - PALADIN
    // [EX1_384] Avenging Wrath - COST:6
    // - Faction: Neutral, Set: Expert1, Rarity: Epic
    // --------------------------------------------------------
    // Text: Deal $8 damage randomly split among all enemies.
    // --------------------------------------------------------
    // GameTag:
    // - ImmuneToSpellpower = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new EnqueueTask({ new RandomTask(EntityType::ENEMIES, 1),
                                         new DamageTask(EntityType::STACK, 1) },
                                       8, true));
    cards.emplace("EX1_384", power);

    // ---------------------------------------- SPELL - PALADIN
    // [EX1_619] Equality - COST:4
    // - Faction: Neutral, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: Change the Health of ALL minions to 1.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        new AddEnchantmentTask("EX1_619e", EntityType::ALL_MINIONS));
    cards.emplace("EX1_619", power);
}

void Expert1CardsGen::AddPaladinNonCollect(std::map<std::string, Power>& cards)
{
    Power power;

    // --------------------------------------- MINION - PALADIN
    // [EX1_130a] Defender (*) - COST:1 [ATK:2/HP:1]
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("EX1_130a", power);

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [EX1_355e] Blessed Champion (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: This minion's Attack has been doubled.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(new Enchant(GameTag::ATK, EffectOperator::MUL, 2));
    cards.emplace("EX1_355e", power);

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [EX1_382e] Stand Down! (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: Attack changed to 1.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(new Enchant(Effects::SetAttack(1)));
    cards.emplace("EX1_382e", power);

    // --------------------------------------- WEAPON - PALADIN
    // [EX1_383t] Ashbringer (*) - COST:5 [ATK:5/HP:0]
    // - Faction: Neutral, Set: Expert1
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DURABILITY = 3
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("EX1_383t", power);

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [EX1_619e] Equality (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: Health changed to 1.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(new Enchant(Effects::SetMaxHealth(1)));
    cards.emplace("EX1_619e", power);
}

void Expert1CardsGen::AddPriest(std::map<std::string, Power>& cards)
{
    Power power;

    // ----------------------------------------- SPELL - PRIEST
    // [CS1_129] Inner Fire - COST:1
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: Change a minion's Attack to be equal to its Health.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new GetGameTagTask(EntityType::TARGET, GameTag::HEALTH));
    power.AddPowerTask(
        new GetGameTagTask(EntityType::TARGET, GameTag::DAMAGE, 0, 1));
    power.AddPowerTask(new MathNumberIndexTask(0, 1, MathOperation::SUB));
    power.AddPowerTask(
        new AddEnchantmentTask("CS1_129e", EntityType::TARGET, true));
    cards.emplace("CS1_129", power);

    // ---------------------------------------- MINION - PRIEST
    // [EX1_091] Cabal Shadow Priest - COST:6 [ATK:4/HP:5]
    // - Faction: Neutral, Set: Expert1, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Take control of an enemy minion
    //       that has 2 or less Attack.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_TARGET_MAX_ATTACK = 2
    // - REQ_MINION_TARGET = 0
    // - REQ_ENEMY_TARGET = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new ControlTask(EntityType::TARGET));
    cards.emplace("EX1_091", power);

    // ----------------------------------------- SPELL - PRIEST
    // [EX1_332] Silence - COST:0
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Silence</b> a minion.
    // --------------------------------------------------------
    // GameTag:
    // - SILENCE = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new SilenceTask(EntityType::TARGET));
    cards.emplace("EX1_332", power);

    // ---------------------------------------- MINION - PRIEST
    // [EX1_341] Lightwell - COST:2 [ATK:0/HP:5]
    // - Faction: Neutral, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: At the start of your turn, restore 3 Health
    //       to a damaged friendly character.
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(new Trigger(TriggerType::TURN_START));
    power.GetTrigger()->tasks = {
        new IncludeTask(EntityType::FRIENDS),
        new FilterStackTask(SelfCondition::IsDamaged()),
        new RandomTask(EntityType::STACK, 1), new HealTask(EntityType::STACK, 3)
    };
    cards.emplace("EX1_341", power);

    // ----------------------------------------- SPELL - PRIEST
    // [EX1_345] Mindgames - COST:4
    // - Faction: Neutral, Set: Expert1, Rarity: Epic
    // --------------------------------------------------------
    // Text: Put a copy of a random minion from
    //       your opponent's deck into the battlefield.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new IncludeTask(EntityType::ENEMY_DECK));
    power.AddPowerTask(new FilterStackTask(SelfCondition::IsMinion()));
    power.AddPowerTask(new CountTask(EntityType::STACK));
    power.AddPowerTask(new ConditionTask(
        EntityType::HERO, { SelfCondition::IsStackNum(1, RelaSign::GEQ) }));
    power.AddPowerTask(new FlagTask(
        true, { new RandomTask(EntityType::STACK, 1),
                new CopyTask(EntityType::STACK, ZoneType::PLAY) }));
    power.AddPowerTask(
        new FlagTask(false, { new SummonTask("EX1_345t", SummonSide::SPELL) }));
    cards.emplace("EX1_345", power);

    // ----------------------------------------- SPELL - PRIEST
    // [EX1_621] Circle of Healing - COST:0
    // - Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: Restore #4 Health to ALL minions.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new HealTask(EntityType::ALL_MINIONS, 4));
    cards.emplace("EX1_621", power);

    // ---------------------------------------- MINION - PRIEST
    // [EX1_623] Temple Enforcer - COST:6 [ATK:6/HP:6]
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give a friendly minion +3 Health.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_FRIENDLY_TARGET = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_TARGET_IF_AVAILABLE = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new AddEnchantmentTask("EX1_623e", EntityType::TARGET));
    cards.emplace("EX1_623", power);

    // ----------------------------------------- SPELL - PRIEST
    // [EX1_624] Holy Fire - COST:6
    // - Faction: Priest, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: Deal $5 damage. Restore #5 Health to your hero.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new DamageTask(EntityType::TARGET, 5, true));
    power.AddPowerTask(new HealTask(EntityType::HERO, 5));
    cards.emplace("EX1_624", power);

    // ----------------------------------------- SPELL - PRIEST
    // [EX1_625] Shadowform - COST:3
    // - Faction: Priest, Set: Expert1, Rarity: Epic
    // --------------------------------------------------------
    // Text: Your Hero Power becomes 'Deal 2 damage'.
    //       If already in Shadowform: 3 damage.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new ConditionTask(
        EntityType::SOURCE, { SelfCondition::IsHeroPowerCard("EX1_625t") }));
    power.AddPowerTask(
        new FlagTask(true, { new ChangeHeroPowerTask("EX1_625t2") }));
    power.AddPowerTask(new FlagTask(
        false,
        { new ConditionTask(EntityType::SOURCE,
                            { SelfCondition::IsHeroPowerCard("EX1_625t2") }),
          new FlagTask(false, { new ChangeHeroPowerTask("EX1_625t") }) }));
    cards.emplace("EX1_625", power);

    // ----------------------------------------- SPELL - PRIEST
    // [EX1_626] Mass Dispel - COST:4
    // - Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Silence</b> all enemy minions. Draw a card.
    // --------------------------------------------------------
    // GameTag:
    // - SILENCE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new SilenceTask(EntityType::ENEMY_MINIONS));
    power.AddPowerTask(new DrawTask(1));
    cards.emplace("EX1_626", power);
}

void Expert1CardsGen::AddPriestNonCollect(std::map<std::string, Power>& cards)
{
    Power power;

    // ----------------------------------------- ENCHANTMENT - PRIEST
    // [CS1_129e] Inner Fire - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: Change a minion's Attack to be equal to its Health.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(new Enchant(Enchants::SetAttackScriptTag));
    cards.emplace("CS1_129e", power);

    // ---------------------------------------- MINION - PRIEST
    // [EX1_345t] Shadow of Nothing - COST:0 [ATK:0/HP:1]
    // - Faction: Neutral, Set: Expert1
    // --------------------------------------------------------
    // Text: Mindgames whiffed! Your opponent had no minions!
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("EX1_345t", power);

    // ----------------------------------- ENCHANTMENT - PRIEST
    // [EX1_623e] Infusion (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: +3 Health.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(Enchants::GetEnchantFromText("EX1_623e"));
    cards.emplace("EX1_623e", power);
}

void Expert1CardsGen::AddRogue(std::map<std::string, Power>& cards)
{
    Power power;

    // ------------------------------------------ SPELL - ROGUE
    // [CS2_073] Cold Blood - COST:1
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: Give a minion +2 Attack. <b>Combo:</b> +4 Attack instead.
    // --------------------------------------------------------
    // GameTag:
    // - COMBO = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new AddEnchantmentTask("CS2_073e", EntityType::TARGET));
    power.AddComboTask(new AddEnchantmentTask("CS2_073e2", EntityType::TARGET));
    cards.emplace("CS2_073", power);

    // ------------------------------------------ SPELL - ROGUE
    // [CS2_233] Blade Flurry - COST:4
    // - Faction: Neutral, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: Destroy your weapon and deal its damage to all enemy minions.
    // --------------------------------------------------------
    // GameTag:
    // - AFFECTED_BY_SPELL_POWER = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_WEAPON_EQUIPPED = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new GetGameTagTask(EntityType::WEAPON, GameTag::ATK));
    power.AddPowerTask(new DamageNumberTask(EntityType::ENEMY_MINIONS, true));
    power.AddPowerTask(new DestroyTask(EntityType::WEAPON));
    cards.emplace("CS2_233", power);

    // ------------------------------------------ SPELL - ROGUE
    // [EX1_124] Eviscerate - COST:2
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: Deal $2 damage. <b>Combo:</b> Deal $4 damage instead. @spelldmg
    // --------------------------------------------------------
    // GameTag:
    // - COMBO = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new DamageTask(EntityType::TARGET, 2, true));
    power.AddComboTask(new DamageTask(EntityType::TARGET, 4, true));
    cards.emplace("EX1_124", power);

    // ------------------------------------------ SPELL - ROGUE
    // [EX1_126] Betrayal - COST:2
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: Force an enemy minion to deal its damage
    //       to the minions next to it.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_ENEMY_TARGET = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new GetGameTagTask(EntityType::TARGET, GameTag::ATK));
    power.AddPowerTask(new IncludeAdjacentTask(EntityType::TARGET));
    power.AddPowerTask(new DamageNumberTask(EntityType::STACK));
    cards.emplace("EX1_126", power);

    // ----------------------------------------- MINION - ROGUE
    // [EX1_131] Defias Ringleader - COST:2 [ATK:2/HP:2]
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Combo:</b> Summon a 2/1 Defias Bandit.
    // --------------------------------------------------------
    // GameTag:
    // - COMBO = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddComboTask(new SummonTask("EX1_131t", SummonSide::RIGHT));
    cards.emplace("EX1_131", power);

    // ----------------------------------------- WEAPON - ROGUE
    // [EX1_133] Perdition's Blade - COST:3 [ATK:2/HP:0]
    // - Faction: Neutral, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 1 damage. <b>Combo:</b> Deal 2 instead.
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 2
    // - BATTLECRY = 1
    // - COMBO = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new DamageTask(EntityType::TARGET, 1));
    power.AddComboTask(new DamageTask(EntityType::TARGET, 2));
    cards.emplace("EX1_133", power);

    // ----------------------------------------- MINION - ROGUE
    // [EX1_134] SI:7 Agent - COST:3 [ATK:3/HP:3]
    // - Faction: Neutral, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Combo:</b> Deal 2 damage.
    // --------------------------------------------------------
    // GameTag:
    // - COMBO = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_FOR_COMBO = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddComboTask(new DamageTask(EntityType::TARGET, 2));
    cards.emplace("EX1_134", power);

    // ------------------------------------------ SPELL - ROGUE
    // [EX1_137] Headcrack - COST:3
    // - Faction: Neutral, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: Deal $2 damage to the enemy hero.
    //       <b>Combo:</b> Return this to your hand next turn.
    // --------------------------------------------------------
    // GameTag:
    // - COMBO = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new DamageTask(EntityType::ENEMY_HERO, 2, true));
    power.AddComboTask(new DamageTask(EntityType::ENEMY_HERO, 2, true));
    power.AddComboTask(
        new SetGameTagTask(EntityType::SOURCE, GameTag::HEADCRACK_COMBO, 1));
    power.AddTrigger(new Trigger(TriggerType::TURN_END));
    power.GetTrigger()->tasks = {
        new ConditionTask(
            EntityType::SOURCE,
            { SelfCondition::IsTagValue(GameTag::HEADCRACK_COMBO, 1) }),
        new FlagTask(true, { new IncludeTask(EntityType::SOURCE),
                             new FuncPlayableTask(
                                 [=](const std::vector<Playable*>& playables) {
                                     auto source = playables[0];
                                     source->zone->Remove(source);
                                     source->SetGameTag(
                                         GameTag::HEADCRACK_COMBO, 0);

                                     return std::vector<Playable*>{ source };
                                 }),
                             new AddStackToTask(EntityType::HAND) })
    };
    power.GetTrigger()->removeAfterTriggered = true;
    cards.emplace("EX1_137", power);

    // ------------------------------------------ SPELL - ROGUE
    // [EX1_144] Shadowstep - COST:0
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: Return a friendly minion to your hand. It costs (2) less.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_FRIENDLY_TARGET = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new ReturnHandTask(EntityType::TARGET));
    power.AddPowerTask(
        new AddAuraEffectTask(Effects::ReduceCost(2), EntityType::TARGET));
    cards.emplace("EX1_144", power);

    // ----------------------------------------- MINION - ROGUE
    // [EX1_522] Patient Assassin - COST:2 [ATK:1/HP:1]
    // - Faction: Neutral, Set: Expert1, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Stealth</b>
    //        <b>Poisonous</b>
    // --------------------------------------------------------
    // GameTag:
    // - STEALTH = 1
    // - POISONOUS = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("EX1_522", power);

    // ----------------------------------------- MINION - ROGUE
    // [NEW1_005] Kidnapper - COST:6 [ATK:5/HP:3]
    // - Faction: Neutral, Set: Expert1, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Combo:</b> Return a minion to its owner's hand.
    // --------------------------------------------------------
    // GameTag:
    // - COMBO = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // - REQ_TARGET_FOR_COMBO = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddComboTask(new ReturnHandTask(EntityType::TARGET));
    cards.emplace("NEW1_005", power);
}

void Expert1CardsGen::AddRogueNonCollect(std::map<std::string, Power>& cards)
{
    Power power;

    // ------------------------------------ ENCHANTMENT - ROGUE
    // [CS2_073e] Cold Blood (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: +2 Attack.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(Enchants::GetEnchantFromText("CS2_073e"));
    cards.emplace("CS2_073e", power);

    // ------------------------------------ ENCHANTMENT - ROGUE
    // [CS2_073e2] Cold Blood (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: +4 Attack.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(Enchants::GetEnchantFromText("CS2_073e2"));
    cards.emplace("CS2_073e2", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_131t] Defias Bandit (*) - COST:1 [ATK:2/HP:1]
    // - Faction: Neutral, Set: Expert1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("EX1_131t", power);
}

void Expert1CardsGen::AddShaman(std::map<std::string, Power>& cards)
{
    Power power;

    // ----------------------------------------- SPELL - SHAMAN
    // [CS2_038] Ancestral Spirit - COST:2
    // - Faction: Neutral, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: Give a minion "<b>Deathrattle:</b> Resummon this minion."
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new AddEnchantmentTask("CS2_038e", EntityType::TARGET));
    cards.emplace("CS2_038", power);

    // ----------------------------------------- SPELL - SHAMAN
    // [CS2_053] Far Sight - COST:3
    // - Faction: Neutral, Set: Expert1, Rarity: Epic
    // --------------------------------------------------------
    // Text: Draw a card. That card costs (3) less.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new DrawTask(1, true));
    power.AddPowerTask(new AddEnchantmentTask("CS2_053e", EntityType::STACK));
    cards.emplace("CS2_053", power);

    // ----------------------------------------- SPELL - SHAMAN
    // [EX1_238] Lightning Bolt - COST:1
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: Deal $3 damage. <b>Overload:</b> (1)
    // --------------------------------------------------------
    // GameTag:
    // - OVERLOAD = 1
    // - OVERLOAD_OWED = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new DamageTask(EntityType::TARGET, 3, true));
    cards.emplace("EX1_238", power);

    // ----------------------------------------- SPELL - SHAMAN
    // [EX1_241] Lava Burst - COST:3
    // - Faction: Neutral, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: Deal $5 damage. <b>Overload:</b> (2)
    // --------------------------------------------------------
    // GameTag:
    // - OVERLOAD = 2
    // - OVERLOAD_OWED = 2
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new DamageTask(EntityType::TARGET, 5, true));
    cards.emplace("EX1_241", power);

    // ---------------------------------------- MINION - SHAMAN
    // [EX1_243] Dust Devil - COST:1 [ATK:3/HP:1]
    // - Race: Elemental, Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Windfury</b>. <b>Overload:</b> (2)
    // --------------------------------------------------------
    // GameTag:
    // - OVERLOAD = 2
    // - OVERLOAD_OWED = 2
    // - WINDFURY = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("EX1_243", power);

    // ----------------------------------------- SPELL - SHAMAN
    // [EX1_245] Earth Shock - COST:1
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Silence</b> a minion, then deal $1 damage to it.
    // --------------------------------------------------------
    // GameTag:
    // - SILENCE = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new SilenceTask(EntityType::TARGET));
    power.AddPowerTask(new DamageTask(EntityType::TARGET, 1, true));
    cards.emplace("EX1_245", power);

    // ---------------------------------------- WEAPON - SHAMAN
    // [EX1_247] Stormforged Axe - COST:2 [ATK:2/HP:0]
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Overload:</b> (1)
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 3
    // - OVERLOAD = 1
    // - OVERLOAD_OWED = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("EX1_247", power);

    // ----------------------------------------- SPELL - SHAMAN
    // [EX1_248] Feral Spirit - COST:3
    // - Faction: Neutral, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: Summon two 2/3 Spirit Wolves with <b>Taunt</b>.
    //       <b>Overload:</b> (2)
    // --------------------------------------------------------
    // GameTag:
    // - OVERLOAD = 2
    // - OVERLOAD_OWED = 2
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new SummonTask("EX1_tk11", 2));
    cards.emplace("EX1_248", power);

    // ---------------------------------------- MINION - SHAMAN
    // [EX1_250] Earth Elemental - COST:5 [ATK:7/HP:8]
    // - Race: Elemental, Faction: Neutral, Set: Expert1, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b><b>Overload</b>:</b> (3)
    // --------------------------------------------------------
    // GameTag:
    // - OVERLOAD = 3
    // - OVERLOAD_OWED = 3
    // - TAUNT = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("EX1_250", power);

    // ----------------------------------------- SPELL - SHAMAN
    // [EX1_251] Forked Lightning - COST:1
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: Deal $2 damage to 2 random enemy minions. <b>Overload:</b> (2)
    // --------------------------------------------------------
    // GameTag:
    // - OVERLOAD = 2
    // - OVERLOAD_OWED = 2
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINIMUM_ENEMY_MINIONS = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new RandomTask(EntityType::ENEMY_MINIONS, 2));
    power.AddPowerTask(new DamageTask(EntityType::STACK, 2, true));
    cards.emplace("EX1_251", power);

    // ---------------------------------------- MINION - SHAMAN
    // [EX1_258] Unbound Elemental - COST:3 [ATK:2/HP:4]
    // - Race: Elemental, Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: Whenever you play a card with <b>Overload</b>, gain +1/+1.
    // --------------------------------------------------------
    // RefTag:
    // - OVERLOAD = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(new Trigger(TriggerType::PLAY_CARD));
    power.GetTrigger()->condition =
        new SelfCondition(SelfCondition::IsOverloadCard());
    power.GetTrigger()->tasks = { new AddEnchantmentTask("EX1_258e",
                                                         EntityType::SOURCE) };
    cards.emplace("EX1_258", power);

    // ---------------------------------------- WEAPON - SHAMAN
    // [EX1_567] Doomhammer - COST:5 [ATK:2/HP:0]
    // - Faction: Neutral, Set: Expert1, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Windfury, Overload:</b> (2)
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 8
    // - WINDFURY = 1
    // - OVERLOAD = 2
    // - OVERLOAD_OWED = 2
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("EX1_567", power);

    // ---------------------------------------- MINION - SHAMAN
    // [EX1_575] Mana Tide Totem - COST:3 [ATK:0/HP:3]
    // - Race: Totem, Faction: Neutral, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: At the end of your turn, draw a card.
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(new Trigger(TriggerType::TURN_END));
    power.GetTrigger()->tasks = { new DrawTask(1) };
    cards.emplace("EX1_575", power);

    // ---------------------------------------- MINION - SHAMAN
    // [NEW1_010] Al'Akir the Windlord - COST:8 [ATK:3/HP:5]
    // - Race: Elemental, Set: Expert1, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Charge, Divine Shield, Taunt, Windfury</b>
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - WINDFURY = 1
    // - TAUNT = 1
    // - DIVINE_SHIELD = 1
    // - CHARGE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("NEW1_010", power);
}

void Expert1CardsGen::AddShamanNonCollect(std::map<std::string, Power>& cards)
{
    Power power;

    // ----------------------------------- ENCHANTMENT - SHAMAN
    // [CS2_038e] Ancestral Spirit (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Resummon this minion.
    // --------------------------------------------------------
    power.ClearData();
    power.AddDeathrattleTask(new CopyTask(EntityType::SOURCE, ZoneType::PLAY));
    power.AddDeathrattleTask(new SummonTask(SummonSide::DEATHRATTLE));
    cards.emplace("CS2_038e", power);

    // ----------------------------------- ENCHANTMENT - SHAMAN
    // [CS2_053e] Far Sight (*) - COST:0
    // - Set: expert1,
    // --------------------------------------------------------
    // Text: One of your cards costs (3) less.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(new Enchant(std::vector<IEffect*>{
        Effects::ReduceCost(3),
        new Effect(GameTag::DISPLAYED_CREATOR, EffectOperator::SET, 1) }));
    power.AddTrigger(new Trigger(TriggerType::PLAY_CARD));
    power.GetTrigger()->triggerSource = TriggerSource::ENCHANTMENT_TARGET;
    power.GetTrigger()->tasks = { new RemoveEnchantmentTask() };
    power.GetTrigger()->removeAfterTriggered = true;
    cards.emplace("CS2_053e", power);

    // ---------------------------------------- MINION - SHAMAN
    // [EX1_tk11] Spirit Wolf (*) - COST:2 [ATK:2/HP:3]
    // - Faction: Neutral, Set: Expert1
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("EX1_tk11", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_258e] Overloading (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: Increased stats.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(new Enchant(Effects::AttackHealthN(1)));
    cards.emplace("EX1_258e", power);
}

void Expert1CardsGen::AddWarlock(std::map<std::string, Power>& cards)
{
    Power power;

    // --------------------------------------- MINION - WARLOCK
    // [CS2_059] Blood Imp - COST:1 [ATK:0/HP:1]
    // - Race: Demon, Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Stealth</b>. At the end of your turn,
    //       give another random friendly minion +1 Health.
    // --------------------------------------------------------
    // GameTag:
    // - STEALTH = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(new Trigger(TriggerType::TURN_END));
    power.GetTrigger()->tasks = {
        new RandomTask(EntityType::MINIONS_NOSOURCE, 1),
        new AddEnchantmentTask("CS2_059o", EntityType::STACK)
    };
    cards.emplace("CS2_059", power);

    // ---------------------------------------- SPELL - WARLOCK
    // [EX1_181] Call of the Void - COST:1
    // - Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: Add a random Demon to your hand.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        new RandomCardTask(CardType::MINION, CardClass::INVALID, Race::DEMON));
    power.AddPowerTask(new AddStackToTask(EntityType::HAND));
    cards.emplace("EX1_181", power);

    // --------------------------------------- MINION - WARLOCK
    // [EX1_301] Felguard - COST:3 [ATK:3/HP:5]
    // - Race: Demon, Faction: Neutral, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Battlecry:</b> Destroy one of your Mana Crystals.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new ManaCrystalTask(-1, false));
    cards.emplace("EX1_301", power);

    // ---------------------------------------- SPELL - WARLOCK
    // [EX1_303] Shadowflame - COST:4
    // - Faction: Neutral, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: Destroy a friendly minion and deal its Attack damage
    //       to all enemy minions.
    // --------------------------------------------------------
    // GameTag:
    // - AFFECTED_BY_SPELL_POWER = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_FRIENDLY_TARGET = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new GetGameTagTask(EntityType::TARGET, GameTag::ATK));
    power.AddPowerTask(new DamageNumberTask(EntityType::ENEMY_MINIONS, true));
    power.AddPowerTask(new DestroyTask(EntityType::TARGET));
    cards.emplace("EX1_303", power);

    // ---------------------------------------- SPELL - WARLOCK
    // [EX1_309] Siphon Soul - COST:6
    // - Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: Destroy a minion. Restore #3 Health to your hero.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new DestroyTask(EntityType::TARGET));
    power.AddPowerTask(new HealTask(EntityType::HERO, 3));
    cards.emplace("EX1_309", power);

    // ---------------------------------------- SPELL - WARLOCK
    // [EX1_312] Twisting Nether - COST:8
    // - Set: Expert1, Rarity: Epic
    // --------------------------------------------------------
    // Text: Destroy all minions.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new DestroyTask(EntityType::ALL_MINIONS));
    cards.emplace("EX1_312", power);

    // --------------------------------------- MINION - WARLOCK
    // [EX1_313] Pit Lord - COST:4 [ATK:5/HP:6]
    // - Race: Demon, Set: Expert1, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 5 damage to your hero.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new DamageTask(EntityType::HERO, 5));
    cards.emplace("EX1_313", power);

    // ---------------------------------------- SPELL - WARLOCK
    // [EX1_317] Sense Demons - COST:3
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: Draw 2 Demons from your deck.
    // --------------------------------------------------------
    power.ClearData();
    for (size_t i = 0; i < 2; ++i)
    {
        power.AddPowerTask(new IncludeTask(EntityType::DECK));
        power.AddPowerTask(
            new FilterStackTask(SelfCondition::IsRace(Race::DEMON)));
        power.AddPowerTask(new CountTask(EntityType::STACK));
        power.AddPowerTask(new ConditionTask(
            EntityType::HERO, { SelfCondition::IsStackNum(1, RelaSign::GEQ) }));
        power.AddPowerTask(new FlagTask(
            true,
            { new RandomTask(EntityType::STACK, 1), new DrawStackTask(1) }));
        power.AddPowerTask(new FlagTask(
            false, { new AddCardTask(EntityType::HAND, "EX1_317t") }));
    }
    cards.emplace("EX1_317", power);

    // ---------------------------------------- SPELL - WARLOCK
    // [EX1_319] Flame Imp - COST:1
    // - Race: Demon, Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 3 damage to your hero.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new DamageTask(EntityType::HERO, 3));
    cards.emplace("EX1_319", power);

    // ---------------------------------------- SPELL - WARLOCK
    // [EX1_320] Bane of Doom - COST:5
    // - Faction: Neutral, Set: Expert1, Rarity: Epic
    // --------------------------------------------------------
    // Text: Deal $2 damage to a character. If that kills it,
    //       summon a random Demon.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new DamageTask(EntityType::TARGET, 2, true));
    power.AddPowerTask(
        new ConditionTask(EntityType::TARGET, { SelfCondition::IsDead() }));
    power.AddPowerTask(new FlagTask(
        true,
        { new RandomCardTask(CardType::MINION, CardClass::INVALID, Race::DEMON),
          new SummonTask(SummonSide::SPELL) }));
    cards.emplace("EX1_320", power);

    // ---------------------------------------- SPELL - WARLOCK
    // [EX1_596] Demonfire - COST:2
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: Deal $2 damage to a minion. If it’s a friendly Demon,
    //       give it +2/+2 instead.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new ConditionTask(EntityType::TARGET,
                                         { SelfCondition::IsRace(Race::DEMON) },
                                         { RelaCondition::IsFriendly() }));
    power.AddPowerTask(new FlagTask(
        true, { new AddEnchantmentTask("EX1_596e", EntityType::TARGET) }));
    power.AddPowerTask(
        new FlagTask(false, { new DamageTask(EntityType::TARGET, 2, true) }));
    cards.emplace("EX1_596", power);
}

void Expert1CardsGen::AddWarlockNonCollect(std::map<std::string, Power>& cards)
{
    Power power;

    // ---------------------------------- ENCHANTMENT - WARLOCK
    // [CS2_059o] Blood Pact (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: Increased Health.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(new Enchant(Effects::HealthN(1)));
    cards.emplace("CS2_059o", power);

    // --------------------------------------- MINION - WARLOCK
    // [EX1_317t] Worthless Imp - COST:1 [ATK:1/HP:1]
    // - Race: Demon, Faction: Neutral, Set: Expert1
    // --------------------------------------------------------
    // Text: <i>You are out of demons!
    //       At least there are always imps...</i>
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("EX1_317t", power);

    // ---------------------------------- ENCHANTMENT - WARLOCK
    // [EX1_596e] Demonfire (*) - COST:0
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: This Demon has +2/+2.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(Enchants::GetEnchantFromText("EX1_596e"));
    cards.emplace("EX1_596e", power);
}

void Expert1CardsGen::AddWarrior(std::map<std::string, Power>& cards)
{
    Power power;

    // ---------------------------------------- SPELL - WARRIOR
    // [CS2_104] Rampage - COST:2
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: Give a damaged minion +3/+3.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_DAMAGED_TARGET = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new AddEnchantmentTask("CS2_104e", EntityType::TARGET));
    cards.emplace("CS2_104", power);

    // ---------------------------------------- SPELL - WARRIOR
    // [EX1_391] Slam - COST:2
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: Deal $2 damage to a minion. If it survives, draw a card.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new DamageTask(EntityType::TARGET, 2, true));
    power.AddPowerTask(
        new ConditionTask(EntityType::TARGET, { SelfCondition::IsNotDead() }));
    power.AddPowerTask(new FlagTask(true, { new DrawTask(1) }));
    cards.emplace("EX1_391", power);

    // ---------------------------------------- SPELL - WARRIOR
    // [EX1_392] Battle Rage - COST:2
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: Draw a card for each damaged friendly character.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        new CountTask(EntityType::FRIENDS, 0, { SelfCondition::IsDamaged() }));
    power.AddPowerTask(new DrawNumberTask());
    cards.emplace("EX1_392", power);

    // --------------------------------------- MINION - WARRIOR
    // [EX1_393] Amani Berserker - COST:2 [ATK:2/HP:3]
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: Has +3 Attack while damaged.
    // --------------------------------------------------------
    // GameTag:
    // - ENRAGED = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(new Trigger(Triggers::EnrageTrigger("EX1_393e")));
    cards.emplace("EX1_393", power);

    // ---------------------------------------- SPELL - WARRIOR
    // [EX1_407] Brawl - COST:5
    // - Faction: Neutral, Set: Expert1, Rarity: Epic
    // --------------------------------------------------------
    // Text: Destroy all minions except one. <i>(chosen randomly)</i>
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINIMUM_TOTAL_MINIONS = 2
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new RandomTask(EntityType::ALL_MINIONS, 1));
    power.AddPowerTask(
        new IncludeTask(EntityType::ALL_MINIONS, { EntityType::STACK }));
    power.AddPowerTask(new DestroyTask(EntityType::STACK));
    cards.emplace("EX1_407", power);

    // ---------------------------------------- SPELL - WARRIOR
    // [EX1_408] Mortal Strike - COST:4
    // - Faction: Neutral, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: Deal $4 damage. If you have 12 or less Health, deal $6 instead.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new ConditionTask(
        EntityType::HERO, { SelfCondition::IsHealth(12, RelaSign::LEQ) }));
    power.AddPowerTask(
        new FlagTask(true, { new DamageTask(EntityType::TARGET, 6, true) }));
    power.AddPowerTask(
        new FlagTask(false, { new DamageTask(EntityType::TARGET, 4, true) }));
    cards.emplace("EX1_408", power);

    // ---------------------------------------- SPELL - WARRIOR
    // [EX1_410] Shield Slam - COST:1
    // - Faction: Neutral, Set: Expert1, Rarity: Epic
    // --------------------------------------------------------
    // Text: Deal 1 damage to a minion for each Armor you have.
    // --------------------------------------------------------
    // GameTag:
    // - AFFECTED_BY_SPELL_POWER = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new GetGameTagTask(EntityType::HERO, GameTag::ARMOR));
    power.AddPowerTask(new DamageNumberTask(EntityType::TARGET, true));
    cards.emplace("EX1_410", power);

    // --------------------------------------- MINION - WARRIOR
    // [EX1_414] Grommash Hellscream - COST:8 [ATK:4/HP:9]
    // - Faction: Neutral, Set: Expert1, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Charge</b> Has +6 Attack while damaged.
    // --------------------------------------------------------
    // GameTag:
    // - CHARGE = 1
    // - ELITE = 1
    // - ENRAGED = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddAura(new EnrageEffect(AuraType::SELF, "EX1_414e"));
    cards.emplace("EX1_414", power);

    // ----------------------------------------- SPELL - WARRIOR
    // [EX1_607] Inner Rage - COST:0
    // - Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: Deal $1 damage to a minion and give it +2 Attack.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new DamageTask(EntityType::TARGET, 1, true));
    power.AddPowerTask(new AddEnchantmentTask("EX1_607e", EntityType::TARGET));
    cards.emplace("EX1_607", power);

    // ----------------------------------------- SPELL - WARRIOR
    // [NEW1_036] Commanding Shout - COST:2
    // - Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: Your minions can't be reduced below 1 Health this turn.
    //       Draw a card.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        new AddEnchantmentTask("NEW1_036e2", EntityType::PLAYER));
    power.AddPowerTask(new DrawTask(1));
    cards.emplace("NEW1_036", power);
}

void Expert1CardsGen::AddWarriorNonCollect(std::map<std::string, Power>& cards)
{
    Power power;

    // ---------------------------------- ENCHANTMENT - WARRIOR
    // [CS2_104e] Rampage (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: +3/+3.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(Enchants::GetEnchantFromText("CS2_104e"));
    cards.emplace("CS2_104e", power);

    // ---------------------------------- ENCHANTMENT - WARRIOR
    // [EX1_393e] Enraged (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: +3 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - ENRAGED = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(Enchants::GetEnchantFromText("EX1_393e"));
    cards.emplace("EX1_393e", power);

    // ---------------------------------- ENCHANTMENT - WARRIOR
    // [EX1_414e] Enraged (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: +6 Attack.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(Enchants::GetEnchantFromText("EX1_414e"));
    cards.emplace("EX1_414e", power);

    // ---------------------------------- ENCHANTMENT - WARRIOR
    // [EX1_607e] Inner Rage (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: +2 Attack.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(Enchants::GetEnchantFromText("EX1_607e"));
    cards.emplace("EX1_607e", power);

    // ---------------------------------- ENCHANTMENT - WARRIOR
    // [NEW1_036e] Commanding Shout (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: Can't be reduced below 1 Health this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(new Enchant(
        new Effect(GameTag::HEALTH_MINIMUM, EffectOperator::SET, 1)));
    {
        const auto enchant = dynamic_cast<Enchant*>(power.GetEnchant());
        enchant->isOneTurnEffect = true;
    }
    power.AddTrigger(new Trigger(TriggerType::PREDAMAGE));
    {
        const auto trigger = dynamic_cast<Trigger*>(power.GetTrigger());
        trigger->triggerSource = TriggerSource::ENCHANTMENT_TARGET;
        trigger->fastExecution = true;
        trigger->tasks = {
            new IncludeTask(EntityType::TARGET),
            new FuncPlayableTask([=](const std::vector<Playable*>& playables) {
                auto minion = dynamic_cast<Minion*>(playables[0]);
                int& eventNumber = minion->game->currentEventData->eventNumber;

                if (eventNumber >= minion->GetHealth())
                {
                    eventNumber = minion->GetHealth() - 1;
                }

                return std::vector<Playable*>{ minion };
            })
        };
    }
    cards.emplace("NEW1_036e", power);

    // ---------------------------------- ENCHANTMENT - WARRIOR
    // [NEW1_036e2] Commanding Shout (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: Your minions can't be reduced below 1 Health this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddAura(new Aura(AuraType::FIELD, "NEW1_036e"));
    cards.emplace("NEW1_036e2", power);
}

void Expert1CardsGen::AddNeutral(std::map<std::string, Power>& cards)
{
    Power power;

    // --------------------------------------- MINION - NEUTRAL
    // [CS1_069] Fen Creeper - COST:5 [ATK:3/HP:6]
    // - Faction: Alliance, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("CS1_069", power);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_117] Earthen Ring Farseer - COST:3 [ATK:3/HP:3]
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Restore 3 Health.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new HealTask(EntityType::TARGET, 3));
    cards.emplace("CS2_117", power);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_146] Southsea Deckhand - COST:1 [ATK:2/HP:1]
    // - Race: Pirate, Faction: Alliance, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: Has <b>Charge</b> while you have a weapon equipped.
    // --------------------------------------------------------
    // RefTag:
    // - CHARGE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddAura(new AdaptiveEffect(
        new SelfCondition(SelfCondition::IsWeaponEquipped()), GameTag::CHARGE));
    cards.emplace("CS2_146", power);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_151] Silver Hand Knight - COST:5 [ATK:4/HP:4]
    // - Faction: Alliance, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon a 2/2 Squire.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new SummonTask("CS2_152", SummonSide::RIGHT));
    cards.emplace("CS2_151", power);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_161] Ravenholdt Assassin - COST:7 [ATK:7/HP:5]
    // - Faction: Alliance, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Stealth</b>
    // --------------------------------------------------------
    // GameTag:
    // - STEALTH = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("CS2_161", power);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_169] Young Dragonhawk - COST:1 [ATK:1/HP:1]
    // - Race: Beast, Faction: Horde, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Windfury</b>
    // --------------------------------------------------------
    // GameTag:
    // - WINDFURY = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("CS2_169", power);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_181] Injured Blademaster - COST:3 [ATK:4/HP:7]
    // - Faction: Horde, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 4 damage to HIMSELF.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new DamageTask(EntityType::SOURCE, 4, false));
    cards.emplace("CS2_181", power);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_188] Abusive Sergeant - COST:1 [ATK:1/HP:1]
    // - Faction: Alliance, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give a minion +2 Attack this turn.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new AddEnchantmentTask("CS2_188o", EntityType::TARGET));
    cards.emplace("CS2_188", power);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_203] Ironbeak Owl - COST:3 [ATK:2/HP:1]
    // - Race: Beast, Faction: Horde, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Silence</b> a minion.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - SILENCE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new SilenceTask(EntityType::TARGET));
    cards.emplace("CS2_203", power);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_221] Spiteful Smith - COST:5 [ATK:4/HP:6]
    // - Faction: Horde, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Enrage:</b> Your weapon has +2 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - ENRAGED = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddAura(new EnrageEffect(AuraType::WEAPON, "CS2_221e"));
    cards.emplace("CS2_221", power);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_227] Venture Co. Mercenary - COST:5 [ATK:7/HP:6]
    // - Faction: Horde, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: Your minions cost (3) more.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddAura(new Aura(AuraType::HAND, { Effects::AddCost(3) }));
    {
        const auto aura = dynamic_cast<Aura*>(power.GetAura());
        aura->condition = new SelfCondition(SelfCondition::IsMinion());
    }
    cards.emplace("CS2_227", power);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_231] Wisp - COST:0 [ATK:1/HP:1]
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("CS2_231", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_001] Lightwarden - COST:1 [ATK:1/HP:2]
    // - Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: Whenever a character is healed, gain +2 Attack.
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(new Trigger(TriggerType::HEAL));
    power.GetTrigger()->tasks = { new AddEnchantmentTask("EX1_001e",
                                                         EntityType::SOURCE) };
    cards.emplace("EX1_001", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_002] The Black Knight - COST:6 [ATK:4/HP:5]
    // - Set: Expert1, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Destroy an enemy minion with <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_MUST_TARGET_TAUNTER = 0
    // - REQ_ENEMY_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new DestroyTask(EntityType::TARGET));
    cards.emplace("EX1_002", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_004] Young Priestess - COST:1 [ATK:2/HP:1]
    // - Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: At the end of your turn, give another random
    //       friendly minion +1 Health.
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(new Trigger(TriggerType::TURN_END));
    power.GetTrigger()->tasks = {
        new RandomTask(EntityType::MINIONS_NOSOURCE, 1),
        new AddEnchantmentTask("EX1_004e", EntityType::STACK)
    };
    cards.emplace("EX1_004", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_005] Big Game Hunter - COST:5 [ATK:4/HP:2]
    // - Set: Expert1, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Destroy a minion
    //       with 7 or more Attack.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_TARGET_MIN_ATTACK = 7
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new DestroyTask(EntityType::TARGET));
    cards.emplace("EX1_005", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_006] Alarm-o-Bot - COST:3 [ATK:0/HP:3]
    // - Race: Mechanical, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: At the start of your turn,
    //       swap this minion with a
    //       random one in your hand.
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(new Trigger(TriggerType::TURN_START));
    power.GetTrigger()->condition =
        new SelfCondition(SelfCondition::HasMinionInHand());
    power.GetTrigger()->tasks = {
        new GetGameTagTask(EntityType::SOURCE, GameTag::ZONE_POSITION),
        new MoveToSetasideTask(EntityType::SOURCE),
        new IncludeTask(EntityType::HAND),
        new FilterStackTask(SelfCondition::IsMinion()),
        new RandomTask(EntityType::STACK, 1),
        new RemoveHandTask(EntityType::STACK),
        new SummonTask(SummonSide::NUMBER),
        new ReturnHandTask(EntityType::SOURCE)
    };
    cards.emplace("EX1_006", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_007] Acolyte of Pain - COST:3 [ATK:1/HP:3]
    // - Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: Whenever this minion takes damage, draw a card.
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(new Trigger(TriggerType::TAKE_DAMAGE));
    power.GetTrigger()->triggerSource = TriggerSource::SELF;
    power.GetTrigger()->tasks = { new DrawTask(1) };
    cards.emplace("EX1_007", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_008] Argent Squire - COST:1 [ATK:1/HP:1]
    // - Faction: Alliance, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Divine Shield</b>
    // --------------------------------------------------------
    // GameTag:
    // - DIVINE_SHIELD = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("EX1_008", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_009] Angry Chicken - COST:1 [ATK:1/HP:1]
    // - Race: Beast, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Enrage:</b> +5 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - ENRAGED = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(new Trigger(Triggers::EnrageTrigger("EX1_009e")));
    cards.emplace("EX1_009", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_010] Worgen Infiltrator - COST:1 [ATK:2/HP:1]
    // - Faction: Alliance, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Stealth</b>
    // --------------------------------------------------------
    // GameTag:
    // - STEALTH = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("EX1_010", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_012] Bloodmage Thalnos - COST:2 [ATK:1/HP:1]
    // - Fac: neutral, Set: expert1, Rarity: legendary
    // --------------------------------------------------------
    // Text: <b>Spell Damage +1</b>
    //       <b>Deathrattle:</b> Draw a card.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - SPELLPOWER = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddDeathrattleTask(new DrawTask(1));
    cards.emplace("EX1_012", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_014] King Mukla - COST:3 [ATK:5/HP:5]
    // - Race: Beast, Set: Expert1, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give your opponent 2 Bananas.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new AddCardTask(EntityType::ENEMY_HAND, "EX1_014t", 2));
    cards.emplace("EX1_014", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_017] Jungle Panther - COST:3 [ATK:4/HP:2]
    // - Race: Beast, Faction: Horde, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Stealth</b>
    // --------------------------------------------------------
    // GameTag:
    // - STEALTH = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("EX1_017", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_020] Scarlet Crusader - COST:3 [ATK:3/HP:1]
    // - Faction: Alliance, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Divine Shield</b>
    // --------------------------------------------------------
    // GameTag:
    // - DIVINE_SHIELD = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("EX1_020", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_021] Thrallmar Farseer - COST:3 [ATK:2/HP:3]
    // - Faction: Horde, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Windfury</b>
    // --------------------------------------------------------
    // GameTag:
    // - WINDFURY = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("EX1_021", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_023] Silvermoon Guardian - COST:4 [ATK:3/HP:3]
    // - Faction: Horde, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Divine Shield</b>
    // --------------------------------------------------------
    // GameTag:
    // - DIVINE_SHIELD = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("EX1_023", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_028] Stranglethorn Tiger - COST:5 [ATK:5/HP:5]
    // - Race: Beast, Faction: Alliance, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Stealth</b>
    // --------------------------------------------------------
    // GameTag:
    // - STEALTH = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("EX1_028", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_029] Leper Gnome - COST:1 [ATK:1/HP:1]
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Deal 2 damage to the enemy hero.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddDeathrattleTask(new DamageTask(EntityType::ENEMY_HERO, 2, false));
    cards.emplace("EX1_029", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_032] Sunwalker - COST:6 [ATK:4/HP:5]
    // - Faction: Alliance, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Divine Shield</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - DIVINE_SHIELD = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("EX1_032", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_033] Windfury Harpy - COST:6 [ATK:4/HP:5]
    // - Faction: Alliance, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Windfury</b>
    // --------------------------------------------------------
    // GameTag:
    // - WINDFURY = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("EX1_033", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_043] Twilight Drake - COST:4 [ATK:4/HP:1]
    // - Faction: Alliance, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Gain +1 Health for each card in your hand.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new CountTask(EntityType::HAND));
    power.AddPowerTask(
        new AddEnchantmentTask("EX1_043e", EntityType::SOURCE, true));
    cards.emplace("EX1_043", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_044] Questing Adventurer - COST:3 [ATK:2/HP:2]
    // - Faction: Alliance, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: Whenever you play a card, gain +1/+1.
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(new Trigger(TriggerType::PLAY_CARD));
    power.GetTrigger()->triggerSource = TriggerSource::FRIENDLY;
    power.GetTrigger()->tasks = { new AddEnchantmentTask("EX1_044e",
                                                         EntityType::SOURCE) };
    cards.emplace("EX1_044", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_045] Ancient Watcher - COST:2 [ATK:4/HP:5]
    // - Faction: Alliance, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: Can't attack.
    // --------------------------------------------------------
    // GameTag:
    // - CANT_ATTACK = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("EX1_045", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_046] Dark Iron Dwarf - COST:4 [ATK:4/HP:4]
    // - Faction: Alliance, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give a minion +2 Attack this turn.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new AddEnchantmentTask("EX1_046e", EntityType::TARGET));
    cards.emplace("EX1_046", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_048] Spellbreaker - COST:4 [ATK:4/HP:3]
    // - Faction: Horde, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Silence</b> a minion.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_NONSELF_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - SILENCE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new SilenceTask(EntityType::TARGET));
    cards.emplace("EX1_048", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_049] Youthful Brewmaster - COST:2 [ATK:3/HP:2]
    // - Faction: Alliance, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Return a friendly minion
    //       from the battlefield to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_NONSELF_TARGET = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_FRIENDLY_TARGET = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new ReturnHandTask(EntityType::TARGET));
    cards.emplace("EX1_049", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_055] Mana Addict - COST:2 [ATK:1/HP:3]
    // - Faction: Alliance, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: Whenever you cast a spell, gain +2 Attack this turn.
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(new Trigger(TriggerType::CAST_SPELL));
    power.GetTrigger()->triggerSource = TriggerSource::FRIENDLY;
    power.GetTrigger()->tasks = { new AddEnchantmentTask("EX1_055o",
                                                         EntityType::SOURCE) };
    cards.emplace("EX1_055", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_057] Ancient Brewmaster - COST:4 [ATK:5/HP:4]
    // - Faction: Alliance, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Return a friendly minion
    //       from the battlefield to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_FRIENDLY_TARGET = 0
    // - REQ_NONSELF_TARGET = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new ReturnHandTask(EntityType::TARGET));
    cards.emplace("EX1_057", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_058] Sunfury Protector - COST:2 [ATK:2/HP:3]
    // - Faction: Alliance, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give adjacent minions <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new IncludeTask(EntityType::MINIONS));
    power.AddPowerTask(
        new FilterStackTask(EntityType::SOURCE, RelaCondition::IsSideBySide()));
    power.AddPowerTask(
        new SetGameTagTask(EntityType::STACK, GameTag::TAUNT, 1));
    cards.emplace("EX1_058", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_059] Crazed Alchemist - COST:2 [ATK:2/HP:2]
    // - Faction: Neutral, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Swap the Attack and Health of a minion.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // - REQ_TARGET_IF_AVAILABLE = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        new SwapAttackHealthTask(EntityType::TARGET, "EX1_059e"));
    cards.emplace("EX1_059", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_067] Argent Commander - COST:6 [ATK:4/HP:2]
    // - Faction: Neutral, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Charge</b>
    //       <b>Divine Shield</b>
    // --------------------------------------------------------
    // GameTag:
    // - DIVINE_SHIELD = 1
    // - CHARGE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("EX1_067", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_076] Pint-Sized Summoner - COST:2 [ATK:2/HP:2]
    // - Faction: Alliance, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: The first minion you play each turn costs (1) less.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddAura(new SwitchingAura(
        AuraType::HAND, SelfCondition::MinionsPlayedThisTurn(0),
        TriggerType::PLAY_MINION, { Effects::ReduceCost(1) }));
    {
        const auto aura = dynamic_cast<SwitchingAura*>(power.GetAura());
        aura->condition = new SelfCondition(SelfCondition::IsMinion());
    }
    cards.emplace("EX1_076", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_080] Secretkeeper - COST:1 [ATK:1/HP:2]
    // - Faction: Alliance, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: Whenever a <b>Secret</b> is played, gain +1/+1.
    // --------------------------------------------------------
    // RefTag:
    // - SECRET = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(new Trigger(TriggerType::CAST_SPELL));
    power.GetTrigger()->condition =
        new SelfCondition(SelfCondition::IsSecret());
    power.GetTrigger()->tasks = { new AddEnchantmentTask("EX1_080o",
                                                         EntityType::SOURCE) };
    cards.emplace("EX1_080", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_082] Mad Bomber - COST:2 [ATK:3/HP:2]
    // - Faction: Alliance, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 3 damage randomly split
    //       between all other characters.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        new EnqueueTask({ new RandomTask(EntityType::ALL_NOSOURCE, 1),
                          new DamageTask(EntityType::STACK, 1) },
                        3, false));
    cards.emplace("EX1_082", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_083] Tinkmaster Overspark - COST:3 [ATK:3/HP:3]
    // - Faction: Alliance, Set: Expert1, Rarity: Legendary
    // --------------------------------------------------------
    // Text: [x]<b>Battlecry:</b> Transform another random minion
    //       into a 5/5 Devilsaur or a 1/1 Squirrel.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new RandomTask(EntityType::ALL_MINIONS_NOSOURCE, 1));
    power.AddPowerTask(new ChanceTask(true));
    power.AddPowerTask(new FlagTask(
        true, { new TransformTask(EntityType::STACK, "EX1_tk28") }));
    power.AddPowerTask(new FlagTask(
        false, { new TransformTask(EntityType::STACK, "EX1_tk29") }));
    cards.emplace("EX1_083", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_085] Mind Control Tech - COST:3 [ATK:3/HP:3]
    // - Faction: Alliance, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If your opponent has 4 or
    //       more minions, take control of one at random.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new IncludeTask(EntityType::ENEMY_MINIONS));
    power.AddPowerTask(
        new FuncPlayableTask([=](const std::vector<Playable*>& playables) {
            return playables.size() > 3 ? playables : std::vector<Playable*>{};
        }));
    power.AddPowerTask(new RandomTask(EntityType::STACK, 1));
    power.AddPowerTask(new ConditionTask(EntityType::SOURCE,
                                         { SelfCondition::IsFieldFull() }));
    power.AddPowerTask(
        new FlagTask(true, { new DestroyTask(EntityType::STACK) }));
    power.AddPowerTask(
        new FlagTask(false, { new ControlTask(EntityType::STACK) }));
    cards.emplace("EX1_085", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_089] Arcane Golem - COST:3 [ATK:4/HP:4]
    // - Faction: Neutral, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give your opponent a Mana Crystal.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new ManaCrystalTask(1, false, true));
    cards.emplace("EX1_089", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_093] Defender of Argus - COST:4 [ATK:2/HP:3]
    // - Faction: Alliance, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give adjacent minions +1/+1 and <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new IncludeTask(EntityType::MINIONS));
    power.AddPowerTask(
        new FilterStackTask(EntityType::SOURCE, RelaCondition::IsSideBySide()));
    power.AddPowerTask(new AddEnchantmentTask("EX1_093e", EntityType::STACK));
    cards.emplace("EX1_093", power);

    // ---------------------------------------- MINION - NEUTRAL
    // [EX1_095] Gadgetzan Auctioneer - COST:5 [ATK:4/HP:4]
    // - Faction: Neutral, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: Whenever you cast a spell, draw a card.
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(new Trigger(TriggerType::CAST_SPELL));
    power.GetTrigger()->triggerSource = TriggerSource::FRIENDLY;
    power.GetTrigger()->tasks = { new DrawTask(1) };
    cards.emplace("EX1_095", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_096] Loot Hoarder - COST:2 [ATK:2/HP:1]
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Draw a card.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddDeathrattleTask(new DrawTask(1));
    cards.emplace("EX1_096", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_097] Abomination - COST:5 [ATK:4/HP:4]
    // - Faction: Neutral, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Taunt</b>. <b>Deathrattle:</b> Deal 2
    //       damage to ALL characters.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddDeathrattleTask(new DamageTask(EntityType::ALL, 2));
    cards.emplace("EX1_097", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_100] Lorewalker Cho - COST:2 [ATK:0/HP:4]
    // - Faction: Neutral, Set: Expert1, Rarity: Legendary
    // --------------------------------------------------------
    // Text: Whenever a player casts a spell, put a copy
    //       into the other player's hand.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(new Trigger(TriggerType::CAST_SPELL));
    power.GetTrigger()->tasks = {
        new ConditionTask(EntityType::TARGET, { RelaCondition::IsFriendly() }),
        new FlagTask(true, { new CopyTask(EntityType::TARGET, ZoneType::HAND, 1,
                                          false, true) }),
        new FlagTask(false,
                     { new CopyTask(EntityType::TARGET, ZoneType::HAND) })
    };
    cards.emplace("EX1_100", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_102] Demolisher - COST:3 [ATK:1/HP:4]
    // - Race: Mechanical, - Faction: Neutral, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: At the start of your turn, deal 2 damage to a random enemy.
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(new Trigger(TriggerType::TURN_START));
    power.GetTrigger()->tasks = { new RandomTask(EntityType::ENEMIES, 1),
                                  new DamageTask(EntityType::STACK, 2) };
    cards.emplace("EX1_102", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_103] Coldlight Seer - COST:3 [ATK:2/HP:3]
    // - Race: Murloc, Faction: Neutral, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give your other Murlocs +2 Health.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new IncludeTask(EntityType::MINIONS_NOSOURCE));
    power.AddPowerTask(
        new FilterStackTask(SelfCondition::IsRace(Race::MURLOC)));
    power.AddPowerTask(new AddEnchantmentTask("EX1_103e", EntityType::STACK));
    cards.emplace("EX1_103", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_105] Mountain Giant - COST:12 [ATK:8/HP:8]
    // - Race: Elemental, Faction: Neutral, Set: Expert1, Rarity: Epic
    // --------------------------------------------------------
    // Text: Costs (1) less for each other card in your hand.
    // --------------------------------------------------------
    power.ClearData();
    power.AddAura(new AdaptiveCostEffect([](Playable* playable) {
        return playable->player->GetHandZone()->GetCount() - 1;
    }));
    cards.emplace("EX1_105", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_110] Cairne Bloodhoof - COST:6 [ATK:4/HP:5]
    // - Faction: Alliance, Set: Expert1, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon a 4/5 Baine Bloodhoof.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddDeathrattleTask(
        new SummonTask("EX1_110t", SummonSide::DEATHRATTLE));
    cards.emplace("EX1_110", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_116] Leeroy Jenkins - COST:5 [ATK:6/HP:2]
    // - Faction: Alliance, Set: Expert1, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Charge</b>. <b>Battlecry:</b> Summon two 1/1 Whelps
    //       for your opponent.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - CHARGE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new EnqueueTask({ new SummonOpTask("EX1_116t") }, 2));
    cards.emplace("EX1_116", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_162] Dire Wolf Alpha - COST:2 [ATK:2/HP:2]
    // - Race: Beast, Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: Adjacent minions have +1 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - ADJACENT_BUFF = 1
    // - AURA = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddAura(new AdjacentAura("EX1_162o"));
    cards.emplace("EX1_162", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_170] Emperor Cobra - COST:3 [ATK:2/HP:3]
    // - Race: Beast, Faction: Neutral, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Poisonous</b>
    // --------------------------------------------------------
    // GameTag:
    // - POISONOUS = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("EX1_170", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_249] Baron Geddon - COST:7 [ATK:7/HP:5]
    // - Race: Elemental, Faction: Neutral, Set: Expert1, Rarity: Legendary
    // --------------------------------------------------------
    // Text: At the end of your turn, deal 2 damage to ALL other characters.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(new Trigger(TriggerType::TURN_END));
    power.GetTrigger()->tasks = { new DamageTask(EntityType::ALL_NOSOURCE, 2) };
    cards.emplace("EX1_249", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_283] Frost Elemental - COST:6 [ATK:5/HP:5]
    // - Race: Elemental, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Freeze</b> a character.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        new SetGameTagTask(EntityType::TARGET, GameTag::FROZEN, 1));
    cards.emplace("EX1_283", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_390] Tauren Warrior - COST:3 [ATK:2/HP:3]
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b> Has +3 Attack while damaged.
    // --------------------------------------------------------
    // GameTag:
    // - ENRAGED = 1
    // - TAUNT = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(new Trigger(Triggers::EnrageTrigger("EX1_390e")));
    cards.emplace("EX1_390", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_396] Mogu'shan Warden - COST:4 [ATK:1/HP:7]
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("EX1_396", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_405] Shieldbearer - COST:1 [ATK:0/HP:4]
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("EX1_405", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_412] Raging Worgen - COST:3 [ATK:3/HP:3]
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: Has +1 Attack and <b>Windfury</b> while damaged.
    // --------------------------------------------------------
    // GameTag:
    // - ENRAGED = 1
    // --------------------------------------------------------
    // RefTag:
    // - WINDFURY = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddAura(new EnrageEffect(AuraType::SELF, "EX1_412e"));
    cards.emplace("EX1_412", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_507] Murloc Warleader - COST:3 [ATK:3/HP:3]
    // - Race: Murloc, Faction: Neutral, Set: Expert1, Rarity: Epic
    // --------------------------------------------------------
    // Text: Your other Murlocs have +2 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddAura(new Aura(AuraType::FIELD_EXCEPT_SOURCE, "EX1_507e"));
    {
        const auto aura = dynamic_cast<Aura*>(power.GetAura());
        aura->condition =
            new SelfCondition(SelfCondition::IsRace(Race::MURLOC));
    }
    cards.emplace("EX1_507", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_509] Murloc Tidecaller - COST:1 [ATK:1/HP:2]
    // - Race: Murloc, Faction: Neutral, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: Whenever you summon a Murloc, gain +1 Attack.
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(new Trigger(TriggerType::SUMMON));
    power.GetTrigger()->triggerSource = TriggerSource::FRIENDLY;
    power.GetTrigger()->condition =
        new SelfCondition(SelfCondition::IsRace(Race::MURLOC));
    power.GetTrigger()->tasks = { new AddEnchantmentTask("EX1_509e",
                                                         EntityType::SOURCE) };
    cards.emplace("EX1_509", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_556] Harvest Golem - COST:3 [ATK:2/HP:3]
    // - Race: Mechanical, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon a 2/1 Damaged Golem.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddDeathrattleTask(
        new SummonTask("skele21", SummonSide::DEATHRATTLE));
    cards.emplace("EX1_556", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_557] Nat Pagle - COST:2 [ATK:0/HP:4]
    // - Faction: Neutral, Set: Expert1, Rarity: Legendary
    // --------------------------------------------------------
    // Text: At the start of your turn, you have a 50% chance to
    //       draw an extra card.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(new Trigger(TriggerType::TURN_START));
    power.GetTrigger()->percentage = 0.5f;
    power.GetTrigger()->tasks = { new DrawTask(1) };
    cards.emplace("EX1_557", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_563] Malygos - COST:9 [ATK:4/HP:12]
    // - Race: Dragon, Faction: Neutral, Set: Expert1, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Spell Damage +5</b>
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - SPELLPOWER = 5
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("EX1_563", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_564] Faceless Manipulator - COST:5 [ATK:3/HP:3]
    // - Faction: Neutral, Set: Expert1, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Choose a minion and become a copy of it.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_NONSELF_TARGET = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new TransformCopyTask());
    cards.emplace("EX1_564", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_572] Ysera - COST:9 [ATK:4/HP:12]
    // - Race: Dragon, Faction: Neutral, Set: Expert1, Rarity: Legendary
    // --------------------------------------------------------
    // Text: At the end of your turn, add a Dream Card to your hand.
    // --------------------------------------------------------
    // Entourage: DREAM_01, DREAM_02, DREAM_03, DREAM_04, DREAM_05
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(new Trigger(TriggerType::TURN_END));
    power.GetTrigger()->tasks = { new RandomEntourageTask(1),
                                  new AddStackToTask(EntityType::HAND) };
    cards.emplace("EX1_572", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_577] The Beast - COST:6 [ATK:9/HP:7]
    // - Race: Beast, Faction: Neutral, Set: Expert1, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon a 3/3 Finkle Einhorn for your opponent.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddDeathrattleTask(new SummonOpTask("EX1_finkle"));
    cards.emplace("EX1_577", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_583] Priestess of Elune - COST:6 [ATK:5/HP:4]
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Restore 4 Health to your hero.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new HealTask(EntityType::HERO, 4));
    cards.emplace("EX1_583", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_584] Ancient Mage - COST:4 [ATK:2/HP:5]
    // - Faction: Neutral, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give adjacent minions <b>Spell Damage +1</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - SPELLPOWER = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new IncludeTask(EntityType::MINIONS));
    power.AddPowerTask(
        new FilterStackTask(EntityType::SOURCE, RelaCondition::IsSideBySide()));
    power.AddPowerTask(new AddEnchantmentTask("EX1_584e", EntityType::STACK));
    cards.emplace("EX1_584", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_597] Imp Master - COST:3 [ATK:1/HP:5]
    // - Faction: Neutral, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: At the end of your turn, deal 1 damage to this minion
    //       and summon a 1/1 Imp.
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(new Trigger(TriggerType::TURN_END));
    power.GetTrigger()->tasks = { new DamageTask(EntityType::SOURCE, 1),
                                  new SummonTask("EX1_598",
                                                 SummonSide::RIGHT) };
    cards.emplace("EX1_597", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_614] Illidan Stormrage - COST:6 [ATK:7/HP:5]
    // - Race: Demon, Faction: Neutral, Set: Expert1, Rarity: Legendary
    // --------------------------------------------------------
    // Text: Whenever you play a card, summon a 2/1 Flame of_Azzinoth.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(new Trigger(TriggerType::PLAY_CARD));
    power.GetTrigger()->tasks = { new SummonTask("EX1_614t",
                                                 SummonSide::RIGHT) };
    cards.emplace("EX1_614", power);

    // --------------------------------------- MINION - NEUTRAL
    // [NEW1_017] Hungry Crab - COST:1 [ATK:1/HP:2]
    // - Race: Beast, Set: Expert1, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Destroy a Murloc and gain +2/+2.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_TARGET_WITH_RACE = 14
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new ConditionTask(
        EntityType::TARGET, { SelfCondition::IsRace(Race::MURLOC) }));
    power.AddPowerTask(new FlagTask(
        true, { new DestroyTask(EntityType::TARGET),
                new AddEnchantmentTask("NEW1_017e", EntityType::SOURCE) }));
    cards.emplace("NEW1_017", power);

    // --------------------------------------- MINION - NEUTRAL
    // [NEW1_018] Bloodsail Raider - COST:2 [ATK:2/HP:3]
    // - Race: Pirate, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Gain Attack equal to the Attack
    //       of your weapon.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new GetGameTagTask(EntityType::WEAPON, GameTag::ATK));
    power.AddPowerTask(
        new AddEnchantmentTask("NEW1_018e", EntityType::SOURCE, true));
    cards.emplace("NEW1_018", power);

    // --------------------------------------- MINION - NEUTRAL
    // [NEW1_019] Knife Juggler - COST:2 [ATK:2/HP:2]
    // - Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: After you summon a minion,
    //       deal 1 damage to a random enemy.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(new Trigger(TriggerType::AFTER_SUMMON));
    power.GetTrigger()->triggerSource = TriggerSource::MINIONS_EXCEPT_SELF;
    power.GetTrigger()->tasks = { new IncludeTask(EntityType::ENEMIES),
                                  new FilterStackTask(
                                      SelfCondition::IsNotDead()),
                                  new RandomTask(EntityType::STACK, 1),
                                  new DamageTask(EntityType::STACK, 1) };
    cards.emplace("NEW1_019", power);

    // --------------------------------------- MINION - NEUTRAL
    // [NEW1_020] Wild Pyromancer - COST:2 [ATK:3/HP:2]
    // - Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: After you cast a spell, deal 1 damage to ALL minions.
    // --------------------------------------------------------
    power.AddTrigger(new Trigger(TriggerType::AFTER_CAST));
    power.GetTrigger()->triggerSource = TriggerSource::FRIENDLY;
    power.GetTrigger()->tasks = { new DamageTask(EntityType::ALL_MINIONS, 1) };
    cards.emplace("NEW1_020", power);

    // --------------------------------------- MINION - NEUTRAL
    // [NEW1_021] Doomsayer - COST:2 [ATK:0/HP:7]
    // - Faction: Neutral, Set: Expert1, Rarity: Epic
    // --------------------------------------------------------
    // Text: At the start of your turn, destroy ALL minions.
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(new Trigger(TriggerType::TURN_START));
    power.GetTrigger()->tasks = { new DestroyTask(EntityType::ALL_MINIONS) };
    cards.emplace("NEW1_021", power);

    // --------------------------------------- MINION - NEUTRAL
    // [NEW1_024] Captain Greenskin - COST:5 [ATK:5/HP:4]
    // - Race: Pirate, Set: Expert1, Rarity: legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give your weapon +1/+1.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new AddEnchantmentTask("NEW1_024o", EntityType::WEAPON));
    cards.emplace("NEW1_024", power);

    // --------------------------------------- MINION - NEUTRAL
    // [NEW1_025] Bloodsail Corsair - COST:2 [ATK:1/HP:2]
    // - Race: Pirate, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Remove 1 Durability from your
    //       opponent's weapon.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new RemoveDurabilityTask(1, true));
    cards.emplace("NEW1_025", power);

    // --------------------------------------- MINION - NEUTRAL
    // [NEW1_027] Southsea Captain - COST:3 [ATK:3/HP:3]
    // - Race: Pirate, Faction: Neutral, Set: Expert1, Rarity: Epic
    // --------------------------------------------------------
    // Text: Your other Pirates have +1/+1.
    // --------------------------------------------------------
    power.ClearData();
    power.AddAura(new Aura(AuraType::FIELD_EXCEPT_SOURCE, "NEW1_027e"));
    {
        const auto aura = dynamic_cast<Aura*>(power.GetAura());
        aura->condition =
            new SelfCondition(SelfCondition::IsRace(Race::PIRATE));
    }
    cards.emplace("NEW1_027", power);

    // --------------------------------------- MINION - NEUTRAL
    // [NEW1_030] Deathwing - COST:10 [ATK:12/HP:12]
    // - Race: Dragon, Set: Expert1, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Destroy all other minions and discard your hand.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new DestroyTask(EntityType::ALL_MINIONS_NOSOURCE));
    power.AddPowerTask(new RemoveHandTask(EntityType::HAND));
    cards.emplace("NEW1_030", power);

    // --------------------------------------- MINION - NEUTRAL
    // [NEW1_037] Master Swordsmith - COST:2 [ATK:1/HP:3]
    // - Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: At the end of your turn,
    //       give another random friendly minion +1 Attack.
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(new Trigger(TriggerType::TURN_END));
    power.GetTrigger()->tasks = {
        new RandomTask(EntityType::MINIONS_NOSOURCE, 1),
        new AddEnchantmentTask("NEW1_037e", EntityType::STACK)
    };
    cards.emplace("NEW1_037", power);

    // --------------------------------------- MINION - NEUTRAL
    // [NEW1_040] Hogger - COST:6 [ATK:4/HP:4]
    // - Set: Expert1, Rarity: Legendary
    // --------------------------------------------------------
    // Text: At the end of your turn,
    //       summon a 2/2 Gnoll with <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(new Trigger(TriggerType::TURN_END));
    power.GetTrigger()->tasks = { new SummonTask("NEW1_040t",
                                                 SummonSide::RIGHT) };
    cards.emplace("NEW1_040", power);

    // --------------------------------------- MINION - NEUTRAL
    // [NEW1_041] Stampeding Kodo - COST:5 [ATK:3/HP:5]
    // - Race: Beast, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Destroy a random enemy minion
    //       with 2 or less Attack.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new IncludeTask(EntityType::ENEMY_MINIONS));
    power.AddPowerTask(new FilterStackTask(
        SelfCondition::IsTagValue(GameTag::ATK, 2, RelaSign::LEQ)));
    power.AddPowerTask(new RandomTask(EntityType::STACK, 1));
    power.AddPowerTask(new DestroyTask(EntityType::STACK));
    cards.emplace("NEW1_041", power);
}
void Expert1CardsGen::AddNeutralNonCollect(std::map<std::string, Power>& cards)
{
    Power power;

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_152] Squire (*) - COST:1 [ATK:2/HP:2]
    // - Faction: Alliance, Set: Expert1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("CS2_152", power);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [CS2_188o] Inspired (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: This minion has +2 Attack this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(Enchants::GetEnchantFromText("CS2_188o"));
    cards.emplace("CS2_188o", power);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [CS2_221e] Sharp! (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: +2 Attack from Spiteful Smith.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(
        new Enchant(new Effect(GameTag::ATK, EffectOperator::ADD, 2)));
    cards.emplace("CS2_221e", power);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DREAM_05e] Nightmare (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: This minion has +5/+5, but will be destroyed soon.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(Enchants::GetEnchantFromText("DREAM_05e"));
    power.AddTrigger(new Trigger(TriggerType::TURN_START));
    power.GetTrigger()->tasks = { new DestroyTask(EntityType::TARGET) };
    cards.emplace("DREAM_05e", power);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [EX1_001e] Warded (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: Increased Attack.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(new Enchant(Effects::AttackN(2)));
    cards.emplace("EX1_001e", power);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [EX1_004e] Elune's Grace (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: Increased Health.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(new Enchant(Effects::HealthN(2)));
    cards.emplace("EX1_004e", power);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [EX1_009e] Enraged (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: +5 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - ENRAGED = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(Enchants::GetEnchantFromText("EX1_009e"));
    cards.emplace("EX1_009e", power);

    // ---------------------------------------- SPELL - NEUTRAL
    // [EX1_014t] Bananas (*) - COST:1
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: Give a minion +1/+1.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new AddEnchantmentTask("EX1_014te", EntityType::TARGET));
    cards.emplace("EX1_014t", power);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [EX1_014te] Bananas (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: Has +1/+1.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(Enchants::GetEnchantFromText("EX1_014te"));
    cards.emplace("EX1_014te", power);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [EX1_043e] Hour of Twilight (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: Increased Health.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(new Enchant(Enchants::AddHealthScriptTag));
    cards.emplace("EX1_043e", power);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [EX1_044e] Level Up! (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: Increased Attack and Health.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(new Enchant(Effects::AttackHealthN(1)));
    cards.emplace("EX1_044e", power);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [EX1_046e] Tempered (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: +2 Attack this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(Enchants::GetEnchantFromText("EX1_046e"));
    cards.emplace("EX1_046e", power);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [EX1_055o] Empowered (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: Mana Addict has increased Attack.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(new Enchant(Effects::AttackN(2), false, true));
    cards.emplace("EX1_055o", power);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [EX1_059e] Experiments! (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: Attack and Health have been swapped by Crazed Alchemist.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(new Enchant(Enchants::SetAttackHealthScriptTag));
    cards.emplace("EX1_059e", power);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [EX1_080o] Keeping Secrets (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: Increased stats.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(new Enchant({ Effects::AttackHealthN(1) }));
    cards.emplace("EX1_080o", power);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [EX1_093e] Hand of Argus (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: +1/+1 and <b>Taunt</b>.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(Enchants::GetEnchantFromText("EX1_093e"));
    cards.emplace("EX1_093e", power);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [EX1_103e] Mrghlglhal (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: +2 Health.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(Enchants::GetEnchantFromText("EX1_103e"));
    cards.emplace("EX1_103e", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_110t] Baine Bloodhoof (*) - COST:4 [ATK:4/HP:5]
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("EX1_110t", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_116t] Whelp (*) - COST:1 [ATK:1/HP:1]
    // - Race: Dragon, Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("EX1_116t", power);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [EX1_162o] Strength of the Pack (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: +1 Attack from Dire Wolf Alpha.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(Enchants::GetEnchantFromText("EX1_162o"));
    cards.emplace("EX1_162o", power);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [EX1_390e] Enraged (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: +3 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - ENRAGED = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(Enchants::GetEnchantFromText("EX1_390e"));
    cards.emplace("EX1_390e", power);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [EX1_412e] Enraged (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: +1 Attack and <b>Windfury</b>.
    // --------------------------------------------------------
    // GameTag:
    // - ENRAGED = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(Enchants::GetEnchantFromText("EX1_412e"));
    cards.emplace("EX1_412e", power);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [EX1_507e] Mrgglaargl! (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: +2 Attack from Murloc Warleader.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(Enchants::GetEnchantFromText("EX1_507e"));
    cards.emplace("EX1_507e", power);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [EX1_509e] Blarghghl (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: Increased Attack.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(new Enchant(Effects::AttackN(1)));
    cards.emplace("EX1_509e", power);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [EX1_584e] Teachings of the Kirin Tor (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: <b>Spell Damage +1</b>.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(new Enchant(Effects::SpellPowerN(1)));
    cards.emplace("EX1_584e", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_614t] Flame of Azzinoth (*) - COST:1 [ATK:2/HP:1]
    // - Race: Elemental, Set: Expert1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("EX1_614t", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_598] Imp (*) - COST:1 [ATK:1/HP:1]
    // - Race: Demon, Faction: Neutral, Set: Expert1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("EX1_598", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_finkle] Finkle Einhorn (*) - COST:3 [ATK:3/HP:3]
    // - Race: Beast, Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("EX1_finkle", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_tk28] Squirrel (*) - COST:1 [ATK:1/HP:1]
    // - Race: Beast, Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("EX1_tk28", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_tk29] Devilsaur (*) - COST:5 [ATK:5/HP:5]
    // - Race: Beast, Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("EX1_tk29", power);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [NEW1_017e] Full Belly (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: +2/+2. Full of Murloc.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(Enchants::GetEnchantFromText("NEW1_017e"));
    cards.emplace("NEW1_017e", power);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [NEW1_018e] Treasure Crazed (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: Increased Attack.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(new Enchant(Enchants::AddAttackScriptTag));
    cards.emplace("NEW1_018e", power);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [NEW1_024o] Greenskin's Command (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(new Enchant(std::vector<IEffect*>(
        { Effects::AttackN(1), Effects::DurabilityN(1) })));
    cards.emplace("NEW1_024o", power);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [NEW1_037e] Equipped (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: Increased Attack.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(new Enchant(Effects::AttackN(1)));
    cards.emplace("NEW1_037e", power);

    // --------------------------------------- MINION - NEUTRAL
    // [NEW1_040t] Gnoll (*) - COST:2 [ATK:2/HP:2]
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("NEW1_040t", power);

    // --------------------------------------- MINION - NEUTRAL
    // [skele21] Damaged Golem (*) - COST:1 [ATK:2/HP:1]
    // - Race: Mechanical, Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("skele21", power);
}

void Expert1CardsGen::AddDreamNonCollect(std::map<std::string, Power>& cards)
{
    Power power;

    // ----------------------------------------- MINION - DREAM
    // [DREAM_01] Laughing Sister (*) - COST:3 [ATK:3/HP:5]
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: Can't be targeted by spells or Hero Powers.
    // --------------------------------------------------------
    // GameTag:
    // - CANT_BE_TARGETED_BY_SPELLS = 1
    // - CANT_BE_TARGETED_BY_HERO_POWERS = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("DREAM_01", power);

    // ------------------------------------------ SPELL - DREAM
    // [DREAM_02] Ysera Awakens (*) - COST:2
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: Deal $5 damage to all characters except Ysera.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new IncludeTask(EntityType::ALL));
    power.AddPowerTask(
        new FilterStackTask(SelfCondition::IsName("Ysera", false)));
    power.AddPowerTask(new DamageTask(EntityType::STACK, 5, true));
    cards.emplace("DREAM_02", power);

    // ----------------------------------------- MINION - DREAM
    // [DREAM_03] Emerald Drake (*) - COST:4 [ATK:7/HP:6]
    // - Race: Dragon, Set: Expert1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("DREAM_03", power);

    // ------------------------------------------ SPELL - DREAM
    // [DREAM_04] Dream (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: Return a minion to its owner's hand.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new ReturnHandTask(EntityType::TARGET));
    cards.emplace("DREAM_04", power);

    // ------------------------------------------ SPELL - DREAM
    // [DREAM_05] Nightmare (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: Give a minion +5/+5. At the start of your next turn, destroy it.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new AddEnchantmentTask("DREAM_05e", EntityType::TARGET));
    cards.emplace("DREAM_05", power);
}

void Expert1CardsGen::AddAll(std::map<std::string, Power>& cards)
{
    AddHeroes(cards);
    AddHeroPowers(cards);

    AddDruid(cards);
    AddDruidNonCollect(cards);

    AddHunter(cards);
    AddHunterNonCollect(cards);

    AddMage(cards);
    AddMageNonCollect(cards);

    AddPaladin(cards);
    AddPaladinNonCollect(cards);

    AddPriest(cards);
    AddPriestNonCollect(cards);

    AddRogue(cards);
    AddRogueNonCollect(cards);

    AddShaman(cards);
    AddShamanNonCollect(cards);

    AddWarlock(cards);
    AddWarlockNonCollect(cards);

    AddWarrior(cards);
    AddWarriorNonCollect(cards);

    AddNeutral(cards);
    AddNeutralNonCollect(cards);

    AddDreamNonCollect(cards);
}
}  // namespace RosettaStone
