#pragma once
#include "DayPlan.h"
#include "ProgramManager.h"


#define NUM_RULES 4

using namespace std;
class WeekPlan
{
private:
	//plan
	DayPlan week_plan[7];
	//rules
protected:
	int rule_list[7][NUM_RULES];
	
public:
	enum rule { num_films = 0, num_ads_after = 1, movies_full_h = 2, num_priority = 3};

	WeekPlan();
	WeekPlan(ProgramManager* my_program_base, const int* my_rule_list[7][NUM_RULES]);
// TODO: wczytywanie zestawu zasad z pliku  

	bool addProgram(Program* my_program);
	bool addProgram(Program* my_program, const unsigned int my_star_time, const bool force=false);

	DayPlan* getDayPlan(Program::day d);

	bool ConstructPlan(ProgramManager* my_program_base);

	int getRule(rule my_rule, Program::day my_day) const;
	void setRule(rule my_rule, Program::day my_day, int rule_val);
	void setRule(rule my_rule, int rule_val);

	void print(Program::day d);
	void print();


	/*template<typename T, typename ... Args>
	week PlanWeek(programList my_list, T arg, Args... args);

	template<typename T, typename ... Args>
	day PlanDay(programList my_list, T arg, Args... args);*/

};