// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Actions/Draw.hpp>
#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Tasks/SimpleTasks/DrawStackTask.hpp>

namespace RosettaStone::SimpleTasks
{
DrawStackTask::DrawStackTask(std::size_t amount) : m_amount(amount)
{
    // Do nothing
}

TaskStatus DrawStackTask::Impl(Player* player)
{
    auto& stack = player->game->taskStack.playables;
    const std::size_t amount =
        (m_amount <= stack.size()) ? m_amount : stack.size();

    for (std::size_t i = 0; i < amount; ++i)
    {
        Playable* card = stack.at(i);
        Generic::Draw(player, card);
    }

    stack.clear();

    return TaskStatus::COMPLETE;
}

ITask* DrawStackTask::CloneImpl()
{
    return new DrawStackTask(m_amount);
}
}  // namespace RosettaStone::SimpleTasks
