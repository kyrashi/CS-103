/*
queue.cpp
*/

#include "queue.h"

//Constructor: maxlen is as large as the total number
// of Locations that will ever be entered into the Queue.
Location::Location(int r, int c){
  row=r;
  col=c;
}

Location::Location(){
  row=0;
  col=0;
}


Queue::Queue(int maxlen) {
    head = 0;
    tail = 0;
    contents=new Location[maxlen];
}

Queue::~Queue() {
    delete [] contents;
}

void Queue::add_to_back(Location loc) {
  contents[tail]= loc;
  tail++;
}

Location Queue::remove_from_front() {
  return contents[head++];
}

bool Queue::is_empty() {
    return head == tail;
}

