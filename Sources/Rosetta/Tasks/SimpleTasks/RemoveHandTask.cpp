// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Tasks/SimpleTasks/IncludeTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/RemoveHandTask.hpp>
#include <Rosetta/Zones/HandZone.hpp>

namespace RosettaStone::SimpleTasks
{
RemoveHandTask::RemoveHandTask(EntityType entityType) : ITask(entityType)
{
    // Do nothing
}

TaskStatus RemoveHandTask::Impl(Player* player)
{
    auto playables =
        IncludeTask::GetEntities(m_entityType, player, m_source, m_target);
    std::vector<Playable*> list;

    for (auto& playable : playables)
    {
        if (playable->zone->GetType() == ZoneType::HAND)
        {
            playable->player->GetHandZone()->Remove(playable);
            list.emplace_back(playable);
        }
    }

    player->game->taskStack.playables = list;

    return TaskStatus::COMPLETE;
}

ITask* RemoveHandTask::CloneImpl()
{
    return new RemoveHandTask(m_entityType);
}
}  // namespace RosettaStone::SimpleTasks
