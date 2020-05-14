#include <cstdint>
#include <sstream>
#include <chrono>
#include <thread>

#include "Game.h"
#include "Phase.h"

Game::Game(uint16_t noPlayers) :
	m_noPlayers(noPlayers)
{
}

Game::Game() :
	m_noPlayers(0), m_playersNames({ " " }), m_playersToSkip({ 0,0,0,0,0,0 })
{

}

std::vector<Player> Game::GetPlayers()
{
	return m_players;
}

void Game::SetPLayers(std::vector<Player> players)
{
	m_players = players;
}

std::stack<Card> Game::GetDiscardedCards()
{
	return m_discardedCards;
}

void Game::SetDiscardedCards(std::stack<Card> discardedCards)
{
	m_discardedCards = discardedCards;
}

void Game::ShowPlayers(std::vector<Player> players) const
{
	for (auto player : players)
	{
		std::cout << player.GetId() << ") " << player.GetName() << " -score: " << player.GetScore() << "\n";
	}
	std::cout << "\n";
}

void Game::ReadPlayers()
{
	std::string auxNumber;
	bool ok = true;
	std::cin.exceptions(std::istream::failbit);

	do {
		try
		{
			std::cout << "Insert number of players: ";
			std::cin >> auxNumber;

			if (auxNumber.size() == 1) {
				std::stringstream intNumber(auxNumber);
				int x;
				intNumber >> x;

				if (x <= 6 && x >= 2)
				{
					m_noPlayers = x;
					ok = true;
				}

				else {
					throw std::runtime_error("\nYou have to insert a digit between 2 and 6!\n");
				}
			}
			else {
				throw std::runtime_error("\nYou have to insert a digit between 2 and 6!\n");
			}
		}

		catch (std::runtime_error& e)
		{
			ok = false;
			std::cout << "\nYou have to insert a digit between 2 and 6!\n";
			std::cin.clear();
			std::string tmp;
			getline(std::cin, tmp);
		}

	} while (ok == false);

	for (int index = 0; index < m_noPlayers; index++)
	{
		bool ok = false;
		while (!ok) {
			std::cout << "Name for player nr " << index + 1 << " : ";
			std::string name;
			std::cin >> name;
			if (std::find(m_playersNames.begin(), m_playersNames.end(), name) != m_playersNames.end()) {
				std::cout << "Name already exists!\n";
			}
			else {
				m_playersNames.push_back(name);
				Player player(name, index + 1);
				m_players.push_back(player);
				ok = true;
			}
		}
	}

	Share10Cards();

}

void Game::Share10Cards()
{
	m_deck.ShuffleDeck();
	for (auto& player : m_players)
	{
		for (int index = 0; index < 10; index++)
		{
			player.m_handCards.push_back(m_deck.PickCardFromDeck());
		}
	}
}

void Game::StartGame()
{
	uint8_t gameType;

	ReadPlayers();
	GameType(gameType);

	Player currentPlayer;
	Board board;
	Phase phase;

	bool winHand = false;
	bool winGame = false;
	int countHands = 0;

	while (winGame == false)
	{
		winHand = false;
		while (winHand == false)
		{
			for (int indexPlayer = 0; indexPlayer < m_noPlayers; indexPlayer++)
			{
				system("cls");
				board.ShowDisplayedCards(m_players);
				currentPlayer = m_players[indexPlayer];
				std::cout << "\n" << currentPlayer;


				if (m_playersToSkip[currentPlayer.GetId() - 1])
				{
					m_playersToSkip[currentPlayer.GetId() - 1]--;
					std::cout << "You are skipped!" << "\n";
					std::this_thread::sleep_for(std::chrono::milliseconds(3000));
					system("pause");
				}

				else
				{
					if (m_deck.IsEmpty())
					{
						RemakeDeck();
						m_deck.ShuffleDeck();
					}
					PickCard(currentPlayer);

					if (currentPlayer.m_displayedCards.empty())
					{
						for (int index = 0; index < currentPlayer.m_handCards.size(); index++)
						{
							std::cout << index + 1 << ". " << currentPlayer.m_handCards[index];
						}

						std::string auxOption;
						int option;
						bool ok = true;

						do {
							try
							{
								ShowCurrentPhase(currentPlayer.GetCurrentPhase());

								std::cout << "\nDo you want to display (choose 1 for yes and 2 for no)?\n";
								std::cin >> auxOption;
								if (auxOption.size() == 1) {

									std::stringstream intNumber(auxOption);
									int x = -1;
									intNumber >> x;

									if (x == 2 || x == 1)
									{
										option = x;
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

						switch (option)
						{
						case 1:
						{
							while (option != 2)
							{
								phase.IsPhase(currentPlayer);

								if (!currentPlayer.m_displayedCards.empty())
								{
									option = 0;
									break;
								}
								else
								{
									do
									{
										try
										{
											std::cout << "\nDo you still want to display (choose 1 for yes and 2 for no)?\n";
											std::cin >> auxOption;

											if (auxOption.size() == 1)
											{
												std::stringstream intNumber(auxOption);
												int x = -1;
												intNumber >> x;

												if (x == 2 || x == 1)
												{
													option = x;
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
								}
							}
							break;
						}

						case 2:
						{
							break;
						}

						default:
							break;
						}
					}

					std::cout << "\nRemaining cards are:\n";
					for (int index2 = 0; index2 < currentPlayer.m_handCards.size(); index2++)
					{
						std::cout << index2 + 1 << ". " << currentPlayer.m_handCards[index2];
					}

					std::cout << "\nMy displayed cards are:\n";
					for (int index = 0; index < currentPlayer.m_displayedCards.size(); index++)
					{
						for (int index2 = 0; index2 < currentPlayer.m_displayedCards[index].size(); index2++)
						{
							std::cout << currentPlayer.m_displayedCards[index][index2];
						}
						std::cout << std::endl;
					}

					if (!currentPlayer.m_displayedCards.empty())
					{
						m_players[indexPlayer] = currentPlayer;
						int option;
						std::string auxOption;
						bool ok = true;

						do
						{
							do
							{
								try
								{
									std::cout << "\nDo you want to annex a card (choose 1 for yes and 2 for no)? \n";
									std::cin >> auxOption;

									if (auxOption.size() == 1)
									{
										std::stringstream intNumber(auxOption);
										int x = -1;
										intNumber >> x;

										if (x == 2 || x == 1)
										{
											option = x;
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

							switch (option)
							{
							case 1:
							{
								int indexCard;
								Card cardToAnnex;

								std::string auxNumber;
								bool ok = true;
								std::cin.exceptions(std::istream::failbit);

								int option = -1;
								do
								{
									try
									{
										std::cout << "\nWhich card?\n";
										std::cin >> auxNumber;
										std::cout << "\n";

										if (auxNumber.size() == 1) {
											std::stringstream intNumber(auxNumber);
											int x;
											intNumber >> x;

											if (x <= m_players[indexPlayer].m_handCards.size() && x >= 1)
											{
												indexCard = x;
												option--;
												ok = true;
											}
											else
											{
												throw std::runtime_error("\nYou have to insert a valid option \n");
											}
										}
										else
										{
											throw std::runtime_error("\nYou have to insert a valid option \n");
										}
									}
									catch (std::runtime_error& e)
									{
										ok = false;
										std::cout << "\nYou have to insert a digit between 1 and " << m_players[indexPlayer].m_handCards.size() << std::endl;
										std::cin.clear();
										std::string tmp;
										getline(std::cin, tmp);
									}
								} while (ok == false);

								ShowPlayers(m_players);

								ok = true;
								std::cin.exceptions(std::istream::failbit);
								option = -1;

								do
								{
									try
									{
										std::cout << "\nPlayer (choose id):\n";
										std::cin >> auxNumber;

										if (auxNumber.size() == 1) {
											std::stringstream intNumber(auxNumber);
											int x;
											intNumber >> x;

											if (x <= m_noPlayers && x >= 1)
											{
												option = x;
												option--;
												bool annexed;
												Player auxPlayer = m_players[option];
												AnnexCard(m_players, currentPlayer.GetId() - 1, option, indexCard - 1, annexed);

												if (annexed)
												{
													if ((m_players[option].m_displayedCards[0].size() != auxPlayer.m_displayedCards[0].size()) || (m_players[option].m_displayedCards[1].size() != auxPlayer.m_displayedCards[1].size()))
													{
														std::cout << m_players[option].GetName() << "'s displayed cards: \n";
														for (int index2 = 0; index2 < m_players[option].m_displayedCards.size(); index2++)
														{
															for (int index3 = 0; index3 < m_players[option].m_displayedCards[index2].size(); index3++)
															{
																std::cout << m_players[option].m_displayedCards[index2][index3];
															}
															std::cout << std::endl;
														}
													}
													currentPlayer = m_players[indexPlayer];
													ok = true;
												}
											}
											else
											{
												throw std::runtime_error("\nYou have to insert a valid option \n");
											}
										}
										else
										{
											throw std::runtime_error("\nYou have to insert a valid option \n");
										}
									}
									catch (std::runtime_error& e)
									{
										ok = false;
										std::cout << "\nYou have to insert a digit between 1 and " << m_noPlayers << std::endl;
										std::cin.clear();
										std::string tmp;
										getline(std::cin, tmp);
									}
								} while (ok == false);
								break;
							}

							case 0:
							{
								break;
							}

							default:
								break;
							}
						} while (option != 2);

					}

					if (!currentPlayer.m_handCards.empty())
					{
						DecartCard(currentPlayer);
					}

					if (m_players[indexPlayer].m_handCards.empty())
					{
						std::cout << "\n" << m_players[indexPlayer].GetName() << " wins this hand!\n\n";
						winHand = true;
						std::this_thread::sleep_for(std::chrono::milliseconds(3000));
						system("pause");
						break;
					}
				}
			}
		}

		countHands++;

		for (auto& player : m_players)
		{
			player.CountScore();
		}

		system("cls");

		std::string auxOption;
		int stopGame;
		bool ok = true;

		do {
			try
			{
				std::cout << "Do you still want to play? (1 for yes and 2 for no) \n";
				std::cin >> auxOption;
				if (auxOption.size() == 1) {

					std::stringstream intNumber(auxOption);
					int x = -1;
					intNumber >> x;

					if (x == 2 || x == 1)
					{
						stopGame = x;
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

		switch (stopGame)
		{
		case 1:
		{

			RemakeHand();
			Share10Cards();
			switch (gameType)
			{
			case 1:
			{
				if (countHands >= 10)
				{
					std::vector<Player> winners;
					for (auto player : m_players)
					{
						if (player.GetCurrentPhase() == 10)
						{
							winners.push_back(player);
							winGame = true;
						}
					}

					if (winners.size() == 1)
					{
						std::cout << "\n\nThe winner is: " << winners[0].GetName() << "\n\n";
					}
					else if (winners.size() > 1)
					{
						uint16_t minimScore = INT16_MAX;
						int idMinim = -1;

						for (auto player : winners)
						{
							if (player.GetScore() < minimScore)
							{
								minimScore = player.GetScore();
								idMinim = player.GetId();
							}
						}
						std::cout << "\n\nThe winner is: " << m_players[idMinim].GetName() << "\n\n";
					}
				}
				break;
			}
			case 2:
			{
				if (countHands >= 5)
				{
					std::vector<Player> winners;
					for (auto player : m_players)
					{
						if (player.GetCurrentPhase() == 9)
						{
							winners.push_back(player);
							winGame = true;
						}
					}

					if (winners.size() == 1)
					{
						std::cout << "\n\nThe winner is: " << winners[0].GetName() << "\n\n";
					}
					else if (winners.size() > 1)
					{
						uint16_t minimScore = INT16_MAX;
						int idMinim = -1;

						for (auto player : winners)
						{
							if (player.GetScore() < minimScore)
							{
								minimScore = player.GetScore();
								idMinim = player.GetId();
							}
						}
						std::cout << "\n\nThe winner is: " << m_players[idMinim].GetName() << "\n\n";
					}
				}
				break;
			}
			case 3:
			{
				if (countHands >= 5)
				{
					std::vector<Player> winners;
					for (auto player : m_players)
					{
						if (player.GetCurrentPhase() == 10)
						{
							winners.push_back(player);
							winGame = true;
						}
					}

					if (winners.size() == 1)
					{
						std::cout << "\n\nThe winner is: " << winners[0].GetName() << "\n\n";
					}
					else if (winners.size() > 1)
					{
						uint16_t minimScore = INT16_MAX;
						int idMinim = -1;

						for (auto player : winners)
						{
							if (player.GetScore() < minimScore)
							{
								minimScore = player.GetScore();
								idMinim = player.GetId();
							}
						}
						std::cout << "\n\nThe winner is: " << m_players[idMinim].GetName() << "\n\n";
					}
				}
				break;
			}
			}
			break;
		}

		case 2:
		{
			winGame = true;

			for (auto player : m_players)
			{
				std::cout << "Player " << player.GetName() << " is at phase " << player.GetCurrentPhase() << " and has " << player.GetScore() << " points.\n";
			}

			break;
		}
		default:
			break;
		}

	}

}

void Game::TestGame()
{
	/*Phase phase;
	Board board;

	ReadPlayers();

	int index = 0;
	while (index < m_noPlayers)
	{
		Player player = m_players.front();
		m_players.pop();
		phase.isPhase(player);
		m_players.push(player);
		index++;
	}
	board.ShowDisplayedCards(m_players);*/

	//system("cls");



	//std::vector<Card> cards;
	//Card c1(Color::RED, Status::ONE, Place::HAND);
	//Card c2(Color::YELLOW, Status::ONE, Place::HAND);
	//Card c3(Color::RED, Status::ONE, Place::HAND);
	////Card c4(Color::BLUE, Status::ELEVEN, Place::HAND);
	//
	//cards.push_back(c1);
	//cards.push_back(c2);
	//cards.push_back(c3);
	////cards.push_back(c4);
	//
	//std::vector<Card> cards1;
	//Card c11(Color::RED, Status::ONE, Place::HAND);
	//Card c22(Color::YELLOW, Status::WILD, Place::HAND);
	//Card c33(Color::RED, Status::THREE, Place::HAND);
	//Card c44(Color::BLUE, Status::FOUR, Place::HAND);
	//
	//cards1.push_back(c11);
	//cards1.push_back(c22);
	//cards1.push_back(c33);
	//cards1.push_back(c44);
	//int inc = 0;

	/*players.front().m_phase[1] = true;
	players.front().m_phase[2] = true;
	players.front().m_phase[3] = true;
	players.front().m_phase[4] = true;
	players.front().m_phase[5] = true;
	players.front().m_phase[6] = true;
	players.front().m_phase[7] = true;
	players.front().m_phase[8] = true;
	players.front().m_phase[9] = true;


	if (phase.isPhase(players.front()))
	{
		std::cout << "Da <3";

		std::cout << "\n";
		std::cout << "Hand Cards \n";
		for (int index = 0; index < players.front().m_handCards.size(); index++)
		{

			std::cout << players.front().m_handCards[index] << "\n ";
		}
		std::cout << "Displayed Cards \n";
		for (int index = 0; index < 2; index++)
		{
			for (int index1 = 0; index1 < players.front().m_displayedCards[index].size(); index1++)
			{
				std::cout << players.front().m_displayedCards[index][index1] << "\n ";
			}
			std::cout << "*************************************\n";
		}
	}
	else
		std::cout << "BUZZ";*/


		/*Player player = players.front();
		CountScore(player);
		std::cout << player;*/

		/*std::vector<Card> cards;
		Card c1 (Color::RED, Status::ONE, Place::HAND);
		Card c2 (Color::YELLOW, Status::TEN, Place::HAND);
		Card c3 (Color::RED, Status::EIGHT, Place::HAND);
		Card c4(Color::BLUE, Status::ELEVEN, Place::HAND);
		Card c5(Color::BLUE, Status::TWELVE, Place::HAND);
		cards.push_back(c1);
		cards.push_back(c2);
		cards.push_back(c3);
		cards.push_back(c4);
		cards.push_back(c5);
		if (isColor(cards))
			std::cout << "Da. <3 ";
		else std::cout << "BUZZ";*/

		//test DropCard
		/*int index = 0;
		while (index<noPlayers)
		{
			Player player = players.front();
			players.pop();

			bool skipped = false;
			for (std::string name : playersToSkip)
			{
				if (name == player.GetName())
				{
					skipped = true;
					name = "";
				}
			}

			if (skipped)
			{
				std::cout << "You are skiped!" << "\n";
				players.push(player);
				index++;

			}

			else
			{
				PickCard(player);
				DecartCard(player);
				std::cout << "Cartile ramase in mana sunt: ";
				for (int index2 = 0; index2 < player.m_handCards.size(); index2++)
				{
					std::cout << player.m_handCards[index2];
					std::cout << "\n";
				}
				players.push(player);

				index++;

			}

		}*/

}

void Game::DecartCard(Player& player)
{
	std::string auxNumber;
	bool ok = true;
	std::cin.exceptions(std::istream::failbit);

	int option;
	do
	{
		try
		{
			std::cout << "Choose a card to discard from your hand (from 1 to " << player.m_handCards.size() << ") : ";

			std::cin >> auxNumber;
			if (auxNumber.size() <= 2) {
				std::stringstream intNumber(auxNumber);
				int x;
				intNumber >> x;
				if (x <= player.m_handCards.size() && x >= 1)
				{
					option = x;
					option--;
					ok = true;
				}

				else {
					throw std::runtime_error("\nYou have to insert a valid option \n");
				}
			}
			else {
				throw std::runtime_error("\nYou have to insert a valid option \n");
			}
		}

		catch (std::runtime_error& e)
		{
			ok = false;
			std::cout << "\nYou have to insert a digit between 1 and " << player.m_handCards.size() << std::endl;
			std::cin.clear();
			std::string tmp;
			getline(std::cin, tmp);
		}

	} while (ok == false);

	Card discarded = player.DropCard(option);
	m_discardedCards.push(discarded);

	m_players[player.GetId() - 1] = player;

	if (discarded.GetStatus() == Status::SKIP)
	{
		ShowPlayers(m_players);

		std::string auxNumber;
		bool ok = true;
		std::cin.exceptions(std::istream::failbit);
		int option;

		do
		{
			try
			{
				std::cout << "Which player do you want to skip? (choose id)" << "\n";

				std::cin >> auxNumber;
				if (auxNumber.size() == 1) {
					std::stringstream intNumber(auxNumber);
					int x;
					intNumber >> x;
					if (x <= m_noPlayers && x >= 1)
					{
						option = x;
						option--;
						m_playersToSkip[option]++;
						ok = true;
					}

					else {
						throw std::runtime_error("\nYou have to insert a valid option \n");
					}
				}
				else {
					throw std::runtime_error("\nYou have to insert a valid option \n");
				}
			}

			catch (std::runtime_error& e)
			{
				ok = false;
				std::cout << "\nYou have to insert a digit between 1 and " << m_noPlayers << std::endl;
				std::cin.clear();
				std::string tmp;
				getline(std::cin, tmp);
			}

		} while (ok == false);
	}

}

Card Game::PickCardFromDiscardedStack()
{
	Card card = m_discardedCards.top();
	m_discardedCards.pop();
	return card;
}

void Game::PickCard(Player& player)
{
	if (m_discardedCards.empty())
	{
		std::cout << "\nYou received a card from deck.\n";
		Card card = m_deck.PickCardFromDeck();
		player.m_handCards.push_back(card);
	}
	else
	{
		int option;
		do {
			std::string auxOption;
			bool ok = true;
			do {

				try
				{
					std::cout << "From where do you want to pick a card?\n";
					std::cout << "1.Deck\n";
					std::cout << "2.Discarded Cards: " << m_discardedCards.top() << "\n";

					std::cin >> auxOption;
					if (auxOption.size() == 1) {

						std::stringstream intNumber(auxOption);
						int x = -1;
						intNumber >> x;
						if (x == 2 || x == 1)
						{
							option = x;
							ok = true;
						}

						else {
							throw std::runtime_error("\nYou have to insert a valid option!\n");
						}
					}
					else {
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


			switch (option)
			{
			case 1:
			{
				Card card = m_deck.PickCardFromDeck();
				player.m_handCards.push_back(card);
				break;
			}
			case 2:
			{
				if (m_discardedCards.top().GetStatus() == Status::SKIP)
				{
					std::cout << "You can't pick that card.\nYou received a card from deck.\n";
					Card card = m_deck.PickCardFromDeck();
					player.m_handCards.push_back(card);
				}
				else {
					Card card = PickCardFromDiscardedStack();
					player.m_handCards.push_back(card);
				}
				break;
			}

			default:
			{
				std::cout << "Insert a valid option!";
				break;
			}
			}

		} while (option != 1 && option != 2);
	}

}

void Game::AnnexCard(std::vector<Player>& m_players, int idCurrentPlayer, int idPlayerToAnnex, int cardToAnnex, bool& annexed)
{
	if (m_players[idPlayerToAnnex].m_displayedCards.empty())
	{
		std::cout << "The chosen player doesn't have displayed cards.\n\n";
		annexed = false;
	}
	else
	{
		bool ok = false;
		std::vector<Card>vector;
		Phase phase;
		Card card = m_players[idCurrentPlayer].m_handCards[cardToAnnex];

		for (int index = 0; index < m_players[idPlayerToAnnex].m_displayedCards.size(); index++)
		{
			vector = m_players[idPlayerToAnnex].m_displayedCards[index];
			vector.push_back(card);

			if (m_players[idPlayerToAnnex].m_phase[6] == 1 && m_players[idPlayerToAnnex].m_phase[7] == 1 && m_players[idPlayerToAnnex].m_phase[8] == 0)
			{
				if (phase.IsColor(vector))
				{
					m_players[idPlayerToAnnex].m_displayedCards[index] = vector;
					ok = true;

					for (int index2 = cardToAnnex; index2 < m_players[idCurrentPlayer].m_handCards.size() - 1; index2++)
					{
						m_players[idCurrentPlayer].m_handCards[index2] = m_players[idCurrentPlayer].m_handCards[index2 + 1];
					}

					m_players[idCurrentPlayer].m_handCards.pop_back();
					break;
				}
			}
			else
			{
				if (phase.IsRun(vector) || phase.IsSet(vector))
				{
					m_players[idPlayerToAnnex].m_displayedCards[index] = vector;
					ok = true;

					for (int index2 = cardToAnnex; index2 < m_players[idCurrentPlayer].m_handCards.size() - 1; index2++)
					{
						m_players[idCurrentPlayer].m_handCards[index2] = m_players[idCurrentPlayer].m_handCards[index2 + 1];
					}

					m_players[idCurrentPlayer].m_handCards.pop_back();
					break;
				}

				else
				{
					vector.pop_back();
					size_t size = vector.size();
					size++;
					vector.resize(size);

					for (size_t index = vector.size() - 1; index > 0; index--)
					{
						vector[index] = vector[index - 1];
					}
					vector[0] = card;

					if (phase.IsRun(vector) || phase.IsSet(vector))
					{
						m_players[idPlayerToAnnex].m_displayedCards[index] = vector;
						ok = true;

						for (int index2 = cardToAnnex; index2 < m_players[idCurrentPlayer].m_handCards.size() - 1; index2++)
						{
							m_players[idCurrentPlayer].m_handCards[index2] = m_players[idCurrentPlayer].m_handCards[index2 + 1];
						}

						m_players[idCurrentPlayer].m_handCards.pop_back();
						break;
					}

				}
			}
		}

		if (ok)
			std::cout << "Annexed the card.\n\n";
		else
			std::cout << "Could not annex.\n\n";

		std::cout << "Remaining cards are: \n";
		for (int index = 0; index < m_players[idCurrentPlayer].m_handCards.size(); index++)
		{
			std::cout << index + 1 << ". " << m_players[idCurrentPlayer].m_handCards[index];
		}
		std::cout << "\n";
		annexed = true;
	}
}

void Game::RemakeDeck()
{
	Card lastCard = m_discardedCards.top();
	m_discardedCards.pop();

	while (!m_discardedCards.empty())
	{
		m_deck.AddCard(m_discardedCards.top());
		m_discardedCards.pop();
	}

	m_discardedCards.push(lastCard);
}

void Game::RemakeHand()
{
	for (auto& player : m_players)
	{
		player.RemakePlayer();
	}

	m_playersToSkip = { 0,0,0,0,0,0 };

	while (!m_discardedCards.empty())
	{
		m_discardedCards.pop();
	}

	this->m_deck = Deck();
}

void Game::ShowCurrentPhase(int currentPhase) const
{
	switch (currentPhase)
	{
	case 1:
	{
		std::cout << "\nPhase 1: 2 sets of 3 cards.\n";
		break;
	}

	case 2:
	{
		std::cout << "\nPhase 2: 1 set of 3 cards.\n";
		std::cout << "	1 run of 4 cards.\n";
		break;
	}

	case 3:
	{
		std::cout << "\nPhase 3: 1 set of 4 cards.\n";
		std::cout << "	1 run of 4 cards.\n";
		break;
	}

	case 4:
	{
		std::cout << "\nPhase 4: 1 run of 7 cards.\n";
		break;
	}

	case 5:
	{
		std::cout << "\nPhase 5: 1 run of 8 cards.\n";
		break;
	}

	case 6:
	{
		std::cout << "\nPhase 6: 1 run of 9 cards.\n";
		break;
	}

	case 7:
	{
		std::cout << "\nPhase 7: 2 sets of 4 cards.\n";
		break;
	}

	case 8:
	{
		std::cout << "\nPhase 8: 7 cards of the same color.\n";
		break;
	}

	case 9:
	{
		std::cout << "\nPhase 9: 1 set of 5 cards.\n";
		std::cout << "	1 set of 2 cards.\n";
		break;
	}

	case 10:
	{
		std::cout << "\nPhase 10: 1 set of 5 cards.\n";
		std::cout << "	1 set of 3 cards.\n";
		break;
	}
	default:
		break;
	}
}

void Game::GameType(uint8_t& gameType)
{
	gameType = -1;
	std::string aux;
	bool valid = true;
	std::cin.exceptions(std::istream::failbit);

	do {
		try
		{
			std::cout << "\n1. Play all phases.\n2. Play only odd phases.\n3. Play only even phases.\n";
			std::cout << "\nChoose an option (1, 2 or 3): ";
			std::cin >> aux;

			if (aux.size() == 1) {
				std::stringstream intNumber(aux);
				int x;
				intNumber >> x;

				if (x == 1 || x == 2 || x == 3)
				{
					gameType = x;
					valid = true;
				}

				else {
					throw std::runtime_error("\nYou have to insert a valid option!\n");
				}
			}
			else {
				throw std::runtime_error("\nYou have to insert a valid option!\n");
			}
		}

		catch (std::runtime_error& e)
		{
			valid = false;
			std::cout << "\nYou have to insert a valid option!\n";
			std::cin.clear();
			std::string tmp;
			getline(std::cin, tmp);
		}

	} while (valid == false);

	switch (gameType)
	{
	case 1:
	{
		for (auto& player : m_players)
		{
			player.m_phase[0] = 1;
		}
		break;
	}
	case 2:
	{
		for (auto& player : m_players)
		{
			player.m_phase[0] = 1;
			player.m_phase[2] = 1;
			player.m_phase[4] = 1;
			player.m_phase[6] = 1;
			player.m_phase[8] = 1;
		}
		break;
	}
	case 3:
	{
		for (auto& player : m_players)
		{
			player.m_phase[1] = 1;
			player.m_phase[3] = 1;
			player.m_phase[5] = 1;
			player.m_phase[7] = 1;
			player.m_phase[9] = 1;
		}
		break;
	}
	}
}

