
#ifndef PLAYER1_H
#define PLAYER1_H

#include <algorithm>

struct recordMove
{
	int row, col, heur;
};

void playerOne(int &roW, int &coL);
bool isSolved();

#endif


