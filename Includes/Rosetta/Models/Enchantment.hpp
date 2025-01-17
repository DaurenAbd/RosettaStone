// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_ENCHANTMENT_HPP
#define ROSETTASTONE_ENCHANTMENT_HPP

#include <Rosetta/Models/Playable.hpp>

namespace RosettaStone
{
class Player;

//!
//! \brief Enchantment class.
//!
//! This class inherits from Playable class.
//!
class Enchantment : public Playable
{
 public:
    //! Constructs enchantment with given \p player, \p card, \p tags
    //! and \p target.
    //! \param player The owner of the card.
    //! \param card The card.
    //! \param tags The game tags.
    //! \param target A target of enchantment.
    Enchantment(Player* player, Card* card, std::map<GameTag, int> tags,
                Entity* target);

    //! Default destructor.
    ~Enchantment() = default;

    //! Deleted copy constructor.
    Enchantment(const Enchantment&) = delete;

    //! Deleted copy assignment operator.
    Enchantment& operator=(const Enchantment&) = delete;

    //! Deleted move constructor.
    Enchantment(Enchantment&&) noexcept = delete;

    //! Deleted move assignment operator.
    Enchantment& operator=(Enchantment&&) noexcept = delete;

    //! Creates and adds a new Enchantment to the given player's game.
    //! \param player The controller of the enchantment.
    //! \param card The card from which the enchantment must be derived.
    //! \param target The entity who is subjected to the enchantment.
    //! \param num1 The number of GameTag::TAG_SCRIPT_DATA_NUM_1.
    //! \param num2 The number of GameTag::TAG_SCRIPT_DATA_NUM_2.
    //! \return The resulting enchantment entity.
    static Enchantment* GetInstance(Player* player, Card* card, Entity* target,
                                    int num1 = 0, int num2 = 0);

    //! Returns the target of enchantment.
    //! \return The target of enchantment.
    Entity* GetTarget() const;

    //! Returns the number of GameTag::TAG_SCRIPT_DATA_NUM_1.
    //! \return The number of GameTag::TAG_SCRIPT_DATA_NUM_1.
    int GetScriptTag1() const;

    //! Returns the number of GameTag::TAG_SCRIPT_DATA_NUM_2.
    //! \return The number of GameTag::TAG_SCRIPT_DATA_NUM_2.
    int GetScriptTag2() const;

    //! Returns the flag that indicates whether it is one turn active.
    //! \return The flag that indicates whether it is one turn active.
    bool IsOneTurnActive() const;

    //! Removes enchantment.
    void Remove();

 private:
    Entity* m_target = nullptr;

    bool m_isOneTurnActive = false;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_ENCHANTMENT_HPP
