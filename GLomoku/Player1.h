
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
		int pOneMoves;
		int boardsExamined; // total boards looked at per call
		int twoAr[2][100], threeAr[3][50], fourAr[4][10],
			two, three, four,
			two_P_BB, two_P_BO, twp_P_OO,		// color 'P'
			two_T_BB, two_T_BO, twp_T_OO,		// color 'T'
			three_P_BB, three_P_BO, three_P_OO,	// Blocked Blocked
			three_T_BB, three_T_BO, three_T_OO,	// Blocked Open
			four_P_BB, four_P_BO, four_P_OO,	// Open Open
			four_T_BB, four_T_BO, four_T_OO;
	
		char pOneBoard[BoardSize][BoardSize];
	
		bool isSolved(char &whoWon);
		void TALLY_heur_vars(int &line, int &lineValue, char &playerColor);
		
		int checkEnds(char &dir, char &moveColor, int &line, int &row, int &col);
		int totalEnds(int &line, char &moveColor, char &leftVal, char &rightVal);

		bool playerDetected(int row, int col);
	
		int getHeuristic(int depth, char winner, bool MAXplayer);	
		int alphaBeta (int depth, int alpha, int beta, bool MAXplayer);
};

#endif


