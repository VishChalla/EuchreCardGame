#ifndef DECK_H
#define DECK_H

#include <string>
#include <vector>

// A single playing card. `score` is the card's strength for the current
// trump suit and is filled in by Dealer::RankHand.
struct Card
{
    std::string suit;
    std::string face;
    double score = 0.0;
};

// The 24-card Euchre pack: 9 through Ace in each of the four suits.
class Deck
{
public:
    Deck();

    // Shuffle using a time-based seed, or a fixed seed for repeatable games.
    void Shuffle();
    void Shuffle(unsigned seed);

    std::vector<Card> deck;
    const std::vector<std::string> suitArray = {"Hearts", "Diamonds", "Spades", "Clubs"};
    const std::vector<std::string> faceArray = {"9", "10", "Jack", "Queen", "King", "Ace"};

    Card trumpCard;         // the turned-up card that proposes trump
    std::string sisterSuit; // the other suit of the same colour as trump
};

#endif
