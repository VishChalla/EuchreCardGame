#include "Dealer.h"

#include <algorithm>
#include <iostream>
#include <stdexcept>

Dealer::Dealer()
{
    const char *names[kPlayers] = {"playerOne", "playerTwo", "playerThree", "playerFour"};
    for (int i = 0; i < kPlayers; i++)
    {
        playerArray[i].name = names[i];
    }
}

void Dealer::Deal(const std::string &typeOfDeal)
{
    if (typeOfDeal != "twoFirst" && typeOfDeal != "threeFirst")
    {
        throw std::invalid_argument("Deal type must be \"twoFirst\" or \"threeFirst\"");
    }
    int firstRound = typeOfDeal == "twoFirst" ? 2 : 3;
    int rounds[2] = {firstRound, kHandSize - firstRound};

    for (Player &player : playerArray)
    {
        player.hand.clear();
    }
    for (int cardsThisRound : rounds)
    {
        for (Player &player : playerArray)
        {
            for (int k = 0; k < cardsThisRound; k++)
            {
                player.hand.push_back(packOfCards.deck.front()); // always deal from the top
                packOfCards.deck.erase(packOfCards.deck.begin());
            }
        }
    }
}

Card Dealer::ExposeTopCard() const { return packOfCards.deck.at(0); }

void Dealer::RemoveTopCardFromDeck() { packOfCards.deck.erase(packOfCards.deck.begin()); }

std::string Dealer::DetermineSisterSuit() const
{
    const std::string &trump = packOfCards.trumpCard.suit;
    if (trump == "Clubs")
    {
        return "Spades";
    }
    if (trump == "Spades")
    {
        return "Clubs";
    }
    if (trump == "Diamonds")
    {
        return "Hearts";
    }
    return "Diamonds";
}

// Card strengths are approximate chances of winning a trick, taken from
// EuchreUniverse.blogspot.com.
double Dealer::RankHand(Player &player)
{
    packOfCards.sisterSuit = DetermineSisterSuit();
    const std::string &trump = packOfCards.trumpCard.suit;
    const std::string &sister = packOfCards.sisterSuit;

    player.handScore = 0.0;
    for (Card &card : player.hand)
    {
        bool isTrump = card.suit == trump;
        bool isSister = card.suit == sister;

        if (isTrump && card.face == "Jack") // right bower
        {
            card.score = 1.0;
        }
        else if (isSister && card.face == "Jack") // left bower
        {
            card.score = 0.76;
        }
        else if (isTrump && card.face == "Ace")
        {
            card.score = 0.53;
        }
        else if (!isSister && card.face == "Ace") // off-colour ("green") ace
        {
            card.score = 0.50;
        }
        else if (isTrump && card.face == "King")
        {
            card.score = 0.45;
        }
        else if (isSister && card.face == "Ace")
        {
            card.score = 0.44;
        }
        else if (isTrump && card.face == "Queen")
        {
            card.score = 0.40;
        }
        else if (isTrump && card.face == "10")
        {
            card.score = 0.34;
        }
        else if (isTrump && card.face == "9")
        {
            card.score = 0.32;
        }
        else if (!isSister && card.face == "King") // green king
        {
            card.score = 0.19;
        }
        else if (isSister && card.face == "King")
        {
            card.score = 0.13;
        }
        else if (!isSister && card.face == "Queen") // green queen
        {
            card.score = 0.06;
        }
        else
        {
            card.score = 0.01;
        }
        player.handScore = std::max(player.handScore, card.score);
    }
    return player.handScore;
}

int Dealer::ChooseTrump()
{
    for (int i = 0; i < kPlayers; i++)
    {
        // Order it up only with something better than the trump ace.
        if (RankHand(playerArray[i]) > 0.53)
        {
            std::cout << playerArray[i].name << " has declared " << packOfCards.trumpCard.suit
                      << " as trump!\n\n";
            startingPlayer = playerArray[i];
            return i;
        }
    }
    std::cout << "Nobody ordered it up, so " << packOfCards.trumpCard.suit
              << " stands as trump.\n\n";
    return -1;
}

int Dealer::DetermineRoundWinner()
{
    int best = 0;
    for (int i = 1; i < kPlayers; i++)
    {
        if (playerArray[i].bestCard.score > playerArray[best].bestCard.score)
        {
            best = i;
        }
    }
    winner = playerArray[best];
    std::cout << "-------------------------------\n"
              << winner.name << " has won the trick!\n"
              << "-------------------------------\n";
    return best;
}

void Dealer::RemoveCardFromHand(Player &player)
{
    if (player.cardPlayedIndex < 0 || player.cardPlayedIndex >= static_cast<int>(player.hand.size()))
    {
        throw std::logic_error(player.name + " has not played a card this trick");
    }
    player.hand.erase(player.hand.begin() + player.cardPlayedIndex);
    player.cardPlayedIndex = -1;
}
