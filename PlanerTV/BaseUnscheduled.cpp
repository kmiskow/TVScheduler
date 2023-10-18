#include "BaseUnscheduled.h"

string SeriesEpisode::getSeriesName()
{
	return series_name;
}
int SeriesEpisode::getEpisodeNum()
{
	return episode_num;
}
string Film::getGenre()
{
	return this->getType();
}