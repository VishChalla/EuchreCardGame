#include "Player.h"

Player::Player()
{
    
}

Card Player::PlayCard(Player &player, Deck packOfCards)
{
    std::vector<double> cardScores;
    std::vector<Card> eligibleCards;

    for (int i = 0; i < player.hand.size(); i++)
    {
        if (player.hand.at(i).suit == packOfCards.trumpCard.suit || (player.hand.at(i).face == "Jack" && player.hand.at(i).suit == packOfCards.sisterSuit))
        {
            eligibleCards.push_back(player.hand.at(i));
        }

        cardScores.push_back(player.hand.at(i).score); // assign card scores in hand to vector
    }

    double highestScore = *std::max_element(cardScores.begin(), cardScores.end());

    if (eligibleCards.empty())
    {
        for (int i = 0; i < player.hand.size(); i++)
        {
            if (player.hand.at(i).score == highestScore)
            {
                player.bestCard = player.hand.at(i);
                return player.hand.at(i); // play card with highest score
            }
        }
    }
    else
    {
        while (!eligibleCards.empty())
        {
            for (int i = 0; i < player.hand.size(); i++)
            {
                double highestEligibleScore = *std::max_element(cardScores.begin(), cardScores.end());

                if (player.hand.at(i).score == highestEligibleScore)
                {
                    if (player.hand.at(i).suit == packOfCards.trumpCard.suit || (player.hand.at(i).suit == packOfCards.sisterSuit && player.hand.at(i).face == "Jack"))
                    {
                        player.bestCard = player.hand.at(i);
                        player.cardPlayedIndex = i;
                        return player.hand.at(i); // play card with highest score
                    }
                    else
                    {
                        cardScores.erase(cardScores.begin() + i);
                    }
                }
            }
        }
    }

    return player.hand.at(0);
}


