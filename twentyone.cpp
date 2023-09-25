/*******************************************************************************
 * CS 103 Twenty-One (Blackjack) Project
/******************************************************************************/

#include <iostream>
#include <cstdlib>

using namespace std;

/* Prototypes */
void shuffle(int cards[]);
void printCard(int id);
int cardValue(int id);
void printHand(int hand[], int numCards);
int getBestScore(int hand[], int numCards);

const int NUM_CARDS = 52;

/**
 * Global arrays to be used as look-up tables.
 */
const char suit[4] = {'H','S','D','C'};
const char* type[13] = 
  {"2","3","4","5","6","7",
   "8","9","10","J","Q","K","A"};
const int value[13] = {2,3,4,5,6,7,8,9,10,10,10,10,11};

/**
 * Should permute the deck of cards, effectively shuffling it, 
 * using the Fisher-Yates / Durstenfeld shuffle algorithm.
 */
void shuffle(int cards[])
{
  int temp;

  for(int i=51; i>0; i--){
    int j=rand()%(i+1);

    //swap
    temp = cards[i];
    cards[i] = cards[j];
    cards[j] = temp;
  }
}

/**
 * Prints the card in a "type-suit" format:   
 *  Examples:  K-C  (King of clubs), 2-H (2 of hearts)
 *  Valid Types are: 2,3,4,5,6,7,8,9,10,J,Q,K,A
 *  Valid Suits are: H, D, C, S
 */
void printCard(int id)
{
  cout << type[id%13] << "-" << suit[id/13];
}

/**
 * Returns the numeric value of the card.
 *  Should return 11 for an ACE and can then
 *  be adjusted externally based on the sum of the score.
 *
 */
int cardValue(int id)
{
  return value[id%13];
}

/**
 * Should print out each card in the hand separated by a space and
 * then print a newline at the end.  
 */
void printHand(int hand[], int numCards)
{
  for(int i=0; i<numCards; i++){
    printCard(hand[i]);
    cout << " ";
  }
  cout << endl;
}

/**
 * Should return the total score of the provided hand.  
 * ACES should be treated as 11s to make the highest possible hand
 *  and only being reduced to 1s as needed to avoid busting.
 */
int getBestScore(int hand[], int numCards)
{
  int sum=0;
  int card;
  int ace=0;

  for(int i=0; i<numCards; i++){
    card=hand[i];
    sum=sum+cardValue(card);

    if(card%13==12)
    {
      ace++;
    }

    if(ace>0&&(sum>21))
    {
      sum-=10;
      ace--;
    }
  }
  return sum;
}

/**
 * Main program logic for the game of 21
 */
int main(int argc, char* argv[])
{
  //---------------------------------------
  // Do not change this code -- Begin
  //---------------------------------------
  if(argc < 2){
    cout << "Error - Please provide the seed value." << endl;
    return 1;
  }
  int seed = atoi(argv[1]);
  srand(seed);

  int cards[52];
  int dhand[9];
  int phand[9];
  //---------------------------------------
  // Do not change this code -- End
  //---------------------------------------

  bool game=true;
  char g;
  
  while(game==true)
  {
    //reset
    int player_sum=0;
    int dealer_sum=0;
    
    //initialize card deck
    for(int i=0; i<52; i++){
      cards[i]=i;
    }

    shuffle(cards);
  
    //deal
    phand[0] = cards[0];
    dhand[0] = cards[1];
    phand[1] = cards[2];
    dhand[1] = cards[3];

    cout << "Dealer: ? ";
    printCard(dhand[1]);
    cout<<endl;
    cout << "Player: ";
    printHand(phand,2);

    player_sum = getBestScore(phand,2);
    dealer_sum = getBestScore(dhand,2);

    //player's turn
    char key;
    int card;
    int c_id=4;
    int d_id=2;
    int p_id=2;
  
    if(player_sum==21)
    {
      key='s';
    }
    else
    {
      cout << "Type 'h' to hit and 's' to stay:" << endl;
      cin>>key;
    }
    
    while(key=='h')
    {
      card = cards[c_id];
      phand[p_id]=card;
      c_id++;
      p_id++;

      cout << "Player: ";
      printHand(phand, p_id);
      player_sum=getBestScore(phand, p_id);
      
      if(player_sum>21){
        cout << "Player busts" << endl;
        key='b';
      }
      else if(player_sum==21)
      {
        key='s';
      }
      else
      {
        cout << "Type 'h' to hit and 's' to stay:" << endl;
        cin>>key;
      }
    }

      //dealer's turn
      if(key=='s')
      {
        while(dealer_sum<17){
          card = cards[c_id];
          dhand[d_id]=card;
          c_id++;
          d_id++;

          dealer_sum=getBestScore(dhand, d_id);
        }

        cout << "Dealer: ";
        printHand(dhand, d_id);

        if(dealer_sum>21)
        {
          cout << "Dealer busts" << endl;
        }

        key='b';
      }

      //compare
      if(key=='b')
      {
        if(dealer_sum<22 && (dealer_sum>player_sum || player_sum>21))
        {
          cout << "Lose " << player_sum << " " << dealer_sum << endl << endl;

        }
        else if(player_sum<22 && (player_sum>dealer_sum || dealer_sum>21))
        {
          cout << "Win " << player_sum << " " << dealer_sum << endl << endl;
        }
        else if(player_sum==dealer_sum)
        {
          cout << "Tie " << player_sum << " " << dealer_sum << endl << endl;
        }
      }

      else
      {
        return 0;
      }

      //play again?
      cout << "Play again? [y/n]" << endl;
      cin>>g;
      if(g=='y')
      {
        game=true;
      }
      else
      {
        game=false;
      }
    }  
    
  return 0;
}
