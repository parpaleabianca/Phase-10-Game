#include "Board.h"


Board::Board()
{

}


Board::~Board()
{

}

void Board::ShowDisplayedCards(std::vector<Player> players) const
{
	for (auto player : players)
	{

		std::cout << player.GetName() << "'s current phase is " << player.GetCurrentPhase() << "\n";
		std::cout << player.GetName() << "'s displayed cards are:\n";

		for (int index = 0; index < player.m_displayedCards.size(); index++)
		{
			for (int index2 = 0; index2 < player.m_displayedCards[index].size(); index2++)
			{
				std::cout << player.m_displayedCards[index][index2];
			}
			std::cout << std::endl;
		}
	}
}
