#include "DayPlan.h"
#include <iostream>
#include <iomanip>
#include <typeinfo>
#include <string>
#include <cstdlib>

bool DayPlan::add(Program* my_prog)
{
	if (program_list.empty())
	{
		program_list.push_back(my_prog);
		starting_time_list.push_back(0);
		return true;
	}
	if (getEndingTime(program_list.size()-1) + my_prog->getTime() > SECONDS_IN_DAY)
	{
		return false;
	}
	starting_time_list.push_back(starting_time_list.back() + program_list.back()->getTime() + 1);
	program_list.push_back(my_prog);
	
	return true;
}
bool DayPlan::add(Program* my_prog, int my_time)
{	
	if (starting_time_list.size() == 0 or (starting_time_list.size() == 1 and starting_time_list[0] < my_time) or starting_time_list.back() < my_time)
	{
		starting_time_list.push_back(my_time);
		program_list.push_back(my_prog);
		return true;
	}
	if (starting_time_list[0] > my_time)
	{
		starting_time_list.insert(starting_time_list.begin(), my_time);
		program_list.insert(program_list.begin(), my_prog);
		return true;
	}
	for (int i = 1; i < starting_time_list.size(); i++)
	{
		if (starting_time_list.at(i-1) < my_time and starting_time_list.at(i) > my_time)
		{
			starting_time_list.insert(starting_time_list.begin() + i, my_time);
			program_list.insert(program_list.begin() + i, my_prog);
			return true;
		}
	}
	return false;
}
bool DayPlan::replace(int my_index)
{
	// TODO implement DayPlan::replace
	return false;
}
//bool DayPlan::removeFirstOccurence(Program* my_prog)
//{
//	// TODO implement DayPlan::removeFirstOccurence
//	return false;
//}
bool DayPlan::removeByTime(int my_time)
{
	for (int i = 0; i < program_list.size(); i++)
	{
		if (starting_time_list.at(i) <= my_time and starting_time_list.at(i) + program_list[i]->getTime() >= my_time)
		{
			program_list.erase(program_list.begin() + i);
			starting_time_list.erase(starting_time_list.begin() + i);
			return true;
		}
	}
	return false;
}
bool DayPlan::removeByIndex(int my_index)
{
	if (my_index >= starting_time_list.size()) { return false; }
	starting_time_list.erase(starting_time_list.begin() + my_index);
	program_list.erase(program_list.begin() + my_index);
	return true;
}

void DayPlan::clear()
{
	starting_time_list.clear();
	program_list.clear();
}

Program* DayPlan::getAtTime(int my_time)
{
	for (int i = 0; i < program_list.size(); i++)
	{
		if (starting_time_list.at(i) <= my_time and getEndingTime(i) >= my_time)
		{
			return program_list[i];
		}
	}
	return nullptr;
}
Program* DayPlan::getAtIndex(int my_index)
{
	return program_list[my_index];
}
Program* DayPlan::getNext(int my_time)
{
	for (int i = 0; i < program_list.size(); i++)
	{
		if (starting_time_list.at(i) >= my_time)
		{
			return program_list[i];
		}
	}
	return nullptr;
}
int DayPlan::getNextIndex(int my_time)
{
	for (int i = 0; i < program_list.size(); i++)
	{
		if (starting_time_list.at(i) >= my_time)
		{
			return i;
		}
	}
	return -1;
}

int DayPlan::getEndingTime(int my_index)
{
	return starting_time_list[my_index] + program_list[my_index]->getTime();
}

bool DayPlan::isFull()
{
	if (program_list.size() == 0 or (program_list.size() == 1
		and program_list[0]->getTime() < SECONDS_IN_DAY))
	{
		return false;
	}
	for (int i = 0; i < program_list.size()-1; i++)
	{
		if(getEndingTime(i) != starting_time_list.at(i+1)-1)
		{
			return false;
		}
	}
	if (starting_time_list[0] != 0 and getEndingTime(starting_time_list.size() - 1) >= SECONDS_IN_DAY)
	{
		return false;
	}
	return true;
}

void DayPlan::print()
{
	cout << setw(2) << "ID" << '|' << setw(15) << "Type" << '|' << setw(20) << "Name" << '|' << setw(10)
		<< "Length" << '|' << setw(20) << "Addl. Info" << '|' << setw(10) << "Start Time" << endl;
	cout << endl;

	for (int i = 0; i < program_list.size(); i++)
	{
		string name = typeid(*program_list[i]).name();
		cout << setw(2) << i << '|' << setw(15) << name.substr(6, 15) << '|' << setw(20) << program_list[i]->getName() << '|' << setw(10)
			<< convertToHHMMSS(program_list[i]->getTime()) << '|' << setw(20) << program_list[i]->getType() << '|' << setw(10) << convertToHHMMSS(starting_time_list[i]) << endl;
	}
}
string convertToHHMMSS(int my_time_secs)
{
	int hours = my_time_secs / 3600;
	int minutes = (my_time_secs % 3600) / 60;
	int seconds = (my_time_secs % 3600) % 60;
	return to_string(hours) + ":" + to_string(minutes) + ":" + to_string(seconds);

}

int DayPlan::getStartTime(int my_index)
{
	return starting_time_list[my_index];
}

size_t DayPlan::getSize()
{
	return program_list.size();
}