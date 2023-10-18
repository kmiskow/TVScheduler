#include <iostream>
#include <typeinfo>
#include "BaseScheduled.h"
#include "BaseUnscheduled.h"

bool operator>(const Program& left, const Program& right)
{
	return left.getTime() > right.getTime();
}

bool operator<(const ScheduledProgram& left, const ScheduledProgram& right)
{
	return left.getStartTime() < right.getStartTime();
}

ostream& operator<<(ostream& os, const Program& prog)
{
	os << "Program" << "," << prog.getName() << "," << prog.getTime() << "," << prog.getType() \
		<< "," << prog.canPartition();
	return os;
}

