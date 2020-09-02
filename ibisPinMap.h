#ifndef _IBISPINMAP
#define _IBISPINMAP

#include <string>
using String = std::string;

class ibisPinMap
{
  String pinName = "";
  String pullupRef = "";
  String pulldownRef = "";
  String powerClampRef = "";
  String gndClampRef = "";

  ibisPinMap nextPinMap;

  public void setnext(ibisPinMap nextPinMap1) {
    this.nextPinMap = nextPinMap1;
  }


  public ibisPinMap getnext() {
    return this.nextPinMap;
  }
};

#endif
