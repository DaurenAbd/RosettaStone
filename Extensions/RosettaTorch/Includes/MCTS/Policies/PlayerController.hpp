// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_MCTS_PLAYER_CONTROLLER_HPP
#define ROSETTASTONE_TORCH_MCTS_PLAYER_CONTROLLER_HPP

#include <Rosetta/Views/Board.hpp>

namespace RosettaTorch::MCTS
{
//!
//! \brief PlayerController class.
//!
//! This class contains Player class for MCTS and related getters and setters.
//!
class PlayerController
{
 public:
    //!
    //! \brief PlayerController::Player class.
    //!
    //! Note that this class is different from RosettaStone's.
    //!
    class Player
    {
     public:
        //! Constructs player with given \p playerType.
        //! \param playerType The type of player.
        explicit Player(RosettaStone::PlayerType playerType);

        //! Operator overloading: operator==.
        bool operator==(const Player& rhs) const;

        //! Operator overloading: operator!=.
        bool operator!=(const Player& rhs) const;

        //! Returns the player 1.
        //! \return The player 1.
        static Player Player1();

        //! Returns the player 2.
        //! \return The player 2.
        static Player Player2();

        //! Returns the opponent player.
        //! \return The opponent player.
        Player Opponent() const;

        //! Returns the flag indicates that this player is player 1.
        //! \return The flag indicates that this player is player 1.
        bool IsPlayer1() const;

        //! Returns the flag indicates that this player is player 2.
        //! \return The flag indicates that this player is player 2.
        bool IsPlayer2() const;

        //! Returns the type of player.
        //! \return The type of player.
        RosettaStone::PlayerType GetPlayerType() const;

     private:
        RosettaStone::PlayerType m_playerType;
    };

    //! Returns the player.
    //! \return The player.
    Player GetPlayer() const;

    //! Returns the board of the player.
    //! \param player The player to get board.
    //! \return The board of the player.
    RosettaStone::Board GetPlayerBoard(Player player) const;

    //! Starts the game.
    template <class StartBoardGetter>
    void StartEpisode(StartBoardGetter&& startBoardGetter)
    {
        m_game = startBoardGetter();
    }

 private:
    RosettaStone::Game* m_game = nullptr;
};
}  // namespace RosettaTorch::MCTS

#endif  // ROSETTASTONE_TORCH_MCTS_PLAYER_CONTROLLER_HPP