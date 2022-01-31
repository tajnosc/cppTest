#pragma once

#include <vector>

class Card;

class PokerDeck
{
private:
    std::vector<Card> cards_;

    static std::vector<Card> GeneratePokerDeck();

public:
    using const_iterator = std::vector<Card>::const_iterator;

    explicit PokerDeck();

    const_iterator begin() const;

    const_iterator end() const;

    void shuffle();

    static bool isFlush(const std::vector<Card>& cards);

    static bool isStraight(const std::vector<Card>& cards);

};