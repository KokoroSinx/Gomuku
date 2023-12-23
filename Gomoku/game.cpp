#include "game.h"
#include <graphics.h>

game::game(player* Player, AICom* ai, Chess* chess)
{
	this->Player = Player;
	this->ai = ai;
	this->chess = chess;

	Player->init(chess);
	ai->init(chess);
}

void game::play()
{	
	chess->init();
	while (true) {
		Player->go();
		if (chess->checkOver()) {
			chess->init();
			continue;
		}

		ai->go();
		if (chess->checkOver()) {
			chess->init();
			continue;
		}
	}
}
