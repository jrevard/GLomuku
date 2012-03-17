#include "Board.h"

Board::Board() {
	pieceCount = 0;
	for (int row=0; row < Size; row++)
		for (int col=0; col < Size; col++)
			pieces[row][col] = PieceNone;
}

void Board::SetPiece(int row, int col, Piece piece) {
	pieces[row][col] = piece;
	pieceCount++;
}

bool Board::IsSolved(int row, int col, Winner &whoWon) {
	whoWon = WinnerNone;
	if (IsSolved(row, col, PiecePlayer1)) {
		whoWon = WinnerPlayer1;
	}
	if (IsSolved(row, col, PiecePlayer2)) {
		whoWon = WinnerPlayer2;
	}
	if (pieceCount == Size*Size) {
		whoWon = WinnerDraw;
	}
	return whoWon != WinnerNone;
}

int max(int a, int b) {
	return (a > b) ? a : b;
}
int min(int a, int b) {
	return (a < b) ? a : b;
}

bool Board::IsSolved(int pRow, int pCol, Piece piece) {
	int count;

	// Check horizontal
	count = 0;
	for (int i=0; i < Size; i++) {
		if (pieces[pRow][i] == piece) count++;
		else count = 0;
		if (count == WinCount) return true;
	}

	// Check vertical
	count = 0;
	for (int i=0; i < Size; i++) {
		if (pieces[i][pCol] == piece) count++;
		else count = 0;
		if (count == WinCount) return true;
	}

	int row, col;
	// Check Diagonal \ -- Start at the top left
	count = 0;
	col = max(pCol - pRow, 0);
	row = pRow - (pCol - col);
	while (row < Size && col < Size) {
		if (pieces[row][col] == piece) count++;
		else count = 0;
		if (count == WinCount) return true;
		row++;
		col++;
	}

	// Check Diagonal / -- Start at the top right
	count = 0;
	col = min(pCol + pRow, Size-1);
	row = pRow - (col - pCol);
	while (row < Size && col >= 0) {
		if (pieces[row][col] == piece) count++;
		else count = 0;
		if (count == WinCount) return true;
		row++;
		col--;
	}

	return false;
}