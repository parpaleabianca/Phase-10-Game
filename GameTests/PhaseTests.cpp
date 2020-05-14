#include "CppUnitTest.h"
#include "pch.h"
#include "../Phase 10/Card.h"
#include "../Phase 10/Phase.h"

#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GameTests
{
	TEST_CLASS(PhaseTests)
	{
	public:

		TEST_METHOD(IsSet)
		{
			Phase phase;

			std::vector<Card> cards;
			cards.emplace_back(Color::BLUE, Status::NINE, Place::HAND);
			cards.emplace_back(Color::RED, Status::NINE, Place::HAND);
			cards.emplace_back(Color::BLACK, Status::WILD, Place::HAND);
			
			Assert::IsTrue(phase.IsSet(cards));

			std::vector<Card> cards2;
			cards2.emplace_back(Color::BLUE, Status::NINE, Place::HAND);
			cards2.emplace_back(Color::RED, Status::ONE, Place::HAND);
			cards2.emplace_back(Color::BLACK, Status::WILD, Place::HAND);

			Assert::IsFalse(phase.IsSet(cards2));
		}

		TEST_METHOD(IsRun)
		{
			Phase phase;

			std::vector<Card> cards;
			cards.emplace_back(Color::BLACK, Status::WILD, Place::HAND);
			cards.emplace_back(Color::RED, Status::THREE, Place::HAND);
			cards.emplace_back(Color::BLACK, Status::FOUR, Place::HAND);

			Assert::IsTrue(phase.IsRun(cards));

			std::vector<Card> cards2;
			cards2.emplace_back(Color::BLACK, Status::WILD, Place::HAND);
			cards2.emplace_back(Color::RED, Status::ONE, Place::HAND);
			cards2.emplace_back(Color::BLACK, Status::TWO, Place::HAND);

			Assert::IsFalse(phase.IsRun(cards2));
		}

		TEST_METHOD(IsColor)
		{
			Phase phase;

			std::vector<Card> cards;
			cards.emplace_back(Color::BLACK, Status::WILD, Place::HAND);
			cards.emplace_back(Color::RED, Status::THREE, Place::HAND);
			cards.emplace_back(Color::RED, Status::FOUR, Place::HAND);

			Assert::IsTrue(phase.IsColor(cards));

			std::vector<Card> cards2;
			cards2.emplace_back(Color::BLACK, Status::WILD, Place::HAND);
			cards2.emplace_back(Color::BLUE, Status::THREE, Place::HAND);
			cards2.emplace_back(Color::RED, Status::FOUR, Place::HAND);

			Assert::IsFalse(phase.IsColor(cards2));
		}

	};
}