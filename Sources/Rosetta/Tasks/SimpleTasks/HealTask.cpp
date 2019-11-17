// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Tasks/SimpleTasks/HealTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/IncludeTask.hpp>

namespace RosettaStone::SimpleTasks
{
HealTask::HealTask(EntityType entityType, int amount)
    : ITask(entityType), m_amount(amount)
{
    // Do nothing
}

TaskStatus HealTask::Impl(Player* player)
{
    auto playables =
        IncludeTask::GetEntities(m_entityType, player, m_source, m_target);

    for (auto& playable : playables)
    {
        auto character = dynamic_cast<Character*>(playable);
        character->TakeHeal(dynamic_cast<Playable*>(m_source), m_amount);
    }

    return TaskStatus::COMPLETE;
}

ITask* HealTask::CloneImpl()
{
    return new HealTask(m_entityType, m_amount);
}
}  // namespace RosettaStone::SimpleTasks
