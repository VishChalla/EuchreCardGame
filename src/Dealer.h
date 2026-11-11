#ifndef DEALER_H
#define DEALER_H

#include <array>
#include <string>

#include "Deck.h"
#include "Player.h"

// Runs the game: deals, settles trump, scores hands and decides each trick.
class Dealer
{
public:
    static const int kPlayers = 4;
    static const int kHandSize = 5;

    Dealer();

    // Deal five cards to each player in two rounds, "twoFirst" (2 then 3)
    // or "threeFirst" (3 then 2), as is traditional.
    void Deal(const std::string &typeOfDeal);

    Card ExposeTopCard() const;
    void RemoveTopCardFromDeck();

    std::string DetermineSisterSuit() const;

    // Score every card in the hand for the current trump suit and return the
    // hand's strength (its best card).
    double RankHand(Player &player);

    // The first player holding a strong enough hand orders up the turned-up
    // suit. If nobody does, the turned-up suit stands. Returns that player's
    // index, or -1 when nobody ordered it up.
    int ChooseTrump();

    // Compare the cards just played and record who took the trick.
    int DetermineRoundWinner();
    void RemoveCardFromHand(Player &player);

    Deck packOfCards;
    std::array<Player, kPlayers> playerArray;
    Player startingPlayer;
    Player winner;
};

#endif
