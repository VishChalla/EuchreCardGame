#include <iostream>
#include "Deck.cpp"
#include "Dealer.cpp"
#include "Player.cpp"
#include <sstream>

int main()
{
    Deck d = Deck();
    Dealer dealer = Dealer();
    Player player = Player();

    std::cout << "" << std::endl;
    std::cout << "Unshuffled cards: " << std::endl;
    std::cout << "" << std::endl;

    for (int i = 0; i < d.deck.size(); i++)
    {
        std::cout << d.deck.at(i).face + " Of " + d.deck.at(i).suit << std::endl; // print all the cards we need in order
    }

    std::cout << "" << std::endl;
    std::cout << " Shuffled: " << std::endl;
    std::cout << "" << std::endl;
    d.Shuffle();

    for (int i = 0; i < d.deck.size(); i++)
    {
        std::cout << d.deck.at(i).face + " Of " + d.deck.at(i).suit << std::endl; // print shuffled cards to demonstrate shuffle works
    }

    std::cout << "" << std::endl;
    std::cout << "The Deal:" << std::endl;
    std::cout << "" << std::endl;

    dealer.packOfCards.Shuffle(); // Shuffle the cards we need to give to the players
    dealer.Deal("threeFirst");    // deal three first, then two

    std::cout << "Flip over top card:" << std::endl;

    std::cout << "----------------" << std::endl;
    std::cout << dealer.ExposeTopCard().face + " Of " + dealer.ExposeTopCard().suit << std::endl; // print top card
    std::cout << "----------------" << std::endl;
    std::cout << "" << std::endl;

    dealer.packOfCards.trumpCard.face = dealer.packOfCards.faceArray[2]; // Set to be jack

    dealer.packOfCards.trumpCard.suit = dealer.ExposeTopCard().suit; // set accepted suit to be trump suit

    dealer.ChooseTrump();
    dealer.RemoveTopCardFromDeck();

    ///////////////////////////////////////////////

    int numTricks = 5;
    int trickCounter = 1;

    for (int i = 0; i < numTricks; i++)
    {
        std::cout<<"ROUND " << trickCounter<<std::endl; // print round number
        std::cout << "///////////////////////////////////////" << std::endl;
        std::cout << "" << std::endl;
 
        for (int i = 0; i < sizeof(dealer.playerArray) / sizeof(dealer.playerArray[0]); i++) //PRINT PLAYER HANDS
        {
            std::cout << dealer.playerArray[i].name + ":" << std::endl; // print player names

            for (int k = 0; k < dealer.playerArray[i].hand.size(); k++)
            {
                std::cout << dealer.playerArray[i].hand.at(k).face + " Of " + dealer.playerArray[i].hand.at(k).suit << std::endl;
            }

            std::cout << "" << std::endl; 
        }

        std::cout << "Trump card:" << std::endl;

        std::cout << "----------------" << std::endl; // PRINT TRUMP CARD
        std::cout << dealer.packOfCards.trumpCard.face + " Of " + dealer.packOfCards.trumpCard.suit << std::endl; 
        std::cout << "----------------" << std::endl;
        std::cout << "" << std::endl;

        std::string result; // used for conversion in cout

        for (int i = 0; i < sizeof(dealer.playerArray) / sizeof(dealer.playerArray[0]); i++) // PRINT HAND RANKS
        {
            std::ostringstream convert;
            convert << dealer.RankHand(dealer.playerArray[i]);
            result = convert.str();
            std::cout << dealer.playerArray[i].name + " HandScore:" << std::endl;
            std::cout << result << std::endl;
        }

        std::cout << "" << std::endl;

        for (int i = 0; i < sizeof(dealer.playerArray) / sizeof(dealer.playerArray[0]); i++) // PLAY CARDS
        {
            Card cardPlayed;
            cardPlayed = player.PlayCard(dealer.playerArray[i], dealer.packOfCards);
            std::cout << dealer.playerArray[i].name + " plays: " + cardPlayed.face + " Of " + cardPlayed.suit << std::endl;
        }

        for (int i = 0; i < sizeof(dealer.playerArray) / sizeof(dealer.playerArray[0]); i++) // REMOVE CARDS PLAYED FROM HAND
        {
            dealer.RemoveCardFromHand(dealer.playerArray[i]);
        } 
   
        dealer.DetermineRoundWinner();

        trickCounter++;

        std::cout << "///////////////////////////////////////" << std::endl;
    }

    return 0;
}