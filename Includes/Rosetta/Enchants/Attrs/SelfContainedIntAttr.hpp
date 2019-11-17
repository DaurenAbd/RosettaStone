// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_SELF_CONTAINED_INT_ATTR_HPP
#define ROSETTASTONE_SELF_CONTAINED_INT_ATTR_HPP

#include <Rosetta/Enchants/Attrs/IntAttr.hpp>
#include <Rosetta/Enchants/GenericEffect.hpp>

namespace RosettaStone
{
//!
//! \brief SelfContainedIntAttr class.
//!
//! This class inherits from IntAttr class and contains Effect() method
//! for generating generic effect using CRTP(Curiously Recurring Template
//! Pattern) technique.
//!
template <typename SelfT, typename TargetT = Entity>
class SelfContainedIntAttr : public IntAttr<TargetT>
{
 public:
    //! Default virtual destructor.
    virtual ~SelfContainedIntAttr() = default;

    //! Generates new generic effect for integer attribute.
    //! \param effectOp The effect operator of the generic effect.
    //! \param value The value of the generic effect.
    //! \return The generic effect that is dynamically allocated.
    static GenericEffect<TargetT, SelfT>* Effect(EffectOperator effectOp,
                                                 int value)
    {
        if (m_singleton == nullptr)
        {
            m_singleton = new SelfT();
        }

        return new GenericEffect<TargetT, SelfT>(m_singleton, effectOp, value);
    }

 private:
    inline static SelfT* m_singleton = nullptr;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_SELF_CONTAINED_INT_ATTR_HPP
