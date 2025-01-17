// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Auras/AdaptiveEffect.hpp>
#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Models/Entity.hpp>
#include <Rosetta/Models/Player.hpp>

namespace RosettaStone
{
AdaptiveEffect::AdaptiveEffect(SelfCondition* condition, GameTag tag)
    : m_condition(condition),
      m_tag(tag),
      m_operator(EffectOperator::SET),
      m_isSwitching(true)
{
    // Do nothing
}

void AdaptiveEffect::Activate(Playable* owner, [[maybe_unused]] bool cloning)
{
    auto instance = new AdaptiveEffect(*this, *owner);

    if (!m_isSwitching)
    {
        if (const auto weapon = dynamic_cast<Weapon*>(owner); weapon)
        {
            if (weapon->player->GetHero()->auraEffects != nullptr)
            {
                weapon->player->GetHero()->auraEffects =
                    new AuraEffects(CardType::HERO);
            }
        }
        else if (owner->auraEffects == nullptr)
        {
            owner->auraEffects = new AuraEffects(CardType::MINION);
        }
    }

    owner->game->auras.emplace_back(instance);
    owner->onGoingEffect = instance;
}

void AdaptiveEffect::Update()
{
    if (m_turnOn)
    {
        int value;

        if (m_isSwitching)
        {
            value = m_condition->Evaluate(m_owner) ? 1 : 0;

            if (value == m_lastValue)
            {
                return;
            }

            Effect(m_tag, m_operator, m_lastValue).RemoveFrom(m_owner);
            Effect(m_tag, m_operator, value).ApplyTo(m_owner);
        }
        else
        {
            value = m_valueFunc(m_owner);

            Effect(m_tag, m_operator, m_lastValue).RemoveFrom(m_owner);
            Effect(m_tag, m_operator, value).ApplyTo(m_owner);
        }

        m_lastValue = value;
    }
    else
    {
        if (m_isSwitching)
        {
            Effect(m_tag, m_operator, m_lastValue).RemoveFrom(m_owner);
        }
        else
        {
            Effect(m_tag, m_operator, m_lastValue).RemoveAuraFrom(m_owner);
        }

        EraseIf(m_owner->game->auras,
                [this](IAura* aura) { return aura == this; });
    }
}

void AdaptiveEffect::Remove()
{
    m_owner->onGoingEffect = nullptr;
    m_turnOn = false;
}

void AdaptiveEffect::Clone(Playable* clone)
{
    Activate(clone);
}

AdaptiveEffect::AdaptiveEffect(AdaptiveEffect& prototype, Playable& owner)
{
    m_owner = &owner;

    m_condition = prototype.m_condition;
    m_valueFunc = prototype.m_valueFunc;

    m_tag = prototype.m_tag;
    m_operator = prototype.m_operator;

    m_lastValue = prototype.m_lastValue;
    m_turnOn = prototype.m_turnOn;
    m_isSwitching = prototype.m_isSwitching;
}
}  // namespace RosettaStone
