#include "BaseScheduled.h"

void Game::setScore(int x, int y)
{
	score_left = x;
	score_right = y;
}
void Game::setTeams(string x, string y)
{
	team_left = x;
	team_right = y;
}
int Game::getScoreLeft()
{
	return score_left;
}
int Game::getScoreRight()
{
	return score_right;
}