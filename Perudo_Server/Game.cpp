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
            const char* buffer = "Tout le monde est prêt";
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

bool Game::send_message()
{
    for (int i = 0; i < joueurs.size(); i++)
    {
        Output::GetInstance()->print("\n");
        Output::GetInstance()->print(allPlayersSocket.size());
        Output::GetInstance()->print("\n");
        if (send(allPlayersSocket.at(i), "test", strlen("test"), 0) == -1) 
        {
            char* error = new char[100];
#pragma warning(suppress : 4996) sprintf(error, "[PLAYER_%d] Error while sending message to client ", allPlayersId.at(i));
            Output::GetInstance()->print_error(error);
            Output::GetInstance()->print("\n");
            delete[] error;
            return false;
        }
    
    }
    return true;
}
*/