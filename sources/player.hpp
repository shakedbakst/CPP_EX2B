#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <iostream>
#include <string>
#include <vector>
#include"card.hpp"
using namespace std;
namespace ariel{};

class Player{

    private:
        string name;
        int wonCards = 0;
        int winnings = 0;
        bool isPlaying = false;
        vector <Card> PlayerStack;
        

    public:
        
        Player(string pName);
        string getName() const;
        int stacksize();
        int cardesTaken();
        Card cardPlay();
        void insertCardesStack(Card card);
        int getWinnings();
        void addWonCard();
        bool getIsPlaying();
        void setIsPlaying();
        void increaseWonCards();
        void increaseWonCardDraw();
        void increaseWinnings();

};

#endif
