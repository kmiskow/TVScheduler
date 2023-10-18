// PlanerTV.cpp : Defines the functions for the static library.
//
#include "WeekPlan.h"
#include "BaseScheduled.h"
#include "BaseUnscheduled.h"
#include "ProgramManager.h"


using namespace std;
//template<typename T, typename ... Args>
//day Plan::PlanDay(programList my_list, T arg, Args... args)
//{
//	
//}
//template<typename T, typename ... Args>
//day Plan::PlanDay(programList my_list, T arg, Args... args)
//{
//
//
WeekPlan::WeekPlan() : rule_list{} //initializes rule list with zeros
{}

WeekPlan::WeekPlan(ProgramManager* my_program_base, const int* my_rule_list[7][NUM_RULES])
{
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			rule_list[i][j] = *my_rule_list[i][j];
		}
	}
	ConstructPlan(my_program_base);
}

bool WeekPlan::addProgram(Program* my_program)
{
	return false;
}
bool WeekPlan::addProgram(Program* my_program, const unsigned int my_star_time, const bool force)
{
	return false;
}

DayPlan* WeekPlan::getDayPlan(Program::day d)
{
	return &week_plan[d];
}

int WeekPlan::getRule(rule my_rule, Program::day my_day) const
{
	return rule_list[my_day][my_rule];
}
void WeekPlan::setRule(rule my_rule, Program::day my_day, int rule_val)
{
	rule_list[my_day][my_rule] = rule_val;
	return;
}
void WeekPlan::setRule(rule my_rule, int rule_val)
{
	for (int i = 0; i < 7; i++)
	{
		rule_list[i][my_rule] = rule_val;
	}
	return;
}

//size_t Plan::getPlanSize(const day my_day) const
//{
//	return program_list[my_day].size();
//}

bool WeekPlan::ConstructPlan(ProgramManager* my_program_base)
{
	
	bool warning = false;
	
	for (int d = 0; d < 7; d++)
	{	
		int current_time = 0;
		//inserting the priority prorgams
		for (int i = 0; i < rule_list[d][num_priority]; i++)
		{	
			ScheduledProgram* next_prog = dynamic_cast<ScheduledProgram*>(my_program_base->getPriority(SECONDS_IN_DAY-current_time, current_time, (Program::day)d));
			if (next_prog == nullptr) { warning = true; break; }
			bool added = week_plan[d].add(next_prog, next_prog->getStartTime());
			current_time =  next_prog->getStartTime() + next_prog->getTime() + 1;
			//adding ads after programs
			for (int y = rule_list[d][num_ads_after]; y > 0; y--)
			{
				Program* next_ad = my_program_base->getAdd(SECONDS_IN_DAY - current_time);
				if (next_ad == nullptr) { break; }
				
				week_plan[d].add(next_ad, current_time);
				current_time += next_ad->getTime() + 1;
				
			}
		}
		current_time = 0;
		int cover_to_time = 0;

		for (int i = 0; i < week_plan[d].getSize(); i++)
		{
			if (week_plan[d].getStartTime(i) > current_time)
			{
				int nearest_priotiry_time = week_plan[d].getAtIndex(i)->getTime();
				cover_to_time = week_plan[d].getStartTime(i) + 1;
				while (current_time < cover_to_time)
				{
					Program* next_prog = my_program_base->getOther(cover_to_time - current_time);
					if (next_prog != nullptr)
					{
						week_plan[d].add(next_prog, current_time);
						current_time += next_prog->getTime() + 1;
						for (int y = rule_list[d][num_ads_after]; y > 0; y--)
						{
							Program* next_ad = my_program_base->getAdd(cover_to_time - current_time);
							if (next_ad == nullptr) { break; }

							week_plan[d].add(next_ad, current_time);
							current_time += next_ad->getTime() + 1;
						}
					}
					else
					{
						Program* next_interlude = new Interlude("Interlude1", cover_to_time - current_time, "Interlude");

						week_plan[d].add(next_interlude, current_time);
						current_time += next_interlude->getTime() + 1;
						current_time += nearest_priotiry_time + 1;
					}

					
				}


			}
		}
		while (current_time <= SECONDS_IN_DAY)
		{
			Program* next_prog = my_program_base->getOther(SECONDS_IN_DAY + 1 - current_time);
			if (next_prog != nullptr)
			{
				week_plan[d].add(next_prog, current_time);
				current_time += next_prog->getTime() + 1;
				for (int y = rule_list[d][num_ads_after]; y > 0; y--)
				{
					Program* next_ad = my_program_base->getAdd(SECONDS_IN_DAY + 1 - current_time);
					if (next_ad == nullptr) { break; }

					week_plan[d].add(next_ad, current_time);
					current_time += next_ad->getTime() + 1;
				}
			}
			else
			{
				Program* next_interlude = new Interlude("Interlude1", SECONDS_IN_DAY + 1 - current_time, "Interlude");
				week_plan[d].add(next_interlude, current_time);
				current_time += next_interlude->getTime() + 1;
			}


		}
		
	}
	
	return warning;
}

void WeekPlan::print(Program::day d)
{
	const string day_strings[7] = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday" };
	cout << "Plan for " << day_strings[d] << endl;
	week_plan[d].print();
	if (!week_plan[d].isFull())
	{
		cout << "Warning! Plan incomplete" << endl;
	}
}
void WeekPlan::print()
{
	const string day_strings[7] = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday" };
	for (int i = 0; i < 7; i++)
	{
		cout << setfill('-') << setw(82) << '-' << setfill(' ') << endl;
		cout << "Plan for " << day_strings[i] << endl << endl;
		week_plan[i].print();
		if (!week_plan[i].isFull())
		{
			cout << "Warning! Plan incomplete" << endl;
		}
	}
}