#pragma once
#include <vector>
#include "Player.h"

class Game
{

private:

	static Game* singleton_;

public:

	Game();
	~Game();

	std::vector<Player*> joueurs;

	bool allPlayerReady();

	void AddPlayers(std::vector<Player*> players);

	static Game* GetInstance();

};

