#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>

#include "Deck.h"

// A computer-controlled Euchre player.
class Player
{
public:
    std::string name;
    std::vector<Card> hand;
    double handScore = 0.0;

    Card bestCard;            // the card chosen for the current trick
    int cardPlayedIndex = -1; // where that card sits in `hand`

    // Choose a card for this trick: the strongest trump (including the left
    // bower) if the player holds one, otherwise the strongest card overall.
    // Cards must have been scored by Dealer::RankHand first.
    Card PlayCard(const Deck &packOfCards);
};

#endif
