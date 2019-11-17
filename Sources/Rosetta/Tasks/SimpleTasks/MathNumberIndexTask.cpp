// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Tasks/SimpleTasks/IncludeTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/MathNumberIndexTask.hpp>

namespace RosettaStone::SimpleTasks
{
MathNumberIndexTask::MathNumberIndexTask(int indexA, int indexB,
                                         MathOperation mathOp, int resultIndex)
    : m_indexA(indexA),
      m_indexB(indexB),
      m_mathOp(mathOp),
      m_resultIndex(resultIndex)
{
    // Do nothing
}

TaskStatus MathNumberIndexTask::Impl(Player* player)
{
    TaskStack& stack = player->game->taskStack;

    const int numberA = GetNumber(m_indexA, stack);
    const int numberB = GetNumber(m_indexB, stack);

    int result = 0;

    switch (m_mathOp)
    {
        case MathOperation::ADD:
            result = numberA + numberB;
            break;
        case MathOperation::SUB:
            result = numberA - numberB;
            break;
        case MathOperation::MUL:
            result = numberA * numberB;
            break;
        case MathOperation::DIV:
            result = numberA / numberB;
            break;
    }

    switch (m_resultIndex)
    {
        case 0:
            stack.num = result;
            break;
        case 1:
            stack.num1 = result;
            break;
        default:
            throw std::invalid_argument(
                "MathNumberIndexTask::Impl() - Unknown result index!\n");
    }

    return TaskStatus::COMPLETE;
}

ITask* MathNumberIndexTask::CloneImpl()
{
    return new MathNumberIndexTask(m_indexA, m_indexB, m_mathOp, m_resultIndex);
}

int MathNumberIndexTask::GetNumber(int index, const TaskStack& taskStack)
{
    switch (index)
    {
        case 0:
            return taskStack.num;
        case 1:
            return taskStack.num1;
        default:
            throw std::invalid_argument(
                "MathNumberIndexTask::GetNumber() - Unknown index!\n");
    }
}
}  // namespace RosettaStone::SimpleTasks
