// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_ADAPTIVE_COST_EFFECT_HPP
#define ROSETTASTONE_ADAPTIVE_COST_EFFECT_HPP

#include <Rosetta/Auras/Aura.hpp>

namespace RosettaStone
{
//!
//! \brief AdaptiveCostEffect class.
//!
//! Implementation of the specific effects of varying cost. e.g. Giants.
//!
class AdaptiveCostEffect : public IAura
{
 public:
    //! Constructs adaptive cost effect with given \p costFunc and \p effectOp.
    //! \param costFunc The function to vary cost.
    //! \param effectOp The operator to vary cost.
    explicit AdaptiveCostEffect(std::function<int(Playable*)> costFunc,
                                EffectOperator effectOp = EffectOperator::SUB);

    //! Create new Aura instance to the owner's game.
    //! \param owner An owner of adaptive cost effect.
    //! \param cloning The flag to indicate that it is cloned.
    void Activate(Playable* owner, bool cloning = false) override;

    //! Varies cost with given \p value.
    //! \param value The value of cost to vary.
    //! \return The value of cost that is varied.
    int Apply(int value) const;

    //! Updates this effect to apply the effect to recently modified entities.
    void Update() override;

    //! Removes this effect from the game to stop affecting entities.
    void Remove() override;

    //! Clones aura effect to \p clone.
    //! \param clone The entity to clone aura effect.
    void Clone(Playable* clone) override;

 private:
    //! Constructs adaptive cost effect with given \p prototype and \p owner.
    //! \param prototype An adaptive cost effect for prototype.
    //! \param owner An owner of adaptive cost effect.
    AdaptiveCostEffect(AdaptiveCostEffect& prototype, Playable& owner);

    Playable* m_owner = nullptr;

    std::function<int(Playable*)> m_costFunc;
    EffectOperator m_effectOp;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_ADAPTIVE_COST_EFFECT_HPP
