#ifndef _PINMAPLIST
#define _PINMAPLIST

#include "ibisPinMap.h"

class pinMapList
{
  ibisPinMap head = null;
  ibisPinMap tail = null;
  ibisPinMap current = null;
  int count = 0;




  public void add(ibisPinMap newPinMap) {
    this.count++;
    ibisPinMap temp = newPinMap;


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
}


#endif
