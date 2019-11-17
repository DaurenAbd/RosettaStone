// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Actions/Generic.hpp>
#include <Rosetta/Commons/Constants.hpp>
#include <Rosetta/Models/Enchantment.hpp>
#include <Rosetta/Zones/DeckZone.hpp>
#include <Rosetta/Zones/FieldZone.hpp>
#include <Rosetta/Zones/GraveyardZone.hpp>
#include <Rosetta/Zones/HandZone.hpp>
#include <Rosetta/Zones/SecretZone.hpp>
#include <Rosetta/Zones/SetasideZone.hpp>

namespace RosettaStone::Generic
{
void TakeDamageToCharacter(Playable* source, Character* target, int amount,
                           bool isSpellDamage)
{
    if (isSpellDamage)
    {
        amount += static_cast<int>(source->player->currentSpellPower);
    }

    target->TakeDamage(source, amount);
}

void AddCardToHand(Player* player, Playable* entity)
{
    // Add card to graveyard if hand is full
    if (player->GetHandZone()->IsFull())
    {
        player->GetGraveyardZone()->Add(entity);
        return;
    }

    // Add card to hand
    player->GetHandZone()->Add(entity);
}

void AddEnchantment(Card* enchantmentCard, Playable* creator, Entity* target,
                    int num1, int num2)
{
    Power power = enchantmentCard->power;

    if (power.GetAura() != nullptr || power.GetTrigger() != nullptr ||
        !power.GetDeathrattleTask().empty())
    {
        // Create Enchantment instance Only when it is needed.
        // As an owner entity for auras, triggers or deathrattle tasks.
        Enchantment* enchantment =
            Enchantment::GetInstance(creator->player, enchantmentCard, target);

        if (auto aura = power.GetAura(); aura)
        {
            aura->Activate(enchantment);
        }

        if (auto trigger = power.GetTrigger(); trigger)
        {
            trigger->Activate(enchantment);
        }
    }

    if (auto enchant = power.GetEnchant(); enchant)
    {
        enchant->ActivateTo(target, num1, num2);
    }
}

void ShuffleIntoDeck(Player* player, Playable* entity)
{
    // Add card to graveyard if deck is full
    if (player->GetDeckZone()->IsFull())
    {
        return;
    }

    // Add card into deck and shuffle it
    player->GetDeckZone()->Add(entity);
    player->GetDeckZone()->Shuffle();
}

void ChangeManaCrystal(Player* player, int amount, bool fill)
{
    // Available and maximum mana are up to a maximum of 10
    if (player->GetTotalMana() + amount > MANA_UPPER_LIMIT)
    {
        // Add mana crystal when fill is true
        if (!fill)
        {
            player->SetUsedMana(player->GetUsedMana() + MANA_UPPER_LIMIT -
                                player->GetTotalMana());
        }
        else
        {
            player->SetUsedMana(player->GetUsedMana() + MANA_UPPER_LIMIT -
                                player->GetTotalMana() - amount);
        }

        player->SetTotalMana(MANA_UPPER_LIMIT);
    }
    // Maximum mana are up to a minimum of 0
    else if (player->GetTotalMana() + amount < 0)
    {
        player->SetTotalMana(0);
    }
    else
    {
        if (!fill)
        {
            player->SetUsedMana(player->GetUsedMana() + amount);
        }

        player->SetTotalMana(player->GetTotalMana() + amount);
    }
}

void TransformMinion(Player* player, Minion* oldMinion, Card* card)
{
    const auto newMinion =
        dynamic_cast<Minion*>(Entity::GetFromCard(player, card));
    if (newMinion == nullptr)
    {
        return;
    }

    player->GetFieldZone()->Replace(oldMinion, newMinion);
}

IZone* GetZone(Player* player, ZoneType zoneType)
{
    switch (zoneType)
    {
        case ZoneType::PLAY:
            return player->GetFieldZone();
        case ZoneType::DECK:
            return player->GetDeckZone();
        case ZoneType::HAND:
            return player->GetHandZone();
        case ZoneType::GRAVEYARD:
            return player->GetGraveyardZone();
        case ZoneType::SETASIDE:
            return player->GetSetasideZone();
        case ZoneType::SECRET:
            return player->GetSecretZone();
        case ZoneType::INVALID:
        case ZoneType::REMOVEDFROMGAME:
            return nullptr;
    }

    return nullptr;
}
}  // namespace RosettaStone::Generic
