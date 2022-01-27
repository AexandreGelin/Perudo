#pragma once
#include <vector>
#include "Player.h"
#include "Semaphore.h"

class Game
{

private:

	static Game* singleton_;

public:

	Game();
	~Game();

	std::vector<Player*> joueurs;

	std::vector<SOCKET> allPlayersSocket;

	std::vector<int> allPlayersId;

	std::vector<CSemaphore*> sems;

	int currentPlayer;

	static Game* GetInstance();
	void AddPlayers(Player* p);
	bool allPlayerReady();
	//std::vector<int> GetAllPlayerId();
	//std::vector<SOCKET> getAllSocket(); 
	//bool send_message();
	void startGame();

};

