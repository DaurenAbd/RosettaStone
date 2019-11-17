// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Tasks/SimpleTasks/DestroyTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/IncludeTask.hpp>

namespace RosettaStone::SimpleTasks
{
DestroyTask::DestroyTask(EntityType entityType) : ITask(entityType)
{
    // Do nothing
}

TaskStatus DestroyTask::Impl(Player* player)
{
    auto playables =
        IncludeTask::GetEntities(m_entityType, player, m_source, m_target);

    for (auto& playable : playables)
    {
        playable->Destroy();
    }

    return TaskStatus::COMPLETE;
}

ITask* DestroyTask::CloneImpl()
{
    return new DestroyTask(m_entityType);
}
}  // namespace RosettaStone::SimpleTasks
