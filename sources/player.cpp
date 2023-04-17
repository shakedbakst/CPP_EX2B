#include <iostream>
#include <string>
#include <exception>
#include <vector>
#include "player.hpp"
#include "card.hpp"
using namespace std;
using namespace ariel;


Player::Player(string Pname) : name(Pname), wonCards(0), winnings(0), isPlaying(false) {}

string Player::getName() const{
    return name;
}

int  Player::stacksize(){
    if (PlayerStack.size()>=0 && PlayerStack.size()<=52){
        return PlayerStack.size();
    }else{
        throw std::runtime_error("Error! There is a problem with stack size");
    }
}

int Player::cardesTaken(){
    return wonCards;
}

Card Player::cardPlay(){
    Card t = PlayerStack.back();
    PlayerStack.pop_back();
    return t;
}

void Player::insertCardesStack(Card card){
    PlayerStack.push_back(card);
}

int Player::getWinnings() {
    return winnings;
}

void Player::addWonCard() {
    wonCards++;
}

bool Player::getIsPlaying() {
    return isPlaying;
}

void Player::setIsPlaying() {
    isPlaying = !isPlaying;
}

void Player::increaseWonCards() {
    wonCards += 2;   
}

void Player::increaseWonCardDraw() {
    wonCards += 4;
}

void Player::increaseWinnings() {
    winnings++;
}





