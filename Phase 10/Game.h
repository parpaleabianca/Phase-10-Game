#pragma once

#include <queue>
#include <stack>

#include "Deck.h"
#include "Player.h"
#include "Board.h"

class Game
{
public:
	Game(uint16_t noPlayers);
	Game();
	~Game() = default;
	std::vector<Player> GetPlayers();
	void SetPLayers(std::vector<Player> players);
	std::stack<Card> GetDiscardedCards();
	void SetDiscardedCards(std::stack<Card> discardedCards);

public:
	void ShowPlayers(std::vector<Player> players) const;
	void ReadPlayers();
	void Share10Cards();
	void StartGame();
	void TestGame();
	Card PickCardFromDiscardedStack();

private:
	void RemakeDeck();
	void DecartCard(Player& player);
	void PickCard(Player& player);
	void AnnexCard(std::vector<Player>& m_players, int idCurrentPlayer, int idPlayerToAnnex, int cardToAnnex, bool& annexed);
	void RemakeHand();
	void ShowCurrentPhase(int currentPhase) const;
	void GameType(uint8_t& gameType);

private:
	std::vector<std::string> m_playersNames;
	uint16_t m_noPlayers;
	std::vector <Player> m_players;
	std::stack<Card> m_discardedCards;
	Deck m_deck;
	std::vector<uint8_t> m_playersToSkip;
};

