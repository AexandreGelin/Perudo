#include "Game.h"
#include "EndPoint.h"
#include <iostream>
#include "Output.h"

Game* Game::singleton_ = nullptr;

Game::Game()
{

}


Game* Game::GetInstance()
{
    if (singleton_ == nullptr) {
        singleton_ = new Game();
    }
    return singleton_;
}

Game::~Game()
{

}

bool Game::allPlayerReady()
{
    /*Output::GetInstance()->print("\n Nombre de joueurs dans allPlayerReady : \n");
    Output::GetInstance()->print(joueurs.size());
    Output::GetInstance()->print("\n");*/
    int nbPlayerReady = 0;

    for (std::vector<Player*>::iterator it = joueurs.begin(); it != joueurs.end(); ++it)
    {
        //Output::GetInstance()->print((*it)->checkReady());
        if ((*it)->checkReady() == 1)
        {
            nbPlayerReady++;
        }
    }

    if (joueurs.size() == nbPlayerReady)
    {
        for (std::vector<Player*>::iterator it = joueurs.begin(); it != joueurs.end(); ++it)
        {
            Output::GetInstance()->print("ENVOIS du message all ready \n");
            SOCKET socket = (*it)->getSocketPlayer();
            const char* buffer = "Tout le monde est pr�t";
            send(socket, buffer, strlen(buffer), 0);

        }
        return true;
    }
    else
    {
        return false;
    }

}

void Game::AddPlayers(Player* p)
{
    joueurs.push_back(p);
    Output::GetInstance()->print("jsuis la \n", joueurs.at(0)->getSocketPlayer(), "\n");
}

/*std::vector<int> Game::GetAllPlayerId()
{
    for (std::vector<Player*>::iterator it = joueurs.begin(); it != joueurs.end(); ++it)
    {
        allPlayersId.push_back((*it)->getIdPlayer());
    }

    return allPlayersId;
}

std::vector<SOCKET> Game::getAllSocket()
{
    for (std::vector<Player*>::iterator it = joueurs.begin(); it != joueurs.end(); ++it)
    {
        allPlayersSocket.push_back((*it)->getSocketPlayer());
    }

    return allPlayersSocket;

}

*/

void Game::StartGame()
{
    for (std::vector<Player*>::iterator it = joueurs.begin(); it != joueurs.end(); ++it)
    {
        (*it)->giveDice(6);
    }
}

void Game::GetMise(int dice, int type, int id)
{
    nbDiceMisee = dice;
    typeDyceMisee = type;
    idJoueurEnCours = id;

    Output::GetInstance()->print("\n");
    Output::GetInstance()->print(nbDiceMisee);
    Output::GetInstance()->print("\n");
    Output::GetInstance()->print(typeDyceMisee);
    Output::GetInstance()->print("\n");
    Output::GetInstance()->print(idJoueurEnCours);
}