#ifndef _IBISDIFFPIN
#define _IBISDIFFPIN

#include <string>
using String = std::string;

class ibisDiffPin
{
  String pinName = "";
  String invPin = "";
  double vdiff = 0.0D;
  double tdelay_typ = -1.33287736222333005E18D;
  double tdelay_min = -1.33287736222333005E18D;
  double tdelay_max = -1.33287736222333005E18D;

  ibisDiffPin nextDiffPin;

  void setnext(ibisDiffPin nextDiffPin1) {
    this.nextDiffPin = nextDiffPin1;
  }


  ibisDiffPin getnext() {
    return this.nextDiffPin;
  }
};

#endif
