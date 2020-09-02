#ifndef _IBISSERIESPIN
#define _IBISSERIESPIN

#include <string>
using String = std::string;

class ibisSeriesPin
{
  String seriesPinName = null;
  String seriesPin2name = null;
  String modelName = null;
  String fnTableGp = null;
  ibisModel seriesModel;

  public void setnext(ibisSeriesPin nextSeriesPin1) {
    this.nextSeriesPin = nextSeriesPin1;
  }
  ibisSeriesPin nextSeriesPin;

  public ibisSeriesPin getnext() {
    return this.nextSeriesPin;
  }
}


#endif
