#include <iostream>
#include <sstream>
#include <cstdint>

#include "Card.h"
#include "Deck.h"
#include "Player.h"
#include "Game.h"

void StartGame()
{
	Deck deck;

	bool anotherGame = true;

	while (anotherGame)
	{
		Game game;
		system("cls");
		game.StartGame();

		std::string auxOption;
		int newGame;
		bool ok = true;

		do {
			try
			{
				std::cout << "\nDo you want to start another game? (1 for yes and 2 for no) \n";
				std::cin >> auxOption;
				if (auxOption.size() == 1) {

					std::stringstream intNumber(auxOption);
					int x = -1;
					intNumber >> x;

					if (x == 2 || x == 1)
					{
						newGame = x;
						ok = true;
					}
					else
					{
						throw std::runtime_error("\nYou have to insert a valid option!\n");
					}
				}
				else
				{
					throw std::runtime_error("\nYou have to insert a valid option!\n");
				}
			}
			catch (std::runtime_error& e)
			{
				ok = false;
				std::cout << "\nYou have to insert a valid option!\n";
				std::cin.clear();
				std::string tmp;
				getline(std::cin, tmp);
			}
		} while (ok == false);

		switch (newGame)
		{
		case 1:
		{
			anotherGame = true;
			break;
		}
		case 2:
		{
			anotherGame = false;
			break;
		}
		default:
			break;
		}
	}
}

int main()
{
	StartGame();

	system("pause");
	return 0;
}