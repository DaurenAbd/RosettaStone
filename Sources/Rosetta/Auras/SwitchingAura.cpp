// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Auras/SwitchingAura.hpp>
#include <Rosetta/Cards/Card.hpp>
#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Models/Entity.hpp>
#include <Rosetta/Models/Player.hpp>

#include <utility>

namespace RosettaStone
{
SwitchingAura::SwitchingAura(AuraType type, SelfCondition initCondition,
                             TriggerType offTrigger,
                             std::vector<IEffect*> effects)
    : Aura(type, std::move(effects)),
      m_initCondition(std::move(initCondition)),
      m_offTrigger(offTrigger)
{
    // Do nothing
}

void SwitchingAura::Activate(Playable* owner, bool cloning)
{
    if (m_effects.empty())
    {
        m_effects = m_enchantmentCard->power.GetEnchant()->effects;
    }

    auto instance = new SwitchingAura(*this, *owner);

    AddToGame(*owner, *instance);

    owner->game->triggerManager.startTurnTrigger = instance->m_onHandler;
    owner->game->triggerManager.endTurnTrigger = instance->m_offHandler;

    switch (m_offTrigger)
    {
        case TriggerType::PLAY_MINION:
            owner->game->triggerManager.playMinionTrigger =
                instance->m_offHandler;
            break;
        case TriggerType::CAST_SPELL:
            owner->game->triggerManager.castSpellTrigger =
                instance->m_offHandler;
            break;
        default:
            throw std::invalid_argument(
                "SwitchingAura::Activate() - Invalid trigger type!");
    }

    if (!cloning)
    {
        if (!instance->m_initCondition.Evaluate(owner))
        {
            instance->m_turnOn = false;
        }
        else
        {
            instance->m_auraUpdateInstQueue.Push(
                AuraUpdateInstruction(AuraInstruction::ADD_ALL), 1);
        }
    }
}

void SwitchingAura::Remove()
{
    Aura::Remove();

    m_isRemoved = true;

    m_owner->game->triggerManager.startTurnTrigger = nullptr;
    m_owner->game->triggerManager.endTurnTrigger = nullptr;

    switch (m_offTrigger)
    {
        case TriggerType::PLAY_MINION:
            m_owner->game->triggerManager.playMinionTrigger = nullptr;
            break;
        case TriggerType::CAST_SPELL:
            m_owner->game->triggerManager.castSpellTrigger = nullptr;
            break;
        default:
            throw std::invalid_argument(
                "SwitchingAura::Activate() - Invalid trigger type!");
    }
}

void SwitchingAura::RemoveInternal()
{
    for (auto& entity : m_appliedEntities)
    {
        for (auto& effect : m_effects)
        {
            effect->RemoveAuraFrom(entity);
        }
    }

    m_appliedEntities.clear();

    if (m_isRemoved)
    {
        EraseIf(m_owner->game->auras,
                [this](IAura* aura) { return aura == this; });
    }
}

void SwitchingAura::TurnOn(Player*, Entity*)
{
    if (m_turnOn)
    {
        return;
    }

    m_turnOn = true;

    m_auraUpdateInstQueue.Push(AuraUpdateInstruction(AuraInstruction::ADD_ALL),
                               1);
}

void SwitchingAura::TurnOff(Player*, Entity*)
{
    if (!m_turnOn)
    {
        return;
    }

    m_turnOn = false;

    m_auraUpdateInstQueue.Push(
        AuraUpdateInstruction(AuraInstruction::REMOVE_ALL), 0);
}

SwitchingAura::SwitchingAura(SwitchingAura& prototype, Playable& owner)
    : Aura(prototype, owner),
      m_initCondition(prototype.m_initCondition),
      m_offTrigger(prototype.m_offTrigger),
      m_onHandler(std::bind(&SwitchingAura::TurnOn, this, std::placeholders::_1,
                            std::placeholders::_2)),
      m_offHandler(std::bind(&SwitchingAura::TurnOff, this,
                             std::placeholders::_1, std::placeholders::_2))
{
    // Do nothing
}
}  // namespace RosettaStone
