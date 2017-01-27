#include "game.h"
#include "pile.h"
#include "card.h"
#include "winningdialog.h"
#include "cardmove.h"

//------------------------------------------------|
Game::Game(QWidget *par)
    :parent(par)
{

}
//------------------------------------------------|
Game::~Game()
{
    Clear();
}

//------------------------------------------------|
void Game::Clear()
{

}
//------------------------------------------------|
void Game::AddPile(Pile *p)
{
    piles.append(p);
}

//------------------------------------------------|
bool Game::PlayOff(Card *c){
    //TODO
    return false;
}

//------------------------------------------------|
void Game::PlayOffAll(){
    //TODO
}

//------------------------------------------------|
void Game::CheckWin(){
    //TODO
}

//------------------------------------------------|
