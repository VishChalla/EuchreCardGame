#ifndef PLAYER_H
#define PLAYER_H

#include <vector> 
#include "Deck.h" 

// Player class definition
class Player
{
    public:
    Player();
    std::vector<Card> hand = std::vector<Card>(5); 
    std::string name;   
    double handScore;
    Card PlayCard(Player playerArray[]);
    Card bestCard;
    int cardPlayedIndex;
    Card PlayCard(Player &player, Deck packOfCards);
};


#endif