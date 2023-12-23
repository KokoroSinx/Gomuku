#pragma once
#include "Chess.h"
class AICom
{
public:
	void init(Chess* chess);
	void go();
private:
	Chess* chess;
	std::vector<std::vector<int>> scoreMap;

	void calculateScore();
	ChessPos think();
};

 