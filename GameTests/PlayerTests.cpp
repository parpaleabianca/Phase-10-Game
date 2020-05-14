#include "CppUnitTest.h"
#include "pch.h"
#include "../Phase 10/Player.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GameTests
{
	TEST_CLASS(PlayerTests)
	{
	public:

		TEST_METHOD(Constructor)
		{
			Player player("Ana",1);

			Assert::IsTrue("Ana" == player.GetName());
			Assert::IsTrue(1 == player.GetId());
			Assert::IsTrue(0 == player.GetScore());
		}

		TEST_METHOD(GetCurrentPhase)
		{
			Player player("a",1);
			player.m_phase[0] = player.m_phase[1] = player.m_phase[2] = 1;

			Assert::IsTrue(3 == player.GetCurrentPhase());
        }

		TEST_METHOD(DropCard)
		{
			Player player("a", 1);
			player.m_handCards.emplace_back(Color::BLUE, Status::NINE, Place::HAND);
			Card card = player.DropCard(0);

			Assert::IsTrue(Color::BLUE == card.GetColor());
			Assert::IsTrue(Status::NINE == card.GetStatus());
			Assert::IsTrue(Place::HAND == card.GetPlace());
		}

		TEST_METHOD(CountScore)
		{
			Player player("a", 1);
			player.m_handCards.emplace_back(Color::BLUE, Status::TWO, Place::HAND);
			player.m_handCards.emplace_back(Color::BLACK, Status::WILD, Place::HAND);
			player.m_handCards.emplace_back(Color::RED, Status::TWELVE, Place::HAND);
			
			player.CountScore();

			Assert::IsTrue(35 == player.GetScore());
		}

		TEST_METHOD(Print)
		{
			Player player("Ana", 1);

			std::stringstream stream;
			stream << player;
			Assert::AreEqual(std::string("Ana has 0 points.\nAna's cards:\n\n"), stream.str(), L"If you see this message, piece is not printed correctly");
		}

		TEST_METHOD(Assignment)
		{
			Player player("Ana", 1);
			Player player2 = player;
			
			Assert::IsTrue(player2.GetName() == player.GetName());
			Assert::IsTrue(player2.GetId() == player.GetId());
			Assert::IsTrue(player2.GetScore() == player.GetScore());
		}
	};
}