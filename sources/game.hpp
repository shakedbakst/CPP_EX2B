#ifndef GAME_HPP
#define GAME_HPP
#include <iostream>
#include "player.hpp"
#include "card.hpp"
namespace ariel{};

using namespace std;

class Game{

    private:
        Player &pl1;
        Player &pl2;
        void shuffleStack(vector <Card> &stack);
        void resetStack(vector <Card> &stack);
        vector <Card> stack;
        vector <string> turns;
        int numRounds = 0;
        int numOfDraws = 0;
      

    public:
       
        Game(Player &pl1, Player &pl2);
        int dualTurn(Card card1, Card card2);
        int getRounds();
        void increaseRounds();
        void playTurn();
        void printLastTurn();
        void playAll();
        void printWiner();
        void printLog();
        void printStats();
        
};

#endif
