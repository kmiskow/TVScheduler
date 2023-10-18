#include "pch.h"
#include "CppUnitTest.h"
#include "../PlanerTV/DayPlan.h"
#include "../PlanerTV/WeekPlan.h"
#include "../PlanerTV/ProgramManager.h"
#include <iostream>
#include <variant>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PlanerTest
{
	TEST_CLASS(DayPlanTest)
	{
	public:

		TEST_METHOD(add_Test_simple)
		{
			DayPlan day_plan1;
			Film* film1 = new Film("film1", 7200, "Horror");
			Reklama* reklama1 = new Reklama("reklama1", 30, "AGD");
			Game* game1 = new Game("game1", 90, "Football", Program::monday, 18000, "Legia", "Lech");
			day_plan1.add(film1);
			day_plan1.add(reklama1);
			day_plan1.add(game1);
			Assert::AreEqual(day_plan1.getStartTime(0), 0);
			Assert::AreEqual(day_plan1.getStartTime(1), 7201);
			Assert::AreEqual(day_plan1.getStartTime(2), 7232);
		}

		TEST_METHOD(add_Test_at_time)
		{
			DayPlan day_plan1;
			Film* film1 = new Film("film1", 7200, "Horror");
			Reklama* reklama1 = new Reklama("reklama1", 30, "AGD");
			Game* game1 = new Game("game1", 90, "Football", Program::monday, 18000, "Legia", "Lech");
			bool add1 = day_plan1.add(film1, 7200);
			bool add2 = day_plan1.add(reklama1, 7300);
			bool add3 = day_plan1.add(film1, 7100);
			day_plan1.add(reklama1, 7250);


			Assert::IsTrue(add1);
			Assert::IsTrue(add2);
			Assert::AreEqual(day_plan1.getStartTime(0), 7100);
			Assert::AreEqual(day_plan1.getStartTime(1), 7200);
			Assert::AreEqual(day_plan1.getStartTime(2), 7250);
			Assert::AreEqual(day_plan1.getStartTime(3), 7300);
		}

		TEST_METHOD(removeByTime)
		{
			DayPlan day_plan1;
			Film* film1 = new Film("film1", 7200, "Horror");
			Reklama* reklama1 = new Reklama("reklama1", 30, "AGD");
			Game* game1 = new Game("game1", 90, "Football", Program::monday, 18000, "Legia", "Lech");
			day_plan1.add(film1);
			day_plan1.add(reklama1);
			day_plan1.add(game1);
			
			day_plan1.removeByTime(7200);
			Assert::IsTrue(day_plan1.getStartTime(0) == 7201);
			Assert::IsTrue(day_plan1.getAtIndex(0) == reklama1);
			Assert::IsTrue(day_plan1.getAtIndex(1) == game1);
			Assert::IsTrue(day_plan1.getStartTime(1) == 7232);
			
		}

		/*TEST_METHOD(removeByIndex)
		{

		}*/

		TEST_METHOD(getAtTime)
		{
			DayPlan day_plan1;
			Film* film1 = new Film("film1", 7200, "Horror");
			Reklama* reklama1 = new Reklama("reklama1", 30, "AGD");
			Game* game1 = new Game("game1", 90, "Football", Program::monday, 18000, "Legia", "Lech");
			day_plan1.add(film1);
			day_plan1.add(reklama1);
			day_plan1.add(game1);

			Assert::IsTrue(day_plan1.getAtTime(0) == film1);
			Assert::IsTrue(day_plan1.getAtTime(2000) == film1);
			Assert::IsTrue(day_plan1.getAtTime(7200) == film1);
			Assert::IsTrue(day_plan1.getAtTime(7201) == reklama1);
			Assert::IsTrue(day_plan1.getAtTime(7202) == reklama1);
			Assert::IsTrue(day_plan1.getAtTime(7231) == reklama1);
			Assert::IsTrue(day_plan1.getAtTime(7232) == game1);
			Assert::IsTrue(day_plan1.getAtTime(7321) == game1);

		}

		TEST_METHOD(getNext)
		{
			DayPlan day_plan1;
			Film* film1 = new Film("film1", 7200, "Horror");
			Reklama* reklama1 = new Reklama("reklama1", 30, "AGD");
			Game* game1 = new Game("game1", 90, "Football", Program::monday, 18000, "Legia", "Lech");
			day_plan1.add(film1);
			day_plan1.add(reklama1);
			day_plan1.add(game1);

			Assert::IsTrue(day_plan1.getNext(7000) == reklama1);
			Assert::IsTrue(day_plan1.getNext(0) == film1);
			Assert::IsTrue(day_plan1.getNext(7900) == nullptr);

		}

		TEST_METHOD(getEndingTime)
		{
			DayPlan day_plan1;
			Film* film1 = new Film("film1", 7200, "Horror");
			Reklama* reklama1 = new Reklama("reklama1", 30, "AGD");
			Game* game1 = new Game("game1", 90, "Football", Program::monday, 18000, "Legia", "Lech");
			day_plan1.add(film1);
			day_plan1.add(reklama1);
			day_plan1.add(game1);

			Assert::IsTrue(day_plan1.getEndingTime(0) == 7200);
			Assert::IsTrue(day_plan1.getEndingTime(1) == 7201+30);
			Assert::IsTrue(day_plan1.getEndingTime(2) == 7201+30 + 1 + 90);

		}
		TEST_METHOD(isFull)
		{
			DayPlan day_plan1;
			Reklama* reklama1 = new Reklama("reklama1", 30, "AGD");
			for (int i = 0; i < 2880; i++)
			{
				day_plan1.add(reklama1);
			}
			Assert::IsTrue(day_plan1.isFull());
			DayPlan day_plan2;
			day_plan2.add(reklama1);
			day_plan2.add(reklama1, 5000);
			Assert::IsFalse(day_plan2.isFull());
		}

	};

	TEST_CLASS(Program_Manager_Test)
	{
		TEST_METHOD(ProgramManagerConstruct) {
			string proper_name = "name";
			ProgramManager manager("../PlanerTV/Example.csv");
			if (!manager.Priority_empty()) {
				Program* x = manager.getPriority(10000, 1000, Program::monday);
				Assert::AreEqual(proper_name, x->getName());
			}
		}
	};

	TEST_CLASS(WeekPlanTest)
	{
		TEST_METHOD(Constructor)
		{
			WeekPlan plan1;
		}
		TEST_METHOD(Construct_Plan)
		{
			ProgramManager manager("Example.csv");
			WeekPlan plan1;
			plan1.setRule(WeekPlan::rule::num_priority, 5);
			plan1.ConstructPlan(&manager);
			Assert::IsTrue(true);


		}

	};
}
