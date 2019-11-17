// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Actions/PlayCard.hpp>
#include <Rosetta/Cards/Cards.hpp>
#include <Rosetta/Tasks/SimpleTasks/WeaponTask.hpp>

namespace RosettaStone::SimpleTasks
{
WeaponTask::WeaponTask(std::string cardID) : m_cardID(std::move(cardID))
{
    // Do nothing
}

TaskStatus WeaponTask::Impl(Player* player)
{
    Card* weaponCard = Cards::FindCardByID(m_cardID);
    if (weaponCard->id.empty())
    {
        return TaskStatus::STOP;
    }

    if (player->GetHero()->HasWeapon())
    {
        player->GetWeapon().Destroy();
    }

    const auto weapon =
        dynamic_cast<Weapon*>(Entity::GetFromCard(player, weaponCard));
    Generic::PlayWeapon(player, weapon, nullptr);

    return TaskStatus::COMPLETE;
}

ITask* WeaponTask::CloneImpl()
{
    return new WeaponTask(m_cardID);
}
}  // namespace RosettaStone::SimpleTasks
