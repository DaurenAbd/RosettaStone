// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_TRIGGER_ENUMS_HPP
#define ROSETTASTONE_TRIGGER_ENUMS_HPP

namespace RosettaStone
{
//! \brief An enumerator for identifying trigger type.
enum class TriggerType
{
    NONE,          //!< The effect has nothing.
    TURN_START,    //!< The effect will be triggered at the start of turn.
    TURN_END,      //!< The effect will be triggered at the end of turn.
    PLAY_CARD,     //!< The effect will be triggered when a player plays a card.
    CAST_SPELL,    //!< The effect will be triggered when a player plays a Spell
                   //!< card.
    AFTER_CAST,    //!< The effect will be triggered after a spell is played.
    HEAL,          //!< The effect will be triggered when characters are healed.
    ATTACK,        //!< The effect will be triggered when characters attack.
    AFTER_ATTACK,  //!< The effect will be triggered after an attack action is
                   //!< ended.
    SUMMON,  //!< The effect will be triggered whenever a minion is summoned.
    AFTER_SUMMON,  //!< The effect will be triggered after a minion is summoned.
    PLAY_MINION,  //!< The effect will be triggered when a player plays a Minion
                  //!< card.
    AFTER_PLAY_MINION,  //!< The effect will be triggered after a minion is
                        //!< played.
    DEAL_DAMAGE,  //!< The effect will be triggered when a character is damaged.
    TAKE_DAMAGE,  //!< The effect will be triggered when a spell or a character
                  //!< deals damages to source.
    PREDAMAGE,    //!< Effect will be triggered when a character gets predamage.
                  //!< This event happens just before the character is actually
                  //!< damaged.
    TARGET,  //!< The effect will be triggered when a card is targeted by an
             //!< attacking minion or a played card.
    DEATH,   //!< The effect will be triggered when a minion dies.
};

//! \brief An enumerator for identifying trigger source.
enum class TriggerSource
{
    NONE,
    SELF,
    ENEMY,
    HERO,
    ALL_MINIONS,
    MINIONS,
    MINIONS_EXCEPT_SELF,
    ENEMY_MINIONS,
    ENCHANTMENT_TARGET,
    ENEMY_SPELLS,
    FRIENDLY,
};

//! \brief An enumerator for identifying trigger activation.
enum class TriggerActivation
{
    PLAY,
    HAND,
    DECK,
    HAND_OR_PLAY
};

//! \brief An enumerator for identifying sequence type.
enum class SequenceType
{
    NONE,
    PLAY_CARD,
    PLAY_MINION,
    PLAY_SPELL,
    TARGET
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_TRIGGER_ENUMS_HPP
