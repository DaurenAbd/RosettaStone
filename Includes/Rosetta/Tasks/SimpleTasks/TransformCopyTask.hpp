// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_TRANSFORM_COPY_TASK_HPP
#define ROSETTASTONE_TRANSFORM_COPY_TASK_HPP

#include <Rosetta/Tasks/ITask.hpp>

namespace RosettaStone::SimpleTasks
{
//!
//! \brief TransformCopyTask class.
//!
//! This class represents the task for transforming minion to another and coping
//! data such as attack/health, enchantment and so on.
//!
class TransformCopyTask : public ITask
{
 public:
    //! Default constructor.
    TransformCopyTask() = default;

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    TaskStatus Impl(Player* player) override;

    //! Internal method of Clone().
    //! \return The cloned task.
    ITask* CloneImpl() override;
};
}  // namespace RosettaStone::SimpleTasks

#endif  // ROSETTASTONE_TRANSFORM_COPY_TASK_HPP
