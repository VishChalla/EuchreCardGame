#ifndef DECK_H
#define DECK_H

#pragma once

#include <string>       //std::string
#include <algorithm>    // std::random_shuffle
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand
#include <vector>       // std::vector


// Card struct definition
struct Card
{
    public:
        std::string suit;       
        std::string face;
        double score;
};

//Deck class definition
class Deck
{
    public:
        Deck();
        void Shuffle();
        std::vector<Card> deck = std::vector<Card>(24); // vector deck
        // used to give cards suits and faces v
        std::string suitArray[4] = {"Hearts", "Diamonds", "Spades", "Clubs"}; 
        std::string faceArray[6] = {"9", "10", "Jack", "Queen", "King", "Ace"};
        Card trumpCard;
        std::string sisterSuit;
};
#endif