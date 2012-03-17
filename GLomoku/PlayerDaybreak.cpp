#include "PlayerDaybreak.h"

PlayerDaybreak::PlayerDaybreak() {
	_row = 10;
}

void PlayerDaybreak::OpponentDidMove(int row, int col) {
}
void PlayerDaybreak::GetMove(int &row, int &col) {
	row = _row++;
	col = 0;
}