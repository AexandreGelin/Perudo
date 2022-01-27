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

	void AddPlayers(Player* p);

	std::vector<int> StartGame(std::vector<int> allPlayersId);

	static Game* GetInstance();

};

