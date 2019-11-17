// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_GAME_CONFIG_HPP
#define ROSETTASTONE_GAME_CONFIG_HPP

#include <Rosetta/Cards/Card.hpp>
#include <Rosetta/Commons/Constants.hpp>
#include <Rosetta/Models/Player.hpp>

#include <array>

namespace RosettaStone
{
//!
//! \brief GameConfig struct.
//!
//! This struct holds all configuration values to create a new Game instance.
//!
struct GameConfig
{
    PlayerType startPlayer = PlayerType::RANDOM;

    CardClass player1Class = CardClass::MAGE;
    CardClass player2Class = CardClass::WARLOCK;

    std::array<Card, START_DECK_SIZE> player1Deck;
    std::array<Card, START_DECK_SIZE> player2Deck;

    std::array<std::string, NUM_PLAYER_CLASS> fillCardIDs = {
        "UNG_028", "UNG_067", "UNG_116", "UNG_829", "UNG_934",
        "UNG_920", "UNG_940", "UNG_942", "UNG_954"
    };

    bool doFillDecks = false;
    bool doShuffle = true;
    bool skipMulligan = true;
    bool autoRun = true;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_GAME_CONFIG_HPP
