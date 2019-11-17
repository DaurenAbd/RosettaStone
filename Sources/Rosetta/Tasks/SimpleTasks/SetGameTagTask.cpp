// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Tasks/SimpleTasks/IncludeTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/SetGameTagTask.hpp>

namespace RosettaStone::SimpleTasks
{
SetGameTagTask::SetGameTagTask(EntityType entityType, GameTag tag, int amount)
    : ITask(entityType), m_gameTag(tag), m_amount(amount)
{
    // Do nothing
}

TaskStatus SetGameTagTask::Impl(Player* player)
{
    auto playables =
        IncludeTask::GetEntities(m_entityType, player, m_source, m_target);

    for (auto& playable : playables)
    {
        playable->SetGameTag(m_gameTag, m_amount);
    }

    return TaskStatus::COMPLETE;
}

ITask* SetGameTagTask::CloneImpl()
{
    return new SetGameTagTask(m_entityType, m_gameTag, m_amount);
}
}  // namespace RosettaStone::SimpleTasks
