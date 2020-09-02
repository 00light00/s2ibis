#ifndef _COMPONENTLIST
#define _COMPONENTLIST

#include <vector>
using namespace std;

#include "ibisComponent.h"

class componentList
{
public:
    vector<ibisComponent> list;
  int count = 0;




  void add(ibisComponent componentFromParser) {
    this->count++;
    ibisComponent temp = componentFromParser;

    temp.setnext(this->head);
    this->head = temp;
    if (this->tail == nullptr)
    {
      this->tail = temp;
    }
    this->current = temp;
  }



  void gototop() {
    this->current = this->head;
  }


  void next() {
    if (this->current != nullptr)
    {
      this->current = this->current.getnext();
    }
  }
};

#endif
