#ifndef _DIFFPINLIST
#define _DIFFPINLIST

#include "ibisDiffPin.h"

class diffPinList
{
public:
  ibisDiffPin head = null;
  ibisDiffPin tail = null;
  ibisDiffPin current = null;
  int count = 0;




  void add(ibisDiffPin newDiffPin) {
    this.count++;
    ibisDiffPin temp = newDiffPin;


    temp.setnext(this.head);
    this.head = temp;
    if (this.tail == null)
    {
      this.tail = temp;
    }
    this.current = temp;
  }



  void gototop() {
    this.current = this.head;
  }


  public void next() {
    if (this.current != null)
    {
      this.current = this.current.getnext();
    }
  }
}

#endif
