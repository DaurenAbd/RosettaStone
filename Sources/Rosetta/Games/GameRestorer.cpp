// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#include <Rosetta/Cards/Cards.hpp>
#include <Rosetta/Games/GameRestorer.hpp>
#include <Rosetta/Zones/DeckZone.hpp>
#include <Rosetta/Zones/HandZone.hpp>

namespace RosettaStone
{
GameRestorer::GameRestorer(const BoardView& view) : m_view(view)
{
    // Do nothing
}

GameRestorer GameRestorer::Prepare(BoardView& view,
                                   Views::Types::UnknownCardsInfo& p1Unknown,
                                   Views::Types::UnknownCardsInfo& p2Unknown)
{
    GameRestorer restorer(view);

    restorer.p1UnknownCardsManager.Setup(p1Unknown.unknownCardsSets);
    restorer.p2UnknownCardsManager.Setup(p2Unknown.unknownCardsSets);

    return restorer;
}

Game* GameRestorer::RestoreGame()
{
    p1UnknownCardsManager.Prepare();
    p2UnknownCardsManager.Prepare();

    Game* game = new Game();
    MakePlayer(PlayerType::PLAYER1, *game, m_view.GetPlayer1(),
               p1UnknownCardsManager);
    MakePlayer(PlayerType::PLAYER2, *game, m_view.GetPlayer2(),
               p2UnknownCardsManager);
    game->SetCurrentPlayer(m_view.GetCurrentPlayer());
    game->SetTurn(m_view.GetTurn());

    return game;
}

void GameRestorer::MakePlayer(
    PlayerType playerType, Game& game, const Views::Types::Player& viewPlayer,
    const Views::Types::UnknownCardsSetsManager& unknownCardsSetsManager)
{
    MakeHeroAndHeroPower(playerType, game, viewPlayer.hero,
                         viewPlayer.heroPower);
    MakeDeck(playerType, game, viewPlayer.deck, unknownCardsSetsManager);
    MakeHand(playerType, game, viewPlayer.hand, unknownCardsSetsManager);
    MakeMinions(playerType, game, viewPlayer.minions);

    Player* player = (playerType == PlayerType::PLAYER1) ? game.GetPlayer1()
                                                         : game.GetPlayer2();

    player->GetHero()->fatigue = viewPlayer.fatigue;
    MakeManaCrystal(player, viewPlayer.manaCrystal);
}

void GameRestorer::MakeHeroAndHeroPower(
    PlayerType playerType, Game& game, const Views::Types::Hero& hero,
    const Views::Types::HeroPower& heroPower)
{
    Player* player = (playerType == PlayerType::PLAYER1) ? game.GetPlayer1()
                                                         : game.GetPlayer2();

    player->AddHeroAndPower(Cards::FindCardByID(hero.cardID),
                            Cards::FindCardByID(heroPower.cardID));

    player->GetHero()->SetAttack(hero.attack);
    player->GetHero()->SetHealth(hero.health);
    player->GetHero()->SetMaxHealth(hero.maxHealth);
    player->GetHero()->SetArmor(hero.armor);
    player->GetHero()->SetExhausted(hero.isExhausted);

    player->GetHeroPower().SetExhausted(heroPower.isExhausted);
}

void GameRestorer::MakeDeck(
    PlayerType playerType, Game& game,
    std::vector<Views::Types::CardInfo> cards,
    const Views::Types::UnknownCardsSetsManager& unknownCardsSetsManager)
{
    Player* player = (playerType == PlayerType::PLAYER1) ? game.GetPlayer1()
                                                         : game.GetPlayer2();

    for (const auto& card : cards)
    {
        const std::string cardID = card.GetCardID(unknownCardsSetsManager);
        Playable* playable =
            Entity::GetFromCard(player, Cards::FindCardByID(cardID),
                                std::nullopt, player->GetDeckZone());

        player->GetDeckZone()->Add(playable);
    }
}

void GameRestorer::MakeHand(
    PlayerType playerType, Game& game,
    std::vector<Views::Types::CardInfo> cards,
    const Views::Types::UnknownCardsSetsManager& unknownCardsSetsManager)
{
    Player* player = (playerType == PlayerType::PLAYER1) ? game.GetPlayer1()
                                                         : game.GetPlayer2();

    for (const auto& card : cards)
    {
        const std::string cardID = card.GetCardID(unknownCardsSetsManager);
        Playable* playable =
            Entity::GetFromCard(player, Cards::FindCardByID(cardID),
                                std::nullopt, player->GetHandZone());

        player->GetHandZone()->Add(playable);
    }
}

void GameRestorer::MakeMinions(PlayerType playerType, Game& game,
                               const Views::Types::Minions& minions)
{
    int pos = 0;

    for (const auto& minion : minions.minions)
    {
        AddMinion(playerType, game, minion, pos);
        ++pos;
    }
}

void GameRestorer::MakeManaCrystal(Player* player,
                                   const Views::Types::ManaCrystal& manaCrystal)
{
    player->SetUsedMana(manaCrystal.used);
    player->SetTotalMana(manaCrystal.total);
    player->SetOverloadOwed(manaCrystal.overloadOwed);
    player->SetOverloadLocked(manaCrystal.overloadLocked);
}

void GameRestorer::AddMinion(PlayerType playerType, Game& game,
                             const Views::Types::Minion& minion, int pos)
{
    Player* player = (playerType == PlayerType::PLAYER1) ? game.GetPlayer1()
                                                         : game.GetPlayer2();

    Playable* playable =
        Entity::GetFromCard(player, Cards::FindCardByID(minion.cardID),
                            std::nullopt, player->GetFieldZone());
    player->GetFieldZone()->Add(playable, pos);

    Minion* m = (*player->GetFieldZone())[pos];
    m->SetAttack(minion.attack);
    m->SetHealth(minion.health);
    m->SetMaxHealth(minion.maxHealth);
    m->SetSpellPower(minion.spellPower);
    m->SetExhausted(minion.isExhausted);
}
}  // namespace RosettaStone