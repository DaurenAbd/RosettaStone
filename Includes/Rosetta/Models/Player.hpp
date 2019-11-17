// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_PLAYER_HPP
#define ROSETTASTONE_PLAYER_HPP

#include <Rosetta/Enums/GameEnums.hpp>
#include <Rosetta/Models/Choice.hpp>
#include <Rosetta/Models/Entity.hpp>
#include <Rosetta/Models/Hero.hpp>

#include <string>

namespace RosettaStone
{
class Game;
class DeckZone;
class FieldZone;
class GraveyardZone;
class HandZone;
class SecretZone;
class SetasideZone;

//!
//! \brief Player class.
//!
//! This class stores various information that used in Hearthstone game.
//! NOTE: This information should be used differently from the existing card
//! information because there are various effects on the card.
//!
class Player : public Entity
{
 public:
    static constexpr std::size_t USER_INVALID = 255;

    //! Default constructor.
    Player();

    //! Destructor.
    ~Player();

    //! Default copy constructor.
    Player(const Player&) = delete;

    //! Default move constructor.
    Player(Player&&) noexcept = delete;

    //! Default copy assignment operator.
    Player& operator=(const Player&) = delete;

    //! Default move assignment operator.
    Player& operator=(Player&&) noexcept = delete;

    //! Copies the contents from reference \p rhs.
    //! \param rhs The source to copy the content.
    void RefCopy(const Player& rhs);

    //! Returns player's field zone.
    //! \return Player's field zone.
    FieldZone* GetFieldZone() const;

    //! Returns player's deck zone.
    //! \return Player's deck zone.
    DeckZone* GetDeckZone() const;

    //! Returns player's graveyard zone.
    //! \return Player's graveyard zone.
    GraveyardZone* GetGraveyardZone() const;

    //! Returns player's hand zone.
    //! \return Player's hand zone.
    HandZone* GetHandZone() const;

    //! Returns player's secret zone.
    //! \return player's secret zone.
    SecretZone* GetSecretZone() const;

    //! Returns player's setaside zone.
    //! \return Player's setaside zone.
    SetasideZone* GetSetasideZone() const;

    //! Returns player's hero.
    //! \return Player's hero.
    Hero* GetHero() const;

    //! Returns player's hero power.
    //! \return Player's hero power.
    HeroPower& GetHeroPower() const;

    //! Returns player's hero weapon.
    //! \return Player's hero weapon.
    Weapon& GetWeapon() const;

    //! Returns the value of game tag.
    //! \param tag The game tag of card.
    //! \return The value of game tag.
    int GetGameTag(GameTag tag) const;

    //! Sets game tag to the card.
    //! \param tag The game tag to indicate ability or condition.
    //! \param value The value to set for game tag.
    void SetGameTag(GameTag tag, int value);

    //! Returns total amount of mana available.
    //! \return Total amount of mana available.
    int GetTotalMana() const;

    //! Sets total amount of mana available.
    //! \param amount Total amount of mana available.
    void SetTotalMana(int amount);

    //! Returns amount of mana used.
    //! \return Amount of mana used.
    int GetUsedMana() const;

    //! Sets amount of mana used.
    //! \param amount Amount of mana used.
    void SetUsedMana(int amount);

    //! Returns additional mana gained during this turn.
    //! \return additional mana gained during this turn.
    int GetTemporaryMana() const;

    //! Sets additional mana gained during this turn.
    //! \param amount additional mana gained during this turn.
    void SetTemporaryMana(int amount);

    //! Returns amount of mana which will be locked during the next turn.
    //! \return Amount of mana which will be locked during the next turn.
    int GetOverloadOwed() const;

    //! Sets amount of mana which will be locked during the next turn.
    //! \param amount Amount of mana which will be locked during the next turn.
    void SetOverloadOwed(int amount);

    //! Returns amount of mana locked this turn.
    //! \return amount of mana locked this turn.
    int GetOverloadLocked() const;

    //! Sets amount of mana locked this turn.
    //! \param amount Amount of mana locked this turn.
    void SetOverloadLocked(int amount);

    //! Returns the amount of mana available to actually use after calculating
    //! all resource factors.
    //! \return The amount of mana available to actually use.
    int GetRemainingMana() const;

    //! Returns whether combo is active.
    //! \return Whether combo is active.
    bool IsComboActive() const;

    //! Sets the value of combo active.
    //! \param isActive Whether combo is active.
    void SetComboActive(bool isActive);

    //! Returns the number of minions that played this turn.
    //! \return The number of minions that played this turn.
    int GetNumMinionsPlayedThisTurn() const;

    //! Sets the number of minions that played this turn.
    //! \param value The number of minions that played this turn.
    void SetNumMinionsPlayedThisTurn(int value);

    //! Adds hero and hero power.
    //! \param heroCard A card that represents hero.
    //! \param powerCard A card that represents hero power.
    void AddHeroAndPower(Card* heroCard, Card* powerCard);

    std::string nickname;
    PlayerType playerType = PlayerType::PLAYER1;
    std::size_t playerID = 0;

    PlayState playState = PlayState::INVALID;
    Mulligan mulliganState = Mulligan::INVALID;
    std::optional<Choice> choice = std::nullopt;

    Player* opponent = nullptr;

    int currentSpellPower = 0;

 private:
    Hero* m_hero = nullptr;

    DeckZone* m_deckZone = nullptr;
    FieldZone* m_fieldZone = nullptr;
    GraveyardZone* m_graveyardZone = nullptr;
    HandZone* m_handZone = nullptr;
    SecretZone* m_secretZone = nullptr;
    SetasideZone* m_setasideZone = nullptr;

    std::map<GameTag, int> m_gameTags;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_PLAYER_HPP
