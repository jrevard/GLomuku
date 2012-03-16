
// Player 1 color = 'P' for purple
// Player 2 color = 'T'	for tan

#include <algorithm>
#include "Player1.h"

int test1 = 10;
int boardSize = 0;

char pOneBoard[19][19] = { 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', // 0
						   'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', // 1
						   'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', // 2
						   'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', // 3
						   'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', // 4
						   'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', // 5
						   'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', // 6
						   'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', // 7
						   'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', // 8
						   'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', // 9
						   'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', // 10
						   'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', // 11
						   'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', // 12
						   'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', // 13
						   'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', // 14
						   'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', // 15
						   'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', // 16
						   'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', // 17
						   'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E'};// 18

//--------------------------------------------------------------


bool isSolved(char &whoWon) // 5 in a row?
{
	int l, m, line, row;	bool victory = false;
	char evaluate = 'X';	// alternate between 'P' and 'T'

// HORIZONTAL check for ROWS for win

	for (l = 0; l < 19; l++)
	{
		line = 0;	// reset every new row

		for (m = 0; m < 19; m++)
		{
			if (pOneBoard[l][m] == 'E') line = 0; // holes reset line

			if (pOneBoard[l][m] == 'P')
			{
				if (evaluate == 'P') line++;	// line already started
				else				{
					evaluate = 'P';	 // start new line
					line = 1;		}
			}
			else if (pOneBoard[l][m] == 'T')
			{
				if (evaluate == 'T') line++; // line already started
				else				{
					evaluate = 'T';	 // start new line
					line = 1;		}
			}

			if (line == 5)			{
				victory = true;	
				whoWon = evaluate;
				return victory;		}
		}
	}

// VERTICAL check for COLUMNS for wins 
	
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

			if (line == 5)			{
				victory = true;
				whoWon = evaluate;
				return victory;		}
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

			if (line == 5){
				victory = true;
				whoWon = evaluate;
				return victory;}

			row++;	
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

			if (line == 5){
				victory = true;
				whoWon = evaluate;
				return victory;}

			row--;
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

			if (line == 5){
				victory = true;
				whoWon = evaluate;
				return victory;}

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

			if (line == 5)			{
				victory = true;
				whoWon = evaluate;
				return victory;		}

			row--;	}}

	return victory;
}


//--------------------------------------------------------------

// restrict game moves to those within n blocks of opponent 

bool enemyDetected(int row, int col)
{
	for (int p = row - 4; p < row + 4; p++){
		for (int q = col - 4; q < col + 4; q++)
		{
			if (0 <= p && p < 19) {		// in range
				if (0 <= q && q < 19)	// in range
				{
					if (pOneBoard[p][q] == 'T')
						return true;
				}}}}

	return false;
}

//--------------------------------------------------------------

// if solved heuristic = 400 - depth*2 

int getHeuristic (int depth, char winner, bool MAXplayer)
{
	int heu;

/*
	if (winner == 'P' || winner == 'T') 
		heu = 400 - depth * 2;
	else
		heu = 100;
*/


	if (winner == 'P') 
	{
		heu = 400 + depth * 2;
	}
	else if (winner == 'T')
	{
		heu = -400 - depth * 2;
	}
	else if (MAXplayer)
	{
		// search for runs of 3, blocks of 2 ...

		// temp val
		heu = 200; // intermediate board
	}
	else
	{
		heu = -200; // intermediate board
	}

	return heu;
}

//--------------------------------------------------------------

// depth - a cap on how low the search reaches in the tree

// function alphabeta(node, depth, α, β, Player)      
int alphaBeta (int depth, int alpha, int beta, bool MAXplayer)
{
	int heuristic = 0;	int temp;	char winner = 'N'; // 'N' for NULL
	   
    if (depth == 10 || isSolved(winner) ) // or node is a terminal node
	{
		heuristic = getHeuristic(depth, winner, MAXplayer);
        return heuristic;// the heuristic value of node
	}
	
    if (MAXplayer)	//for each child of node
	{ 
		for (int p = 0; p < 19; p++){
			for (int q = 0; q < 19; q++)
			{
				if (pOneBoard[p][q] == 'E') // && enemyDetected(p,q))
				{
					// make move on board
					pOneBoard[p][q] = 'P';

					//alpha = max(alpha, alphaBeta(depth+1, alpha, beta, !MAXplayer ));     
					temp = alphaBeta(depth+1, alpha, beta, !(MAXplayer)); 

					if (temp > alpha)	
						alpha = temp;

					if (beta <= alpha)	
					{
						pOneBoard[p][q] = 'E';
						break; // (* Beta cut-off *)
					}
					else
					{
						// unmake move on board
						pOneBoard[p][q] = 'E';
					}

				}}}

		return alpha;	// α
	}
    else	//for each child of node
	{    
		for (int p = 0; p < 19; p++){
			for (int q = 0; q < 19; q++)
			{
				if (pOneBoard[p][q] == 'E') // && enemyDetected(p,q))
				{
					// make move on board
					pOneBoard[p][q] = 'T';

					// β := min(β, alphabeta(depth+1, α, β, not(Player) ))     
					temp = alphaBeta(depth+1, alpha, beta, !(MAXplayer)); 

					if (temp < beta)	
						beta = temp;
          
					if (beta <= alpha)	
					{
						//pOneBoard[p][q] = 'E';
						break; // (* Alpha cut-off *)
					}
					else
					{
						// unmake move on board
						pOneBoard[p][q] = 'E';
					}
				}}}

		return beta;	// β 
	}
}

//--------------------------------------------------------------


//http://en.wikipedia.org/wiki/Alpha-beta_pruning


// returns x and y vals ranging 0-18 (coord's for gameBoard[][])
void playerOne(int &roW, int &coL)
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

	if (roW >= 0 && coL >=0)		// if not first game move
	{
		pOneBoard[roW][coL] = 'T';	// record opponents move
		boardSize++;
	}

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
				if (f == 12 && e == 9)
					depth = 0;

				bool detected = enemyDetected(e,f);

				if (pOneBoard[e][f] == 'E')// && detected)
				{
					// make move on board
					//pOneBoard[e][f] = 'P';
				
					// get hueristic value of terminal node of move
					// alphabeta(origin, depth, -infinity, +infinity, maxPlayer)
					depth = 0;
					terminal = alphaBeta(depth, alpha, beta, (maxPlayer)); 
				
					if (moveCount == 0)

					if (terminal < bestMove.heur || bestMove.col == -1)
					{
						bestMove.row = e;
						bestMove.col = f;
						bestMove.heur = terminal;
					}

					possibeMoves[moveCount][0] = terminal;
					possibeMoves[moveCount][1] = e;
					possibeMoves[moveCount][2] = f;
					moveCount++;

					// unmake move on board
					//pOneBoard[e][f] = 'E';
				}
			}
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

