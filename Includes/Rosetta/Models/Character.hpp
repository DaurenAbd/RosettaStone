// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_CHARACTER_HPP
#define ROSETTASTONE_CHARACTER_HPP

#include <Rosetta/Models/Playable.hpp>

namespace RosettaStone
{
class Player;

//!
//! \brief Abstract character class that stores hero and minion data.
//!
//! This class inherits from Playable class. Also, it stores some
//! attributes that only characters have such as attack and health.
//!
class Character : public Playable
{
 public:
    //! Constructs character with given \p player, \p card and \p tags.
    //! \param player The owner of the card.
    //! \param card The card.
    //! \param tags The game tags.
    Character(Player* player, Card* card, std::map<GameTag, int> tags);

    //! Default destructor.
    ~Character() = default;

    //! Deleted copy constructor.
    Character(const Character&) = delete;

    //! Deleted copy assignment operator.
    Character& operator=(const Character&) = delete;

    //! Deleted move constructor.
    Character(Character&&) noexcept = delete;

    //! Deleted move assignment operator.
    Character& operator=(Character&&) noexcept = delete;

    //! Returns the value of attack.
    //! \return The value of attack.
    virtual int GetAttack() const;

    //! Sets the value of attack.
    //! \param attack The value of attack.
    void SetAttack(int attack);

    //! Returns the value of pre-damage.
    //! \return The value of pre-damage.
    int GetPreDamage() const;

    //! Sets the value of pre-damage.
    //! \param preDamage The value of pre-damage.
    void SetPreDamage(int preDamage);

    //! Returns the value of damage.
    //! \return The value of damage.
    int GetDamage() const;

    //! Sets the value of damage.
    //! \param damage The value of damage.
    void SetDamage(int damage);

    //! Returns the value of health.
    //! \return The value of health.
    int GetHealth() const;

    //! Sets the value of health.
    //! \param health The value of health.
    void SetHealth(int health);

    //! Returns the value of max health.
    //! \return The value of max health.
    int GetMaxHealth() const;

    //! Sets the value of max health.
    //! \param maxHealth The value of max health.
    void SetMaxHealth(int maxHealth);

    //! Returns the value of spell power.
    //! \return The value of spell power.
    int GetSpellPower() const;

    //! Sets the value of spell power.
    //! \param spellPower The value of spell power.
    void SetSpellPower(int spellPower);

    //! Returns the number of attacks at this turn.
    //! \return The number of attacks at this turn.
    int GetNumAttacksThisTurn() const;

    //! Gets the number of attacks at this turn.
    //! \param amount The number of attacks at this turn.
    void SetNumAttacksThisTurn(int amount);

    //! Returns the flag that indicates whether this character is \p race.
    //! \param race The value of race.
    //! \return The flag that indicates whether this character is \p race.
    bool IsRace(Race race) const;

    //! Returns the flag that indicates whether this character is immune.
    //! \return The flag that indicates whether this character is immune.
    bool IsImmune() const;

    //! Returns the flag that indicates whether this character has taunt.
    //! \return The flag that indicates whether this character has taunt.
    bool HasTaunt() const;

    //! Returns the flag that indicates whether this character has stealth.
    //! \return The flag that indicates whether this character has stealth.
    bool HasStealth() const;

    //! Returns whether attack is possible.
    //! \return Whether attack is possible.
    bool CanAttack() const;

    //! Returns whether the target is valid in combat.
    //! \param opponent The opponent player.
    //! \param target A pointer to the target.
    //! \return true if the target is valid, and false otherwise.
    bool IsValidCombatTarget(Player* opponent, Character* target) const;

    //! Returns a list of valid target in combat.
    //! \param opponent The opponent player.
    //! \return A list of pointer to valid target.
    std::vector<Character*> GetValidCombatTargets(Player* opponent) const;

    //! Takes damage from a certain other entity.
    //! \param source An entity to give damage.
    //! \param damage The value of damage.
    //! \return Final damage taking into account ability.
    int TakeDamage(Playable* source, int damage);

    //! Takes heal up all taken damage.
    //! \param source An entity to give full heal.
    void TakeFullHeal(Playable* source);

    //! Takes heal a specified amount of health.
    //! \param source An entity to give heal.
    //! \param heal The value of heal.
    void TakeHeal(Playable* source, int heal);

    std::function<void(Player*, Entity*)> preDamageTrigger;
    std::function<void(Player*, Entity*)> takeDamageTrigger;
    std::function<void(Player*, Entity*)> afterAttackTrigger;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_CHARACTER_HPP
