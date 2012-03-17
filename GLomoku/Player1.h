
#ifndef PLAYER1_H
#define PLAYER1_H

#include <algorithm>
#include "Board.h"
#include "Player.h"

struct recordMove
{
	int row, col, heur;
};

class Player1 : public Player
{
	public:
	virtual void OpponentDidMove(int row, int col);
	virtual void GetMove(int &row, int &col);
	Player1();

	private:
	int test1;
	int boardSize;
	char pOneBoard[BoardSize][BoardSize];
	bool isSolved(char &whoWon);
	bool playerDetected(int row, int col);
	int getHeuristic(int depth, char winner, bool MAXplayer);
	int alphaBeta (int depth, int alpha, int beta, bool MAXplayer);
};

#endif


