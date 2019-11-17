// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Tasks/SimpleTasks/IncludeTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/MoveToSetasideTask.hpp>
#include <Rosetta/Zones/SetasideZone.hpp>

namespace RosettaStone::SimpleTasks
{
MoveToSetasideTask::MoveToSetasideTask(EntityType entityType)
    : ITask(entityType)
{
    // Do nothing
}

TaskStatus MoveToSetasideTask::Impl(Player* player)
{
    auto playables =
        IncludeTask::GetEntities(m_entityType, player, m_source, m_target);

    for (auto& playable : playables)
    {
        playable->zone->Remove(playable);
        playable->player->GetSetasideZone()->Add(playable);
    }

    return TaskStatus::COMPLETE;
}

ITask* MoveToSetasideTask::CloneImpl()
{
    return new MoveToSetasideTask(m_entityType);
}
}  // namespace RosettaStone::SimpleTasks
