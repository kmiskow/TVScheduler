#pragma once
#include "BaseScheduled.h"
#include "BaseUnscheduled.h"
#include <vector>
class DayPlan
{
private:
	vector<Program*> program_list;
	vector<int> starting_time_list;
public:
	DayPlan() {};
	bool add(Program* my_prog);
	bool add(Program* my_prog, int my_time);
	bool replace(int my_index);
	//bool removeFirstOccurence(Program* my_prog);
	bool removeByTime(int my_time);
	bool removeByIndex(int my_index);

	int getStartTime(int my_index);

	void clear();

	Program* getAtTime(int my_time);
	Program* getAtIndex(int my_index);
	Program* getNext(int my_time);

	int getNextIndex(int my_time);

	int getEndingTime(int my_index);

	bool isFull();

	void print();

	size_t getSize();

};

string convertToHHMMSS(int my_time_secs);