// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_ADAPTIVE_EFFECT_HPP
#define ROSETTASTONE_ADAPTIVE_EFFECT_HPP

#include <Rosetta/Auras/Aura.hpp>

namespace RosettaStone
{
//!
//! \brief AdaptiveEffect class.
//!
//! Effects of this kind of Auras are influenced by other factors in game, in
//! real time. e.g. Lightspawn, Southsea Deckhand.
//!
class AdaptiveEffect : public IAura
{
 public:
    //! Constructs adaptive effect with given \p condition and \p tag.
    //! \param condition The specific condition.
    //! \param tag The game tag.
    AdaptiveEffect(SelfCondition* condition, GameTag tag);

    //! Create new Aura instance to the owner's game.
    //! \param owner An owner of adaptive effect.
    //! \param cloning The flag to indicate that it is cloned.
    void Activate(Playable* owner,
                  [[maybe_unused]] bool cloning = false) override;

    //! Updates this effect to apply the effect to recently modified entities.
    void Update() override;

    //! Removes this effect from the game to stop affecting entities.
    void Remove() override;

    //! Clones aura effect to \p clone.
    //! \param clone The entity to clone aura effect.
    void Clone(Playable* clone) override;

 private:
    //! Constructs adaptive effect with given \p prototype and \p owner.
    //! \param prototype An adaptive effect for prototype.
    //! \param owner An owner of adaptive effect.
    AdaptiveEffect(AdaptiveEffect& prototype, Playable& owner);

    Playable* m_owner = nullptr;

    SelfCondition* m_condition = nullptr;
    std::function<int(Playable*)> m_valueFunc;

    GameTag m_tag;
    EffectOperator m_operator;

    int m_lastValue = 0;
    bool m_turnOn = true;
    bool m_isSwitching = false;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_ADAPTIVE_EFFECT_HPP
