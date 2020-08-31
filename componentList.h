#ifndef _COMPONENTLIST
#define _COMPONENTLIST


class componentList
{
  ibisComponent head = null;
  ibisComponent tail = null;
  ibisComponent current = null;
  int count = 0;




  public void add(ibisComponent componentFromParser) {
    this.count++;
    ibisComponent temp = componentFromParser;

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
