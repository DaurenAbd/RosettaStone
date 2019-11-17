// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Tasks/SimpleTasks/FuncPlayableTask.hpp>

#include <utility>

namespace RosettaStone::SimpleTasks
{
FuncPlayableTask::FuncPlayableTask(
    std::function<std::vector<Playable*>(std::vector<Playable*>)> func)
    : m_func(std::move(func))
{
    // Do nothing
}

TaskStatus FuncPlayableTask::Impl(Player* player)
{
    if (m_func != nullptr)
    {
        player->game->taskStack.playables =
            m_func(player->game->taskStack.playables);
    }

    return TaskStatus::COMPLETE;
}

ITask* FuncPlayableTask::CloneImpl()
{
    return new FuncPlayableTask(m_func);
}
}  // namespace RosettaStone::SimpleTasks
