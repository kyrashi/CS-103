/*
maze.cpp
*/

#include <iostream>
#include "mazeio.h"
#include "queue.h"

using namespace std;

// Prototypes
int maze_search(char**, int, int);
int check_validity(char**, int, int);

// Main function to read, solve maze, and print result
int main(int argc, char* argv[]) {
    int rows, cols; //result
    char** mymaze=NULL;
    const char* invalid_char_message = "Error, invalid character.";
    const char* invalid_maze_message = "Invalid maze.";
    const char* no_path_message = "No path could be found!";

    if(argc < 2)
    {
        cout << "Please provide a maze input file" << endl;
        return 1;
    }

    mymaze = read_maze(argv[1],&rows,&cols);
    
    // Check the validity of the maze
    int error = check_validity(mymaze,rows,cols);
    if(error==1){
        cout << invalid_char_message << endl;
    }
    if(error==2){
        cout << invalid_maze_message << endl;
    }

    //================================
    // Print maze
    int search = maze_search(mymaze,rows,cols);
    if(search==1){
        print_maze(mymaze, rows, cols);
    }
    if(search==0){
        cout << no_path_message << endl;
    }

    //================================
    // Delete memory
    for(int i=0;i<rows;i++){
        delete [] mymaze[i];
    }
    delete [] mymaze;

    return 0;
}

/**************************************************
 * Attempt to find shortest path and return:
 *  1 if successful
 *  0 if no path exists
 *
 * If path is found, it will be filled in with '*' characters
 *************************************************/
int maze_search(char** maze, const int rows, const int cols)
{
    if(check_validity(maze,rows,cols)!=0){
        return -1;
    }

    Queue my_queue = Queue(rows*cols);
    Location** predecessor=new Location*[rows];
    int** explored=new int*[rows];
    for(int i=0;i<rows;i++){
      predecessor[i]=new Location[cols];
      explored[i]=new int[cols];
    }    

    //find start
    for(int r=0;r<rows;r++){
        for(int c=0;c<cols;c++){
            char val = maze[r][c];
            if(val=='S'){
                my_queue.add_to_back(Location(r,c));
                explored[r][c]=1;
            }
            else{
              explored[r][c]=0;
            }
        }
    }

    //BFS
    bool found=false;
    int r;
    int c;
    int nums[4][2]= {{0,-1},{-1,0},{0,1},{1,0}};

    while(my_queue.is_empty()==false && !found){
      Location loc = my_queue.remove_from_front();
      r=loc.row;
      c=loc.col;
      for(int* n:nums){
        Location nloc=Location(r+n[0],c+n[1]);
        int nr=nloc.row;
        int nc=nloc.col;

        //out of bounds
        if(nr<0 || nr>=rows || nc<0 || nc>=cols){
          continue;
        }
        //explored
        else if(explored[nr][nc]==1){
          continue;
        }
        //wall
        else if(maze[nr][nc]=='#'){
          explored[nr][nc]=1;
          continue;
        }
        //found
        else if(maze[nr][nc]=='F'){
          found=true;
          r=nr;
          c=nc;
          predecessor[nr][nc]=loc;
          break;
        }

        explored[nr][nc]=1;
        my_queue.add_to_back(nloc);
        predecessor[nr][nc]=loc;
      }
    }

    //not found
    if(!found){
      for(int i=0;i<rows;i++){
        delete [] predecessor[i];
        delete [] explored[i];
      }
      delete [] predecessor;
      delete [] explored;
      return 0;
    }
    
    //backtrace
    while(maze[r][c]!='S'){
      Location tloc=predecessor[r][c];
      r=tloc.row;
      c=tloc.col;

      if(maze[r][c]=='S'){
        break;
      }
      maze[r][c]='*';
    }
    for(int i=0;i<rows;i++){
      delete [] predecessor[i];
      delete [] explored[i];
    }
    delete [] predecessor;
    delete [] explored;
    return 1;
  }

int check_validity(char** maze,int rows,int cols){
    int s_count=0;
    int f_count=0;
    for(int r=0;r<rows;r++){
        for(int c=0;c<cols;c++){
            char val = maze[r][c];
            if(val!='.' && val!='#' && val!='S' && val!='F'){
                return 1;
            }
            if(val=='S'){
                s_count++;
            }
            if(val=='F'){
                f_count++;
            }
        }
    }
    if(s_count!=1 || f_count!=1){
        return 2;
    }
    return 0;
}

