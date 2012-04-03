
#ifndef ARES_H
#define ARES_H

#include <algorithm>
#include "Board.h"
#include "Player.h"

struct recordMov
{
	int row, col, heur;		// used to record best move 
	int block_r, block_c;	// used to record the coord's
	int direction;			// and dir of line needing blocking
	char side_already_blocked;						
};							

class Ares : public Player
{
	public:
	
		virtual void OpponentDidMove(int row, int col);
		virtual void GetMove(int &row, int &col);
		Ares();

	private:

		bool block;
		recordMov block_2_OO;	// block coord's for run lengh 2
		recordMov block_3_OO;	// block coord's for run lengh 3
		recordMov block_4_BO;	// block coord's for run lengh 4
	
		int test1, block_line_size;
		int boardSize; // total moves on gameBoard
		int pOneMoves;
		int boardsExamined; // total boards looked at per call
		int twoAr[2][100], threeAr[3][50], fourAr[4][10],
			two, three, four,
			two_P_BB, two_P_BO, two_P_OO,		// color 'P'
			two_T_BB, two_T_BO, two_T_OO,		// color 'T'
			three_P_BB, three_P_BO, three_P_OO,	// Blocked Blocked
			three_T_BB, three_T_BO, three_T_OO,	// Blocked Open
			four_P_BB, four_P_BO, four_P_OO,	// Open Open
			four_T_BB, four_T_BO, four_T_OO;
	
		char pOneBoard[BoardSize][BoardSize];
	
		bool isPlayerOne;
		bool isSolved(char &whoWon);
		void TALLY_heur_vars(int &line, int &lineValue, char &playerColor);
		
		void checkEnds(char &dir, char &moveColor, int &line, int &row, int &col);
		void totalEnds(int &line, char &moveColor, char &leftVal, 
					  char &rightVal, int row, int col, char dir);

		bool playerDetected(int row, int col);
		void Block(int &row, int &col);
	
		int getHeuristic(int depth, char winner);	
		int alphaBeta (int depth, int alpha, int beta, bool MAXplayer);
};

#endif


