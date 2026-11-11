#include "Player.h"

#include <stdexcept>

namespace
{
bool IsTrump(const Card &card, const Deck &pack)
{
    bool leftBower = card.face == "Jack" && card.suit == pack.sisterSuit;
    return card.suit == pack.trumpCard.suit || leftBower;
}
} // namespace

Card Player::PlayCard(const Deck &packOfCards)
{
    if (hand.empty())
    {
        throw std::logic_error(name + " has no cards left to play");
    }

    int bestTrump = -1;
    int bestOverall = 0;
    for (int i = 0; i < static_cast<int>(hand.size()); i++)
    {
        if (hand.at(i).score > hand.at(bestOverall).score)
        {
            bestOverall = i;
        }
        if (IsTrump(hand.at(i), packOfCards) &&
            (bestTrump == -1 || hand.at(i).score > hand.at(bestTrump).score))
        {
            bestTrump = i;
        }
    }

    cardPlayedIndex = bestTrump != -1 ? bestTrump : bestOverall;
    bestCard = hand.at(cardPlayedIndex);
    return bestCard;
}
