// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Tasks/SimpleTasks/GetGameTagTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/IncludeTask.hpp>

namespace RosettaStone::SimpleTasks
{
GetGameTagTask::GetGameTagTask(EntityType entityType, GameTag tag,
                               int entityIndex, int numIndex)
    : ITask(entityType),
      m_gameTag(tag),
      m_entityIndex(entityIndex),
      m_numIndex(numIndex)
{
    // Do nothing
}

TaskStatus GetGameTagTask::Impl(Player* player)
{
    auto entities =
        IncludeTask::GetEntities(m_entityType, player, m_source, m_target);
    if (entities.empty() || static_cast<int>(entities.size()) <= m_entityIndex)
    {
        return TaskStatus::STOP;
    }

    const int value = entities[m_entityIndex]->GetGameTag(m_gameTag);

    if (m_numIndex == 0)
    {
        player->game->taskStack.num = value;
    }
    else if (static_cast<int>(entities.size()) > m_entityIndex)
    {
        switch (m_numIndex)
        {
            case 1:
                player->game->taskStack.num1 = value;
                break;
            default:
                throw std::invalid_argument(
                    "GetGameTagTask::Impl() - Invalid number index");
        }
    }

    return TaskStatus::COMPLETE;
}

ITask* GetGameTagTask::CloneImpl()
{
    return new GetGameTagTask(m_entityType, m_gameTag, m_entityIndex,
                              m_numIndex);
}
}  // namespace RosettaStone::SimpleTasks
