#include <sstream>
#include "Phase.h"
#include"Card.h"


bool Phase::IsSet(std::vector<Card> cards)
{
	Status value = Status::WILD;

	for (Card card : cards)
	{
		if (card.GetStatus() == Status::SKIP)
		{
			return false;
		}
		else
			if (card.GetStatus() <= Status::TWELVE)
			{
				value = card.GetStatus();
				break;
			}
	}

	if (value != Status::WILD)
	{
		for (Card card : cards)
		{
			if (value != card.GetStatus() && card.GetStatus() != Status::WILD)
			{

				return false;
			}
		}
	}

	return true;
}

bool Phase::IsRun(std::vector<Card> cards)
{
	int no = 0;
	int countWild = 0;

	for (auto it = 0; it <= cards.size() - 1; it++)
	{
		if (cards[it].GetStatus() == Status::SKIP)
		{
			return false;
		}
		else
		{
			if (cards[it].GetStatus() == Status::WILD)
			{
				countWild++;
			}
			else
			{
				if (no == 0)
				{
					if (static_cast<int>(cards[it].GetStatus()) < it + 1 || cards.size() - it > 13 - static_cast<int>(cards[it].GetStatus()))  //wild-uri si carte
					{
						return false;
					}
					else
					{
						no = static_cast<int>(cards[it].GetStatus());
						countWild = 0;
					}
				}
				else
				{
					if (countWild != 0)
					{
						if (static_cast<int>(cards[it].GetStatus()) - no != countWild + 1)
							return false;
					}
					else
					{
						if (static_cast<int>(cards[it].GetStatus()) - no != 1)
							return false;
					}
					countWild = 0;
				}
				no = static_cast<int>(cards[it].GetStatus());
			}
		}
	}
	return true;
}

bool Phase::IsColor(std::vector<Card> cards)
{
	Color value = Color::BLACK;

	for (Card card : cards)
	{
		if (card.GetStatus() == Status::SKIP)
		{
			return false;
		}
		else
			if (card.GetColor() <= Color::BLUE)
			{
				value = card.GetColor();
				break;
			}
	}

	if (value != Color::BLACK)
	{
		for (Card card : cards)
		{
			if (value != card.GetColor() && card.GetColor() != Color::BLACK)
			{
				return false;
			}
		}
	}

	return true;
}

void Phase::IsPhase(Player& player)
{
	int current = player.GetCurrentPhase();

	std::vector<Card> chosenCards1, chosenCards2;

	switch (current)
	{
	case 1:
	{
		std::vector<int> options1, options2;

		std::cout << "\nChoose cards for a set of three:\n";
		ChoseCards(3, player, options1, chosenCards1);

		std::cout << "\nChoose cards for a set of three:\n";
		ChoseCards(3, player, options2, chosenCards2);

		for (int index = 0; index < options2.size(); index++)
		{
			if (std::find(options1.begin(), options1.end(), options2[index]) != options1.end())
			{
				std::cout << "\nYou can't choose the same card twice.\n";
				return;
			}
		}

		for (int index = 0; index < options1.size() - 1; index++)
		{
			for (int index2 = index + 1; index2 < options1.size(); index2++)
			{
				if (options1[index] == options1[index2] || options2[index] == options2[index2])
				{
					std::cout << "\nYou can't insert the same card twice.\n";
					return;
				}
			}
		}

		uint8_t incorrect = 0;
		bool foundCard = false;
		if (!IsPhase1(chosenCards1, chosenCards2, incorrect))
		{
			if (incorrect == 1)
				std::cout << "\nThe first set is incorrect!\n";

			if (incorrect == 2)
				std::cout << "\nThe second set is incorrect!\n";

			return;
		}
		else
		{
			std::vector <Card> newHandCards;

			for (int index = 0; index < player.m_handCards.size(); index++)
			{
				if ((std::find(options1.begin(), options1.end(), index + 1) == options1.end()) && (std::find(options2.begin(), options2.end(), index + 1) == options2.end()))
				{
					newHandCards.push_back(player.m_handCards[index]);
				}
			}

			player.m_handCards = std::move(newHandCards);

			player.m_displayedCards.push_back(chosenCards1);
			player.m_displayedCards.push_back(chosenCards2);

			player.SetPhase(current);
		}
		break;
	}

	case 2:
	{
		std::vector<int> options1, options2;

		std::cout << "\nChoose cards for a set of three:\n";
		ChoseCards(3, player, options1, chosenCards1);

		std::cout << "\nChoose cards for a run of four:\n";
		ChoseCards(4, player, options2, chosenCards2);

		for (int index = 0; index < options2.size(); index++)
		{
			if (std::find(options1.begin(), options1.end(), options2[index]) != options1.end())
			{
				std::cout << "\nYou can't choose the same card twice.\n";
				return;
			}
		}

		for (int index = 0; index < options1.size() - 1; index++)
		{
			for (int index2 = index + 1; index2 < options1.size(); index2++)
			{
				if (options1[index] == options1[index2] || options2[index] == options2[index2])
				{
					std::cout << "\nYou can't insert the same card twice.\n";
					return;
				}
			}
		}

		uint8_t incorrect = 0;

		if (!IsPhase2(chosenCards1, chosenCards2, incorrect))
		{
			if (incorrect == 1)
				std::cout << "\nThe first set is incorrect!\n";
			if (incorrect == 2)
				std::cout << "\nThe second set is incorrect!\n";
			return;
		}
		else
		{
			std::vector <Card> newHandCards;

			for (int index = 0; index < player.m_handCards.size(); index++)
			{
				if ((std::find(options1.begin(), options1.end(), index + 1) == options1.end()) && (std::find(options2.begin(), options2.end(), index + 1) == options2.end()))
				{
					newHandCards.push_back(player.m_handCards[index]);
				}
			}

			player.m_handCards = std::move(newHandCards);

			player.m_displayedCards.push_back(chosenCards1);
			player.m_displayedCards.push_back(chosenCards2);

			player.SetPhase(current);
		}
		break;
	}

	case 3:
	{
		std::vector<int> options1, options2;

		std::cout << "\nChoose cards for a set of four:\n";
		ChoseCards(4, player, options1, chosenCards1);

		std::cout << "\nChoose cards for a run of four:\n";
		ChoseCards(4, player, options2, chosenCards2);

		for (int index = 0; index < options2.size(); index++)
		{
			if (std::find(options1.begin(), options1.end(), options2[index]) != options1.end())
			{
				std::cout << "\nYou can't choose the same card twice.\n";
				return;
			}
		}

		for (int index = 0; index < options1.size() - 1; index++)
		{
			for (int index2 = index + 1; index2 < options1.size(); index2++)
			{
				if (options1[index] == options1[index2] || options2[index] == options2[index2])
				{
					std::cout << "\nYou can't insert the same card twice.\n";
					return;
				}
			}
		}

		uint8_t incorrect = 0;

		if (!IsPhase3(chosenCards1, chosenCards2, incorrect))
		{
			if (incorrect == 1)
				std::cout << "\nThe first set is incorrect!\n";
			if (incorrect == 2)
				std::cout << "\nThe second set is incorrect!\n";
			return;
		}
		else
		{
			std::vector <Card> newHandCards;
			for (int index = 0; index < player.m_handCards.size(); index++)
			{
				if ((std::find(options1.begin(), options1.end(), index + 1) == options1.end()) && (std::find(options2.begin(), options2.end(), index + 1) == options2.end()))
				{
					newHandCards.push_back(player.m_handCards[index]);
				}
			}

			player.m_handCards = std::move(newHandCards);

			player.m_displayedCards.push_back(chosenCards1);
			player.m_displayedCards.push_back(chosenCards2);

			player.SetPhase(current);
		}
		break;
	}

	case 4:
	{
		std::vector<int> options;

		std::cout << "\nChoose cards for a run of seven:\n";
		ChoseCards(7, player, options, chosenCards1);

		for (int index = 0; index < options.size() - 1; index++)
		{
			for (int index2 = index + 1; index2 < options.size(); index2++)
			{
				if (options[index] == options[index2])
				{
					std::cout << "\nYou can't insert the same card twice.\n";
					return;
				}
			}
		}

		if (!IsPhase4(chosenCards1))
		{
			return;
		}
		else
		{
			std::vector <Card> newHandCards;
			for (int index = 0; index < player.m_handCards.size(); index++)
			{
				if (std::find(options.begin(), options.end(), index + 1) == options.end())
				{
					newHandCards.push_back(player.m_handCards[index]);
				}
			}

			player.m_handCards = std::move(newHandCards);

			player.m_displayedCards.push_back(chosenCards1);

			player.SetPhase(current);
		}
		break;
	}

	case 5:
	{
		std::vector<int> options;
		std::cout << "\nChoose cards for a run of eight:\n";
		ChoseCards(8, player, options, chosenCards1);

		for (int index = 0; index < options.size() - 1; index++)
		{
			for (int index2 = index + 1; index2 < options.size(); index2++)
			{
				if (options[index] == options[index2])
				{
					std::cout << "\nYou can't insert the same card twice.\n";
					return;
				}
			}
		}

		if (!IsPhase5(chosenCards1))
		{
			return;
		}
		else
		{
			std::vector <Card> newHandCards;
			for (int index = 0; index < player.m_handCards.size(); index++)
			{
				if (std::find(options.begin(), options.end(), index + 1) == options.end())
				{
					newHandCards.push_back(player.m_handCards[index]);
				}
			}

			player.m_handCards = std::move(newHandCards);

			player.m_displayedCards.push_back(chosenCards1);

			player.SetPhase(current);
		}
		break;
	}

	case 6:
	{
		std::vector<int> options;
		std::cout << "\nChoose cards for a run of nine:\n";
		ChoseCards(9, player, options, chosenCards1);

		for (int index = 0; index < options.size() - 1; index++)
		{
			for (int index2 = index + 1; index2 < options.size(); index2++)
			{
				if (options[index] == options[index2])
				{
					std::cout << "\nYou can't insert the same card twice.\n";
					return;
				}
			}
		}

		if (!IsPhase6(chosenCards1))
		{
			return;
		}
		else
		{
			std::vector <Card> newHandCards;
			for (int index = 0; index < player.m_handCards.size(); index++)
			{
				if (std::find(options.begin(), options.end(), index + 1) == options.end())
				{
					newHandCards.push_back(player.m_handCards[index]);
				}
			}

			player.m_handCards = std::move(newHandCards);

			player.m_displayedCards.push_back(chosenCards1);

			player.SetPhase(current);
		}
		break;
	}

	case 7:
	{
		std::vector<int> options1, options2;
		std::cout << "\nChoose cards for a set of four:\n";
		ChoseCards(4, player, options1, chosenCards1);

		std::cout << "\nChoose cards for a set of four:\n";
		ChoseCards(4, player, options2, chosenCards2);

		for (int index = 0; index < options2.size(); index++)
		{

			if (std::find(options1.begin(), options1.end(), options2[index]) != options1.end())
			{
				std::cout << "\nYou can't choose the same card twice.\n";
				return;
			}
		}

		for (int index = 0; index < options1.size() - 1; index++)
		{
			for (int index2 = index + 1; index2 < options1.size(); index2++)
			{
				if (options1[index] == options1[index2] || options2[index] == options2[index2])
				{
					std::cout << "\nYou can't insert the same card twice.\n";
					return;
				}
			}
		}

		uint8_t incorrect = 0;

		if (!IsPhase7(chosenCards1, chosenCards2, incorrect))
		{
			if (incorrect == 1)
				std::cout << "\nThe first set is incorrect!\n";
			if (incorrect == 2)
				std::cout << "\nThe second set is incorrect!\n";
			return;
		}
		else
		{
			std::vector <Card> newHandCards;
			for (int index = 0; index < player.m_handCards.size(); index++)
			{
				if ((std::find(options1.begin(), options1.end(), index + 1) == options1.end()) && (std::find(options2.begin(), options2.end(), index + 1) == options2.end()))
				{
					newHandCards.push_back(player.m_handCards[index]);
				}
			}

			player.m_handCards = std::move(newHandCards);

			player.m_displayedCards.push_back(chosenCards1);
			player.m_displayedCards.push_back(chosenCards2);

			player.SetPhase(current);
		}
		break;
	}

	case 8:
	{
		std::vector<int> options;

		std::cout << "\nChoose seven cards with the same color:\n";
		ChoseCards(7, player, options, chosenCards1);

		for (int index = 0; index < options.size() - 1; index++)
		{
			for (int index2 = index + 1; index2 < options.size(); index2++)
			{
				if (options[index] == options[index2])
				{
					std::cout << "\nYou can't insert the same card twice.\n";
					return;
				}
			}
		}

		if (!IsPhase8(chosenCards1))
		{
			return;
		}
		else
		{
			std::vector <Card> newHandCards;
			for (int index = 0; index < player.m_handCards.size(); index++)
			{
				if (std::find(options.begin(), options.end(), index + 1) == options.end())
				{
					newHandCards.push_back(player.m_handCards[index]);
				}
			}

			player.m_handCards = std::move(newHandCards);

			player.m_displayedCards.push_back(chosenCards1);

			player.SetPhase(current);
		}
		break;
	}

	case 9:
	{
		std::vector<int> options1, options2;
		std::cout << "\nChoose cards for a set of five:\n";
		ChoseCards(5, player, options1, chosenCards1);

		std::cout << "\nChoose cards for a set of two:\n";
		ChoseCards(2, player, options2, chosenCards2);

		for (int index = 0; index < options2.size(); index++)
		{
			if (std::find(options1.begin(), options1.end(), options2[index]) != options1.end())
			{
				std::cout << "\nYou can't choose the same card twice.\n";
				return;
			}
		}

		for (int index = 0; index < options1.size() - 1; index++)
		{
			for (int index2 = index + 1; index2 < options1.size(); index2++)
			{
				if (options1[index] == options1[index2] || options2[index] == options2[index2])
				{
					std::cout << "\nYou can't insert the same card twice.\n";
					return;
				}
			}
		}

		uint8_t incorrect = 0;

		if (!IsPhase9(chosenCards1, chosenCards2, incorrect))
		{
			if (incorrect == 1)
				std::cout << "\nThe first set is incorrect!\n";
			if (incorrect == 2)
				std::cout << "\nThe second set is incorrect!\n";
			return;
		}
		else
		{
			std::vector <Card> newHandCards;
			for (int index = 0; index < player.m_handCards.size(); index++)
			{
				if ((std::find(options1.begin(), options1.end(), index + 1) == options1.end()) && (std::find(options2.begin(), options2.end(), index + 1) == options2.end()))
				{
					newHandCards.push_back(player.m_handCards[index]);
				}
			}

			player.m_handCards = std::move(newHandCards);

			player.m_displayedCards.push_back(chosenCards1);
			player.m_displayedCards.push_back(chosenCards2);

			player.SetPhase(current);
		}
		break;
	}

	case 10:
	{
		std::vector<int> options1, options2;
		std::cout << "\nChoose cards for a set of five:\n";
		ChoseCards(5, player, options1, chosenCards1);

		std::cout << "\nChoose cards for a set of three:\n";
		ChoseCards(3, player, options2, chosenCards2);

		for (int index = 0; index < options2.size(); index++)
		{
			if (std::find(options1.begin(), options1.end(), options2[index]) != options1.end())
			{
				std::cout << "\nYou can't choose the same card twice.\n";
				return;
			}
		}

		for (int index = 0; index < options1.size() - 1; index++)
		{
			for (int index2 = index + 1; index2 < options1.size(); index2++)
			{
				if (options1[index] == options1[index2] || options2[index] == options2[index2])
				{
					std::cout << "\nYou can't insert the same card twice.\n";
					return;
				}
			}
		}

		uint8_t incorrect = 0;

		if (!IsPhase10(chosenCards1, chosenCards2, incorrect))
		{
			if (incorrect == 1)
				std::cout << "\nThe first set is incorrect!\n";
			if (incorrect == 2)
				std::cout << "\nThe second set is incorrect!\n";
			return;
		}
		else {
			std::vector <Card> newHandCards;
			for (int index = 0; index < player.m_handCards.size(); index++)
			{
				if ((std::find(options1.begin(), options1.end(), index + 1) == options1.end()) && (std::find(options2.begin(), options2.end(), index + 1) == options2.end()))
				{
					newHandCards.push_back(player.m_handCards[index]);
				}
			}

			player.m_handCards = std::move(newHandCards);

			player.m_displayedCards.push_back(chosenCards1);
			player.m_displayedCards.push_back(chosenCards2);

			player.SetPhase(current);
		}
		break;
	}
	default:
		break;
	}
}

void Phase::ChoseCards(int no, Player player, std::vector<int>& options, std::vector<Card>& chosenCards)
{
	for (int index = 0; index < no; index++)
	{
		int option;
		std::string auxOption;
		bool ok = true;

		do {
			try
			{
				std::cout << "Card number " << index + 1 << " (choose the index of the card): ";
				std::cin >> auxOption;

				if (auxOption.size() == 1 || auxOption == "10" || auxOption == "11")
				{

					std::stringstream intNumber(auxOption);
					int x = -1;
					intNumber >> x;

					if (x <= player.m_handCards.size() && x >= 1)
					{
						option = x;
						options.push_back(option);
						chosenCards.push_back(player.m_handCards[--option]);
						ok = true;
					}

					else {
						throw std::runtime_error("\nYou have to insert a valid card!\n\n");
					}
				}
				else {
					throw std::runtime_error("\nYou have to insert a valid card!\n\n");
				}
			}

			catch (std::runtime_error& e)
			{
				ok = false;
				std::cout << "\nYou have to insert a valid card!\n\n";
				std::cin.clear();
				std::string tmp;
				getline(std::cin, tmp);
			}

		} while (ok == false);


	}
}

bool Phase::IsPhase1(std::vector<Card> cards1, std::vector<Card> cards2, uint8_t& incorrect)
{
	if (cards1.size() != 3)
	{
		incorrect = 1;
		return false;
	}
	else
		if (cards2.size() != 3)
		{
			incorrect = 2;
			return false;
		}

	if (!IsSet(cards1))
	{
		incorrect = 1;
		return false;
	}

	if (!IsSet(cards2))
	{
		incorrect = 2;
		return false;
	}

	return true;
}

bool Phase::IsPhase2(std::vector<Card> cards1, std::vector<Card> cards2, uint8_t& incorrect)
{
	if (cards1.size() != 3)
	{
		incorrect = 1;
		return false;
	}
	else
		if (cards2.size() != 4)
		{
			incorrect = 2;
			return false;
		}

	if (!IsSet(cards1))
	{
		incorrect = 1;
		return false;
	}

	if (!IsRun(cards2))
	{
		incorrect = 2;
		return false;
	}

	return true;
}

bool Phase::IsPhase3(std::vector<Card> cards1, std::vector<Card> cards2, uint8_t& incorrect)
{
	if (cards1.size() != 4)
	{
		incorrect = 1;
		return false;
	}
	else
		if (cards2.size() != 4)
		{
			incorrect = 2;
			return false;
		}

	if (!IsSet(cards1))
	{
		incorrect = 1;
		return false;
	}

	if (!IsRun(cards2))
	{
		incorrect = 2;
		return false;
	}

	return true;
}

bool Phase::IsPhase4(std::vector<Card> cards)
{
	if (cards.size() != 7)
		return false;

	if (!IsRun(cards))
		return false;

	return true;
}

bool Phase::IsPhase5(std::vector<Card> cards)
{
	if (cards.size() != 8)
		return false;

	if (!IsRun(cards))
		return false;

	return true;
}

bool Phase::IsPhase6(std::vector<Card> cards)
{
	if (cards.size() != 9)
		return false;

	if (!IsRun(cards))
		return false;

	return true;
}

bool Phase::IsPhase7(std::vector<Card> cards1, std::vector<Card> cards2, uint8_t& incorrect)
{
	if (cards1.size() != 4)
	{
		incorrect = 1;
		return false;
	}
	else
		if (cards2.size() != 4)
		{
			incorrect = 2;
			return false;
		}

	if (!IsSet(cards1))
	{
		incorrect = 1;
		return false;
	}

	if (!IsSet(cards2))
	{
		incorrect = 2;
		return false;
	}

	return true;
}

bool Phase::IsPhase8(std::vector<Card> cards)
{
	if (cards.size() != 7)
		return false;

	if (!IsColor(cards))
		return false;

	return true;
}

bool Phase::IsPhase9(std::vector<Card> cards1, std::vector<Card> cards2, uint8_t& incorrect)
{
	if (cards1.size() != 5)
	{
		incorrect = 1;
		return false;
	}
	else
		if (cards2.size() != 2)
		{
			incorrect = 2;
			return false;
		}

	if (!IsSet(cards1))
	{
		incorrect = 1;
		return false;
	}

	if (!IsSet(cards2))
	{
		incorrect = 2;
		return false;
	}

	return true;
}

bool Phase::IsPhase10(std::vector<Card> cards1, std::vector<Card> cards2, uint8_t& incorrect)
{
	if (cards1.size() != 5)
	{
		incorrect = 1;
		return false;
	}
	else
		if (cards2.size() != 3)
		{
			incorrect = 2;
			return false;
		}

	if (!IsSet(cards1))
	{
		incorrect = 1;
		return false;
	}

	if (!IsSet(cards2))
	{
		incorrect = 2;
		return false;
	}

	return true;
}
