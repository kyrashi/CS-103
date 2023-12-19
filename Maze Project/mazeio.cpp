/*
mazeio.cpp
*/

#include <iostream>
#include <fstream>
#include "mazeio.h"

using namespace std;

/*************************************************
 * read_maze:
 * Read the maze from the given filename into a
 *  2D dynamically  allocated array.
 *
 * Return the pointer to that array.
 * Return NULL (a special address) if there is a problem,
 * opening the file or reading in the integer sizes.
 *
 *************************************************/
char** read_maze(char* filename, int* rows, int* cols)
{
  //open file
  ifstream ifile(filename);
  if(ifile.fail()){
    return NULL;
  }
  try{
    ifile>>*rows;
    ifile>>*cols;
  }
  catch(int e){
    return NULL;
  }

  //create maze array
  char** maze=new char*[*rows];
  for(int r=0; r<*rows; r++){
    maze[r]=new char[*cols];
    for(int c=0; c<*cols; c++){
      ifile >> maze[r][c];
    }
  }
  ifile.close();
  return maze;
}

/*************************************************
 * Print the maze contents to the screen in the
 * same format as the input (rows and columns, then
 * the maze character grid).
 *************************************************/
void print_maze(char** maze, int rows, int cols)
{
  cout << rows << " " << cols << endl;

  for(int r=0;r<rows;r++){
    for(int c=0; c<cols; c++){
      cout << maze[r][c];
    }
    cout << endl;
  }
}

