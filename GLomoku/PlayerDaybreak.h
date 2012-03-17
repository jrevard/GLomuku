#ifndef PLAYERDAYBREAK_H
#define PLAYERDAYBREAK_H

#include "Player.h"
#include "Board.h"

class PlayerDaybreak : public Player
{
	public:
	PlayerDaybreak();
	virtual void OpponentDidMove(int row, int col);
	virtual void GetMove(int &row, int &col);

	private:
	int _row;
	Board board;
	bool IsPlayerRow3(int &row, int &col);
	void GetRandom(int &row, int &col);
};

#endif