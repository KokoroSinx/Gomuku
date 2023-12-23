#pragma once
#include <graphics.h>
#include <mmsystem.h>
#include "tools.h"
#pragma comment(lib, "winmm.lib")
#include <vector>
#include <conio.h>

struct ChessPos {
	int row, col;

	ChessPos(int r = 0, int c = 0):row(r),col(c){}
};
        
typedef enum {
	CHESS_WHITE = -1,
	CHESS_BLACK = 1
}chess_kind_t;

class Chess
{
public:
	Chess(int gradeSize, int marginX, int marginY, float chessSize) {
		this->gradeSize = gradeSize;
		this->margin_x = marginX;
		this->margin_y = marginY;
		this->chessSize = chessSize;
		turn = CHESS_BLACK;

		for (int i = 0; i < gradeSize; i++)
		{
			std::vector<int> row;
			for (int j = 0; j < gradeSize; j++)
			{
				row.push_back(0);
			}
			chessMap.push_back(row);
		}
	}

	void init();
	bool clickBoard(int x, int y, ChessPos* pos);
	void chessDown(ChessPos* pos, chess_kind_t kind);
	int getGradeSize();//is this necessary?
	bool checkOver();
	int getChessData(ChessPos* pos);
	int getChessData(int row, int col);
private:
	IMAGE chessBlackImg;
	IMAGE chessWhiteImg;
	IMAGE chessBoardImg;
	IMAGE Menu;

	int gradeSize;
	int margin_x, margin_y;
	float chessSize;

	std::vector<std::vector<int>> chessMap;

	bool turn; //true: black false: white

	void updateGameMap(ChessPos* pos);

	bool checkWin(); //If end, return true, else return false.

	ChessPos lastPos;
};

