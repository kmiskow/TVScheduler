#pragma once
#include "ScheduledProgram.h"
#include <vector>


class Game : public virtual ScheduledProgram
{
private:
	int score_left = 0;
	int score_right = 0;
	string team_left;
	string team_right;
	
	void setScore(int x, int y);
	void setTeams(string x, string y);

	int getScoreLeft();
	int getScoreRight();

public:
	Game(string my_name, int my_time, string my_type, day my_day, int my_start_time, string my_team_left, string my_team_right,
		bool my_can_partition = false, int my_min_age = 0)
		:ScheduledProgram(my_name, my_time, my_type, my_day, my_start_time, my_can_partition, 
			my_min_age), Program(my_name, my_time, my_type, my_can_partition, my_min_age), team_left(my_team_left), team_right(my_team_right) {}
};

class BreakfastShow : public ScheduledProgram
{
private:
	vector<string> segments;
	vector<string> guests;
public:
	BreakfastShow(string my_name, int my_time, string my_type, day my_day, int my_start_time, vector<string> my_segments, vector<string> my_guests,
		bool my_can_partition = false, int my_min_age = 0)
		: ScheduledProgram(my_name, my_time, my_type, my_day, my_start_time, my_can_partition,
			my_min_age), Program(my_name, my_time, my_type, my_can_partition, my_min_age), segments(my_segments), guests(my_guests) {}
};