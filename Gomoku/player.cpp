#include "player.h"

void player::init(Chess* chess)
{
	this->chess = chess;
}

void player::go()
{
	MOUSEMSG msg;  
	ChessPos pos;

	while (true) {
		msg = GetMouseMsg();
		if (msg.uMsg == WM_LBUTTONDOWN && chess->clickBoard(msg.x, msg.y, &pos)) {
			break;
		}
	}
	//printf("%d,%d\n", pos.row, pos.col);
	chess->chessDown(&pos, CHESS_BLACK);
}
