// Plays one hand of simplified Euchre between four computer players and
// prints every step. Pass a number to replay a specific shuffle:
//
//     ./euchre        random game
//     ./euchre 42     the same game every time

#include <cstdlib>
#include <iostream>

#include "Dealer.h"

namespace
{
void PrintCard(const Card &card) { std::cout << card.face << " of " << card.suit << '\n'; }

void PrintHands(const Dealer &dealer)
{
    for (const Player &player : dealer.playerArray)
    {
        std::cout << player.name << " (hand score " << player.handScore << "):\n";
        for (const Card &card : player.hand)
        {
            PrintCard(card);
        }
        std::cout << '\n';
    }
}
} // namespace

int main(int argc, char *argv[])
{
    Dealer dealer;

    if (argc > 1)
    {
        dealer.packOfCards.Shuffle(static_cast<unsigned>(std::strtoul(argv[1], nullptr, 10)));
    }
    else
    {
        dealer.packOfCards.Shuffle();
    }
    dealer.Deal("threeFirst");

    std::cout << "Top card turned up:\n----------------\n";
    PrintCard(dealer.ExposeTopCard());
    std::cout << "----------------\n\n";

    dealer.packOfCards.trumpCard = dealer.ExposeTopCard();
    dealer.ChooseTrump();
    dealer.RemoveTopCardFromDeck();

    int tricksWon[Dealer::kPlayers] = {0};

    for (int trick = 1; trick <= Dealer::kHandSize; trick++)
    {
        std::cout << "TRICK " << trick << "\n///////////////////////////////////////\n\n";

        for (Player &player : dealer.playerArray)
        {
            dealer.RankHand(player);
        }
        PrintHands(dealer);
        std::cout << "Trump suit: " << dealer.packOfCards.trumpCard.suit << "\n\n";

        for (Player &player : dealer.playerArray)
        {
            Card played = player.PlayCard(dealer.packOfCards);
            std::cout << player.name << " plays: ";
            PrintCard(played);
        }

        tricksWon[dealer.DetermineRoundWinner()]++;

        for (Player &player : dealer.playerArray)
        {
            dealer.RemoveCardFromHand(player);
        }
        std::cout << "///////////////////////////////////////\n\n";
    }

    std::cout << "FINAL TRICK COUNT\n";
    for (int i = 0; i < Dealer::kPlayers; i++)
    {
        std::cout << dealer.playerArray[i].name << ": " << tricksWon[i] << '\n';
    }
    return 0;
}
