#include "Program.h"
bool Program::getUsed()
{
	return used;
}
void Program::setUsed()
{
	used = true;
}
const string Program::getName() const
{
	return name;
}

const int Program::getTime() const
{
	return time;
}

const int Program::getMinAge() const
{
	return min_age;
}

const bool Program::canPartition() const
{
	return can_partition;
}
const string Program::getType() const
{
	return type;
}
bool Program::isScheduled() const
{
	return scheduled;
}