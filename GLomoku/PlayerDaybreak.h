#ifndef PLAYERDAYBREAK_H
#define PLAYERDAYBREAK_H

#include "Player.h"

class PlayerDaybreak : Player
{
	public:
	PlayerDaybreak();
	virtual void OpponentDidMove(int row, int col);
	virtual void GetMove(int &row, int &col);

	private:
	int _row;
};

#endif