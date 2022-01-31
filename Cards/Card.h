#pragma once

#include <cstdint>
#include <vector>

enum class Suit : std::uint8_t
{
	Hearts = 0,   // 00
	Diamonds = 1, // 01
	Clubs = 2,    // 10
	Spades = 3    // 11
};

enum class Rank : std::uint8_t
{
	Ace = 1,
	Two = 2,
	Three = 3,
	Four = 4,
	Five = 5,
	Six = 6,
	Seven = 7,
	Eight = 8,
	Nine = 9,
	Ten = 10,
	Jack = 11,
	Queen = 12,
	King = 13
};

class Card
{
private:
	/*!
	 * \brief Raw bytes represents one card 
	 * 
	 * \detail Bytes use the following encoding:
	 *			- 2 first bytes containing leading zeros;
	 * 	  		- 4 following bytes encoding rank;
	 *			- 2 following bytes encoding suit;
	 */
	std::uint8_t rawBytes;

	constexpr static std::uint8_t RankMask{ 0b00111100 };

public:
	static constexpr std::uint8_t ToBytes(const Suit suit, const Rank rank)
	{
		return (static_cast<std::uint8_t>(rank) << 2 | static_cast<std::uint8_t>(suit));
	}

	constexpr explicit Card(const std::uint8_t bytes) :
		rawBytes{ bytes }
	{
	}

public:
	constexpr Card(const Suit suit, const Rank rank) :
		rawBytes{ ToBytes(suit,rank) }
	{
	}

	constexpr Card(const Card&) = default;
	constexpr Card& operator=(const Card&) = default;
	
	constexpr Suit getSuit() const
	{
		constexpr std::uint8_t SuitMask{ 0b00000011 };
		return static_cast<Suit>( (rawBytes & SuitMask) ) ;
	}

	constexpr Rank getRank() const
	{
		return static_cast<Rank>((rawBytes & RankMask) >> 2 );
	}

	constexpr static Card Min() 
	{
		return Card{ Suit::Hearts, Rank::Ace };
	}

	static std::vector<Card> GenerateDeck(
		const Card firstCard,
		const std::size_t deckSize);

	static constexpr bool CmpRank(const Card& lhs, const Card& rhs)
	{
		return ( lhs.rawBytes & RankMask ) < ( rhs.rawBytes & RankMask );
	}

	static constexpr std::int16_t RankDistance(const Card first, const Card last)
	{
		return ((last.rawBytes & RankMask) >> 2) - ((first.rawBytes & RankMask) >> 2);
	}
};
