#ifndef _MODELSLIST
#define _MODELSLIST

#include "ibisModel.h"

class modelsList
{
  int count;
  ibisModel head;
  ibisModel tail;
  ibisModel current = new ibisModel();



  public modelsList() {
    this.head = null;
    this.tail = null;
    this.current = null;
    this.count = 0;
  }



  public void add(ibisModel modelFromParser) {
    this.count++;
    ibisModel temp = modelFromParser;

    temp.setnext(this.head);
    this.head = temp;
    if (this.tail == null)
    {
      this.tail = temp;
    }
    this.current = temp;
  }



  public void gototop() {
    this.current = this.head;
  }


  public void next() {
    if (this.current != null)
    {
      this.current = this.current.getnext();
    }
  }
};

#endif
