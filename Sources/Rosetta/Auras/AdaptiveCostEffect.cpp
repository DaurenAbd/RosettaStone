// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Auras/AdaptiveCostEffect.hpp>
#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Models/Entity.hpp>

#include <utility>

namespace RosettaStone
{
AdaptiveCostEffect::AdaptiveCostEffect(std::function<int(Playable*)> costFunc,
                                       EffectOperator effectOp)
    : m_costFunc(std::move(costFunc)), m_effectOp(effectOp)
{
    // Do nothing
}

void AdaptiveCostEffect::Activate(Playable* owner, bool cloning)
{
    if (!cloning && owner->GetZoneType() != ZoneType::HAND)
    {
        return;
    }

    auto instance = new AdaptiveCostEffect(*this, *owner);

    if (owner->costManager == nullptr)
    {
        owner->costManager = new CostManager();
    }

    owner->costManager->ActivateAdaptiveEffect(instance);
    owner->onGoingEffect = instance;
    owner->game->auras.emplace_back(instance);
}

int AdaptiveCostEffect::Apply(int value) const
{
    if (m_costFunc != nullptr)
    {
        if (m_effectOp == EffectOperator::ADD)
        {
            return value + m_costFunc(m_owner);
        }

        if (m_effectOp == EffectOperator::SUB)
        {
            return value - m_costFunc(m_owner);
        }

        if (m_effectOp == EffectOperator::MUL)
        {
            return value * m_costFunc(m_owner);
        }

        if (m_effectOp == EffectOperator::SET)
        {
            return m_costFunc(m_owner);
        }
    }

    return value;
}

void AdaptiveCostEffect::Update()
{
    m_owner->costManager->UpdateAdaptiveEffect();
}

void AdaptiveCostEffect::Remove()
{
    m_owner->onGoingEffect = nullptr;

    EraseIf(m_owner->game->auras, [this](IAura* aura) { return aura == this; });

    if (const auto costManager = m_owner->costManager; costManager)
    {
        costManager->DeactivateAdaptiveEffect();
    }
}

void AdaptiveCostEffect::Clone(Playable* clone)
{
    Activate(clone, true);
}

AdaptiveCostEffect::AdaptiveCostEffect(AdaptiveCostEffect& prototype,
                                       Playable& owner)
{
    m_owner = &owner;

    m_costFunc = prototype.m_costFunc;
    m_effectOp = prototype.m_effectOp;
}
}  // namespace RosettaStone
