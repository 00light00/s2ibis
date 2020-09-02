#ifndef _PINSLIST
#define _PINSLIST
class pinsList
{
  ibisPin head = null;
  ibisPin tail = null;
  ibisPin current = null;
  int count = 0;




  public void add(ibisPin pinFromParser) {
    this.count++;
    ibisPin temp = pinFromParser;

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
