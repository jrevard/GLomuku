
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
		int boardSize; // total moves on gameBoard
		int boardsExamined; // total boards looked at per call
		int twoAr[2][100], threeAr[3][50], fourAr[4][10],
			two, three, four;
	
		char pOneBoard[BoardSize][BoardSize];
	
		bool isSolved(char &whoWon);
		void TALLY_heur_vars(int &run, char &playerColor);
		int checkEnds(int &dir, int &line, int &row, int &col);

		bool playerDetected(int row, int col);
	
		int getHeuristic(int depth, char winner, bool MAXplayer);	
		int alphaBeta (int depth, int alpha, int beta, bool MAXplayer);
};

#endif


