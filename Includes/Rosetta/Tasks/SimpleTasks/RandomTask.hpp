// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_RANDOM_TASK_HPP
#define ROSETTASTONE_RANDOM_TASK_HPP

#include <Rosetta/Tasks/ITask.hpp>

namespace RosettaStone::SimpleTasks
{
//!
//! \brief RandomTask class.
//!
//! This class represents the task for picking entities at random.
//!
class RandomTask : public ITask
{
 public:
    //! Constructs task with given \p entityType and \p amount.
    //! \param entityType The type of entity.
    //! \param amount The amount of entities to pick.
    RandomTask(EntityType entityType, int amount);

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    TaskStatus Impl(Player* player) override;

    //! Internal method of Clone().
    //! \return The cloned task.
    ITask* CloneImpl() override;

    int m_amount = 0;
};
}  // namespace RosettaStone::SimpleTasks

#endif  // ROSETTASTONE_RANDOM_TASK_HPP
