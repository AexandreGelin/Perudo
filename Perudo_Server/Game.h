#pragma once
#include <vector>
#include "Player.h"
class Game
{

private:

public:

	Game();
	~Game();

	std::vector<Player*> joueurs;

	bool allPlayerReady();
};

