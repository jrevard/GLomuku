#include "Board.h"
#include <algorithm>
#include <assert.h>

using namespace std;

Board::Board() {
	pieceCount = 0;
	for (int row=0; row < BoardSize; row++)
		for (int col=0; col < BoardSize; col++)
			pieces[row][col] = PieceNone;
}

void BoundsCheck(int row, int col) {
	assert(row >= 0 && row < BoardSize);
	assert(col >= 0 && col < BoardSize);
}

void Board::SetPiece(int row, int col, Piece piece) {
	BoundsCheck(row, col);
	if (pieces[row][col] == PieceNone && piece != PieceNone) pieceCount++;
	pieces[row][col] = piece;
}

Piece Board::GetPiece(int row, int col) {
	BoundsCheck(row, col);
	return pieces[row][col];
}

bool Board::IsSolved(int row, int col, Winner &whoWon) {
	BoundsCheck(row, col);
	whoWon = WinnerNone;
	if (IsSolved(row, col, PiecePlayer1)) {
		whoWon = WinnerPlayer1;
	}
	if (IsSolved(row, col, PiecePlayer2)) {
		whoWon = WinnerPlayer2;
	}
	if (pieceCount == BoardSize*BoardSize) {
		whoWon = WinnerDraw;
	}
	return whoWon != WinnerNone;
}

bool Board::IsSolved(int pRow, int pCol, Piece piece) {
	int count;

	// Check horizontal
	count = 0;
	for (int i=0; i < BoardSize; i++) {
		if (pieces[pRow][i] == piece) count++;
		else count = 0;
		if (count == WinCount) return true;
	}

	// Check vertical
	count = 0;
	for (int i=0; i < BoardSize; i++) {
		if (pieces[i][pCol] == piece) count++;
		else count = 0;
		if (count == WinCount) return true;
	}

	int row, col;
	// Check Diagonal \ -- Start at the top left
	count = 0;
	col = max(pCol - pRow, 0);
	row = pRow - (pCol - col);
	while (row < BoardSize && col < BoardSize) {
		if (pieces[row][col] == piece) count++;
		else count = 0;
		if (count == WinCount) return true;
		row++;
		col++;
	}

	// Check Diagonal / -- Start at the top right
	count = 0;
	col = min(pCol + pRow, BoardSize-1);
	row = pRow - (col - pCol);
	while (row < BoardSize && col >= 0) {
		if (pieces[row][col] == piece) count++;
		else count = 0;
		if (count == WinCount) return true;
		row++;
		col--;
	}

	return false;
}