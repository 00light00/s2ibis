#ifndef _IBISSERIESMODEL
#define _IBISSERIESMODEL
class ibisSeriesModel
{
  boolean OnState;
  ibisTypMinMax RSeriesOn = new ibisTypMinMax();
  ibisTypMinMax LSeriesOn = new ibisTypMinMax();
  ibisTypMinMax CSeriesOn = new ibisTypMinMax();
  ibisTypMinMax RlSeriesOn = new ibisTypMinMax();
  ibisTypMinMax RcSeriesOn = new ibisTypMinMax();
  seriesMosfet series_MOSFET = new seriesMosfet();

  boolean OffState;
  ibisTypMinMax RSeriesOff = new ibisTypMinMax();
  ibisTypMinMax LSeriesOff = new ibisTypMinMax();
  ibisTypMinMax CSeriesOff = new ibisTypMinMax();
  ibisTypMinMax RlSeriesOff = new ibisTypMinMax();
  ibisTypMinMax RcSeriesOff = new ibisTypMinMax();


  int series_type;

  public ibisSeriesModel() {
    this.OnState = false;
    this.OffState = false;
  }
};


#endif
