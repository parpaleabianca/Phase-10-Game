#pragma once

#include <vector>

#include "Player.h"

class Card;

class Phase
{
public:
	bool IsSet(std::vector<Card> cards);
	bool IsRun(std::vector<Card> cards);
	bool IsColor(std::vector<Card> cards);
	void IsPhase(Player& player);

private:
	void ChoseCards(int no, Player player, std::vector<int>& options, std::vector<Card>& chosenCards);

	bool IsPhase1(std::vector<Card> cards1, std::vector<Card> cards2, uint8_t& incorrect);
	bool IsPhase2(std::vector<Card> cards1, std::vector<Card> cards2, uint8_t& incorrect);
	bool IsPhase3(std::vector<Card> cards1, std::vector<Card> cards2, uint8_t& incorrect);
	bool IsPhase4(std::vector<Card> cards);
	bool IsPhase5(std::vector<Card> cards);
	bool IsPhase6(std::vector<Card> cards);
	bool IsPhase7(std::vector<Card> cards1, std::vector<Card> cards2, uint8_t& incorrect);
	bool IsPhase8(std::vector<Card> cards);
	bool IsPhase9(std::vector<Card> cards1, std::vector<Card> cards2, uint8_t& incorrect);
	bool IsPhase10(std::vector<Card> cards1, std::vector<Card> cards2, uint8_t& incorrect);
};

