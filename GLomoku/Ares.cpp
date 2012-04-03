
// ATTACKING

// alphabeta provides excellent attack moves.

// BLOCKING

// alphabeta provides limited blocking.  Block() is a backup
// function meant to provide additional blocking functionality.
// Timewise Block() is almost immediate compaired to alphabeta. 

// http://cs.ucla.edu/~rosen/161/notes/alphabeta.html 
// http://www.gamedev.net/topic/96798-where-is-a-link-to-c-minimax-source-code/
// http://www.cs.northwestern.edu/~forbus/c95-gd/lectures/Game_AI_Introduction.pdf
// http://www.faui01.de/brettspiele/schaeffer-alphabetaenhancements.pdf

// Player 1 color = 'P' for purple
// Player 2 color = 'T'	for tan

#include <iostream>
#include <string>
#include <algorithm>
#include "Ares.h"
using namespace std;


//--------------------------------------------------------------


Ares::Ares() 
{
	test1 = 10;	boardSize = 0; pOneMoves = 0; boardsExamined = 0;

	// initialize player 1 19x19 board with all 'E' for empty 
	for (int row=0; row < BoardSize; row++)
		for (int col=0; col < BoardSize; col++)
			pOneBoard[row][col] = 'E';
}


//--------------------------------------------------------------


void Ares::OpponentDidMove(int row, int col) 
{
	pOneBoard[row][col] = 'T';	// record opponents move
	boardSize++;
}

//--------------------------------------------------------------

// f() adds up how many runs of lengh 2, 3, and 4 belong to
// each player and whether those runs are blocked on both sides
// (not desirable), open on one side (semi-desirable), or open 
// on both sides (ideal in many cases).

void Ares::totalEnds(int &line, char &moveColor, char &back, 
					   char &front, int row, int col, char dir)
{  
	if (back == 'B' && front == 'B')
	{
		if (line == 2 && moveColor == 'P') two_P_BB++;
		if (line == 2 && moveColor == 'T') two_T_BB++;
		if (line == 3 && moveColor == 'P') three_P_BB++;
		if (line == 3 && moveColor == 'T') three_T_BB++;
		if (line == 4 && moveColor == 'P') four_P_BB++;
		if (line == 4 && moveColor == 'T') four_T_BB++;
	}
	else if (back == 'B' && front == 'O')
	{
		if (line == 2 && moveColor == 'P') two_P_BO++;
		if (line == 2 && moveColor == 'T') two_T_BO++;
		if (line == 3 && moveColor == 'P') three_P_BO++;
		if (line == 3 && moveColor == 'T') three_T_BO++;
		if (line == 4 && moveColor == 'P') four_P_BO++;
		
		// candidate for blocking
		if (line == 4 && moveColor == 'T') 
		{
			block_4_BO.block_r = row;
			block_4_BO.block_c = col;
			block_4_BO.direction = dir;
			block_4_BO.side_already_blocked = 'B'; // back

			four_T_BO++;
		}
	}
	else if (back == 'O' && front == 'B')
	{
		if (line == 2 && moveColor == 'P') two_P_BO++;
		if (line == 2 && moveColor == 'T') two_T_BO++;
		if (line == 3 && moveColor == 'P') three_P_BO++;
		if (line == 3 && moveColor == 'T') three_T_BO++;
		if (line == 4 && moveColor == 'P') four_P_BO++;
		
		// candidate for blocking
		if (line == 4 && moveColor == 'T') 
		{
			block_4_BO.block_r = row;
			block_4_BO.block_c = col;
			block_4_BO.direction = dir;
			block_4_BO.side_already_blocked = 'F'; // front

			four_T_BO++;
		}
	}
	else if (back == 'O' && front == 'O')
	{
		if (line == 2 && moveColor == 'P') two_P_OO++;

		// candidate for blocking
		if (line == 2 && moveColor == 'T') 
		{
			block_2_OO.block_r = row;
			block_2_OO.block_c = col;
			block_2_OO.direction = dir;
			
			two_T_OO++;
		}

		if (line == 3 && moveColor == 'P') three_P_OO++;
		
		// candidate for blocking
		if (line == 3 && moveColor == 'T') 
		{
			block_3_OO.block_r = row;
			block_3_OO.block_c = col;
			block_3_OO.direction = dir;
			
			three_T_OO++;
		}
		
		if (line == 4 && moveColor == 'P') four_P_OO++;
		if (line == 4 && moveColor == 'T') four_T_OO++;
	}
}

//--------------------------------------------------------------

//	*** IMPORTANT *** 

// row and col are the coord's of the last node to enter the
// consecutive run of like colored moves

// check for 3 different cases
// open on both ends	- OXXO
// open on one end		- YXXO or OXXY
// closed on both ends	- YXXY

// dir - direction line segment is facing
// H  - left (towards 0) is beginning, right is end
// V  - up (towards 0) is beg. , right is end
// D1 - BL - goes right and down
// D2 - TR - goes left and up
// D3 - BR - goes left and down
// D4 - TL - goes right and up

void Ares::checkEnds(char &dir, char &moveColor, int &line, int &row, int &col)
{
	char back, front;

	if (dir == 'H')			// Horizontal
	{						// front: right
		// back
		if ( (col - line) < 0)
			back = 'B';	// for blocked
		else if (pOneBoard[row][col-line] == 'E')
			back = 'O';
		else	// space filled by opponent 
			back = 'B';

		// front
		if ( (col + 1) == 19)
			front = 'B';	// for blocked
		else if (pOneBoard[row][col + 1] == 'E')
			front = 'O';
		else	// space filled by opponent 
			front = 'B';

		totalEnds(line, moveColor, back, front, row, col, dir);
	}
	else if (dir == 'V')	// Vertical
	{						// front: down
		// back
		if ( (row - line) < 0)
			back = 'B';	// for blocked
		else if (pOneBoard[row-line][col] == 'E')
			back = 'O';
		else // space filled by opponent 
			back = 'B';

		// front
		if ( (row + 1) == 19)
			front = 'B';	// for blocked
		else if (pOneBoard[row + 1][col] == 'E')
			front = 'O';
		else	// space filled by opponent 
			front = 'B';

		totalEnds(line, moveColor, back, front, row, col, dir);
	}
	else if (dir == '1')	// BL triangular quadrant 
	{						// front: down and right
		// back
		if ( (col - line) < 0)	// |<--
			back = 'B';	// for blocked	___ 0
		else if ( (row - line) < 0)	//   ^
			back = 'B';	// for blocked	 |	
		else if (pOneBoard[row-line][col-line] == 'E')
			back = 'O';
		else // space filled by opponent 
			back = 'B';

		// front
		if ( (row + 1) == 19)
			front = 'B';	// for blocked
		else if ( (col + 1) == 19)
			front = 'B';	// for blocked
		else if (pOneBoard[row + 1][col + 1] == 'E')
			front = 'O';
		else	// space filled by opponent 
			front = 'B';

		totalEnds(line, moveColor, back, front, row, col, dir);
	}
	else if (dir == '2')	// TR triangular quadrant 
	{						// front: left and up
		// back
		if ( (col + line) < 0)		// right
			back = 'B';	// for blocked	
		else if ( (row + line) < 0)	// down  
			back = 'B';	// for blocked	 	
		else if (pOneBoard[row + line][col + line] == 'E')
			back = 'O';
		else // space filled by opponent 
			back = 'B';

		// front
		if ( (row - 1) == 19)		// up
			front = 'B';	// for blocked
		else if ( (col - 1) == 19)	// left
			front = 'B';	// for blocked
		else if (pOneBoard[row - 1][col - 1] == 'E')
			front = 'O';
		else	// space filled by opponent 
			front = 'B';

		totalEnds(line, moveColor, back, front, row, col, dir);
	}
	else if (dir == '3')	// BR triangular quadrant 
	{						// front: left and down
		// back
		if ( (col + line) < 0)		// right
			back = 'B';	// for blocked	
		else if ( (row - line) < 0)	// up 
			back = 'B';	// for blocked	 	
		else if (pOneBoard[row - line][col+line] == 'E')
			back = 'O';
		else // space filled by opponent 
			back = 'B';

		// front
		if ( (row + 1) == 19)		// down
			front = 'B';	// for blocked
		else if ( (col - 1) == 19)	// left
			front = 'B';	// for blocked
		else if (pOneBoard[row + 1][col - 1] == 'E')
			front = 'O';
		else	// space filled by opponent 
			front = 'B';

		totalEnds(line, moveColor, back, front, row, col, dir);
	}
	else if (dir == '4')	// TL triangular quadrant 
	{						// front: right and up
		// back
		if ( (col - line) < 0)		// left 
			back = 'B';	// for blocked	
		else if ( (row + line) < 0)	// down   
			back = 'B';	// for blocked	 	
		else if (pOneBoard[row + line][col - line] == 'E')
			back = 'O';
		else // space filled by opponent 
			back = 'B';

		// front
		if ( (row - 1) == 19)		// up
			front = 'B';	// for blocked
		else if ( (col + 1) == 19)	// right	
			front = 'B';	// for blocked
		else if (pOneBoard[row - 1][col + 1] == 'E')
			front = 'O';
		else	// space filled by opponent 
			front = 'B';

		totalEnds(line, moveColor, back, front, row, col, dir);
	}
}


//--------------------------------------------------------------


bool Ares::isSolved(char &whoWon) // 5 in a row?
{
	int l, m, line, row;	bool victory = false;
	int helpfull;			// for diagonal board evaluation
	char coloR = 'X';	// alternate between 'P' and 'T'
	char direction = '@';	// dir of run / line of 2, 3, 4 ...

	block_4_BO.side_already_blocked = 'N';
	block_line_size = 0;// block line size 3 or 4
	block = false;		// if block = true then skip alphabeta 

	two = three = four = 0;	// heur vars
	two_P_BB = two_P_BO = two_P_OO = 0;			// color 'P'
	two_T_BB = two_T_BO = two_T_OO = 0;			// color 'T'
	three_P_BB = three_P_BO = three_P_OO = 0;	// Blocked Blocked
	three_T_BB = three_T_BO = three_T_OO = 0;	// Blocked Open
	four_P_BB = four_P_BO = four_P_OO = 0;		// Open Open
	four_T_BB = four_T_BO = four_T_OO = 0;

// HORIZONTAL check for ROWS for win ---------------------
	
	direction = 'H';

	for (l = 0; l < 19; l++)
	{
		line = 0;	// reset every new row

		for (m = 0; m < 19; m++)
		{
			if (pOneBoard[l][m] == 'E') 
				line = 0; // holes reset line

			if (pOneBoard[l][m] == 'P')
			{
				if (coloR == 'P') 
					line++;	// line already started
				else				
				{
					coloR = 'P';	 // start new line
					line = 1;		
				}
			}
			else if (pOneBoard[l][m] == 'T')
			{
				if (coloR == 'T') 
					line++; // line already started
				else				{
					coloR = 'T';	 // start new line
					line = 1;		}
			}
//--------- TALLY heuristic variables --------------------

			if (2 <= line && line <= 4)
			{
				// check ends : OPPO or OPPT or TPPO or TPPT
				checkEnds(direction, coloR, line, l, m);   
			}
			else if (line == 5)			
			{
				victory = true;	
				whoWon = coloR;
				return victory;		
			}

//--------- END TALLY -------------------------------------

		}
	}

// VERTICAL check for COLUMNS for wins -----------------------

	direction = 'V';
	
	for (l = 0; l < 19; l++)
	{
		line = 0;	// reset every new column

		for (m = 0; m < 19; m++)
		{
			if (pOneBoard[m][l] == 'E')	 line = 0; // holes reset line

			if (pOneBoard[m][l] == 'P')
			{
				if (coloR == 'P') // line already started
					line++;
				else				{
					coloR = 'P';	 // start new line
					line = 1;		}	
			}
			else if (pOneBoard[m][l] == 'T')
			{
				if (coloR == 'T') // line already started
					line++;
				else				{
					coloR = 'T';	 // start new line
					line = 1;		}
			}

//--------- TALLY heuristic variables --------------------

			if (2 <= line && line <= 4)
			{
				checkEnds(direction, coloR, line, m, l);
			}
			else if (line == 5)			
			{
				victory = true;	line = 0;	
				whoWon = coloR;
				return victory;		
			}

//--------- END TALLY -------------------------------------
		}
	}

// 1 DIAGONAL BL, board cut into 2 triangles w/ 45 angle at BL

	direction = '1';

	for (l = 14; l >= 0; l--) // diminishing rows
	{
		line = 0;	row = l;

		for (m = 0; m < 19 - l; m++) // 5 diagonals at row 14
		{
			if (pOneBoard[row][m] == 'E')	 // holes reset line
				line = 0;
			else if (pOneBoard[row][m] == 'P')
			{
				if (coloR == 'P') // line already started
					line++;
				else 
				{
					coloR = 'P';	 // start new line
					line = 1;
				}
			}
			else if (pOneBoard[row][m] == 'T')
			{
				if (coloR == 'T') // line already started
					line++;
				else {
					coloR = 'T';	 // start new line
					line = 1;}
			}

//--------- TALLY heuristic variables --------------------
			
			if (2 <= line && line <= 4)
			{
				checkEnds(direction, coloR, line, row, m);
			}
			else if (line == 5)
			{
				victory = true;
				whoWon = coloR;
				return victory;
			}

//--------- END TALLY -------------------------------------

			row++; // ***************************
		}
	}

// 2 DIAGONAL TR, board cut into 2 triangles w/ 45 angle at TR

	direction = '2';	helpfull = 14;
	
	for (l = 4; l < 18; l++) // not l > 19 - fixed overlap w/ BL
	{
		line = 0;	helpfull--;	row = l;

		for (m = 18; m > helpfull; m--) // 5 diagonals at row 14
		{
			if (pOneBoard[row][m] == 'E')	 // holes reset line
				line = 0;

			if (pOneBoard[row][m] == 'P')
			{
				if (coloR == 'P') // line already started
					line++;
				else {
					coloR = 'P';	 // start new line
					line = 1;}
			}
			else if (pOneBoard[row][m] == 'T')
			{
				if (coloR == 'T') // line already started
					line++;
				else {
					coloR = 'T';	 // start new line
					line = 1;}
			}

//--------- TALLY heuristic variables --------------------
			
			if (2 <= line && line <= 4)
			{
				checkEnds(direction, coloR, line, row, m);
			}
			else if (line == 5)
			{
				victory = true;
				whoWon = coloR;
				return victory;
			}

//--------- END TALLY -------------------------------------

			row--; // ***************************
		}
	}

// 3 DIAGONAL BR, board cut into 2 triangles where 45 angle is at BR
	
	direction = '3';	helpfull = 14;
	
	for (l = 14; l > 0; l--) // not l >= 0 - fixed overlap w/ TL
	{
		line = 0;	helpfull--;	row = l;

		for (m = 18; m > helpfull; m--) // 5 diagonals at row 14
		{
			if (pOneBoard[row][m] == 'E')	 // holes reset line
				line = 0;

			if (pOneBoard[row][m] == 'P')
			{
				if (coloR == 'P') // line already started
					line++;
				else {
					coloR = 'P';	 // start new line
					line = 1;}
			}
			else if (pOneBoard[row][m] == 'T')
			{
				if (coloR == 'T') // line already started
					line++;
				else {
					coloR = 'T';	 // start new line
					line = 1;}
			}

//--------- TALLY heuristic variables --------------------
			
			if (2 <= line && line <= 4)
			{
				checkEnds(direction, coloR, line, row, m);
			}
			else if (line == 5)
			{
				victory = true;
				whoWon = coloR;
				return victory;
			}

//--------- END TALLY -------------------------------------

			row++;	// diagonal goes down and to the left
		}}

// 4 DIAGONAL TL, board cut into 2 triangles w/ 45 angle at TL
	
	direction = '4';	helpfull = 4;
	
	for (l = 4; l < 19; l++)
	{
		line = 0;	helpfull++;		row = l;

		for (m = 0; m < helpfull; m++) // 5 diagonals at row 14
		{
			if (pOneBoard[row][m] == 'E')	 // holes reset line
				line = 0;

			if (pOneBoard[row][m] == 'P')
			{
				if (coloR == 'P') // line already started
					line++;
				else {
					coloR = 'P';	 // start new line
					line = 1;}
			}
			else if (pOneBoard[row][m] == 'T')
			{
				if (coloR == 'T') // line already started
					line++;
				else {
					coloR = 'T';	 // start new line
					line = 1;}
			}

//--------- TALLY heuristic variables --------------------
			
			if (2 <= line && line <= 4)
			{
				checkEnds(direction, coloR, line, row, m);
			}
			else if (line == 5)
			{
				victory = true;
				whoWon = coloR;
				return victory;
			}

//--------- END TALLY -------------------------------------

			row--;	// ***************************
		}
	}

	// reasons to block 

	// opponent has an open run of 3 and I don't
	//if (three_T_OO > three_P_OO)	{							 
	//	block = true;
	//	block_line_size = 3;		}
	/*
	// opponent will win with his next move if I don't block 
	if (four_T_BO > four_T_OO || four_T_BO > four_T_BO) 
	{							 
		block = true;
		block_line_size = 4;
	}
	else if (three_T_OO > three_P_OO)	
	{							 
		block = true;
		block_line_size = 3;		
	}
	//else if (two_T_OO > two_P_OO){block = true;block_line_size = 2;	}
*/
	return victory; // false, but heur vals come back
}

// zab

//--------------------------------------------------------------
//--------------------------------------------------------------


// restrict possible game moves to be within n blocks of a move 
// already made by either player

//col 1  2  3		radius		searchspace
//	|  |  |	 |		1			1+(origin)+1 = 3 by 3
//	|   p,q  |		3			3+1+3		 = 7 by 7
//	|  |  |	 |		5			5+1+5		 = 11 by 11
//	  -  -  - 

bool Ares::playerDetected(int row, int col)
{
	int radius = 1; // origin of search square at (p,q)

	for (int p = row - radius; p <= row + radius; p++){
		for (int q = col - radius; q <= col + radius; q++)
		{
			if (0 <= p && p < 19) {		// within matrix
				if (0 <= q && q < 19)	// within matrix
				{
					if (pOneBoard[p][q] == 'T' || 
						pOneBoard[p][q] == 'P')
						return true;
				}}}}

	return false;
}

//--------------------------------------------------------------
//				   START
//		<------------a------------|
//	-infin ---- optimal move ---- infin
//      |------------b------------>

//				MOVES TOWARDS
//		<-----a--------|
//	-infin --------move-------------infin
//				  |------b------------>

//			 depth 0	1	 2	  3	   4
// time complexity 8 x 16 x 24 x 32 x 40 = 
// 128 x 16 = 3072 x 24 x 32 = 98,304

// -400 ---------------0---------------- 400
//       worse for a	  better for a
//       better for b	  worse for b


int Ares::getHeuristic (int depth, char winner)
{
	int heu, totalOffset, myPoints, opponentPoints; // newOffset;

	two_P_BB *= 0; two_P_BO *= 80; two_P_OO *= 400; 
	two_T_BB *= 0; two_T_BO *= 80; two_T_OO *= 400; 
		
	three_P_BB *= 0; three_P_BO *= 270; three_P_OO *= 2350; 	
	three_T_BB *= 0; three_T_BO *= 270; three_T_OO *= 2350; 
		
	four_P_BB *= 0; four_P_BO *= 3560; four_P_OO *= 12800; 
	four_T_BB *= 0; four_T_BO *= 3560; four_T_OO *= 12800; 

	myPoints = two_P_BO + two_P_OO + three_P_BO + 
			   three_P_OO + four_P_BO + four_P_OO;
	
	opponentPoints = two_T_BO + two_T_OO + three_T_BO + 
				     three_T_OO + four_T_BO + four_T_OO;

	//totalOffset = two + three + four; // using totalEnds()
	totalOffset = myPoints - opponentPoints; // more precise

	if (winner == 'P') 
	{
		heu = 421000 - depth * 2; // the shallower the better
	}
	else if (winner == 'T')
	{
		heu = -421000 + depth * 2; // the shallower the better
	}
	else 
	{
		heu = totalOffset; // intermediate board
	}

 	return heu;

}

//--------------------------------------------------------------

// depth - a cap on how low the search reaches in the tree
// function alphabeta(node, depth, α, β, Player)   

int Ares::alphaBeta (int depth, int alpha, int beta, bool MAXplayer)
{
	int heuristic = 0;	bool go = false;
	int temp;			char winner = 'N'; // 'N' for NULL
	
	go = isSolved(winner); // get heur info 

    if (depth == 2 || go ) // or node is a terminal node
	{
		heuristic = getHeuristic(depth, winner);
        return heuristic;// value of the terminal game tree node
	}
	
    if (MAXplayer)	//for each child of node
	{ 
		for (int p = 0; p < 19; p++){
			for (int q = 0; q < 19; q++)
			{
				if (pOneBoard[p][q] == 'E' && playerDetected(p,q))
				{
					pOneBoard[p][q] = 'P';	// make move on board
					temp = alphaBeta(depth+1, alpha, beta, !(MAXplayer)); 
					pOneBoard[p][q] = 'E';	//unmake move on board
					boardsExamined++; // total recursive calls

// - ab code start- α := min(<) or max(>) 
					if (temp > alpha) alpha = temp; 
					if (beta <= alpha) break; 			
// -- ab cod end ---	
				
				}}}

		return alpha; // α
	}
    else	// MINplayer - for each child of node
	{    
		for (int p = 0; p < 19; p++){
			for (int q = 0; q < 19; q++)
			{
				if (pOneBoard[p][q] == 'E' && playerDetected(p,q))
				{
					pOneBoard[p][q] = 'T'; // make move on board
					temp = alphaBeta(depth+1, alpha, beta, !(MAXplayer)); 
					pOneBoard[p][q] = 'E'; //unmake move on board
					boardsExamined++; // total recursive calls

// - ab code start- β := max(>) or min(<)  
					if (temp < beta) beta = temp; 
					if (beta <= alpha) break; 	
// -- ab cod end --- 	

				}}}

		return beta; // β 
	}
}

// zaz

//--------------------------------------------------------------

// D1 - BL - goes right and down
// D2 - TR - goes left and up
// D3 - BR - goes left and down
// D4 - TL - goes right and up

void Ares::Block(int &row, int &col)
{
	int rback, cback, rfront, cfront; 
	int backHeur = 0, frontHeur = 0;
	char c = 'N';	bool m;

	if (block_line_size == 2) // BLOCK XPPPX  
	{
		if (block_2_OO.direction == 'H')
		{
			// find both ends to block
			rback = block_2_OO.block_r;
			cback = block_2_OO.block_c - 2;
			rfront = block_2_OO.block_r;
			cfront = block_2_OO.block_c + 1;

			// make moves for both to see which is better 
			pOneBoard[rback][cback] = 'P';
			m = isSolved(c);	 
			backHeur = getHeuristic(1, m);
			pOneBoard[rback][cback] = 'E';

			pOneBoard[rfront][cfront] = 'P';
			m = isSolved(c);	 
			frontHeur = getHeuristic(1, m);
			pOneBoard[rfront][cfront] = 'E';

			if (backHeur > frontHeur)			{
				row = rback;	col = cback;	}
			else								{
				row = rfront;	col = cfront;	}
		}
		else if (block_2_OO.direction == 'V')
		{
			// find both ends to block
			rback = block_2_OO.block_r - 2;
			cback = block_2_OO.block_c;
			rfront = block_2_OO.block_r + 1;
			cfront = block_2_OO.block_c;

			// make moves for both to see which is better 
			pOneBoard[rback][cback] = 'P';
			m = isSolved(c);	 
			backHeur = getHeuristic(1, m);
			pOneBoard[rback][cback] = 'E';

			pOneBoard[rfront][cfront] = 'P';
			m = isSolved(c);	 
			frontHeur = getHeuristic(1, m);
			pOneBoard[rfront][cfront] = 'E';

			if (backHeur > frontHeur)			{
				row = rback;	col = cback;	}
			else								{
				row = rfront;	col = cfront;	}
		}
		else if (block_2_OO.direction == '1') // right and down
		{
			// find both ends to block
			rback = block_2_OO.block_r - 2;
			cback = block_2_OO.block_c - 2;
			rfront = block_2_OO.block_r + 1;
			cfront = block_2_OO.block_c + 1;

			// make moves for both to see which is better 
			pOneBoard[rback][cback] = 'P';
			m = isSolved(c);	 
			backHeur = getHeuristic(1, m);
			pOneBoard[rback][cback] = 'E';

			pOneBoard[rfront][cfront] = 'P';
			m = isSolved(c);	 
			frontHeur = getHeuristic(1, m);
			pOneBoard[rfront][cfront] = 'E';

			if (backHeur > frontHeur)			{
				row = rback;	col = cback;	}
			else								{
				row = rfront;	col = cfront;	}
		}
		else if (block_2_OO.direction == '2') // left and up
		{
			// find both ends to block
			rback = block_2_OO.block_r + 2;
			cback = block_2_OO.block_c + 2;
			rfront = block_2_OO.block_r - 1;
			cfront = block_2_OO.block_c - 1;

			// make moves for both to see which is better 
			pOneBoard[rback][cback] = 'P';
			m = isSolved(c);	 
			backHeur = getHeuristic(1, m);
			pOneBoard[rback][cback] = 'E';

			pOneBoard[rfront][cfront] = 'P';
			m = isSolved(c);	 
			frontHeur = getHeuristic(1, m);
			pOneBoard[rfront][cfront] = 'E';

			if (backHeur > frontHeur)			{
				row = rback;	col = cback;	}
			else								{
				row = rfront;	col = cfront;	}
		}
		else if (block_2_OO.direction == '3') // left and down
		{
			// find both ends to block
			rback = block_2_OO.block_r - 2;
			cback = block_2_OO.block_c + 2;
			rfront = block_2_OO.block_r + 1;
			cfront = block_2_OO.block_c - 1;

			// make moves for both to see which is better 
			pOneBoard[rback][cback] = 'P';
			m = isSolved(c);	 
			backHeur = getHeuristic(1, m);
			pOneBoard[rback][cback] = 'E';

			pOneBoard[rfront][cfront] = 'P';
			m = isSolved(c);	 
			frontHeur = getHeuristic(1, m);
			pOneBoard[rfront][cfront] = 'E';

			if (backHeur > frontHeur)			{
				row = rback;	col = cback;	}
			else								{
				row = rfront;	col = cfront;	}
		}
		else if (block_2_OO.direction == '4') // right and up
		{
			// find both ends to block
			rback = block_2_OO.block_r - 2;
			cback = block_2_OO.block_c + 2;
			rfront = block_2_OO.block_r - 1;
			cfront = block_2_OO.block_c + 1;

			// make moves for both to see which is better 
			pOneBoard[rback][cback] = 'P';
			m = isSolved(c);	 
			backHeur = getHeuristic(1, m);
			pOneBoard[rback][cback] = 'E';

			pOneBoard[rfront][cfront] = 'P';
			m = isSolved(c);	 
			frontHeur = getHeuristic(1, m);
			pOneBoard[rfront][cfront] = 'E';

			if (backHeur > frontHeur)			{
				row = rback;	col = cback;	}
			else								{
				row = rfront;	col = cfront;	}	
		}
	}
	else if (block_line_size == 3) // BLOCK XPPPX  
	{
		if (block_3_OO.direction == 'H')
		{
			// find both ends to block
			rback = block_3_OO.block_r;
			cback = block_3_OO.block_c - 3;
			rfront = block_3_OO.block_r;
			cfront = block_3_OO.block_c + 1;

			// make moves for both to see which is better 
			pOneBoard[rback][cback] = 'P';
			m = isSolved(c);	 
			backHeur = getHeuristic(1, m);
			pOneBoard[rback][cback] = 'E';

			pOneBoard[rfront][cfront] = 'P';
			m = isSolved(c);	 
			frontHeur = getHeuristic(1, m);
			pOneBoard[rfront][cfront] = 'E';

			if (backHeur > frontHeur)			{
				row = rback;	col = cback;	}
			else								{
				row = rfront;	col = cfront;	}
		}
		else if (block_3_OO.direction == 'V')
		{
			// find both ends to block
			rback = block_3_OO.block_r - 3;
			cback = block_3_OO.block_c;
			rfront = block_3_OO.block_r + 1;
			cfront = block_3_OO.block_c;

			// make moves for both to see which is better 
			pOneBoard[rback][cback] = 'P';
			m = isSolved(c);	 
			backHeur = getHeuristic(1, m);
			pOneBoard[rback][cback] = 'E';

			pOneBoard[rfront][cfront] = 'P';
			m = isSolved(c);	 
			frontHeur = getHeuristic(1, m);
			pOneBoard[rfront][cfront] = 'E';

			if (backHeur > frontHeur)			{
				row = rback;	col = cback;	}
			else								{
				row = rfront;	col = cfront;	}
		}
		else if (block_3_OO.direction == '1') // right and down
		{
			// find both ends to block
			rback = block_3_OO.block_r - 3;
			cback = block_3_OO.block_c - 3;
			rfront = block_3_OO.block_r + 1;
			cfront = block_3_OO.block_c + 1;

			// make moves for both to see which is better 
			pOneBoard[rback][cback] = 'P';
			m = isSolved(c);	 
			backHeur = getHeuristic(1, m);
			pOneBoard[rback][cback] = 'E';

			pOneBoard[rfront][cfront] = 'P';
			m = isSolved(c);	 
			frontHeur = getHeuristic(1, m);
			pOneBoard[rfront][cfront] = 'E';

			if (backHeur > frontHeur)			{
				row = rback;	col = cback;	}
			else								{
				row = rfront;	col = cfront;	}
		}
		else if (block_3_OO.direction == '2') // left and up
		{
			// find both ends to block
			rback = block_3_OO.block_r + 3;
			cback = block_3_OO.block_c + 3;
			rfront = block_3_OO.block_r - 1;
			cfront = block_3_OO.block_c - 1;

			// make moves for both to see which is better 
			pOneBoard[rback][cback] = 'P';
			m = isSolved(c);	 
			backHeur = getHeuristic(1, m);
			pOneBoard[rback][cback] = 'E';

			pOneBoard[rfront][cfront] = 'P';
			m = isSolved(c);	 
			frontHeur = getHeuristic(1, m);
			pOneBoard[rfront][cfront] = 'E';

			if (backHeur > frontHeur)			{
				row = rback;	col = cback;	}
			else								{
				row = rfront;	col = cfront;	}
		}
		else if (block_3_OO.direction == '3') // left and down
		{
			// find both ends to block
			rback = block_3_OO.block_r - 3;
			cback = block_3_OO.block_c + 3;
			rfront = block_3_OO.block_r + 1;
			cfront = block_3_OO.block_c - 1;

			// make moves for both to see which is better 
			pOneBoard[rback][cback] = 'P';
			m = isSolved(c);	 
			backHeur = getHeuristic(1, m);
			pOneBoard[rback][cback] = 'E';

			pOneBoard[rfront][cfront] = 'P';
			m = isSolved(c);	 
			frontHeur = getHeuristic(1, m);
			pOneBoard[rfront][cfront] = 'E';

			if (backHeur > frontHeur)			{
				row = rback;	col = cback;	}
			else								{
				row = rfront;	col = cfront;	}

		}
		else if (block_3_OO.direction == '4') // right and up
		{
			// find both ends to block
			rback = block_3_OO.block_r - 3;
			cback = block_3_OO.block_c + 3;
			rfront = block_3_OO.block_r - 1;
			cfront = block_3_OO.block_c + 1;

			// make moves for both to see which is better 
			pOneBoard[rback][cback] = 'P';
			m = isSolved(c);	 
			backHeur = getHeuristic(1, m);
			pOneBoard[rback][cback] = 'E';

			pOneBoard[rfront][cfront] = 'P';
			m = isSolved(c);	 
			frontHeur = getHeuristic(1, m);
			pOneBoard[rfront][cfront] = 'E';

			if (backHeur > frontHeur)			{
				row = rback;	col = cback;	}
			else								{
				row = rfront;	col = cfront;	}			
		}
	}
	else if (block_line_size == 4) // BLOCK TPPPPX or XPPPPT 
	{
		// find end to block and return coord's
		if (block_4_BO.direction == 'H')
		{
			if (block_4_BO.side_already_blocked == 'B') // back
			{
				// block right side (front) of horizontal line
				row = block_4_BO.block_r;	
				col = block_4_BO.block_c + 1;
			}
			else if (block_4_BO.side_already_blocked == 'F') // front
			{
				// block left side (back) of horizontal line
				row = block_4_BO.block_r;	
				col = block_4_BO.block_c - 4;
			}
		}
		else if (block_4_BO.direction == 'V')
		{
			if (block_4_BO.side_already_blocked == 'B') // back
			{
				// block bottom (front) of vertical line
				row = block_4_BO.block_r + 1;	
				col = block_4_BO.block_c;
			}
			else if (block_4_BO.side_already_blocked == 'F') // front
			{
				// block top (back) of vertical line
				row = block_4_BO.block_r - 4;	
				col = block_4_BO.block_c;
			}
		}
		else if (block_4_BO.direction == '1') // right and down
		{
			if (block_4_BO.side_already_blocked == 'B') // back
			{
				// block right and down (front) of diag line
				row = block_4_BO.block_r + 1;	
				col = block_4_BO.block_c + 1;
			}
			else if (block_4_BO.side_already_blocked == 'F') // front
			{
				// block left and up (back) of diag line
				row = block_4_BO.block_r - 4;	
				col = block_4_BO.block_c - 4;
			}
		}
		else if (block_4_BO.direction == '2') // goes left and up
		{
			if (block_4_BO.side_already_blocked == 'B') // back
			{
				// block left and up (front) of diag line
				row = block_4_BO.block_r - 1;	
				col = block_4_BO.block_c - 1;
			}
			else if (block_4_BO.side_already_blocked == 'F') // front
			{
				// block right and down (back) of diag line
				row = block_4_BO.block_r + 4;	
				col = block_4_BO.block_c + 4;
			}
		}
		else if (block_4_BO.direction == '3') // left and down
		{
			if (block_4_BO.side_already_blocked == 'B') // back
			{
				// block left and down (front) of diag line
				row = block_4_BO.block_r + 1;	
				col = block_4_BO.block_c - 1;
			}
			else if (block_4_BO.side_already_blocked == 'F') // front
			{
				// block right and up (back) of diag line
				row = block_4_BO.block_r - 4;	
				col = block_4_BO.block_c + 4;
			}
		}
		else if (block_4_BO.direction == '4') // right and up
		{
			if (block_4_BO.side_already_blocked == 'B') // back
			{
				// block right and up (front) of diag line
				row = block_4_BO.block_r - 1;	
				col = block_4_BO.block_c + 1;
			}
			else if (block_4_BO.side_already_blocked == 'F') // front
			{
				// block left and down (back) of diag line
				row = block_4_BO.block_r + 4;	
				col = block_4_BO.block_c - 4;
			}
		}
	}
}

//--------------------------------------------------------------


// f() assigns the desired move to variables roW and coL and
// returns x and y vals ranging 0-18 representing coordinates
// for gameBoard[][]


void Ares::GetMove(int &roW, int &coL)
{	
	int terminal;	// alphabeta return value. terminal node
	int depth;		// determines search height in tree
	int alpha = -500000;			int beta = 500000;
	bool maxPlayer = true;		bool na; char non = 'N'; //throwaway
	int possibeMoves[365][3];	int moveCount = 0;

	recordMov bestMove;
	bestMove.row = bestMove.col = bestMove.heur = -1;
	boardsExamined = 0;	// reset total between moves

	if (pOneMoves == 0) // first move
	{
		isPlayerOne = true;

		// find if other player moved
		for (int zz = 1; zz < 18; zz++)				{	
			for (int zzz = 1; zzz < 18; zzz++)		{	
				if (pOneBoard[zz][zzz] != 'E')		{	
					if (zzz < 9)					{
						roW = zz;	coL = zzz + 1;	}
					if (zzz >= 9)					{
						roW = zz;	coL = zzz - 1;	}
					isPlayerOne = false;			}}}

   		if (isPlayerOne)
			roW = coL = 9;	// center of board
	}
	else // for every 'E' on board
	{
		for (int e = 0; e < 19; e++)		{
			for (int f = 0; f < 19; f++)		
			{
				bool detected = playerDetected(e,f);

				if (pOneBoard[e][f] == 'E' && detected)
				{
					if ( e == 9 && f == 4)
       					cout << "\n\n hey \n\n";

  					depth = 0;
					pOneBoard[e][f] = 'P';
					terminal = alphaBeta(depth+1, alpha, beta, !(maxPlayer)); 				
					pOneBoard[e][f] = 'E';

					boardsExamined++; // total recursive calls

					// search for best move
					if (terminal > bestMove.heur || bestMove.col == -1)
					{
						bestMove.row = e;
						bestMove.col = f;
						bestMove.heur = terminal;
					}

					// update best move
					possibeMoves[moveCount][0] = terminal;
					possibeMoves[moveCount][1] = e;
					possibeMoves[moveCount][2] = f;
					moveCount++;
				}}}	

//----- BLOCK or ATTACK	
		na = isSolved(non);	// set block to true or false
		
		if (block == true && bestMove.heur < 400000) // BLOCK
			Block(roW, coL); 
		else { // ATTACK						
			roW = bestMove.row; coL = bestMove.col;
		}		
	} // end else
	
	pOneBoard[roW][coL] = 'P'; // record your move
	boardSize++;	pOneMoves++;

	cout << "\n" << pOneMoves << " Chose: " << bestMove.heur << " " 
		<< roW << " " << coL;
}

