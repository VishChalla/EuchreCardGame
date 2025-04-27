#ifndef DEALER_H
#define DEALER_H

#include "Deck.h"
#include "Player.h"
#include <vector>
#include <iostream>

//Dealer class definition
class Dealer
{
    public:
        Dealer();
        void Deal(std::string typeOfDeal);
        Deck packOfCards;
        Player playerArray[4];
        Card ExposeTopCard();
        double RankHand(Player &player);
        std::string DetermineSisterSuit();
        void ChooseTrump();
        Player startingPlayer;
        void DetermineBestCard(Player &player);
        void DetermineRoundWinner();
        void RemoveCardFromHand(Player &player);
        void RemoveTopCardFromDeck();
        Player winner;
        
    private:
        Player playerOne; //players instantiation 
        Player playerTwo;
        Player playerThree;
        Player playerFour;
        
};

#endif