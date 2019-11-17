#ifndef ROSETTASTONE_REMOVE_DURABILITY_TASK_HPP
#define ROSETTASTONE_REMOVE_DURABILITY_TASK_HPP

#include <Rosetta/Tasks/ITask.hpp>

namespace RosettaStone::SimpleTasks
{
//!
//! \brief RemoveDurabilityTask class.
//!
//! This class represents the task for removing durability from hero's weapon.
//!
class RemoveDurabilityTask : public ITask
{
 public:
    //! Constructs task with given \p amount and \p isOpponent.
    //! \param amount The amount of durability to remove.
    //! \param isOpponent A flag to owner indicating opponent player.
    RemoveDurabilityTask(int amount, bool isOpponent = false);

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    TaskStatus Impl(Player* player) override;

    //! Internal method of Clone().
    //! \return The cloned task.
    ITask* CloneImpl() override;

    int m_amount;
    bool m_isOpponent;
};
}  // namespace RosettaStone::SimpleTasks

#endif  // ROSETTASTONE_REMOVE_DURABILITY_TASK_HPP
