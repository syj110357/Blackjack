#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cassert>
#include "hand.h"
#include "card.h"
#include "deck.h"
#include "player.h"
#include "rand.h"

using namespace std;
const int minimumbet=5;
int main (int argc, char *argv[])
{
    int bankroll=atoi(argv[1]);
    int hands=atoi(argv[2]);
    string playertype=argv[3];
    Deck deck1;
    Player *simp = get_Simple();
    Player *coun = get_Counting();
    int thishand=0;
    int cut,bet;
    Card card1,card2,card3,card4;
    Hand playerhand,dealerhand;
    cout << "Shuffling the deck"<<endl;
    //Shuffle the deck
    for (int i=0;i<7;i++)
    {
        cut=get_cut();
        cout << "cut at " << cut << endl;
        deck1.shuffle(cut);
        coun->shuffled();
    }
    while (hands>thishand)
    {
        if (bankroll<minimumbet) break;
        thishand++;
        cout << "Hand " << thishand << " bankroll " << bankroll << endl;
        if (deck1.cardsLeft()<20)
        {
            cout << "Shuffling the deck"<<endl;
            for (int ii=0;ii<7;ii++)
            {
                cut=get_cut();
                cout << "cut at " << cut << endl;
                deck1.shuffle(cut);
                coun->shuffled();
            }
        }
        if (playertype.compare("simple")==0)
        {
            bet=simp->bet(bankroll,minimumbet);
            cout << "Player bets " << bet << endl;
        }
        else
        {
            bet=coun->bet(bankroll,minimumbet);
            cout << "Player bets " << bet << endl;
        }
        card1=deck1.deal();
        cout<<"Player dealt "<<SpotNames[card1.spot]<<" of "<<SuitNames[card1.suit]<<endl;
        playerhand.addCard(card1);
        coun->expose(card1);
        card2=deck1.deal();
        cout<<"Dealer dealt "<<SpotNames[card2.spot]<<" of "<<SuitNames[card2.suit]<<endl;
        dealerhand.addCard(card2);
        coun->expose(card2);
        card3=deck1.deal();
        cout<<"Player dealt "<<SpotNames[card3.spot]<<" of "<<SuitNames[card3.suit]<<endl;
        playerhand.addCard(card3);
        coun->expose(card3);
        card4=deck1.deal();
        dealerhand.addCard(card4);
        if ((card1.spot==12 && card3.spot>=8 && card3.spot<=11) || (card3.spot==12 && card1.spot>=8 && card1.spot<=11))
        {
            int naturalwin=1.5*bet;
            bankroll=bankroll+naturalwin;
            cout << "Player dealt natural 21"<<endl;;
        }
        else
        {
            if (playertype.compare("simple")==0)
            {
                while (simp->draw(card2,playerhand)==1)
                {
                    Card cardcard=deck1.deal();
                    playerhand.addCard(cardcard);
                    cout<<"Player dealt "<<SpotNames[cardcard.spot]<<" of "<<SuitNames[cardcard.suit]<<endl;
                    if (playerhand.handValue().count>21)
                    {
                        cout << "Player's total is " << playerhand.handValue().count << endl;
                        cout << "Player busts"<<endl;
                        bankroll=bankroll-bet;
                        break;
                    }
                }
                if (playerhand.handValue().count<=21)
                {
                    cout << "Player's total is " << playerhand.handValue().count << endl;
                    cout<<"Dealer's hole card is "<<SpotNames[card4.spot]<<" of "<<SuitNames[card4.suit]<<endl;
                    while (dealerhand.handValue().count<17)
                    {
                        Card carddealer=deck1.deal();
                        cout<<"Dealer dealt "<<SpotNames[carddealer.spot]<<" of "<<SuitNames[carddealer.suit]<<endl;
                        dealerhand.addCard(carddealer);
                    }
                    cout << "Dealer's total is " << dealerhand.handValue().count << endl;
                    if (dealerhand.handValue().count>21)
                    {
                        cout << "Dealer busts"<<endl;
                        bankroll=bankroll+bet;
                    }
                    else if (dealerhand.handValue().count>playerhand.handValue().count)
                    {
                        cout << "Dealer wins"<<endl;
                        bankroll=bankroll-bet;
                    }
                    else if (dealerhand.handValue().count<playerhand.handValue().count)
                    {
                        cout << "Player wins"<<endl;
                        bankroll=bankroll+bet;
                    }
                    else cout << "Push"<<endl;
                }
            }
            else
            {
                while (coun->draw(card2,playerhand)==1)
                {
                    Card cardcard=deck1.deal();
                    playerhand.addCard(cardcard);
                    coun->expose(cardcard);
                    cout<<"Player dealt "<<SpotNames[cardcard.spot]<<" of "<<SuitNames[cardcard.suit]<<endl;
                    if (playerhand.handValue().count>21)
                    {
                        cout << "Player's total is " << playerhand.handValue().count << endl;
                        cout << "Player busts"<<endl;
                        bankroll=bankroll-bet;
                        break;
                    }
                }
                if (playerhand.handValue().count<=21)
                {
                    cout << "Player's total is " << playerhand.handValue().count << endl;
                    cout<<"Dealer's hole card is "<<SpotNames[card4.spot]<<" of "<<SuitNames[card4.suit]<<endl;
                    coun->expose(card4);
                    while (dealerhand.handValue().count<17)
                    {
                        Card carddealer=deck1.deal();
                        dealerhand.addCard(carddealer);
                        cout<<"Dealer dealt "<<SpotNames[carddealer.spot]<<" of "<<SuitNames[carddealer.suit]<<endl;
                        coun->expose(carddealer);
                    }
                    cout << "Dealer's total is " << dealerhand.handValue().count << endl;
                    if (dealerhand.handValue().count>21)
                    {
                        cout << "Dealer busts"<<endl;
                        bankroll=bankroll+bet;
                    }
                    else if (dealerhand.handValue().count>playerhand.handValue().count)
                    {
                        cout << "Dealer wins"<<endl;
                        bankroll=bankroll-bet;
                    }
                    else if (dealerhand.handValue().count<playerhand.handValue().count)
                    {
                        cout << "Player wins"<<endl;
                        bankroll=bankroll+bet;
                    }
                    else cout << "Push"<<endl;
                }
            }
        }
        playerhand.discardAll();
        dealerhand.discardAll();
    }
    cout << "Player has " << bankroll<< " after " << thishand << " hands"<<endl;
}

