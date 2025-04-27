#include "Dealer.h"

Dealer::Dealer()
{
    // set up 4 players
    playerArray[0] = playerOne;
    playerArray[1] = playerTwo;
    playerArray[2] = playerThree;
    playerArray[3] = playerFour;

    // player names set
    playerArray[0].name = "playerOne";
    playerArray[1].name = "playerTwo";
    playerArray[2].name = "playerThree";
    playerArray[3].name = "playerFour";

    winner = Player();
}

void Dealer::Deal(std::string typeOfDeal)
{
    if (typeOfDeal == "twoFirst")
    {
        for (int i = 0; i < (sizeof(playerArray) / sizeof(playerArray[0])); i++) // Loop through each player
        {
            for (int k = 0; k < 2; k++) // loop through deck and give each player 2 cards
            {
                playerArray[i].hand.at(k) = packOfCards.deck.at(k);   // player at i gets two cards
                packOfCards.deck.erase(packOfCards.deck.begin() + k); // remove the cards given
            }
        }

        for (int i = 0; i < (sizeof(playerArray) / sizeof(playerArray[0])); i++)
        {
            for (int k = 2; k < 5; k++) // this time each player gets three
            {
                playerArray[i].hand.at(k) = packOfCards.deck.at(k);
                packOfCards.deck.erase(packOfCards.deck.begin() + k);
            }
        }
    }
    else if (typeOfDeal == "threeFirst")
    {
        for (int i = 0; i < (sizeof(playerArray) / sizeof(playerArray[0])); i++)
        {
            for (int k = 0; k < 3; k++) // three cards given first
            {
                playerArray[i].hand.at(k) = packOfCards.deck.at(k);
                packOfCards.deck.erase(packOfCards.deck.begin() + k);
            }
        }

        for (int i = 0; i < (sizeof(playerArray) / sizeof(playerArray[0])); i++)
        {
            for (int k = 3; k < 5; k++) // then two
            {
                playerArray[i].hand.at(k) = packOfCards.deck.at(k);
                packOfCards.deck.erase(packOfCards.deck.begin() + k);
            }
        }
    }
}

Card Dealer::ExposeTopCard() { return packOfCards.deck.at(0); }; // returns card at vector index 0

double Dealer::RankHand(Player &player) // handRating percent chances of win are from EuchreUniverse.blogspot.com
{
    packOfCards.sisterSuit = DetermineSisterSuit(); // put this in a determine trump method

    double scoreArray[5];

    for (int i = 0; i < player.hand.size(); i++)
    {
        if (player.hand.at(i).suit == packOfCards.trumpCard.suit && player.hand.at(i).face == "Jack") // Right bower
        {
            player.handScore = 1; // 100% chance of win
            player.hand.at(i).score = 1;
            scoreArray[i] = player.handScore;
            player.bestCard = player.hand.at(i);
        }
        else if (player.hand.at(i).suit == packOfCards.sisterSuit && player.hand.at(i).face == "Jack") // Left Bower
        {
            player.handScore = .76; // 76% chance of win
            player.hand.at(i).score = .76;
            scoreArray[i] = player.handScore;
        }
        else if (player.hand.at(i).suit == packOfCards.trumpCard.suit && player.hand.at(i).face == "Ace") // trump ace
        {
            player.handScore = .53;
            player.hand.at(i).score = .53;
            scoreArray[i] = player.handScore;
        }
        else if (player.hand.at(i).suit != packOfCards.sisterSuit && player.hand.at(i).face == "Ace") // green ace
        {
            player.handScore = .5;
            player.hand.at(i).score = .5;
            scoreArray[i] = player.handScore;
        }
        else if (player.hand.at(i).suit == packOfCards.trumpCard.suit && player.hand.at(i).face == "King") // trump king
        {
            player.handScore = .45;
            player.hand.at(i).score = .45;
            scoreArray[i] = player.handScore;
        }
        else if (player.hand.at(i).suit == packOfCards.sisterSuit && player.hand.at(i).face == "Ace") // sister suit ace
        {
            player.handScore = .44;
            player.hand.at(i).score = .44;
            scoreArray[i] = player.handScore;
        }
        else if (player.hand.at(i).suit == packOfCards.trumpCard.suit && player.hand.at(i).face == "Queen") // trump queen
        {
            player.handScore = .4;
            player.hand.at(i).score = .4;
            scoreArray[i] = player.handScore;
        }
        else if (player.hand.at(i).suit == packOfCards.trumpCard.suit && player.hand.at(i).face == "10") // trump 10
        {
            player.handScore = .34;
            player.hand.at(i).score = .34;
            scoreArray[i] = player.handScore;
        }
        else if (player.hand.at(i).suit == packOfCards.trumpCard.suit && player.hand.at(i).face == "9") // trump 9
        {
            player.handScore = .32;
            player.hand.at(i).score = .32;
            scoreArray[i] = player.handScore;
        }
        else if (player.hand.at(i).suit != packOfCards.sisterSuit && player.hand.at(i).face == "King") // green king
        {
            player.handScore = .19;
            player.hand.at(i).score = .19;
            scoreArray[i] = player.handScore;
        }
        else if (player.hand.at(i).suit == packOfCards.sisterSuit && player.hand.at(i).face == "King") // sister suit king
        {
            player.handScore = .13;
            player.hand.at(i).score = .13;
            scoreArray[i] = player.handScore;
        }
        else if (player.hand.at(i).suit != packOfCards.sisterSuit && player.hand.at(i).face == "Queen") // green queen
        {
            player.handScore = .06;
            player.hand.at(i).score = .06;
            scoreArray[i] = player.handScore;
        }
        else
        {
            player.handScore = .01;
            player.hand.at(i).score = .01;
            scoreArray[i] = player.handScore;
        }
    }
    double *score = std::max_element(scoreArray, scoreArray + 5);
    return *score;
}

std::string Dealer::DetermineSisterSuit()
{
    if (packOfCards.trumpCard.suit == "Clubs")
    {
        return "Spades";
    }
    else if (packOfCards.trumpCard.suit == "Spades")
    {
        return "Clubs";
    }
    else if (packOfCards.trumpCard.suit == "Diamonds")
    {
        return "Hearts";
    }
    else
    {
        return "Diamonds";
    }
}

void Dealer::ChooseTrump()
{
    bool trumpChosen = false;
    for (int i = 0; i < sizeof(playerArray) / sizeof(playerArray[0]); i++)
    {
        if (RankHand(playerArray[i]) > .53f)
        {
            std::cout << playerArray[i].name + " Has declared " + packOfCards.trumpCard.suit + " As trump!" << std::endl;
            std::cout << std::endl;
            startingPlayer = playerArray[i];
            trumpChosen = true;
            break;
        }
    }
    if(!trumpChosen)
    {
        std::cout <<"No player has chosen to declare trump, player to the left of the dealer may now choose."<< std::endl;
        std::cout << playerArray[1].name + " Has declared " + playerArray[1].bestCard.suit + " As trump!" << std::endl;
    
    }
}



void Dealer::DetermineRoundWinner()
{
    double handScores[5];

    for (int i = 0; i < sizeof(playerArray) / sizeof(playerArray[0]); i++)
    {
        handScores[i] = playerArray[i].bestCard.score;
    }

    double highestScore = *std::max_element(handScores, handScores + 5);

    for (int i = 0; i < sizeof(playerArray) / sizeof(playerArray[0]); i++)
    {
        if (playerArray[i].bestCard.score == highestScore)
        {
            std::cout << "-------------------------------" << std::endl;
            std::cout << playerArray[i].name + " has won the trick!" << std::endl;
            std::cout << "-------------------------------" << std::endl;
            winner = playerArray[i]; 
            break;
        }
    }
}

void Dealer::RemoveCardFromHand(Player &player)
{
    player.hand.erase(player.hand.begin() + player.cardPlayedIndex);
}

void Dealer::RemoveTopCardFromDeck()
{
    packOfCards.deck.erase(packOfCards.deck.begin());
}

