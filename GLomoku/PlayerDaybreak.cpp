#include "PlayerDaybreak.h"
#include <algorithm>

using namespace std;

PlayerDaybreak::PlayerDaybreak() {
	_row = 10;
}

class RunCheck
{
	private:
	static const int MinPlayerCount = 3;
	int allCount, playerCount;
	int lastEmptyRow, lastEmptyCol;
	Board *board;

	void ResetCounts() {
		allCount = playerCount = 0;
		lastEmptyRow = lastEmptyCol = -1;
	}

	public:
	RunCheck(Board *board) {
		this->board = board;
		ResetCounts();
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
			ResetCounts();
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
	// Check horizontal
	for (int row=0; row < BoardSize; row++) {
		RunCheck check(&board);
		for (int col=0; col < BoardSize; col++) {
			if (check.Check(row, col, oRow, oCol)) return true;
		}
	}

	// Check vertical
	for (int col=0; col < BoardSize; col++) {
		RunCheck check(&board);
		for (int row=0; row < BoardSize; row++) {
			if (check.Check(row, col, oRow, oCol)) return true;
		}
	}

	// Check Diagonal \ -- Start at the top left
	for (int pRow = 0; pRow < BoardSize; pRow++) {
		RunCheck check(&board);
		int row = pRow;
		int col = 0;
		while (row < BoardSize && col < BoardSize) {
			if (check.Check(row, col, oRow, oCol)) return true;
			row++;
			col++;
		}
	}
	for (int pCol = 0; pCol < BoardSize; pCol++) {
		RunCheck check(&board);
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
		RunCheck check(&board);
		int row = pRow;
		int col = BoardSize-1;
		while (row < BoardSize && col >= 0) {
			if (check.Check(row, col, oRow, oCol)) return true;
			row++;
			col--;
		}
	}
	for (int pCol = BoardSize-1; pCol >= 0; pCol--) {
		RunCheck check(&board);
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

void GetRandom(int &row, int &col) {
}

void PlayerDaybreak::OpponentDidMove(int row, int col) {
	board.SetPiece(row, col, PiecePlayer2);
}
void PlayerDaybreak::GetMove(int &row, int &col) {
	if (!IsPlayerRow3(row, col)) {
		row = _row++;
		col = 0;
	}
	board.SetPiece(row, col, PiecePlayer1);
}