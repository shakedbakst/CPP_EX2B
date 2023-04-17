#ifndef CARD_HPP
#define CARD_HPP
#include "iostream"
#include "stdio.h"
using namespace std;
namespace ariel{};

class Card{
    private:
        int number;
        string suit;

    public:
        Card();
        Card(int number, string suit);
        int getnumber();
        string getsuit();
        string toString();
};

#endif
