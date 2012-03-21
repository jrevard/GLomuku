#ifndef PLAYER_H
#define PLAYER_H

class Player
{
	public:
	virtual void GetMove(int &row, int &col) = 0;
	virtual void OpponentDidMove(int row, int col) = 0;
};

#endif