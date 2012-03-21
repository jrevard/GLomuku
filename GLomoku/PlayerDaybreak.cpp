#include "PlayerDaybreak.h"
#include <algorithm>
#include <time.h>
#include <stdlib.h>

using namespace std;

PlayerDaybreak::PlayerDaybreak() {
	srand((unsigned int)time(NULL));
}

class CountCheck
{
	private:
	static const int MinPlayerCount = 3;
	int allCount, playerCount;
	int lastEmptyRow, lastEmptyCol;
	Board *board;

	public:
	CountCheck(Board *board) {
		this->board = board;
		Reset();
	}

	void Reset() {
		allCount = playerCount = 0;
		lastEmptyRow = lastEmptyCol = -1;
	}

	bool Check(int row, int col, int &oRow, int &oCol) {
		Piece piece = board->GetPiece(row, col);
		if (piece == PiecePlayer2 || piece == PieceNone) {
			allCount++;
			if (piece == PiecePlayer2) playerCount++;
			if (piece == PieceNone) {
				lastEmptyRow = row;
				lastEmptyCol = col;
			}
		} else {
			Reset();
		}
		if (allCount >= WinCount && playerCount >= MinPlayerCount) {
			oRow = lastEmptyRow;
			oCol = lastEmptyCol;
			return true;
		}
		return false;
	}
};

bool PlayerDaybreak::IsPlayerRow3(int &oRow, int &oCol) {
	CountCheck check(&board);

	// Check horizontal
	for (int row=0; row < BoardSize; row++) {
		check.Reset();
		for (int col=0; col < BoardSize; col++) {
			if (check.Check(row, col, oRow, oCol)) return true;
		}
	}

	// Check vertical
	for (int col=0; col < BoardSize; col++) {
		check.Reset();
		for (int row=0; row < BoardSize; row++) {
			if (check.Check(row, col, oRow, oCol)) return true;
		}
	}

	// Check Diagonal \ -- Start at the top left
	for (int pRow = 0; pRow < BoardSize; pRow++) {
		check.Reset();
		int row = pRow;
		int col = 0;
		while (row < BoardSize && col < BoardSize) {
			if (check.Check(row, col, oRow, oCol)) return true;
			row++;
			col++;
		}
	}
	for (int pCol = 0; pCol < BoardSize; pCol++) {
		check.Reset();
		int row = 0;
		int col = pCol;
		while (row < BoardSize && col < BoardSize) {
			if (check.Check(row, col, oRow, oCol)) return true;
			row++;
			col++;
		}
	}

	// Check Diagonal / -- Start at the top right
	for (int pRow = 0; pRow < BoardSize; pRow++) {
		check.Reset();
		int row = pRow;
		int col = BoardSize-1;
		while (row < BoardSize && col >= 0) {
			if (check.Check(row, col, oRow, oCol)) return true;
			row++;
			col--;
		}
	}
	for (int pCol = BoardSize-1; pCol >= 0; pCol--) {
		check.Reset();
		int row = 0;
		int col = pCol;
		while (row < BoardSize && col >= 0) {
			if (check.Check(row, col, oRow, oCol)) return true;
			row++;
			col--;
		}
	}

	return false;
}

void PlayerDaybreak::GetRandom(int &row, int &col) {
	do {
		row = rand() % BoardSize;
		col = rand() % BoardSize;
	} while (board.GetPiece(row, col) != PieceNone);
}

void PlayerDaybreak::OpponentDidMove(int row, int col) {
	board.SetPiece(row, col, PiecePlayer2);
}
void PlayerDaybreak::GetMove(int &row, int &col) {
	if (!IsPlayerRow3(row, col)) {
		GetRandom(row, col);
	}
	board.SetPiece(row, col, PiecePlayer1);
}