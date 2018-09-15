#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cassert>
#include "hand.h"
#include "card.h"
#include "deck.h"

using namespace std;

Hand::Hand()
{
    curValue.count=0;
    curValue.soft=0;
}
void Hand::discardAll()
{
    curValue.count=0;
    curValue.soft=0;
}
void Hand::addCard(Card c)
{
    if (curValue.soft==0)
    {
        if (c.spot<=8) curValue.count=curValue.count+c.spot+2;
        else if (c.spot!=12) curValue.count=curValue.count+10;
        else if (curValue.count+11<=21) {curValue.count=curValue.count+11;curValue.soft=1;}
        else curValue.count=curValue.count+1;
    }
    else
    {
        if (c.spot<=8) curValue.count=curValue.count+c.spot+2;
        else if (c.spot!=12) curValue.count=curValue.count+10;
        else if (curValue.count+11<=21) curValue.count=curValue.count+11;
        else curValue.count=curValue.count+1;
        if (curValue.count>21) {curValue.count=curValue.count-10;curValue.soft=0;}
    }
}

HandValue Hand::handValue() const
{
    return curValue;
}
/*
main function to test hand
int main()
{
    Hand hand1;
    Deck deck1;
    for (int i=0;i<10;i++)
    {
        deck1.deal();
    }
    hand1.addCard(deck1.deal());
    cout<<hand1.handValue().count<<endl;
    hand1.addCard(deck1.deal());
    cout<<hand1.handValue().count<<endl;
    hand1.addCard(deck1.deal());
    cout<<hand1.handValue().count<<endl;
    hand1.addCard(deck1.deal());
    cout<<hand1.handValue().count<<endl;
}*/
