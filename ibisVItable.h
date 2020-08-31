#ifndef _IBISMODEL
#define _IBISMODEL

#include "ibisVItableEntry.h"

class ibisVItable
{
public:
  int size = 0;
  ibisVItableEntry[] VIs;
  ibisVItable nextVITable;

  void setnext(ibisVItable nextVITable1) {
    this.nextVITable = nextVITable1;
  }


  ibisVItable getnext() {
    return this.nextVITable;
  }
};

#endif

