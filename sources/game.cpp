#include <iostream>
#include <stdio.h>
#include <string>
#include "game.hpp"
#include "player.hpp"
#include "card.hpp"
#include <vector>
#include <random>
#include <algorithm>
using namespace std;
using namespace ariel;


void Game::shuffleStack(vector <Card> &stack){
    random_device rd;
    mt19937 g(rd());
    shuffle(stack.begin(), stack.end(), g);
}

void Game::resetStack(vector <Card> &stack){
    string suit_1 = "Diamonds";
    string suit_2 = "Hearts";
    string suit_3 = "Spades";
    string suit_4 = "Clubs";

    for(int i=0 ; i<13 ; ++i){
        stack.push_back(Card(i+1, suit_1));
        stack.push_back(Card(i+1, suit_2));
        stack.push_back(Card(i+1, suit_3));
        stack.push_back(Card(i+1, suit_4));
    }

    shuffleStack(stack);

    for (unsigned long int i = 0; i < 52; ++i) {
        if (i%2 == 0) {
            pl1.insertCardesStack(stack[i]);
        } else {
            pl2.insertCardesStack(stack[i]);
        }
    }

}

Game::Game(Player &pl1, Player &pl2):pl1(pl1), pl2(pl2){
    pl1.setIsPlaying();
    pl2.setIsPlaying();
    resetStack(this->stack);
}

int Game::dualTurn(Card c1, Card c2){
    switch(c1.getnumber()){
        case 1:
            if(c2.getnumber() == 2){
                return -1;
            }
            else if(c2.getnumber() >= 3 && c2.getnumber() <= 13){
                return 1;
            }
            break;
        case 2:
            if(c2.getnumber() == 1){
                return 1;
            }
            else{
                return c1.getnumber() > c2.getnumber() ? 1 : -1;
            }
            break;
        default:
            if(c1.getnumber() > c2.getnumber()){
                return 1;
            }
            else if(c1.getnumber() < c2.getnumber()){
                return -1;
            }
            else{
                return 0;
            }
    }
    throw std::runtime_error("Error! problem with the cards");
}

int Game::getRounds(){
    return this->numRounds;
}

void Game::increaseRounds(){
    numRounds++;
}



void Game :: playTurn(){
    // preliminary checks
     if (&pl1 == &pl2){
        throw std::invalid_argument("Error! You need to change one of the players names");
    }
    
    if (numRounds > 26){
        throw std::runtime_error("Error! Game over");
    }
    
     if (pl1.cardesTaken() + pl2.cardesTaken() == 52){
        throw std::runtime_error("Error! Game over");
    }

    // play cards and get result
    Card c1 = pl1.cardPlay();
    Card c2 = pl2.cardPlay();
    int res = dualTurn(c1, c2);
    string s = pl1.getName() + " played " + c1.toString() +
        " " + pl2.getName() + " played " + c2.toString();

    // update game state based on result
    switch (res) {
        case 1:
            // Player 1 wins
            pl1.increaseWonCards();
            pl1.increaseWinnings();
            increaseRounds();
            turns.push_back(s + ". " + pl1.getName() + " wins.");
            break;

        case -1:
            // Player 2 wins
            pl2.increaseWonCards();
            pl2.increaseWinnings();
            increaseRounds();
            turns.push_back(s + ". " + pl2.getName() + " wins.");
            break;

        default:
            // Tie - continue playing until winner is found
            int numOfTies = 0;
            while (res == 0) {
                // Draw
                s += ". Draw.";
                numOfTies++;

                // Check for empty deck
                if (pl1.stacksize() == 0) {
                    for (int i = 0; i < numOfTies - 1; i++) {
                        pl1.increaseWonCards();
                        pl2.increaseWonCards();
                    }
                    pl1.addWonCard();
                    pl2.addWonCard();
                    increaseRounds();
                    return;
                }
                // Check for one card left in the deck
                if (pl1.stacksize() == 1) {
                    pl1.cardPlay();
                    pl2.cardPlay();
                    for (int i = 0; i < numOfTies; i++) {
                        pl1.increaseWonCards();
                        pl2.increaseWonCards();
                    }
                    return;
                }
                if (pl1.stacksize() >= 2){
                    pl1.cardPlay();
                    pl2.cardPlay();
                }
                
                // Play additional cards and determine new result
                Card cp1 = pl1.cardPlay();
                Card cp2 = pl2.cardPlay();
                res = dualTurn(cp1, cp2);
                s += " " + pl1.getName() + " played " + cp1.toString() + " " +
                         pl2.getName() + " played " + cp2.toString();
            }

            numOfDraws = numOfDraws + numOfTies;
            
            if(res == 1){
            	pl1.increaseWonCards();
            	for(int i=1 ; i<=numOfTies ; i++){
            		pl1.increaseWonCards();
            		increaseRounds();
            	}
            
            	turns.push_back(s+". "+pl1.getName()+"wins.");
            	pl1.increaseWinnings();
            }else if(res == -1){
            	pl2.increaseWonCards();
            	for(int i=1 ; i<=numOfTies ; i++){
            		pl2.increaseWonCards();
            		increaseRounds();
            	}
            	
            	turns.push_back(s+". "+pl2.getName()+"wins.");
            	pl2.increaseWinnings();
            }
            break;	
    }
}

void Game :: printLastTurn(){
     cout << turns.back() << endl;
}

void Game :: playAll(){
    if(pl1.stacksize() == 0 && pl2.stacksize() == 0){
        throw std::logic_error("Error! Game over");
    }
    while(this->pl1.stacksize() != 0 && this->pl2.stacksize() != 0){
        playTurn();
    }
}

void Game :: printWiner(){
    if(pl1.cardesTaken() > pl2.cardesTaken()){
        cout << pl1.getName() << "Won!" <<endl;
        printLastTurn();
    }
    else if(pl1.cardesTaken() < pl2.cardesTaken()){
        cout << pl2.getName() << "Won!" <<endl;
        printLastTurn();
    }
    else if(pl1.cardesTaken() == pl2.cardesTaken()){
        cout << "There is no winner! It is a tie!" << endl;
    }
}

void Game :: printLog(){
    for(unsigned long int i=0 ; i<turns.size(); i++){
        string str = turns[i];
        cout << str << endl;
    }
}

void Game :: printStats(){
    cout << pl1.getName() << "won" << pl1.cardesTaken() << "cards." <<endl;
    cout << pl2.getName() << "won" << pl2.cardesTaken() << "cards." <<endl;
    cout << "There was" << numOfDraws << "draws that happend." << endl;
}




