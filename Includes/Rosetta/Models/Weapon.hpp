// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_WEAPON_HPP
#define ROSETTASTONE_WEAPON_HPP

#include <Rosetta/Models/Playable.hpp>

namespace RosettaStone
{
//!
//! \brief Weapon class.
//!
//! This class inherits from Playable class.
//! Also, it stores durability that shows the number of times you can use that
//! weapon before it is destroyed.
//!
class Weapon : public Playable
{
 public:
    //! Constructs weapon with given \p player, \p card and \p tags.
    //! \param player The owner of the card.
    //! \param card The card.
    //! \param tags The game tags.
    Weapon(Player* player, Card* card, std::map<GameTag, int> tags);

    //! Destructor.
    ~Weapon();

    //! Deleted copy constructor.
    Weapon(const Weapon&) = delete;

    //! Deleted copy assignment operator.
    Weapon& operator=(const Weapon&) = delete;

    //! Deleted move constructor.
    Weapon(Weapon&&) noexcept = delete;

    //! Deleted move assignment operator.
    Weapon& operator=(Weapon&&) noexcept = delete;

    //! Returns the value of attack.
    //! \return The value of attack.
    int GetAttack() const;

    //! Sets the value of attack.
    //! \param attack The value of attack.
    void SetAttack(int attack);

    //! Returns the value of durability.
    //! \return The value of durability.
    int GetDurability() const;

    //! Sets the value of durability.
    //! \param durability The value of durability.
    void SetDurability(int durability);

    //! Remove the value of durability by amount.
    //! \param amount The amount to be removed.
    void RemoveDurability(int amount);
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_WEAPON_HPP
