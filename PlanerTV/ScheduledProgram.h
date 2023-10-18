#pragma once
#include "Program.h"
class ScheduledProgram : public virtual Program
{
private:
	int start_time;
	day scheduled_day;

public:
	static ScheduledProgram NotFound;
	ScheduledProgram(string my_name, int my_time, string my_type, day my_day, int my_start_time,
		bool my_can_partition = false, int my_min_age = 0) : Program(my_name, my_time, my_type, my_can_partition, my_min_age),
		start_time(my_start_time), scheduled_day(my_day) { scheduled = true; }
	const int getStartTime() const;
	const day getDay() const;
	virtual ~ScheduledProgram() = default;
};
bool operator<(const ScheduledProgram& left, const ScheduledProgram& right);
