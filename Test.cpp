#include "Dealer.h"
#include <cassert>
#include <stdio.h>

void EuchreTest()
{
    Dealer dealer = Dealer(); 

    // Set up game -----------------
    dealer.packOfCards.Shuffle(); 

    dealer.Deal("twoFirst");

    assert(dealer.ExposeTopCard().face == dealer.packOfCards.deck.at(0).face && dealer.ExposeTopCard().suit == dealer.packOfCards.deck.at(0).suit);

    dealer.ChooseTrump();
    dealer.RemoveTopCardFromDeck();

    dealer.RankHand(dealer.playerArray[0]);
    dealer.RankHand(dealer.playerArray[1]);
    dealer.RankHand(dealer.playerArray[2]);
    dealer.RankHand(dealer.playerArray[3]);
    // Set up game -----------------

    // Determine sister suit test -----------------
    Card trumpCard = Card();

    trumpCard.face = "Hearts";

    dealer.packOfCards.trumpCard = trumpCard;

    dealer.packOfCards.sisterSuit = dealer.DetermineSisterSuit();

    assert(dealer.packOfCards.sisterSuit == "Diamonds");
    // Determine sister suit test -----------------  

    // Determine round winner check -----------------
    double handScores[5]; 

    for (int i = 0; i < sizeof(dealer.playerArray) / sizeof(dealer.playerArray[0]); i++)
    {
        handScores[i] = dealer.playerArray[i].bestCard.score;
    }

    dealer.DetermineRoundWinner();

    double highestScore = *std::max_element(handScores, handScores + 5);

    for (int i = 0; i < sizeof(dealer.playerArray) / sizeof(dealer.playerArray[0]); i++)
    {
        if (dealer.playerArray[i].bestCard.score == highestScore)
        {
            // There are times that this assertion won't work because of a seg fault that occurs randomly. Because of some error in my game code.
            // If you can find where it happens, I'd love to know!
            assert(dealer.winner.name == dealer.playerArray[i].name); 
        }
    }
    // Determine round winner check -----------------

    // Play card check -----------------
    for (int i = 0; i < sizeof(dealer.playerArray) / sizeof(dealer.playerArray[0]); i++)
    {
        dealer.playerArray[i].PlayCard(dealer.playerArray[i], dealer.packOfCards);
        assert(dealer.playerArray[i].bestCard.face == dealer.playerArray[i].PlayCard(dealer.playerArray[i], dealer.packOfCards).face);
        assert(dealer.playerArray[i].bestCard.suit == dealer.playerArray[i].PlayCard(dealer.playerArray[i], dealer.packOfCards).suit);
    }   
    // Play card check -----------------
}

int main()
{
    EuchreTest();
}