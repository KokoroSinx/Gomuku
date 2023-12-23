#pragma once
#include "player.h"
#include "AICom.h"
#include "Chess.h"

class game
{
public:
	game(player* Player, AICom* ai, Chess* chess);
	void play(); //start
private:
	player* Player;
	AICom* ai;
	Chess* chess;
}; 