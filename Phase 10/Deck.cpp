#include "Deck.h"

#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <time.h>

Deck::Deck()
{
	m_deck.clear();

	for (int status = static_cast<int>(Status::ONE); status <= static_cast<int>(Status::TWELVE); status++)
	{
		for (int color = static_cast<int>(Color::RED); color <= static_cast<int>(Color::BLUE); color++)
		{
			Card card(static_cast<Color>(color), static_cast<Status>(status));
			m_deck.push_back(card);
			m_deck.push_back(card);
		}
	}

	Card skip(Color::BLACK, Status::SKIP);
	for (int index = 0; index <= 3; index++)
	{
		m_deck.push_back(skip);
	}

	Card wild(Color::BLACK, Status::WILD);
	for (int index = 0; index <= 7; index++)
	{
		m_deck.push_back(wild);
	}

	this->ShuffleDeck();

}


void Deck::ShuffleDeck()
{
	//Same shuffle
	auto rng = std::default_random_engine{};
	std::shuffle(std::begin(m_deck), std::end(m_deck), rng);

	//Different shuffle 
	/*srand(time(0));
	std::random_shuffle(std::begin(m_deck), std::end(m_deck));*/
}

Card Deck::PickCardFromDeck()
{
	Card card = m_deck.back();
	m_deck.pop_back();

	return card;
}

void Deck::AddCard(Card card)
{
	m_deck.push_back(card);
}

bool Deck::IsEmpty() const
{
	return m_deck.empty();
}


