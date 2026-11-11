#include "Deck.h"

#include <algorithm>
#include <chrono>
#include <random>

Deck::Deck()
{
    for (const std::string &suit : suitArray)
    {
        for (const std::string &face : faceArray)
        {
            Card card;
            card.suit = suit;
            card.face = face;
            deck.push_back(card);
        }
    }
}

void Deck::Shuffle()
{
    Shuffle(static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count()));
}

void Deck::Shuffle(unsigned seed)
{
    std::mt19937 generator(seed);
    std::shuffle(deck.begin(), deck.end(), generator);
}
