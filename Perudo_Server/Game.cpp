#include "Game.h"
#include "EndPoint.h"
#include <iostream>
#include "Output.h"

Game::Game()
{
    
}

Game::~Game()
{

}

bool Game::allPlayerReady()
{ 
    
    Output::GetInstance()->print("\n\n\n");
    Output::GetInstance()->print(joueurs.size());

    for (std::vector<Player*>::iterator it = joueurs.begin(); it != joueurs.end(); ++it) {
        Output::GetInstance()->print((*it)->checkReady());
    }

    return false;
}