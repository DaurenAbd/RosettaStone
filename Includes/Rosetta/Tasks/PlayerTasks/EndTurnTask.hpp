// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_END_TURN_TASK_HPP
#define ROSETTASTONE_END_TURN_TASK_HPP

#include <Rosetta/Tasks/ITask.hpp>

namespace RosettaStone::PlayerTasks
{
//!
//! \brief EndTurnTask class.
//!
//! This class represents the task for ending current player's turn.
//!
class EndTurnTask : public ITask
{
 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    TaskStatus Impl(Player* player) override;

    //! Returns Clone Of Object (pure virtual).
    //! \returns clone of object.
    //! \this uses for thread safe. not to access same task in multiple threads
    ITask* CloneImpl() override;
};
}  // namespace RosettaStone::PlayerTasks

#endif  // ROSETTASTONE_END_TURN_TASK_HPP
