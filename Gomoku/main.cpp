/*
	Development Dairy
	1. Create Project, Add resource
	2. Design Framework of Project(class)
*/
#include <iostream>
#include "game.h"

int main() {
	player Player;
	Chess chess(13, 40, 40, 68.33);
	AICom ai;
	game Game(&Player, &ai, &chess);
	Game.play();

	return 0;
}