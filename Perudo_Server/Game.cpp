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

std::vector<int> Game::StartGame(std::vector<int> allPlayersId)
{
    for (std::vector<Player*>::iterator it = joueurs.begin(); it != joueurs.end(); ++it)
    {
        allPlayersId.push_back((*it)->getIdPlayer());
    }

    return allPlayersId;
}