// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Tasks/SimpleTasks/FlagTask.hpp>

#include <utility>

namespace RosettaStone::SimpleTasks
{
FlagTask::FlagTask(bool flag, std::vector<ITask*> toDoTasks)
    : m_flag(flag), m_toDoTasks(std::move(toDoTasks))
{
    // Do nothing
}

TaskStatus FlagTask::Impl(Player* player)
{
    if (player->game->taskStack.flag != m_flag)
    {
        return TaskStatus::COMPLETE;
    }

    for (auto& task : m_toDoTasks)
    {
        ITask* clonedTask = task->Clone();

        clonedTask->SetPlayer(player);
        clonedTask->SetSource(player->game->taskStack.source);
        clonedTask->SetTarget(player->game->taskStack.target);

        clonedTask->Run();
    }

    return TaskStatus::COMPLETE;
}

ITask* FlagTask::CloneImpl()
{
    return new FlagTask(m_flag, m_toDoTasks);
}
}  // namespace RosettaStone::SimpleTasks
