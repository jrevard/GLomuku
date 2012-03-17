#ifndef BOARD_H
#define BOARD_H

typedef enum {
	PieceNone,
	PiecePlayer1,
	PiecePlayer2
} Piece;

typedef enum {
	WinnerNone,
	WinnerPlayer1,
	WinnerPlayer2,
	WinnerDraw
} Winner;

// Board class is used to check for winners

class Board
{
	public:
	static const int Size = 19;
	static const int WinCount = 5;

	Board();
	void SetPiece(int row, int col, Piece piece);
	Piece GetPiece(int row, int col);
	
	// Checks to see if there was a winner at a position
	// Returns true if game is over
	bool IsSolved(int row, int col, Winner &whoWon);

	private:
	Piece pieces[Size][Size];
	bool IsSolved(int row, int col, Piece piece);
	int pieceCount;
};

#endif