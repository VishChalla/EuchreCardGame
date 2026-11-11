// Unit tests. No framework needed: each check prints what failed and the
// program exits non-zero if anything did.

#include <iostream>
#include <set>
#include <sstream>
#include <string>

#include "Dealer.h"

namespace
{
int failures = 0;

void Check(bool condition, const std::string &what)
{
    if (!condition)
    {
        std::cerr << "FAILED: " << what << '\n';
        failures++;
    }
}

Card MakeCard(const std::string &face, const std::string &suit)
{
    Card card;
    card.face = face;
    card.suit = suit;
    return card;
}

void TestDeckHas24UniqueCards()
{
    Deck deck;
    std::set<std::string> seen;
    for (const Card &card : deck.deck)
    {
        seen.insert(card.face + card.suit);
    }
    Check(deck.deck.size() == 24, "deck has 24 cards");
    Check(seen.size() == 24, "every card is unique");
}

void TestShuffleIsRepeatableWithASeed()
{
    Deck a, b, c;
    a.Shuffle(7);
    b.Shuffle(7);
    c.Shuffle(8);
    bool same = true, different = false;
    for (size_t i = 0; i < a.deck.size(); i++)
    {
        same = same && a.deck[i].face == b.deck[i].face && a.deck[i].suit == b.deck[i].suit;
        different = different || a.deck[i].face != c.deck[i].face || a.deck[i].suit != c.deck[i].suit;
    }
    Check(same, "same seed gives the same order");
    Check(different, "different seeds give different orders");
}

void TestDealGivesFiveUniqueCardsEach(const std::string &typeOfDeal)
{
    Dealer dealer;
    dealer.packOfCards.Shuffle(1);
    dealer.Deal(typeOfDeal);
    std::set<std::string> seen;
    for (const Player &player : dealer.playerArray)
    {
        Check(player.hand.size() == 5, typeOfDeal + ": each player holds five cards");
        for (const Card &card : player.hand)
        {
            seen.insert(card.face + card.suit);
        }
    }
    Check(seen.size() == 20, typeOfDeal + ": no card dealt twice");
    Check(dealer.packOfCards.deck.size() == 4, typeOfDeal + ": four cards left in the kitty");
}

void TestSisterSuit()
{
    Dealer dealer;
    const char *pairs[4][2] = {
        {"Hearts", "Diamonds"}, {"Diamonds", "Hearts"}, {"Spades", "Clubs"}, {"Clubs", "Spades"}};
    for (auto &pair : pairs)
    {
        dealer.packOfCards.trumpCard = MakeCard("Jack", pair[0]);
        Check(dealer.DetermineSisterSuit() == pair[1], std::string("sister suit of ") + pair[0]);
    }
}

void TestBowersOutrankEverything()
{
    Dealer dealer;
    dealer.packOfCards.trumpCard = MakeCard("9", "Hearts");
    Player &player = dealer.playerArray[0];
    player.hand = {MakeCard("Ace", "Hearts"), MakeCard("Jack", "Diamonds"), MakeCard("Jack", "Hearts"),
                   MakeCard("Ace", "Spades"), MakeCard("9", "Clubs")};
    Check(dealer.RankHand(player) == 1.0, "hand score is the right bower");
    Check(player.hand[2].score > player.hand[1].score, "right bower beats left bower");
    Check(player.hand[1].score > player.hand[0].score, "left bower beats trump ace");
    Check(player.hand[0].score > player.hand[3].score, "trump ace beats off-suit ace");

    Card played = player.PlayCard(dealer.packOfCards);
    Check(played.face == "Jack" && played.suit == "Hearts", "plays the right bower first");
    Check(player.cardPlayedIndex == 2, "records which card was played");
}

void TestPlaysBestCardWithoutTrump()
{
    Dealer dealer;
    dealer.packOfCards.trumpCard = MakeCard("9", "Hearts");
    Player &player = dealer.playerArray[0];
    player.hand = {MakeCard("9", "Clubs"), MakeCard("Ace", "Spades"), MakeCard("King", "Clubs")};
    dealer.RankHand(player);
    Card played = player.PlayCard(dealer.packOfCards);
    Check(played.face == "Ace" && played.suit == "Spades", "with no trump, plays the highest card");
}

void TestTrickGoesToHighestCard()
{
    Dealer dealer;
    for (int i = 0; i < Dealer::kPlayers; i++)
    {
        dealer.playerArray[i].bestCard.score = 0.1 * (i + 1);
    }
    dealer.playerArray[2].bestCard.score = 0.9;
    std::ostringstream quiet;
    std::streambuf *old = std::cout.rdbuf(quiet.rdbuf());
    int winner = dealer.DetermineRoundWinner();
    std::cout.rdbuf(old);
    Check(winner == 2 && dealer.winner.name == "playerThree", "highest card wins the trick");
}

// The original version crashed on some shuffles. Play many complete hands
// and check that every one finishes with all cards played.
void TestThousandFullGames()
{
    std::ostringstream quiet;
    std::streambuf *old = std::cout.rdbuf(quiet.rdbuf());
    bool allFinished = true;
    for (unsigned seed = 0; seed < 1000; seed++)
    {
        Dealer dealer;
        dealer.packOfCards.Shuffle(seed);
        dealer.Deal(seed % 2 == 0 ? "twoFirst" : "threeFirst");
        dealer.packOfCards.trumpCard = dealer.ExposeTopCard();
        dealer.ChooseTrump();
        dealer.RemoveTopCardFromDeck();
        for (int trick = 0; trick < Dealer::kHandSize; trick++)
        {
            for (Player &player : dealer.playerArray)
            {
                dealer.RankHand(player);
                player.PlayCard(dealer.packOfCards);
            }
            dealer.DetermineRoundWinner();
            for (Player &player : dealer.playerArray)
            {
                dealer.RemoveCardFromHand(player);
            }
        }
        for (const Player &player : dealer.playerArray)
        {
            allFinished = allFinished && player.hand.empty();
        }
    }
    std::cout.rdbuf(old);
    Check(allFinished, "1,000 seeded games all finish with empty hands");
}
} // namespace

int main()
{
    TestDeckHas24UniqueCards();
    TestShuffleIsRepeatableWithASeed();
    TestDealGivesFiveUniqueCardsEach("twoFirst");
    TestDealGivesFiveUniqueCardsEach("threeFirst");
    TestSisterSuit();
    TestBowersOutrankEverything();
    TestPlaysBestCardWithoutTrump();
    TestTrickGoesToHighestCard();
    TestThousandFullGames();

    if (failures == 0)
    {
        std::cout << "All tests passed\n";
        return 0;
    }
    std::cerr << failures << " check(s) failed\n";
    return 1;
}
