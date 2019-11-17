// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Actions/Generic.hpp>
#include <Rosetta/Tasks/SimpleTasks/ManaCrystalTask.hpp>

namespace RosettaStone::SimpleTasks
{
ManaCrystalTask::ManaCrystalTask(int amount, bool fill, bool isOpponent)
    : m_amount(amount), m_fill(fill), m_isOpponent(isOpponent)
{
    // Do nothing
}

TaskStatus ManaCrystalTask::Impl(Player* player)
{
    if (m_isOpponent)
    {
        Generic::ChangeManaCrystal(player->opponent, m_amount, m_fill);
    }
    else
    {
        Generic::ChangeManaCrystal(player, m_amount, m_fill);
    }

    return TaskStatus::COMPLETE;
}

ITask* ManaCrystalTask::CloneImpl()
{
    return new ManaCrystalTask(m_amount, m_fill, m_isOpponent);
}
}  // namespace RosettaStone::SimpleTasks
