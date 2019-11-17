// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Actions/PlayCard.hpp>
#include <Rosetta/Tasks/PlayerTasks/PlayCardTask.hpp>

namespace RosettaStone::PlayerTasks
{
PlayCardTask::PlayCardTask(Entity* source, Playable* target, int fieldPos,
                           int chooseOne)
    : ITask(source, target), m_fieldPos(fieldPos), m_chooseOne(chooseOne)
{
    // Do nothing
}

PlayCardTask PlayCardTask::Minion(Entity* source, int chooseOne)
{
    return PlayCardTask(source, nullptr, -1, chooseOne);
}

PlayCardTask PlayCardTask::MinionTarget(Entity* source, Playable* target,
                                        int chooseOne)
{
    return PlayCardTask(source, target, -1, chooseOne);
}

PlayCardTask PlayCardTask::Spell(Entity* source, int chooseOne)
{
    return PlayCardTask(source, nullptr, -1, chooseOne);
}

PlayCardTask PlayCardTask::SpellTarget(Entity* source, Playable* target,
                                       int chooseOne)
{
    return PlayCardTask(source, target, -1, chooseOne);
}

PlayCardTask PlayCardTask::Weapon(Entity* source)
{
    return PlayCardTask(source, nullptr);
}

PlayCardTask PlayCardTask::WeaponTarget(Entity* source, Playable* target)
{
    return PlayCardTask(source, target);
}

TaskStatus PlayCardTask::Impl(Player* player)
{
    const auto source = dynamic_cast<Playable*>(m_source);
    const auto target = dynamic_cast<Character*>(m_target);

    Generic::PlayCard(player, source, target, m_fieldPos, m_chooseOne);

    return TaskStatus::COMPLETE;
}

ITask* PlayCardTask::CloneImpl()
{
    return new PlayCardTask(m_source, m_target, m_fieldPos, m_chooseOne);
}
}  // namespace RosettaStone::PlayerTasks
