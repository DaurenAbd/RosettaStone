// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Auras/Aura.hpp>
#include <Rosetta/Cards/Cards.hpp>
#include <Rosetta/Commons/Utils.hpp>
#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Models/Enchantment.hpp>
#include <Rosetta/Zones/FieldZone.hpp>
#include <Rosetta/Zones/HandZone.hpp>

#include <algorithm>
#include <utility>

namespace RosettaStone
{
Aura::Aura(AuraType type, std::vector<IEffect*> effects)
    : m_type(type), m_effects(std::move(effects))
{
    // Do nothing
}

Aura::Aura(AuraType type, std::string&& enchantmentID)
    : m_type(type), m_enchantmentCard(Cards::FindCardByID(enchantmentID))
{
    // Do nothing
}

void Aura::Activate(Playable* owner, bool cloning)
{
    if (m_effects.empty())
    {
        m_effects = m_enchantmentCard->power.GetEnchant()->effects;
    }

    auto instance = new Aura(*this, *owner);

    AddToGame(*owner, *instance);

    if (!cloning && !restless)
    {
        instance->m_auraUpdateInstQueue.Push(
            AuraUpdateInstruction(AuraInstruction::ADD_ALL), 1);
    }
}

void Aura::Update()
{
    bool addAllProcessed = false;

    if (restless)
    {
        RenewAll();
        addAllProcessed = true;
    }

    while (!m_auraUpdateInstQueue.IsEmpty())
    {
        const AuraUpdateInstruction inst = m_auraUpdateInstQueue.Pop();

        switch (inst.instruction)
        {
            case AuraInstruction::ADD:
                if (!addAllProcessed)
                {
                    Apply(inst.source);
                }
                break;
            case AuraInstruction::ADD_ALL:
                addAllProcessed = true;
                UpdateInternal();
                break;
            case AuraInstruction::REMOVE:
                Disapply(inst.source);
                break;
            case AuraInstruction::REMOVE_ALL:
                RemoveInternal();
                break;
            default:
                throw std::invalid_argument(
                    "Aura::Update() - Invalid aura instruction!");
        }
    }
}

void Aura::Remove()
{
    m_turnOn = false;
    m_auraUpdateInstQueue.Push(
        AuraUpdateInstruction(AuraInstruction::REMOVE_ALL), 0);
    m_owner->onGoingEffect = nullptr;

    switch (m_type)
    {
        case AuraType::ADJACENT:
        case AuraType::FIELD:
        case AuraType::FIELD_EXCEPT_SOURCE:
        {
            EraseIf(m_owner->player->GetFieldZone()->auras,
                    [this](Aura* aura) { return aura == this; });
            break;
        }
        case AuraType::HAND:
        {
            EraseIf(m_owner->player->GetHandZone()->auras,
                    [this](Aura* aura) { return aura == this; });
            break;
        }
        case AuraType::ENEMY_HAND:
        {
            EraseIf(m_owner->player->opponent->GetHandZone()->auras,
                    [this](Aura* aura) { return aura == this; });
            break;
        }
        case AuraType::HANDS:
        {
            EraseIf(m_owner->player->GetHandZone()->auras,
                    [this](Aura* aura) { return aura == this; });
            EraseIf(m_owner->player->opponent->GetHandZone()->auras,
                    [this](Aura* aura) { return aura == this; });
            break;
        }
        case AuraType::FIELD_AND_HAND:
        {
            EraseIf(m_owner->player->GetFieldZone()->auras,
                    [this](Aura* aura) { return aura == this; });
            EraseIf(m_owner->player->GetHandZone()->auras,
                    [this](Aura* aura) { return aura == this; });
            break;
        }
        default:
        {
            // Do nothing
        }
    }

    if (auto enchantment = dynamic_cast<Enchantment*>(m_owner))
    {
        enchantment->Remove();
    }
}

void Aura::Clone(Playable* clone)
{
    Activate(clone, true);
}

void Aura::Apply(Playable* entity)
{
    if (condition != nullptr)
    {
        if (!condition->Evaluate(entity))
        {
            return;
        }
    }

    for (auto& effect : m_effects)
    {
        effect->ApplyAuraTo(entity);
    }

    if (m_enchantmentCard != nullptr &&
        m_enchantmentCard->power.GetTrigger() != nullptr)
    {
        const auto instance =
            Enchantment::GetInstance(entity->player, m_enchantmentCard, entity);

        if (auto trigger = m_enchantmentCard->power.GetTrigger();
            trigger != nullptr)
        {
            trigger->Activate(instance);
        }
    }

    m_appliedEntities.emplace_back(entity);
}

void Aura::Disapply(Playable* entity)
{
    const auto iter =
        std::find(m_appliedEntities.begin(), m_appliedEntities.end(), entity);

    if (iter != m_appliedEntities.end())
    {
        m_appliedEntities.erase(iter);
    }
    else
    {
        return;
    }

    for (auto& effect : m_effects)
    {
        effect->RemoveAuraFrom(entity);
    }

    if (m_enchantmentCard != nullptr &&
        m_enchantmentCard->power.GetTrigger() != nullptr)
    {
        const std::string cardID = m_enchantmentCard->id;
        std::vector<Enchantment*> enchantments = entity->appliedEnchantments;

        for (int i = static_cast<int>(enchantments.size()) - 1; i >= 0; --i)
        {
            if (enchantments[i]->card->id == cardID)
            {
                enchantments.erase(enchantments.begin() + i);
                break;
            }
        }
    }
}

void Aura::NotifyEntityAdded(Playable* entity)
{
    if (!m_turnOn)
    {
        return;
    }

    const auto instruction =
        AuraUpdateInstruction(entity, AuraInstruction::ADD);

    if (!m_auraUpdateInstQueue.IsExist(instruction))
    {
        m_auraUpdateInstQueue.Push(instruction, 2);
    }
}

void Aura::NotifyEntityRemoved(Playable* entity)
{
    if (!m_turnOn)
    {
        return;
    }

    if (entity == m_owner)
    {
        return;
    }

    m_auraUpdateInstQueue.Push(
        AuraUpdateInstruction(entity, AuraInstruction::REMOVE), 1);
}

Aura::Aura(Aura& prototype, Playable& owner)
    : condition(prototype.condition),
      restless(prototype.restless),
      m_type(prototype.m_type),
      m_owner(&owner),
      m_enchantmentCard(prototype.m_enchantmentCard),
      m_effects(prototype.m_effects),
      m_turnOn(prototype.m_turnOn)
{
    if (!prototype.m_auraUpdateInstQueue.IsEmpty())
    {
        m_auraUpdateInstQueue = prototype.m_auraUpdateInstQueue;
    }
}

void Aura::AddToGame(Playable& owner, Aura& aura)
{
    owner.game->auras.emplace_back(&aura);
    owner.onGoingEffect = &aura;

    switch (aura.m_type)
    {
        case AuraType::ADJACENT:
        case AuraType::FIELD:
        case AuraType::FIELD_EXCEPT_SOURCE:
            owner.player->GetFieldZone()->auras.emplace_back(&aura);
            break;
        case AuraType::HAND:
            owner.player->GetHandZone()->auras.emplace_back(&aura);
            break;
        case AuraType::ENEMY_HAND:
            owner.player->opponent->GetHandZone()->auras.emplace_back(&aura);
            break;
        case AuraType::HANDS:
            owner.player->GetHandZone()->auras.emplace_back(&aura);
            owner.player->opponent->GetHandZone()->auras.emplace_back(&aura);
            break;
        case AuraType::FIELD_AND_HAND:
            owner.player->GetFieldZone()->auras.emplace_back(&aura);
            owner.player->GetHandZone()->auras.emplace_back(&aura);
            break;
        default:
            throw std::invalid_argument(
                "Aura::AddToGame() - Invalid aura type!");
    }
}

void Aura::UpdateInternal()
{
    if (!m_turnOn)
    {
        return;
    }

    switch (m_type)
    {
        case AuraType::ADJACENT:
        {
            auto& field = *m_owner->player->GetFieldZone();
            if (field.GetCount() == 1)
            {
                return;
            }

            const int pos = m_owner->GetZonePosition();
            if (pos > 0)
            {
                Apply(field[pos - 1]);
            }
            if (pos < m_owner->player->GetFieldZone()->GetCount() - 1)
            {
                Apply(field[pos + 1]);
            }

            break;
        }
        case AuraType::FIELD:
            for (auto& minion : m_owner->player->GetFieldZone()->GetAll())
            {
                Apply(minion);
            }
            break;
        case AuraType::FIELD_EXCEPT_SOURCE:
        {
            for (auto& minion : m_owner->player->GetFieldZone()->GetAll())
            {
                if (minion != m_owner)
                {
                    Apply(minion);
                }
            }
            break;
        }
        case AuraType::HAND:
        {
            for (auto& card : m_owner->player->GetHandZone()->GetAll())
            {
                Apply(card);
            }
            break;
        }
        default:
            throw std::invalid_argument(
                "Aura::UpdateInternal() - Invalid aura type!");
    }
}

void Aura::RemoveInternal()
{
    for (auto& entity : m_appliedEntities)
    {
        for (auto& effect : m_effects)
        {
            effect->RemoveAuraFrom(entity);
        }
    }

    EraseIf(m_owner->game->auras, [this](IAura* aura) { return aura == this; });

    if (m_enchantmentCard != nullptr &&
        m_enchantmentCard->power.GetTrigger() != nullptr)
    {
        for (auto& entity : m_appliedEntities)
        {
            std::vector<Enchantment*> enchantments =
                entity->appliedEnchantments;

            for (int i = static_cast<int>(enchantments.size()) - 1; i >= 0; --i)
            {
                enchantments.erase(enchantments.begin() + i);
            }
        }
    }
}

void Aura::RenewAll()
{
    auto Renew = [this](Playable* playable) {
        const auto iter = std::find(m_appliedEntities.begin(),
                                    m_appliedEntities.end(), playable);

        if (condition->Evaluate(playable))
        {
            if (iter == m_appliedEntities.end())
            {
                Apply(playable);
            }
        }
        else
        {
            if (iter != m_appliedEntities.end())
            {
                Disapply(playable);
            }
        }
    };

    switch (m_type)
    {
        case AuraType::FIELD:
            m_owner->player->GetFieldZone()->ForEach(Renew);
            break;
        case AuraType::HANDS:
            m_owner->player->GetHandZone()->ForEach(Renew);
            m_owner->player->opponent->GetHandZone()->ForEach(Renew);
            break;
        case AuraType::WEAPON:
            if (!m_owner->player->GetHero()->HasWeapon())
            {
                break;
            }
            Renew(m_owner->player->GetHero()->weapon);
            break;
        case AuraType::HERO:
            Renew(m_owner->player->GetHero());
            break;
        case AuraType::SELF:
            Renew(m_owner);
            break;
        default:
            throw std::invalid_argument(
                "Aura::RenewAll() - Invalid aura type!");
    }
}
}  // namespace RosettaStone
