#ifndef IBISTYPMINMAX_H
#define IBISTYPMINMAX_H

#include "ConstantStuff.h"

/******************************************************************************
CLASS: ibisTypMinMax
******************************************************************************/
struct ibisTypMinMax {
  double typ, min, max;
  // constructor for ibisTypMinMax class
  ibisTypMinMax() {
    typ = ConstantStuff::USE_NA;
    min = ConstantStuff::USE_NA;
    max = ConstantStuff::USE_NA;
  } // constructor for ibisTypMnMax class
};

#endif // IBISTYPMINMAX_H
