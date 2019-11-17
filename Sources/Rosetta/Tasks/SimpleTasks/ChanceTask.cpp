// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Tasks/SimpleTasks/ChanceTask.hpp>

#include <effolkronium/random.hpp>

using Random = effolkronium::random_static;

namespace RosettaStone::SimpleTasks
{
ChanceTask::ChanceTask(bool useFlag) : m_useFlag(useFlag)
{
    // Do nothing
}

TaskStatus ChanceTask::Impl(Player* player)
{
    const auto num = Random::get<int>(0, 1);

    if (!m_useFlag)
    {
        return num == 0 ? TaskStatus::COMPLETE : TaskStatus::STOP;
    }

    player->game->taskStack.flag = (num != 0);
    return TaskStatus::COMPLETE;
}

ITask* ChanceTask::CloneImpl()
{
    return new ChanceTask(m_useFlag);
}
}  // namespace RosettaStone::SimpleTasks
