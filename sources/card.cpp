#include <iostream>
#include <string>
#include "card.hpp"
using namespace std;
using namespace ariel;

Card::Card (int number, string suit){
    this->number = number;
    this->suit = suit;
}

int Card::getnumber(){
    return this->number;
}

string Card::getsuit(){
    return this->suit;
}

string Card::toString(){
    string num = "";
    switch (this->number) {
        case 1:
            num = "Ace";
            break;
        case 11:
            num = "Jack";
            break;
        case 12:
            num = "Queen";
            break;
        case 13:
            num = "King";
            break;
        default:
            num = to_string(this->number);
            break;
    }
    return num + " of " + this->suit;
}
