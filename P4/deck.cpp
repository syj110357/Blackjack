#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cassert>
#include "deck.h"
#include "card.h"
#include "rand.h"

using namespace std;

Deck::Deck()
    {
        next=0;
        for (int suit=0; suit<4; suit++)
        {
            for (int spot=0; spot<13; spot++)
            {
                deck[spot+13*suit].suit= (Suit)(suit);
                deck[spot+13*suit].spot= (Spot)(spot);
            }
        }
    }

void Deck::reset()
{
    next=0;
    for (int suit=0; suit<4; suit++)
        {
            for (int spot=0; spot<13; spot++)
            {
                deck[spot+13*suit].suit= (Suit)(suit);
                deck[spot+13*suit].spot= (Spot)(spot);
            }
        }
}

void Deck::shuffle(int n)
{
    Deck shuffledeck;
    if (n<=26)
    {
        for (int i=0;i<n;i++)
        {
            shuffledeck.deck[2*i+1]=deck[i];
            shuffledeck.deck[2*i]=deck[n+i];
        }
        for (int ii=0;ii<DeckSize-2*n;ii++)
        {
            shuffledeck.deck[2*n+ii]=deck[2*n+ii];
        }
        for (int iii=0;iii<DeckSize;iii++)
        {
            deck[iii]=shuffledeck.deck[iii];
        }
    }
    else
    {
        for (int i=n;i<DeckSize;i++)
        {
            shuffledeck.deck[2*(i-n)]=deck[i];
            shuffledeck.deck[2*(i-n)+1]=deck[i-n];
        }
        for (int ii=0;ii<2*n-DeckSize;ii++)
        {
            shuffledeck.deck[ii+2*(DeckSize-n)]=deck[ii+DeckSize-n];
        }
        for (int iii=0;iii<DeckSize;iii++)
        {
            deck[iii]=shuffledeck.deck[iii];
        }
    }
    next=0;
}

Card Deck::deal()
{
    next=next+1;
    return deck[next-1];
}

int Deck::cardsLeft()
{
    return DeckSize-next;
}
/*
main function to test deck
int main()
{
    Deck deck1;
    deck1.shuffle(45);
    for (int i=0;i<52;i++)
    {
        Card cardshow=deck1.deal();
        cout<<SpotNames[cardshow.spot]<<" "<<SuitNames[cardshow.suit]<<endl;
    }
}*/
