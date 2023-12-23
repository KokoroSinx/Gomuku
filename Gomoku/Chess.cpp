#include "Chess.h"

void Chess::init()
{
	//Create Game Window
	initgraph(897, 895);

	//show Main Menu
	loadimage(&Menu, _T("res/MainMenu.jpg"), 897, 895, true);
	//putimage(0, 0, &Menu);
	//_getch(); 
	
	//Show ChessBoard
	loadimage(&chessBoardImg, _T("res/∆Â≈Ã2.jpg"));
	putimage(0, 0, &chessBoardImg);
	//Play Sound
	mciSendString(_T("play res/start.WAV"), 0, 0, 0);

	//load Chess
	loadimage(&chessBlackImg, L"res/black.png", chessSize, chessSize, true);
	loadimage(&chessWhiteImg, L"res/white.png", chessSize, chessSize, true);

	//once more
	for (int i = 0; i < chessMap.size(); i++) {
		for (int j = 0; j < chessMap[0].size(); j++) {
			chessMap[i][j] = 0;
		}
	}
	turn = true;
}

bool Chess::clickBoard(int x, int y, ChessPos* pos)
{
	int col = (x - margin_x) / chessSize;
	int row = (y - margin_y) / chessSize;
	int leftTopPosX = margin_x + chessSize * col;
	int leftTopPosY = margin_y + chessSize * row;
	int offset = chessSize * 0.4;

	int len;
	bool ret = false;

	do {
		len = sqrt((x - leftTopPosX) * (x - leftTopPosX) + (y - leftTopPosY) * (y - leftTopPosY));
		if (len < offset) {
			pos->row = row;
			pos->col = col;
			if (chessMap[pos->row][pos->col] == 0) {
				ret = true;
			}
			break;
		}

		int x2 = leftTopPosX + chessSize;
		int y2 = leftTopPosY;
		len = sqrt((x - x2) * (x - x2) + (y - y2) * (y - y2));
		if (len < offset) {
			pos->row = row;
			pos->col = col + 1;
			if (chessMap[pos->row][pos->col] == 0) {
				ret = true;
			}
			break;
		}

		x2 = leftTopPosX;
		y2 = leftTopPosY + chessSize;
		len = sqrt((x - x2) * (x - x2) + (y - y2) * (y - y2));
		if (len < offset) {
			pos->row = row + 1;
			pos->col = col;
			if (chessMap[pos->row][pos->col] == 0) {
				ret = true;
			}
			break;
		}

		x2 = leftTopPosX + chessSize;
		y2 = leftTopPosY + chessSize;
		len = sqrt((x - x2) * (x - x2) + (y - y2) * (y - y2));
		if (len < offset) {
			pos->row = row + 1;
			pos->col = col + 1;
			if (chessMap[pos->row][pos->col] == 0) {
				ret = true;
			}
			break;
		}
	} while (0);

	return ret;
}

void Chess::chessDown(ChessPos* pos, chess_kind_t kind)
{
	int x = margin_x + chessSize * pos->col - 0.5 * chessSize;
	int y = margin_y + chessSize * pos->row - 0.5 * chessSize;

	if (kind == CHESS_WHITE) {
		putimagePNG(x, y, &chessWhiteImg);
	}
	else {
		putimagePNG(x, y, &chessBlackImg);
		mciSendString(L"play res/down7.WAV", 0, 0, 0);
	}

	updateGameMap(pos);
}

int Chess::getGradeSize()
{
	return gradeSize;
} 

bool Chess::checkOver()
{
	if (checkWin()) {
		Sleep(1500);
		if (turn == false) {
			//black win
			mciSendString(_T("play res/Victory.mp3"), 0, 0, 0);
			loadimage(0, _T("res/victory.jpg"));
		}
		else {
			mciSendString(_T("play res/Lose.mp3"), 0, 0, 0);
			loadimage(0, _T("res/lose.jpg"));
		}

		_getch();//pause
		return true;
	}

	return false;
}

int Chess::getChessData(ChessPos* pos) {
	return chessMap[pos->row][pos->col];
}

int Chess::getChessData(int row, int col)
{
	return chessMap[row][col];
}

void Chess::updateGameMap(ChessPos* pos)
{	
	lastPos = *pos;
	chessMap[pos->row][pos->col] = turn ? CHESS_BLACK : CHESS_WHITE;
	turn = !turn; //change turn
}

bool Chess::checkWin()
{	
	//Position of the last chessdown
	int row = lastPos.row;
	int col = lastPos.col;

	//left & right check
	for (int i = 0; i < 5; i++)
	{
		// for ith
		//i=0 (row,col) (row,col+1) (row,col+2) (row,col+3) (row,col+4)
		if (col - i >= 0 && col - i + 4 < gradeSize &&
			chessMap[row][col - i] == chessMap[row][col - i + 1] &&
			chessMap[row][col - i] == chessMap[row][col - i + 2] &&
			chessMap[row][col - i] == chessMap[row][col - i + 3] &&
			chessMap[row][col - i] == chessMap[row][col - i + 4])
		{
			return true;
		}
	}
	//up && down
	for (int i = 0; i < 5; i++)
	{
		if (row - i >= 0 && row - i + 4 < gradeSize &&
			chessMap[row - i][col] == chessMap[row - i + 1][col] &&
			chessMap[row - i][col] == chessMap[row - i + 2][col] &&
			chessMap[row - i][col] == chessMap[row - i + 3][col] &&
			chessMap[row - i][col] == chessMap[row - i + 4][col])
		{
			return true;
		}
	}

	// 45
	for (int i = 0; i < 5; i++)
	{
		if (row + i < gradeSize && row + i - 4 >= 0 &&
			col - i >= 0 && col - i + 4 < gradeSize &&
			chessMap[row + i][col - i] == chessMap[row + i - 1][col - i + 1] &&
			chessMap[row + i][col - i] == chessMap[row + i - 2][col - i + 2] &&
			chessMap[row + i][col - i] == chessMap[row + i - 3][col - i + 3] &&
			chessMap[row + i][col - i] == chessMap[row + i - 4][col - i + 4]) {
			return true;
		}
	}

	for (int i = 0; i < 5; i++)
	{
		if (row - i >= 0 && row - i + 4 < gradeSize &&
			col - i >= 0 && col - i + 4 < gradeSize &&
			chessMap[row - i][col - i] == chessMap[row - i + 1][col - i + 1] &&
			chessMap[row - i][col - i] == chessMap[row - i + 2][col - i + 2] &&
			chessMap[row - i][col - i] == chessMap[row - i + 3][col - i + 3] &&
			chessMap[row - i][col - i] == chessMap[row - i + 4][col - i + 4]) {
			return true;
		}
	}

	return false;
}
