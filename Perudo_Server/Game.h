#pragma once
#include <vector>
#include "Player.h"

class Game
{

private:

	static Game* singleton_;

	int nbDiceMisee;
	int typeDyceMisee;
	int idJoueurEnCours;

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

	void StartGame();

	void GetMise(int dice, int type, int idJoueur);

	//std::vector<int> GetAllPlayerId();
	//std::vector<SOCKET> getAllSocket(); 
	//bool send_message();

};

