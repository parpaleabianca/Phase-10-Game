#pragma once
#include <queue>
#include "Player.h"

class Board
{
public:
	Board();
	~Board();

	void ShowDisplayedCards(std::vector<Player> players) const;
};

