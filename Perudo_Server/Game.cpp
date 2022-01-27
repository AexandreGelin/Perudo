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
    Output::GetInstance()->print("\n Nombre de joueurs dans allPlayerReady : \n");
    Output::GetInstance()->print(joueurs.size());
    Output::GetInstance()->print("\n");

    for (std::vector<Player*>::iterator it = joueurs.begin(); it != joueurs.end(); ++it) {
        Output::GetInstance()->print((*it)->checkReady());
    }

    return false;
}

void Game::AddPlayers(std::vector<Player*> players)
{
    //joueurs.push_back(p);
    //Output::GetInstance()->print("Nombre de joueurs après add : ");
    //Output::GetInstance()->print(joueurs.size());

    //Output::GetInstance()->print(players.size());
    joueurs = players;

    //Output::GetInstance()->print(joueurs.size());
}