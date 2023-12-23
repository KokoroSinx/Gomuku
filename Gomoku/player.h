#pragma once
#include "AICom.h"
class player
{
public:
	void init(Chess* chess);
	void go();

private:
	Chess* chess;
};

