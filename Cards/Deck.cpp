#include "Deck.h"

#include "Card.h"

#include "Random.h"

#include <stdexcept>
#include <utility>
#include <random>
#include <set>
#include <iterator>

std::vector<Card> PokerDeck::GeneratePokerDeck()
{
    constexpr Card MinPokerCard{ Card::Min() };
    constexpr std::size_t PokerDeckSize{ 52 };

    return Card::GenerateDeck(MinPokerCard, PokerDeckSize);
}

PokerDeck::PokerDeck() :
    cards_{ GeneratePokerDeck() }
{
}

PokerDeck::const_iterator PokerDeck::begin() const
{
    return cards_.begin();
}

PokerDeck::const_iterator PokerDeck::end() const
{
    return cards_.end();
}

void PokerDeck::shuffle()
{
    if (cards_.size() <= 1)
    {
        return;
    }

    auto& mersenne_twister{ RandomEngine::Get() };

    // Fisher–Yates shuffle
    for (int i = cards_.size() - 1; i > 0; --i)
    {
        std::uniform_int_distribution<> distribution{ 0, i };
        const int j = distribution(mersenne_twister);

        std::swap(cards_[i], cards_[j]);
    }
}

bool PokerDeck::isFlush(const std::vector<Card>& cards)
{
    if (cards.size() < 1)
    {
        return false;
    }

    const auto expectedSuit = cards[0].getSuit();

    for (std::size_t i = 1; i < cards.size(); ++i)
    {
        if (cards.at(i).getSuit() != expectedSuit)
        {
            return false;
        }
    }

    return true;
}


bool PokerDeck::isStraight(const std::vector<Card>& cards)
{
    if (cards.size() != 5)
    {
        throw std::runtime_error{ "Incorrect parameter" };
    }

    std::set< Card, decltype(&Card::CmpRank) > sortedCards{ cards.begin(), cards.end() };

    const bool ranksAreUnique{ sortedCards.size() == 5 };

    if (!ranksAreUnique)
    {
        return false;
    }

    const auto minCard{ sortedCards.begin() };
    const auto maxCard{ sortedCards.end() };

    const bool ranksAreInSequence{ Card::RankDistance(*minCard, *maxCard) == 5 };

    if (ranksAreInSequence)
    {
        return true;
    }

    // Attention! In this design Ace is considered as the smallest element in the deck.
    // We need to add a check for the Ace high straight: A + 10 + J + Q + K
    if (minCard->getRank() == Rank::Ace)
    {
        const bool isAceHighStraight{ Card::RankDistance(*std::next(minCard), *maxCard) == 4 };
        return isAceHighStraight;
    }

    return false;
}