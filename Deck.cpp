#include "Deck.h"

Deck::Deck()
{
    // Both of these are used to iterate suit and face placement in the deck
    int suitIterator = 0;
    int faceIterator = 0;

    //initialize deck   
    for(int i = 0; i < deck.size(); i++) // until i == 24
    {
        if(faceIterator == sizeof(faceArray)/sizeof(faceArray[0])) // if faceiterator == 6
        {
            faceIterator = 0; // reset the face 
            suitIterator++; // move to the next suit
        }
        
        deck.at(i).suit = suitArray[suitIterator]; // set suit
        deck.at(i).face = faceArray[faceIterator]; //set face
        
        faceIterator++;        
    }

    

}
    

void Deck::Shuffle() // Calls std shuffle
{   
    std::srand(unsigned(std::time(0)));
    std::random_shuffle(&deck[0], &deck[24]);
}



