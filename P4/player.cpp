#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cassert>
#include "hand.h"
#include "card.h"
#include "deck.h"
#include "player.h"

using namespace std;

class Simple : public Player
{
    //Need a private variable
protected:
    int counter;
public:
    Simple();
    int bet(unsigned int bankroll, unsigned int minimum);
    bool draw(Card dealer, const Hand &player);
    void expose(Card c);
    void shuffled();
};

//Initialize the class
Simple::Simple():counter(0)
    {

    }
int Simple::bet(unsigned int bankroll, unsigned int minimum)
{
    return minimum;
}

bool Simple::draw(Card dealer, const Hand &player)
{
    if (player.handValue().soft==1)
    {
        if (player.handValue().count>=19) return 0;
        else if (player.handValue().count==18 && (dealer.spot==0 || dealer.spot==5 || dealer.spot==6)) return 0;
        else return 1;
    }
    else
    {
        if (player.handValue().count>=17) return 0;
        else if (player.handValue().count>=13 && player.handValue().count<=16 && (dealer.spot==0 || dealer.spot==1 || dealer.spot==2 || dealer.spot==3 || dealer.spot==4)) return 0;
        else if (player.handValue().count==12 && (dealer.spot==2 || dealer.spot==3 || dealer.spot==4)) return 0;
        else return 1;
    }
}

void Simple::expose(Card c)
{
    if (c.spot>=8) counter--;
    else if (c.spot<=4) counter++;
}

void Simple::shuffled()
{
    counter=0;
}

static Simple sim;
Player *get_Simple()
{
    return & sim;
}

class Counting :public Simple
{
    public:
        Counting();
        int bet(unsigned int bankroll, unsigned int minimum);
};
Counting::Counting()
{

}
int Counting::bet(unsigned int bankroll, unsigned int minimum)
{
    if (counter>=2 && bankroll>=2*minimum) return 2*minimum;
    else return minimum;
}

static Counting cou;
Player *get_Counting()
{
    return & cou;
}
/*
main function to test the players
int main()
{
    Deck deck1;
    Player *s = get_Simple();
    Player *t = get_Counting();
    Card card1,card2,card3;
    card1.spot=TWO;
    card1.suit=SPADES;
    card2.spot=THREE;
    card2.suit=CLUBS;
    card3.spot=ACE;
    card3.suit=CLUBS;
    t->expose(card1);
    t->shuffled();
    t->expose(card2);
    try
    {
        t->bet(50,10);
        cout<<t->bet(50,10)<<endl;
    }
    catch(int i)
    {
        cout<<"Not enough money"<<endl;
    }
}*/
