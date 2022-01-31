#include <iostream>

#include "Card.h"
#include "Deck.h"

#include <cassert>

void testCards()
{
	Card card{ Suit::Clubs, Rank::Four };

	assert(card.getSuit() == Suit::Clubs);
	assert(card.getRank() == Rank::Four);
}

void testCmpRank()
{
	const Card FiveClubs{ Suit::Clubs, Rank::Five };
	const Card SixHearts{ Suit::Hearts, Rank::Six };
	const Card FiveDiamonds{ Suit::Diamonds, Rank::Five };

	assert(Card::CmpRank(FiveClubs, SixHearts));
	assert(!Card::CmpRank(SixHearts, FiveClubs));

	// If ranks equal then a<b && b<a
	assert(!Card::CmpRank(FiveClubs, FiveDiamonds));
	assert(!Card::CmpRank(FiveDiamonds, FiveClubs));
}

void testRankDistance()
{
	const Card FiveClubs{ Suit::Clubs, Rank::Five };
	const Card SixHearts{ Suit::Hearts, Rank::Six };
	const Card FiveDiamonds{ Suit::Diamonds, Rank::Five };
	const Card AceDiamonds{ Suit::Diamonds, Rank::Ace };

	assert(1 == Card::RankDistance(FiveClubs, SixHearts));
	assert(-1 == Card::RankDistance(SixHearts, FiveClubs));
	assert(0 == Card::RankDistance(FiveClubs, FiveDiamonds));
	assert(4 == Card::RankDistance(AceDiamonds, FiveDiamonds));
}

void testDeck()
{
	PokerDeck deck;

	assert(52 == std::distance(deck.begin(), deck.end()));

	int noOfHearts = 0;
	int noOfDiamonds = 0;
	int noOfClubs = 0;
	int noOfSpades = 0;

	for (auto& card : deck)
	{
		switch (card.getSuit())
		{
			case Suit::Hearts: noOfHearts++; break;
			case Suit::Diamonds: noOfDiamonds++; break;
			case Suit::Clubs: noOfClubs++; break;
			case Suit::Spades: noOfSpades++; break;
		}
	}

	assert(13 == noOfHearts);
	assert(13 == noOfDiamonds);
	assert(13 == noOfClubs);
	assert(13 == noOfSpades);
}

void testShuffle()
{
	const int N = 10'000;
	int FirstCardIsHeart = 0;

	for (int i = 0; i < N; ++i)
	{
		PokerDeck d;
		d.shuffle();

		if (std::next(d.begin())->getSuit() == Suit::Hearts)
		{
			FirstCardIsHeart++;
		}
	}

	const double FirstCardIsHeartPercent{
		static_cast<double>(FirstCardIsHeart) / static_cast<double>(N)
	};
	
	assert( std::abs(FirstCardIsHeartPercent - 0.25 ) < 0.01 );
}

void testisFlush()
{
	const std::vector<Card> flush{
		Card{ Suit::Clubs, Rank::Five },
		Card{ Suit::Clubs, Rank::Six },
		Card{ Suit::Clubs, Rank::Ace },
		Card{ Suit::Clubs, Rank::Two },
		Card{ Suit::Clubs, Rank::Queen }
	};

	assert( PokerDeck::isFlush(flush) );

	const std::vector<Card> notFlush{
		Card{ Suit::Clubs, Rank::Five },
		Card{ Suit::Spades, Rank::Six },
		Card{ Suit::Clubs, Rank::Ace },
		Card{ Suit::Diamonds, Rank::Two },
		Card{ Suit::Clubs, Rank::Queen }
	};

	assert(!PokerDeck::isFlush(notFlush));
}

void testisStraight()
{
	const std::vector<Card> straight{
		Card{ Suit::Clubs, Rank::Six },
		Card{ Suit::Diamonds, Rank::Five },
		Card{ Suit::Clubs, Rank::Two },
		Card{ Suit::Clubs, Rank::Four },
		Card{ Suit::Spades, Rank::Three }
	};

	assert(PokerDeck::isStraight(straight));

	const std::vector<Card> aceHighStraight{
		Card{ Suit::Clubs, Rank::Jack },
		Card{ Suit::Diamonds, Rank::Ace },
		Card{ Suit::Clubs, Rank::Ten },
		Card{ Suit::Clubs, Rank::King },
		Card{ Suit::Spades, Rank::Queen }
	};

	assert(PokerDeck::isStraight(aceHighStraight));

	const std::vector<Card> aceLowStraight{
		Card{ Suit::Clubs, Rank::Two },
		Card{ Suit::Diamonds, Rank::Ace },
		Card{ Suit::Clubs, Rank::Four },
		Card{ Suit::Clubs, Rank::Five },
		Card{ Suit::Spades, Rank::Three }
	};

	assert(PokerDeck::isStraight(aceLowStraight));

	const std::vector<Card> notStraight{
		Card{ Suit::Clubs, Rank::Five },
		Card{ Suit::Spades, Rank::Six },
		Card{ Suit::Clubs, Rank::Ace },
		Card{ Suit::Diamonds, Rank::Two },
		Card{ Suit::Clubs, Rank::Queen }
	};

	assert(!PokerDeck::isStraight(notStraight));
}

int main()
{
	testCards();
	testCmpRank();
	testRankDistance();

	testDeck();
	testShuffle();
	testisFlush();
	testisFlush();

	std::cout << "Tests OK.\n";
}
