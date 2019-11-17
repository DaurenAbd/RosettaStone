// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Cards/Card.hpp>
#include <Rosetta/Cards/Cards.hpp>
#include <Rosetta/Loaders/CardLoader.hpp>
#include <Rosetta/Loaders/PowerLoader.hpp>

namespace RosettaStone
{
Card emptyCard;
std::vector<Card*> Cards::m_cards;

Cards::Cards()
{
    CardLoader::Load(m_cards);
    PowerLoader::Load(m_cards);
}

Cards::~Cards()
{
    for (Card* card : m_cards)
    {
        delete card;
    }

    m_cards.clear();
}

Cards& Cards::GetInstance()
{
    static Cards instance;
    return instance;
}

const std::vector<Card*>& Cards::GetAllCards()
{
    return m_cards;
}

Card* Cards::FindCardByID(const std::string& id)
{
    for (Card* card : m_cards)
    {
        if (card->id == id)
        {
            return card;
        }
    }

    return &emptyCard;
}

Card* Cards::FindCardByDbfID(int dbfID)
{
    for (Card* card : m_cards)
    {
        if (card->dbfID == dbfID)
        {
            return card;
        }
    }

    return &emptyCard;
}

std::vector<Card*> Cards::FindCardByRarity(Rarity rarity)
{
    std::vector<Card*> result;

    for (Card* card : m_cards)
    {
        if (card->GetRarity() == rarity)
        {
            result.emplace_back(card);
        }
    }

    return result;
}

std::vector<Card*> Cards::FindCardByClass(CardClass cardClass)
{
    std::vector<Card*> result;

    for (Card* card : m_cards)
    {
        if (card->GetCardClass() == cardClass)
        {
            result.emplace_back(card);
        }
    }

    return result;
}

std::vector<Card*> Cards::FindCardBySet(CardSet cardSet)
{
    std::vector<Card*> result;

    for (Card* card : m_cards)
    {
        if (card->GetCardSet() == cardSet)
        {
            result.emplace_back(card);
        }
    }

    return result;
}

std::vector<Card*> Cards::FindCardByType(CardType cardType)
{
    std::vector<Card*> result;

    for (Card* card : m_cards)
    {
        if (card->GetCardType() == cardType)
        {
            result.emplace_back(card);
        }
    }

    return result;
}

std::vector<Card*> Cards::FindCardByRace(Race race)
{
    std::vector<Card*> result;

    for (Card* card : m_cards)
    {
        if (card->GetRace() == race)
        {
            result.emplace_back(card);
        }
    }

    return result;
}

Card* Cards::FindCardByName(const std::string& name)
{
    for (Card* card : m_cards)
    {
        if (card->name == name)
        {
            return card;
        }
    }

    return &emptyCard;
}

std::vector<Card*> Cards::FindCardByCost(int minVal, int maxVal)
{
    std::vector<Card*> result;

    for (Card* card : m_cards)
    {
        if (card->gameTags.at(GameTag::COST) >= minVal &&
            card->gameTags.at(GameTag::COST) <= maxVal)
        {
            result.emplace_back(card);
        }
    }

    return result;
}

std::vector<Card*> Cards::FindCardByAttack(int minVal, int maxVal)
{
    std::vector<Card*> result;

    for (Card* card : m_cards)
    {
        if (!(card->GetCardType() == CardType::MINION) &&
            !(card->GetCardType() == CardType::WEAPON))
        {
            continue;
        }

        if (card->gameTags.at(GameTag::ATK) >= minVal &&
            card->gameTags.at(GameTag::ATK) <= maxVal)
        {
            result.emplace_back(card);
        }
    }

    return result;
}

std::vector<Card*> Cards::FindCardByHealth(int minVal, int maxVal)
{
    std::vector<Card*> result;

    for (Card* card : m_cards)
    {
        if (!(card->GetCardType() == CardType::MINION) &&
            !(card->GetCardType() == CardType::HERO))
        {
            continue;
        }

        if (card->gameTags.at(GameTag::HEALTH) >= minVal &&
            card->gameTags.at(GameTag::HEALTH) <= maxVal)
        {
            result.emplace_back(card);
        }
    }

    return result;
}

std::vector<Card*> Cards::FindCardBySpellPower(int minVal, int maxVal)
{
    std::vector<Card*> result;

    for (Card* card : m_cards)
    {
        if (card->gameTags.at(GameTag::SPELLPOWER) >= minVal &&
            card->gameTags.at(GameTag::SPELLPOWER) <= maxVal)
        {
            result.emplace_back(card);
        }
    }

    return result;
}

std::vector<Card*> Cards::FindCardByGameTag(std::vector<GameTag> gameTags)
{
    std::vector<Card*> result;

    for (auto& card : m_cards)
    {
        auto cardGameTags = card->gameTags;

        for (const auto gameTag : gameTags)
        {
            if (cardGameTags.find(gameTag) != cardGameTags.end())
            {
                result.emplace_back(card);
            }
        }
    }

    return result;
}

Card* Cards::GetHeroCard(CardClass cardClass)
{
    switch (cardClass)
    {
        case CardClass::DRUID:
            return FindCardByID("HERO_06");
        case CardClass::HUNTER:
            return FindCardByID("HERO_05");
        case CardClass::MAGE:
            return FindCardByID("HERO_08");
        case CardClass::PALADIN:
            return FindCardByID("HERO_04");
        case CardClass::PRIEST:
            return FindCardByID("HERO_09");
        case CardClass::ROGUE:
            return FindCardByID("HERO_03");
        case CardClass::SHAMAN:
            return FindCardByID("HERO_02");
        case CardClass::WARLOCK:
            return FindCardByID("HERO_07");
        case CardClass::WARRIOR:
            return FindCardByID("HERO_01");
        default:
            return &emptyCard;
    }
}

Card* Cards::GetDefaultHeroPower(CardClass cardClass)
{
    switch (cardClass)
    {
        case CardClass::DRUID:
            return FindCardByID("CS2_017");
        case CardClass::HUNTER:
            return FindCardByID("DS1h_292");
        case CardClass::MAGE:
            return FindCardByID("CS2_034");
        case CardClass::PALADIN:
            return FindCardByID("CS2_101");
        case CardClass::PRIEST:
            return FindCardByID("CS1h_001");
        case CardClass::ROGUE:
            return FindCardByID("CS2_083b");
        case CardClass::SHAMAN:
            return FindCardByID("CS2_049");
        case CardClass::WARLOCK:
            return FindCardByID("CS2_056");
        case CardClass::WARRIOR:
            return FindCardByID("CS2_102");
        default:
            return &emptyCard;
    }
}
}  // namespace RosettaStone
