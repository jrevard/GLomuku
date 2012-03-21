
// Player 1 color = 'P' for purple
// Player 2 color = 'T'	for tan

#include <string>
#include <algorithm>
#include "Player1.h"

Player1::Player1() 
{
	test1 = 10;
	boardSize = 0;
	boardsExamined = 0;

	// initialize player 1 19x19 board with all 'E' for empty 
	for (int row=0; row < BoardSize; row++)
		for (int col=0; col < BoardSize; col++)
			pOneBoard[row][col] = 'E';
}


//--------------------------------------------------------------

// check for 3 different cases
// open on both ends	- OXXO
// open on one end		- YXXO or OXXY
// closed on both ends	- YXXY

// dir - direction line segment is facing
// H  - left (towards 0) is beginning, right is end
// V  - up (towards 0) is beg. , right is end
// D1 - 
// D2 - 
// D3 - 
// D4 - 

int Player1::checkEnds(int &dir, int &line, int &row, int &col)
{
	int rval;	

	return 5;
}

//--------------------------------------------------------------

// helper f() for isSolved()
// record runs of 2, 3, and 4 and check each for 3 cases:
//  - no ends (not blocked)		  = great move
//  - one end (partially blocked) = good move
//  - two ends (blocked)		  = bad move

void Player1::TALLY_heur_vars(int &line, char &playerColor)
{
	if (line == 2)
	{
		if (playerColor == 'P')		
		{
			two++; // better for a
		}
		else
			two--; // better for b
	}
	else if (line == 3)
	{
		if (playerColor == 'P')
			three++; // better for a
		else
			three--; // better for b
	}
	else if (line == 4) // something drastic
	{
		if (playerColor == 'P')
			four++; // better for a
		else
			four--; // better for b
	}
}


//--------------------------------------------------------------


bool Player1::isSolved(char &whoWon) // 5 in a row?
{
	int l, m, line, row;	bool victory = false;
	char evaluate = 'X';	// alternate between 'P' and 'T'
	two = three = four = 0;

// HORIZONTAL check for ROWS for win ---------------------

	for (l = 0; l < 19; l++)
	{
		line = 0;	// reset every new row

		for (m = 0; m < 19; m++)
		{
			if (pOneBoard[l][m] == 'E') 
				line = 0; // holes reset line

			if (pOneBoard[l][m] == 'P')
			{
				if (evaluate == 'P') 
					line++;	// line already started
				else				
				{
					evaluate = 'P';	 // start new line
					line = 1;		
				}
			}
			else if (pOneBoard[l][m] == 'T')
			{
				if (evaluate == 'T') 
					line++; // line already started
				else				{
					evaluate = 'T';	 // start new line
					line = 1;		}
			}
//--------- TALLY heuristic variables --------------------

			if (2 <= line && line >= 4)
			{
				// check ends : OPPO or OPPT or TPPO or TPPT
				TALLY_heur_vars(line, evaluate);
			}
			else if (line == 5)			
			{
				victory = true;	
				whoWon = evaluate;
				return victory;		
			}

//--------- END TALLY -------------------------------------

		}
	}

// VERTICAL check for COLUMNS for wins -----------------------
	
	for (l = 0; l < 19; l++)
	{
		line = 0;	// reset every new column

		for (m = 0; m < 19; m++)
		{
			if (pOneBoard[m][l] == 'E')	 line = 0; // holes reset line

			if (pOneBoard[m][l] == 'P')
			{
				if (evaluate == 'P') // line already started
					line++;
				else				{
					evaluate = 'P';	 // start new line
					line = 1;		}	
			}
			else if (pOneBoard[m][l] == 'T')
			{
				if (evaluate == 'T') // line already started
					line++;
				else				{
					evaluate = 'T';	 // start new line
					line = 1;		}
			}

//--------- TALLY heuristic variables --------------------

			if (2 <= line && line >= 4)
			{
				TALLY_heur_vars(line, evaluate);
			}
			else if (line == 5)			
			{
				victory = true;	line = 0;	
				whoWon = evaluate;
				return victory;		
			}

//--------- END TALLY -------------------------------------
		}
	}

//1 DIAGONAL BL, board cut into 2 triangles w/ 45 angle at BL

	for (l = 14; l >= 0; l--) // diminishing rows
	{
		line = 0;	row = l;

		for (m = 0; m < 19 - l; m++) // 5 diagonals at row 14
		{
			if (pOneBoard[row][m] == 'E')	 // holes reset line
				line = 0;

			if (pOneBoard[row][m] == 'P')
			{
				if (evaluate == 'P') // line already started
					line++;
				else {
					evaluate = 'P';	 // start new line
					line = 1;}
			}
			else if (pOneBoard[row][m] == 'T')
			{
				if (evaluate == 'T') // line already started
					line++;
				else {
					evaluate = 'T';	 // start new line
					line = 1;}
			}

//--------- TALLY heuristic variables --------------------
			
			if (2 <= line && line >= 4)
			{
				TALLY_heur_vars(line, evaluate);
			}
			if (line == 5)
			{
				victory = true;
				whoWon = evaluate;
				return victory;
			}

//--------- END TALLY -------------------------------------

			row++; // ***************************
		}
	}

//2 DIAGONAL TR, board cut into 2 triangles w/ 45 angle at TR

	int helpfull = 14;
	
	for (l = 4; l < 19; l++)
	{
		line = 0;	helpfull--;	row = l;

		for (m = 18; m > helpfull; m--) // 5 diagonals at row 14
		{
			if (pOneBoard[row][m] == 'E')	 // holes reset line
				line = 0;

			if (pOneBoard[row][m] == 'P')
			{
				if (evaluate == 'P') // line already started
					line++;
				else {
					evaluate = 'P';	 // start new line
					line = 1;}
			}
			else if (pOneBoard[row][m] == 'T')
			{
				if (evaluate == 'T') // line already started
					line++;
				else {
					evaluate = 'T';	 // start new line
					line = 1;}
			}

//--------- TALLY heuristic variables --------------------
			
			if (2 <= line && line >= 4)
			{
				TALLY_heur_vars(line, evaluate);
			}
			if (line == 5)
			{
				victory = true;
				whoWon = evaluate;
				return victory;
			}

//--------- END TALLY -------------------------------------

			row--; // ***************************
		}
	}

//3 DIAGONAL BR, board cut into 2 triangles where 45 angle is at BR
	
	helpfull = 14;
	
	for (l = 14; l >= 0; l--)
	{
		line = 0;	helpfull--;	row = l;

		for (m = 18; m > helpfull; m--) // 5 diagonals at row 14
		{
			if (pOneBoard[row][m] == 'E')	 // holes reset line
				line = 0;

			if (pOneBoard[row][m] == 'P')
			{
				if (evaluate == 'P') // line already started
					line++;
				else {
					evaluate = 'P';	 // start new line
					line = 1;}
			}
			else if (pOneBoard[row][m] == 'T')
			{
				if (evaluate == 'T') // line already started
					line++;
				else {
					evaluate = 'T';	 // start new line
					line = 1;}
			}

//--------- TALLY heuristic variables --------------------
			
			if (2 <= line && line >= 4)
			{
				TALLY_heur_vars(line, evaluate);
			}
			if (line == 5)
			{
				victory = true;
				whoWon = evaluate;
				return victory;
			}

//--------- END TALLY -------------------------------------

			row++;	// diagonal goes down and to the left
		}}

//4 DIAGONAL TL, board cut into 2 triangles w/ 45 angle at TL
	
	helpfull = 4;
	
	for (l = 4; l < 19; l++)
	{
		line = 0;	helpfull++;		row = l;

		for (m = 0; m < helpfull; m++) // 5 diagonals at row 14
		{
			if (pOneBoard[row][m] == 'E')	 // holes reset line
				line = 0;

			if (pOneBoard[row][m] == 'P')
			{
				if (evaluate == 'P') // line already started
					line++;
				else {
					evaluate = 'P';	 // start new line
					line = 1;}
			}
			else if (pOneBoard[row][m] == 'T')
			{
				if (evaluate == 'T') // line already started
					line++;
				else {
					evaluate = 'T';	 // start new line
					line = 1;}
			}

//--------- TALLY heuristic variables --------------------
			
			if (2 <= line && line >= 4)
			{
				TALLY_heur_vars(line, evaluate);
			}
			if (line == 5)
			{
				victory = true;
				whoWon = evaluate;
				return victory;
			}

//--------- END TALLY -------------------------------------

			row--;	// ***************************
		}
	}

	return victory; // false, but heur vals come back
}

//--------------------------------------------------------------
//--------------------------------------------------------------


// restrict possible game moves to be within n blocks of a move 
// already made by either player

//col 1  2  3		radius		searchspace
//	|  |  |	 |		1			1+(origin)+1 = 3 by 3
//	|   p,q  |		3			3+1+3		 = 7 by 7
//	|  |  |	 |		5			5+1+5		 = 11 by 11
//	  -  -  - 

bool Player1::playerDetected(int row, int col)
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


int Player1::getHeuristic (int depth, char winner, bool MAXplayer)
{
	int heu;
	int twoOffset = two * 3;	 // 1 - ? = 2 - 361/2*2 = 361
	int threeOffs = three * 30; // 1 or 2 average = 100 - 200
	int fourOffse = four * 100;
	int totalOffset = two + three + four;

	if (winner == 'P') 
	{
		heu = 4000 - depth * 2;  // shallower the better
	}
	else if (winner == 'T')
	{
		heu = -4000 + depth * 2;
	}
	else 
	{
		heu = totalOffset; // intermediate board
	}

	if (heu != 2 && heu != 0){	// seen - 0, 1, 2
  		heu++; heu--;	}

 	return heu;

}

//--------------------------------------------------------------

// depth - a cap on how low the search reaches in the tree

// function alphabeta(node, depth, α, β, Player)      
int Player1::alphaBeta (int depth, int alpha, int beta, bool MAXplayer)
{
	int heuristic = 0;	bool go;
	int temp;			char winner = 'N'; // 'N' for NULL
	
	go = isSolved(winner); // get heur info 

    if (depth == 2 || go ) // or node is a terminal node
	{
		heuristic = getHeuristic(depth, winner, !(MAXplayer));
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
//-----------------
					boardsExamined++; // total recursive calls

					if (temp > alpha) //alpha = max(alpha, alphaBeta	
						alpha = temp;

					// (* Beta cut-off *)
					if (beta <= alpha)	
					{
						pOneBoard[p][q] = 'E';
						break; // may cause return problems

		//				alpha = 0;
		//				return alpha; // cleaner
					}
					else
					{
						//unmake move on board
						pOneBoard[p][q] = 'E';
					}
				}	// end if
			}
		}

		return alpha;	// α
	}
    else	//MINplayer	//for each child of node
	{    
		for (int p = 0; p < 19; p++){
			for (int q = 0; q < 19; q++)
			{
				if (pOneBoard[p][q] == 'E' && playerDetected(p,q))
				{
					pOneBoard[p][q] = 'T'; // make move on board
					temp = alphaBeta(depth+1, alpha, beta, !(MAXplayer)); 

//-----------------
					boardsExamined++; // total recursive calls

					if (temp < beta) // β := min(β, alphabeta(
						beta = temp;
          
					// (* Alpha cut-off *)
					if (beta <= alpha) 	
					{
						pOneBoard[p][q] = 'E';
   						break; // may cause return problems

						//beta = 0;
						//return beta; // cleaner
					}
					else // unmake move on board and continue
					{
						pOneBoard[p][q] = 'E';
					}
				}}}

		return beta;	// β 
	}
}

//--------------------------------------------------------------


//http://en.wikipedia.org/wiki/Alpha-beta_pruning

void Player1::OpponentDidMove(int row, int col) 
{
	pOneBoard[row][col] = 'T';	// record opponents move
	boardSize++;
}


//--------------------------------------------------------------


// returns x and y vals ranging 0-18 (coord's for gameBoard[][])
void Player1::GetMove(int &roW, int &coL)
{	
	int terminal;	// alphabeta return value. terminal node
	int depth;		// determines search height in tree
	int alpha = -5000;	int beta = 5000;
	bool maxPlayer = true;
	int possibeMoves[365][3];	int moveCount = 0;

	//for (int i = 0; i < 365; i++)
	//	possibeMoves[i] = 0;		// initialize move array to 0
	
	recordMove bestMove;
	bestMove.row = bestMove.col = bestMove.heur = -1;

	boardsExamined = 0;	// reset total between moves

//--assign desired move to roW coL---

	if (boardSize == 0) // firstmove
	{
		roW = coL = 9;	// make first move in center of board
	}
	else
	{
		// for every 'E' on board
		for (int e = 0; e < 19; e++)		{
			for (int f = 0; f < 19; f++)		
			{
				bool detected = playerDetected(e,f);

				if (pOneBoard[e][f] == 'E' && detected)
				{
					// get hueristic value of terminal node of move
					// alphabeta(origin, depth, -infinity, +infinity, maxPlayer)
					depth = 0;
					terminal = alphaBeta(depth, alpha, beta, (maxPlayer)); 				
//-----------------
					boardsExamined++; // total recursive calls

					if (terminal > bestMove.heur || bestMove.col == -1)
					{
						bestMove.row = e;
						bestMove.col = f;
						bestMove.heur = terminal;
					}

					//if (terminal > 200)
					//	terminal++;

					possibeMoves[moveCount][0] = terminal;
					possibeMoves[moveCount][1] = e;
					possibeMoves[moveCount][2] = f;
					moveCount++;
				}
			}
		}

//-----------------
		if (boardsExamined > 0)
		{
			boardsExamined++; // total recursive calls
			boardsExamined--;
		}

  		roW = bestMove.row;		coL = bestMove.col;

	} // end else

	// possible assignments for roW and coL
	//roW = coL = 9;	// return a new val or f2() will overwrite
	//roW = 10;	coL = test1;	test1++;
	
	pOneBoard[roW][coL] = 'P'; // record your move
	boardSize++;

	// return roW and coL to interface
}

