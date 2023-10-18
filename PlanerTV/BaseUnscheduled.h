#pragma once
#include "Program.h"
class Film : public Program {
private:

public:
	Film(string my_name, int my_time, string my_genre, bool my_can_partition = true, int my_min_age = 0)
		: Program(my_name, my_time, my_genre, my_can_partition, my_min_age) {}
	string getGenre();
};
class Reklama : public Program {
private:
public:
	Reklama(string my_name, int my_time, string my_type, bool my_can_partition = false, int my_min_age = 0)
		: Program(my_name, my_time, my_type, my_can_partition, my_min_age) {}
};
class SeriesEpisode : public Program
{
public:
	SeriesEpisode(string my_name, int my_time, string my_type, string my_series_name, int my_episode_num, bool my_can_partition = true, int my_min_age = 0)
		: Program(my_name, my_time, my_type, my_can_partition, my_min_age), episode_num(my_episode_num), series_name(my_series_name) {}
	string getSeriesName();
	int getEpisodeNum();
private:
	int episode_num;
	string series_name;

};
class Interlude : public Program
{
public:
	Interlude(string my_name, int my_time, string my_type, bool my_can_partition = false, int my_min_age = 0)
		: Program(my_name, my_time, my_type, my_can_partition, my_min_age) {}
};