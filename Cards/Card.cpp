#include "Card.h"

std::vector<Card> Card::GenerateDeck(
	const Card firstCard,
	const std::size_t deckSize)
{
	std::vector<Card> cards;

	cards.reserve(deckSize);

	for (std::uint8_t i = firstCard.rawBytes; i < deckSize + firstCard.rawBytes; ++i)
	{
		cards.emplace_back(i);
	}

	return cards;
}