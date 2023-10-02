/*******************************************************************************
 * Tic-Tac-Toe Project
 Simulates a game of Tic-Tac-Toe that allows two players to play on any size grid (up to 11x11)
/******************************************************************************/

#include <iostream>
#include <cstdlib>
using namespace std;

// The following 3 functions are helper functions to convert
// between 1D and 2D array indices.

char getEntryAtRC(char grid[], int dim, int r, int c);

int idxToRow(int idx, int dim);

int idxToCol(int idx, int dim);


/** Prints the tic-tac-toe board in a nice grid format
 *
 * Parameters:
 *   grid: Array of dim^2 characters representing the state
 *         of each square.  Each entry contains 'X', 'O'
 *         (the letter oh), or '?'.
 */
void printTTT(char grid[], int dim);

/**
 * Checks if any player has won the game yet.
 *
 * Parameters:
 *   grid: Array of dim^2 characters representing the state
 *         of each square.  Each entry contains 'X', 'O', or '?'
 *
 * Return value:
 *   Returns 1 if 'X' has won, 2 if 'O' has won, or 0 (zero)
 *   if the game is still undecided.
 *
 */
int checkForWinner(char grid[], int dim);


/**
 * Should check if there is no possible way any player can win.
 * More specifically, if there does not exist a row, column,
 * or diagonal that can still have 3 of a kind, then the game
 * will be a draw.
 *
 *
 * Parameters:
 *   grid: Array of dim^2 characters representing the state
 *         of each square.  Each entry contains 'X', 'O', or '?'
 *
 * Return value:
 *   Return true if no player can win given the current
 *   game state, false otherwise.
 */
bool checkForDraw(char grid[], int dim);

/**
 * Gets the computer-generated choice for the current player and updates grid
 *
 * Parameters:
 *   grid: Array of dim^2 characters representing the state
 *         of each square.  Each entry contains 'X', 'O', or '?'
 *   dim: the dimension of the tic-tac-toe board
 *   player: current player => 'X' or 'O'
 * @return false If an error occurred or a choice was unable to be made
 * @return true If a play was successfully made
 */
bool getAiChoiceAndUpdateGrid(char grid[], int dim, char player);

/**********************************************************
 *  Function Implementations
 **********************************************************/

char getEntryAtRC(char grid[], int dim, int r, int c)
{
  /* Convert r,c to 1D index */
  return grid[r*dim+c];
}

int idxToRow(int idx, int dim)
{
  /* Convert idx to appropriate row */ 
  return idx/dim;
}

int idxToCol(int idx, int dim)
{
  /* Convert idx to appropriate column */
  return idx%dim;
}

void printTTT(char grid[], int dim)
{
  for(int i=0; i<dim*dim; i++){
    cout << " " << grid[i];

    //not the end of a line
    if((i+1)%dim!=0){
      cout << " |";
    }
    //not the last line
    else if(i!=dim*dim-1){
      cout<<endl;
      for(int n=1; n<4*dim; n++){
        cout <<"-";
      }
      cout<<endl;
    }
  }

  cout<<endl;
}   

int checkForWinner(char grid[], int dim)
{
  bool xcount=true;
  bool ocount=true;
      
  //rows
  for(int r=0; r<dim; r++){
    for(int c=0; c<dim; c++){
      if(xcount && getEntryAtRC(grid, dim, r, c)!='X'){
        xcount=false;
      }
      if(ocount && getEntryAtRC(grid, dim, r, c)!='O'){
        ocount=false;
      }
    }
    if(xcount){
      return 1;
    }
    else if(ocount){
      return 2;
    }
    else{
      xcount=true;
      ocount=true;
    }
  }

  //columns
  for(int c=0; c<dim; c++){
    for(int r=0; r<dim; r++){
      if(xcount && getEntryAtRC(grid, dim, r, c)!='X'){
        xcount=false;
      }
      if(ocount && getEntryAtRC(grid, dim, r, c)!='O'){
        ocount=false;
      }
    }

    if(xcount){
      return 1;
    }
    else if(ocount){
      return 2;
    }
    else{
      xcount=true;
      ocount=true;
    }
  }

  //diagonal 1
  for(int i=0; i<dim; i++){
    if(xcount && getEntryAtRC(grid, dim, i, i)!='X'){
        xcount=false;
    }
    if(ocount && getEntryAtRC(grid, dim, i, i)!='O'){
        ocount=false;
    }
  }

  if(xcount){
    return 1;
  }
  else if(ocount){
    return 2;
  }
  else{
      xcount=true;
      ocount=true;
  }
  

  //diagonal 2
  for(int i=0; i<dim; i++){
    if(xcount && getEntryAtRC(grid, dim, i, dim-i-1)!='X'){
        xcount=false;
    }
    if(ocount && getEntryAtRC(grid, dim, i, dim-i-1)!='O'){
        ocount=false;
    }
  }

  if(xcount){
    return 1;
  }
  else if(ocount){
    return 2;
  }

  return 0;
}

bool checkForDraw(char grid[], int dim)
{
  int xcount=0;
  int ocount=0;

  //rows
  for(int r=0; r<dim; r++){
    for(int c=0; c<dim; c++){
      if(getEntryAtRC(grid, dim, r, c)=='X'){
        xcount++;
      }
      else if(getEntryAtRC(grid, dim, r, c)=='O'){
        ocount++;
      }
    }

    if(!(xcount>0 && ocount>0)){
      return false;
    }
    
    xcount=0;
    ocount=0;
  }
  

  //columns
  for(int c=0; c<dim; c++){
    for(int r=0; r<dim; r++){
      if(getEntryAtRC(grid, dim, r, c)=='X'){
        xcount++;
      }
      else if(getEntryAtRC(grid, dim, r, c)=='O'){
        ocount++;
      }
    }

    if(!(xcount>0 && ocount>0)){
      return false;
    }

    xcount=0;
    ocount=0;
  }


  //diagonal
  for(int i=0; i<dim; i++){
    if(getEntryAtRC(grid, dim, i, i)=='X'){
      xcount++;
    }
    else if(getEntryAtRC(grid, dim, i, i)=='O'){
      ocount++;
    }
  }

  if(!(xcount>0 && ocount>0)){
    return false;
  }

  xcount=0;
  ocount=0;


  //diagonal 2
  for(int i=0; i<dim; i++){
    if(getEntryAtRC(grid, dim, i, dim-i-1)=='X'){
      xcount++;
    }
    else if(getEntryAtRC(grid, dim, i, dim-i-1)=='O'){
      ocount++;
    }
  }

  if(!(xcount>0 && ocount>0)){
    return false;
  }

  return true;
}

bool getAiChoiceAndUpdateGrid(char grid[], int dim, char player)
{
  //win
  for(int i=0; i<dim*dim; i++){
    if(grid[i]=='?'){
      grid[i]=player;

      if(player=='X' && checkForWinner(grid, dim)==1){
        return true;
      }

      if(player=='O' && checkForWinner(grid, dim)==2){
        return true;
      }

      grid[i]='?';
    }
  }

  //block
  for(int i=0; i<dim*dim; i++){
    if(grid[i]=='?'){
      if(player=='X'){
        grid[i]='O';
      }
      else{
        grid[i]='X';
      }

      if(checkForWinner(grid, dim)==1){
        grid[i]='O';
        return true;
      }

      if(checkForWinner(grid, dim)==2){
        grid[i]='X';
        return true;
      }

      grid[i]='?';
    }
  }
          
  return false;
}

/**********************************************************
 *  Main project loop
 **********************************************************/
int main()
{
  // This array holds the actual board/grid of X and Os. It is sized
  // for the biggest possible case (11x11)
  char tttdata[121];
  
  // dim stands for dimension and is the side length of the
  // tic-tac-toe board i.e. dim x dim (3x3 or 5x5).
  int dim;
  int seed;
  // Get the dimension from the user
  cin >> dim >> seed;
  srand(seed);

  int dim_sq = dim*dim;

  for(int i=0; i < dim_sq; i++) {
      tttdata[i] = '?';
  }

  // Print one of these messages when the game is over
  const char xwins_msg[] = "X player wins!";
  const char owins_msg[] = "O player wins!";
  const char draw_msg[] =  "Draw...game over!";

  bool done = false;
  char player = 'X';

  // Show the initial starting board
  printTTT(tttdata, dim);

  bool filled=true;
  int place;
  int win=0;
  bool draw=false;

  while(!done) {
    while(filled){
      cout << "Player " << player << " enter your square choice " << "[0-" << dim_sq-1 << "], -1 (AI), or -2 (Random):" <<endl;
      cin >> place;

      //AI
      if(place==-1){
        filled=false;
        getAiChoiceAndUpdateGrid(tttdata,dim,player);
      }
    
      //random
      else if(place==-2){
        filled=false;
        getRandChoiceAndUpdateGrid(tttdata,dim,player);
      }

      //check out of bounds
      else if(place<0 || place>dim_sq-1){
        return 0;
      } 

      //check if filled
      else if(tttdata[place] == '?'){
        filled=false;

        //update
        tttdata[place]=player;
      }
      
      printTTT(tttdata, dim);

      win=checkForWinner(tttdata, dim);
      draw=checkForDraw(tttdata, dim);
      if(win!=0||draw==true){
        done=true;
      }
  }

  //switch turns
  if(player=='X'){
      player='O';
  }
  else{
      player='X';
  }

  filled=true;
}

  //output messages
  if(win==1){
    cout << xwins_msg << endl;
  }
  else if(win==2){
    cout << owins_msg << endl;
  }
  else if(draw==true){
    cout << draw_msg << endl;
  }

  return 0;
}
