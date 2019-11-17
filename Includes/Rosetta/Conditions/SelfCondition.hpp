// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_SELF_CONDITION_HPP
#define ROSETTASTONE_SELF_CONDITION_HPP

#include <Rosetta/Enums/CardEnums.hpp>
#include <Rosetta/Enums/TaskEnums.hpp>

#include <functional>

namespace RosettaStone
{
class Playable;

//!
//! \brief SelfCondition class.
//!
//! This class is a container for all conditions about the subject entity.
//!
class SelfCondition
{
 public:
    //! Constructs task with given \p func.
    //! \param func The function to check condition.
    explicit SelfCondition(std::function<bool(Playable*)> func);

    //! SelfCondition wrapper for checking the hero power equals \p cardID.
    //! \param cardID The card ID of hero power.
    //! \return Generated SelfCondition for intended purpose.
    static SelfCondition IsHeroPowerCard(const std::string& cardID);

    //! SelfCondition wrapper for checking the entity is destroyed.
    //! \return Generated SelfCondition for intended purpose.
    static SelfCondition IsDead();

    //! SelfCondition wrapper for checking the entity is not destroyed.
    //! \return Generated SelfCondition for intended purpose.
    static SelfCondition IsNotDead();

    //! SelfCondition wrapper for checking the field is full.
    //! \return Generated SelfCondition for intended purpose.
    static SelfCondition IsFieldFull();

    //! SelfCondition wrapper for checking the entity is damaged.
    //! \return Generated SelfCondition for intended purpose.
    static SelfCondition IsDamaged();

    //! SelfCondition wrapper for checking the entity is undamaged.
    //! \return Generated SelfCondition for intended purpose.
    static SelfCondition IsUndamaged();

    //! SelfCondition wrapper for checking the hero equips weapon.
    //! \return Generated SelfCondition for intended purpose.
    static SelfCondition IsWeaponEquipped();

    //! SelfCondition wrapper for checking race of entity is \p race.
    //! \param race The race for checking.
    //! \return Generated SelfCondition for intended purpose.
    static SelfCondition IsRace(Race race);

    //! SelfCondition wrapper for checking there is the entity with \p race in
    //! field zone.
    //! \param race The race for checking.
    //! \return Generated SelfCondition for intended purpose.
    static SelfCondition IsControllingRace(Race race);

    //! SelfCondition wrapper for checking the secret exists
    //! in the owner's secret zone.
    //! \return Generated SelfCondition for intended purpose.
    static SelfCondition IsControllingSecret();

    //! SelfCondition wrapper for checking the entity is minion.
    //! \return Generated SelfCondition for intended purpose.
    static SelfCondition IsMinion();

    //! SelfCondition wrapper for checking the entity is spell.
    //! \return Generated SelfCondition for intended purpose.
    static SelfCondition IsSpell();

    //! SelfCondition wrapper for checking the entity is secret.
    //! \return Generated SelfCondition for intended purpose.
    static SelfCondition IsSecret();

    //! SelfCondition wrapper for checking the entity is frozen.
    //! \return Generated SelfCondition for intended purpose.
    static SelfCondition IsFrozen();

    //! SelfCondition wrapper for checking the player has minion in hand.
    //! \return Generated SelfCondition for intended purpose.
    static SelfCondition HasMinionInHand();

    //! SelfCondition wrapper for checking the card has overload.
    //! \return Generated SelfCondition for intended purpose.
    static SelfCondition IsOverloadCard();

    //! SelfCondition wrapper for checking the number of minion
    //! that played this turn.
    //! \param num The number of minion for checking.
    //! \return Generated SelfCondition for intended purpose.
    static SelfCondition MinionsPlayedThisTurn(int num);

    //! SelfCondition wrapper for checking there is the entity that satisfies
    //! condition with \p tag, \p value and \p relaSign.
    //! \param tag The game tag to check condition.
    //! \param value The value to check condition.
    //! \param relaSign The comparer to check condition.
    //! \return Generated SelfCondition for intended purpose.
    static SelfCondition IsTagValue(GameTag tag, int value,
                                    RelaSign relaSign = RelaSign::EQ);

    //! SelfCondition wrapper for checking the name of entity equals \p name.
    //! \param name The name of card to check condition.
    //! \param isEqual The flag to indicate that the condition for equality.
    //! \return Generated SelfCondition for intended purpose.
    static SelfCondition IsName(const std::string& name, bool isEqual = true);

    //! SelfCondition wrapper for checking num in taskStack satisfy condition
    //! with \p value and \p relaSign.
    //! \param value The value to check condition.
    //! \param relaSign The comparer to check condition.
    //! \param index If index is 0, use num; If index is 1, use num1.
    //! \return Generated SelfCondition for intended purpose.
    static SelfCondition IsStackNum(int value, RelaSign relaSign = RelaSign::EQ,
                                    int index = 0);

    //! SelfCondition wrapper for checking the health that satisfies
    //! condition with \p value and \p relaSign.
    //! \param value The value to check condition.
    //! \param relaSign The comparer to check condition.
    //! \return Generated SelfCondition for intended purpose.
    static SelfCondition IsHealth(int value, RelaSign relaSign);

    //! Evaluates condition using checking function.
    //! \param owner The owner entity.
    //! \return true if the condition is satisfied, false otherwise.
    bool Evaluate(Playable* owner) const;

 private:
    std::function<bool(Playable*)> m_func;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_SELF_CONDITION_HPP
