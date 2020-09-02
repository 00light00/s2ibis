
#include "s2iHeader.h"

/*	CLASS:		setupVoltages
 *
 *	DESCRIPTION: Sets up the power and ground voltages, as well as
 * 		the DC sweep range and the "diode drop" value (used to
 *              determine where the linear portions of the data are).
 *
 */

double sweepStep;         // OUT
double sweepRange;        // OUT
double diodeDrop;         // OUT
ibisTypMinMax sweepStart; // OUT
ibisTypMinMax Vcc;        // OUT
ibisTypMinMax Gnd;        // OUT

setupVoltages(int curveType,  // IN
              ibisModel model // IN
) {
  ibisTypMinMax pullupRef, pulldownRef, powerClampRef, gndClampRef;
  ibisTypMinMax zeros;
  double linRange, minOffset, maxOffset;

  double sweepStepInc;
  /*==== Code =============================================================*/
  zeros.typ = 0;
  zeros.min = 0;
  zeros.max = 0;

  if (goodies.IS_USE_NA(model.pullupRef.typ))
    pullupRef = model.voltageRange;
  else
    pullupRef = model.pullupRef;

  if (goodies.IS_USE_NA(model.pulldownRef.typ))
    pulldownRef = zeros;
  else
    pulldownRef = model.pulldownRef;

  if (goodies.IS_USE_NA(model.powerClampRef.typ))
    powerClampRef = model.voltageRange;
  else
    powerClampRef = model.powerClampRef;

  if (goodies.IS_USE_NA(model.gndClampRef.typ))
    gndClampRef = zeros;
  else
    gndClampRef = model.gndClampRef;

  if (goodies.IS_ECL(model.modelType)) {
    diodeDrop = 0;

    Vcc.typ = pullupRef.typ;
    Vcc.min = pullupRef.min;
    Vcc.max = pullupRef.max;

    if (goodies.IS_USE_NA(model.gndClampRef.typ)) {
      if ((Vcc.typ >= 4.5) && (Vcc.typ <= 5.5)) {
        Gnd.typ = 0;
        Gnd.min = 0;
        Gnd.max = 0;
      } else {
        Gnd.typ = Vcc.typ - 5.2;
        Gnd.min = Vcc.min - 5.2;
        Gnd.max = Vcc.max - 5.2;
      }
    } else {
      Gnd.typ = gndClampRef.typ;
      Gnd.min = gndClampRef.min;
      Gnd.max = gndClampRef.max;
    }

    if (curveType == ConstantStuff.CURVE_TYPE_POWER_CLAMP) {
      sweepStart.typ = powerClampRef.typ;
      sweepStart.min = powerClampRef.min;
      sweepStart.max = powerClampRef.max;

      sweepRange = ConstantStuff.ECL_SWEEP_RANGE_DEFAULT;
      sweepStep = ConstantStuff.SWEEP_STEP_DEFAULT;
      /* *sweepRange += *sweepStep / 10; */
    } else if (curveType == ConstantStuff.CURVE_TYPE_GND_CLAMP) {
      sweepStart.typ = gndClampRef.typ - ConstantStuff.ECL_SWEEP_RANGE_DEFAULT;
      sweepStart.min = sweepStart.typ;
      sweepStart.max = sweepStart.typ;

      sweepRange = powerClampRef.typ - sweepStart.typ;
      if (sweepRange < 0)
        sweepStep = -ConstantStuff.SWEEP_STEP_DEFAULT;
      else
        sweepStep = ConstantStuff.SWEEP_STEP_DEFAULT;

      /*        while ( goodies.ROUND( goodies.fabs( sweepRange / sweepStep )
         + 1 ) > ConstantStuff.MAX_TABLE_SIZE ) sweepStep *= 2;
      */
      /* *sweepRange += *sweepStep / 10; */
    } else {
      sweepStart.typ = pullupRef.typ - ConstantStuff.ECL_SWEEP_RANGE_DEFAULT;
      sweepStart.min = sweepStart.typ;
      sweepStart.max = sweepStart.typ;

      if ((curveType == ConstantStuff.CURVE_TYPE_PULLUP) ||
          (curveType == ConstantStuff.CURVE_TYPE_DISABLED_PULLUP)) {
        maxOffset = Vcc.max - Vcc.typ;
        minOffset = Vcc.min - Vcc.typ;

        sweepStart.max = sweepStart.max + maxOffset;
        sweepStart.min = sweepStart.min + minOffset;
      }

      sweepRange = ConstantStuff.ECL_SWEEP_RANGE_DEFAULT;
      sweepStep = ConstantStuff.SWEEP_STEP_DEFAULT;
      /* *sweepRange += *sweepStep / 10; */
    }
  } // modelType is ECL
  else {
    if ((model.modelType == ConstantStuff.MODEL_TYPE_INPUT) ||
        (model.modelType == ConstantStuff.MODEL_TYPE_TERMINATOR) ||
        (model.modelType == ConstantStuff.MODEL_TYPE_SERIES) ||
        (model.modelType == ConstantStuff.MODEL_TYPE_SERIES_SWITCH))
      linRange = powerClampRef.typ - gndClampRef.typ;
    else
      linRange = pullupRef.typ - pulldownRef.typ;
    linRange = goodies.MIN(linRange, ConstantStuff.LIN_RANGE_DEFAULT);

    if ((curveType == ConstantStuff.CURVE_TYPE_GND_CLAMP) ||
        (curveType == ConstantStuff.CURVE_TYPE_POWER_CLAMP)) {
      Vcc.typ = powerClampRef.typ;
      Vcc.min = powerClampRef.min;
      Vcc.max = powerClampRef.max;

      Gnd.typ = gndClampRef.typ;
      Gnd.min = gndClampRef.min;
      Gnd.max = gndClampRef.max;

      if (curveType == ConstantStuff.CURVE_TYPE_GND_CLAMP) {
        sweepStart.typ = gndClampRef.typ - linRange;
        sweepStart.min = sweepStart.typ;
        sweepStart.max = sweepStart.typ;

        sweepRange = powerClampRef.typ - sweepStart.typ;
      } else {
        sweepStart.typ = powerClampRef.typ;
        sweepStart.min = powerClampRef.min;
        sweepStart.max = powerClampRef.max;

        sweepRange = linRange;
      }

      if (sweepRange < 0) {
        sweepStep = -ConstantStuff.SWEEP_STEP_DEFAULT;
        diodeDrop = -ConstantStuff.DIODE_DROP_DEFAULT;
      } else {
        sweepStep = ConstantStuff.SWEEP_STEP_DEFAULT;
        diodeDrop = ConstantStuff.DIODE_DROP_DEFAULT;
      }

      /*        while ( ( goodies.fabs( sweepRange / sweepStep ) + 1 ) >
         ConstantStuff.MAX_TABLE_SIZE ) sweepStep *= 2;
      */
      /* *sweepRange += *sweepStep / 10; */
    } else {
      Vcc.typ = pullupRef.typ;
      Vcc.min = pullupRef.min;
      Vcc.max = pullupRef.max;

      Gnd.typ = pulldownRef.typ;
      Gnd.min = pulldownRef.min;
      Gnd.max = pulldownRef.max;

      // series
      if (curveType == ConstantStuff.CURVE_TYPE_SERIES_VI)
        sweepStart.typ = pulldownRef.typ;
      else
        sweepStart.typ = pulldownRef.typ - linRange;
      // series

      sweepStart.min = sweepStart.typ;
      sweepStart.max = sweepStart.typ;

      if ((curveType == ConstantStuff.CURVE_TYPE_PULLUP) ||
          (curveType == ConstantStuff.CURVE_TYPE_DISABLED_PULLUP)) {
        maxOffset = Vcc.max - Vcc.typ;
        minOffset = Vcc.min - Vcc.typ;

        sweepStart.max = sweepStart.max + maxOffset;
        sweepStart.min = sweepStart.min + minOffset;
      }
      // series
      if (curveType == ConstantStuff.CURVE_TYPE_SERIES_VI)
        sweepRange = pullupRef.typ;
      else
        sweepRange = pullupRef.typ + linRange - sweepStart.typ;
      // series

      if (sweepRange < 0) {
        sweepStep = -ConstantStuff.SWEEP_STEP_DEFAULT;
        diodeDrop = -ConstantStuff.DIODE_DROP_DEFAULT;
      } else {
        sweepStep = ConstantStuff.SWEEP_STEP_DEFAULT;
        diodeDrop = ConstantStuff.DIODE_DROP_DEFAULT;
      }

      /*        while ( ( goodies.fabs( ( Vcc.typ - Gnd.typ + 2 * diodeDrop )
         / sweepStep ) + 1 ) > ConstantStuff.MAX_TABLE_SIZE ) sweepStep *= 2;
      */
      /* *sweepRange += *sweepStep / 10; */
    }
  }

  sweepStepInc = sweepStep;
  while (
      (goodies.ROUND(sweepRange / sweepStep) >= ConstantStuff.MAX_TABLE_SIZE) ||
      (sweepStep < 0.01))
    sweepStep += sweepStepInc;

} // method setupVoltage
}; // class setupVoltages

/*	CLASS:		findSupplyPins
 *
 *	DESCRIPTION: Assigns pullup and  pulldown Pins. Also assigns
 * 		power and ground  clamp pins. This is done using the
 *              pin map or power and ground pins available.
 *
 */   // Container Class
ibisPin pullupPin;     // OUT
ibisPin pulldownPin;   // OUT
ibisPin powerClampPin; // OUT
ibisPin gndClampPin;   // OUT
int findPins(ibisPin currentPin, pinsList pinList,
             bool hasPinMapping) { // main method

  pinsList tempPList = new pinsList();

  /***** Now look for pulldown Ref****/
  if (hasPinMapping) // returns 0 if successful else 1
  /*--------------------------------------------------------------------
   *   If this component has a pin map, use it to find the correct supplies.
   *   First find the power or gnd pin corresponding to the pullupRef.
   *   To do this, we search through the pin list until we find a POWER
   *   or GND pin with the same bus name in the pullupRef slot.
   *-------------------------------------------------------------------*/
  {

    if (!(currentPin.pullupRef.equalsIgnoreCase("NC"))) {
      pinList.gototop();

      for (tempPList = pinList;
           (tempPList != null) &&
           (!(((tempPList.current.modelName.equalsIgnoreCase("POWER")) ||
               (tempPList.current.modelName.equalsIgnoreCase("GND"))) &&
              tempPList.current.pullupRef.equalsIgnoreCase(
                  currentPin.pullupRef)));
           tempPList.next())
        ;
      if (tempPList == null) {
        printf("No Power or Ground pin"); // modify for refined use
        return (1);
      } else
        pullupPin = tempPList.current;
    } // if oulupRef is NOT a NC
    else
      pullupPin = null;

    /***** Now look for pulldownRef ****/

    if (!(currentPin.pulldownRef.equalsIgnoreCase("NC"))) {
      pinList.gototop();
      for (tempPList = pinList;
           (tempPList != null) &&
           (!(((tempPList.current.modelName.equalsIgnoreCase("POWER")) ||
               (tempPList.current.modelName.equalsIgnoreCase("GND"))) &&
              tempPList.current.pulldownRef.equalsIgnoreCase(
                  currentPin.pulldownRef)));
           tempPList.next())
        ;
      if (tempPList == null) {
        printf("No Power or Ground pin"); // modify for refined use
        return (1);
      } else
        pulldownPin = tempPList.current;
    } // if oulupRef is NOT a NC
    else
      pulldownPin = null;

    /***** Now look for PowerClampRef ****/

    if (!(currentPin.powerClampRef.equalsIgnoreCase("NC"))) {
      pinList.gototop();
      for (tempPList = pinList;
           (tempPList != null) &&
           (!(((tempPList.current.modelName.equalsIgnoreCase("POWER")) ||
               (tempPList.current.modelName.equalsIgnoreCase("GND"))) &&
              tempPList.current.pullupRef.equalsIgnoreCase(
                  currentPin.powerClampRef)));
           tempPList.next())
        ;
      if (tempPList == null) {
        printf("No Power or Ground pin"); // modify for refined use
        return (1);
      } else
        powerClampPin = tempPList.current;
    } // if outupRef is NOT a NC
    else
      powerClampPin = null;

    /***** Now look for gndClampRef ****/

    if (!(currentPin.gndClampRef.equalsIgnoreCase("NC"))) {
      pinList.gototop();
      for (tempPList = pinList;
           (tempPList != null) &&
           (!(((tempPList.current.modelName.equalsIgnoreCase("POWER")) ||
               (tempPList.current.modelName.equalsIgnoreCase("GND"))) &&
              tempPList.current.pulldownRef.equalsIgnoreCase(
                  currentPin.gndClampRef)));
           tempPList.next())
        ;
      if (tempPList == null) {
        printf("No Power or Ground pin"); // modify for refined use
        return (1);
      } else
        gndClampPin = tempPList.current;
    } // if outupRef is NOT a NC
    else
      gndClampPin = null;
  }    // if(hasPinMapping)
  else // Has No Pins Mapping
  /*--------------------------------------------------------------------
   *   If there is no pin mapping, just use the first power and gnd pins
   *   you come to.  First find the POWER pin.
   *-------------------------------------------------------------------*/
  {
    pinList.gototop();
    for (tempPList = pinList;
         (tempPList != null) &&
         !(tempPList.current.modelName.equalsIgnoreCase("POWER"));
         tempPList.next())
      ;
    if (tempPList == null) {
      printf("No Power pin for component. Please specify");
      printf(" at least one pin with model name POWER");
      return (1);
    } else {
      printf("Power pin for component available. Proceeding further ..");
      pullupPin = tempPList.current;
      powerClampPin = tempPList.current;
    }
    /*--------------------------------------------------------------------
     *   Now find the GND pin.
     *-------------------------------------------------------------------*/
    pinList.gototop();
    for (tempPList = pinList;
         (tempPList != null) &&
         !(tempPList.current.modelName.equalsIgnoreCase("GND"));
         tempPList.next())
      ;
    if (tempPList == null) {
      printf("No GND pin for component. Please specify ");
      printf(" at least one pin with model name GND");
      return (1);
    } else {
      printf("GND pin for component available. Proceeding further ..");
      gndClampPin = tempPList.current;
      pulldownPin = tempPList.current;
    }
  } // else

  return (0);
} // main()
}; // class

/*	CLASS:		sortVIData
 *
 *	DESCRIPTION: Sorts VI data and fills the pullup, pulldown,
 * 		powerclamp and groundclamp tables.
 *
 */

int sortVIData(ibisModel model_p, ibisVItable pullupData_p,
               ibisVItable pulldownData_p, ibisVItable powerClampData_p,
               ibisVItable gndClampData_p) {
  ibisTypMinMax Vcc, Gnd, sweepStart;
  double sweepRange = 0, sweepStep = 0, diodeDrop = 0;
  int numLinearPts = 0, numTablePts = 0, VITableSize = 0, increment = 0,
      numInnerPts = 0, pointsToSkip = 0, currentMarker = 0, i = 0, j = 0;
  setupVoltages setupV = new setupVoltages();

  if (goodies.IS_ECL(model_p.modelType))
    numLinearPts = 0;
  else
    numLinearPts = ConstantStuff.NUM_PTS_LINEAR_REGION; // default at 10

  if (pullupData_p != null) {
    setupV.setupVoltages(ConstantStuff.CURVE_TYPE_PULLUP, model_p);
    sweepStep = setupV.sweepStep;
    sweepRange = setupV.sweepRange;
    diodeDrop = setupV.diodeDrop;
    sweepStart = setupV.sweepStart;
    Vcc = setupV.Vcc;
    Gnd = setupV.Gnd;

    if (goodies.IS_ECL(model_p.modelType)) {
      numInnerPts = goodies.ROUND(goodies.fabs(sweepRange / sweepStep)) + 1;
      pointsToSkip = 0;
    } else {
      numInnerPts =
          goodies.ROUND(goodies.fabs(Vcc.typ - Gnd.typ + 2 * diodeDrop) /
                        sweepStep) +
          1;
      pointsToSkip = goodies.ROUND(
          goodies.fabs(sweepRange - (Vcc.typ - Gnd.typ + 2 * diodeDrop)) / 2 *
          sweepStep * numLinearPts);
    }
    //  numTablePts = goodies.ROUND(goodies.fabs(sweepRange/sweepStep))+1;
    numTablePts = (int)(goodies.fabs(sweepRange / sweepStep)) + 1;
    if (pullupData_p.size <= numTablePts) {
      VITableSize = pullupData_p.size;
      pointsToSkip = 1;
      numLinearPts = 5;
      numInnerPts = pullupData_p.size - 10;
      increment = numInnerPts;
    } else {
      VITableSize = numTablePts;
      increment = numInnerPts;
    }

    model_p.pullup = new ibisVItable();
    model_p.pullup.VIs = new ibisVItableEntry[VITableSize];
    if (numTablePts == 0)
      model_p.pullup.size = ConstantStuff.MAX_TABLE_SIZE;
    else
      model_p.pullup.size = VITableSize;

    /*------------------------------------------------------------------
     *   Since this is a pullup curve, we need to make the table data
     *   Vcc relative, i.e. Vtable = Vcc - Vout.  We'll do this by
     *   reading through the data and subtracting the table voltage
     *   from VccTyp.
     *-----------------------------------------------------------------*/
    for (i = 0; i < pullupData_p.size; i++)
      pullupData_p.VIs[i].v = Vcc.typ - pullupData_p.VIs[i].v;
    /*
    j = pullupData_p.size - 2;
    for(i = 0; i <  numLinearPts; i++)
      {
      model_p.pullup.VIs[i] = pullupData_p.VIs[j];
      j -= pointsToSkip;
      }
    j += pointsToSkip;
    currentMarker = i;
    */
    /**Skip data until we get to the start of the active region
     *  Do this only if pullupData size is more than the numTablePts
     */
    /*
    if(pullupData_p.size > numTablePts)
      {
      if(diodeDrop >= 0)
        {
        while (pullupData_p.VIs[j].v < -diodeDrop)
          j--;
        }
      else
        {
        while (pullupData_p.VIs[j].v > -diodeDrop)
          j--;
        }
      }
    */

    /**This is the 'interesting' part of the curve */
    /*
    for( i=currentMarker; i< (currentMarker + increment); i++)
      {
      model_p.pullup.VIs[i] = pullupData_p.VIs[j];
      j--;
      }
    currentMarker = i;
    */
    printf("\n numTablePts :" + numTablePts);
    printf("\n pullupData_p.size :" + pullupData_p.size);

    j = pullupData_p.size - 1;
    for (i = 0; i < numTablePts; i++) {
      model_p.pullup.VIs[i] = pullupData_p.VIs[j];
      j--;
    }

    /**Second Linear part of the curve */
    /*
    j++;
    for( i = currentMarker; i < (VITableSize -1); i++)
      {
      j-=pointsToSkip;
      if(j<0)
        j = 0;
      model_p.pullup.VIs[i] = pullupData_p.VIs[j];
      }

    model_p.pullup.VIs[model_p.pullup.size -1] = pullupData_p.VIs[0];
    */
    /**Apply the derating percentage */

    if (model_p.derateVIPct != 0)
      for (i = 0; i < VITableSize;
           i++) // changed from numTablePts to VITableSize
      {
        if (!(goodies.IS_USE_NA(model_p.pullup.VIs[i].i.min)))
          model_p.pullup.VIs[i].i.min -=
              model_p.pullup.VIs[i].i.min * (model_p.derateVIPct / 100);

        if (!(goodies.IS_USE_NA(model_p.pullup.VIs[i].i.max)))
          model_p.pullup.VIs[i].i.max +=
              model_p.pullup.VIs[i].i.max * (model_p.derateVIPct / 100);
      }
  } // if(pullupData != null)
  /*
  PullDownData
  */
  if (pulldownData_p != null) {
    setupV.setupVoltages(ConstantStuff.CURVE_TYPE_PULLDOWN, model_p);

    sweepStep = setupV.sweepStep;
    sweepRange = setupV.sweepRange;
    diodeDrop = setupV.diodeDrop;
    sweepStart = setupV.sweepStart;
    Vcc = setupV.Vcc;
    Gnd = setupV.Gnd;

    if (goodies.IS_ECL(model_p.modelType)) {
      numInnerPts = goodies.ROUND(goodies.fabs(sweepRange / sweepStep)) + 1;
      pointsToSkip = 0;
    } else {
      numInnerPts =
          goodies.ROUND(goodies.fabs(Vcc.typ - Gnd.typ + 2 * diodeDrop) /
                        sweepStep) +
          1;
      pointsToSkip = goodies.ROUND(
          goodies.fabs(sweepRange - (Vcc.typ - Gnd.typ + 2 * diodeDrop)) / 2 *
          sweepStep * numLinearPts);
    }
    //  numTablePts = goodies.ROUND(goodies.fabs(sweepRange/sweepStep))+1;
    numTablePts = (int)(goodies.fabs(sweepRange / sweepStep)) + 1;
    if (pulldownData_p.size <= numTablePts) {

      VITableSize = pulldownData_p.size;
      pointsToSkip = 1;
      numLinearPts = 5;
      numInnerPts = pulldownData_p.size - 10;
      increment = numInnerPts;
    } else {
      VITableSize = numTablePts;
      increment = numInnerPts;
    }

    model_p.pulldown = new ibisVItable();
    model_p.pulldown.VIs = new ibisVItableEntry[VITableSize];
    if (numTablePts == 0)
      model_p.pulldown.size = ConstantStuff.MAX_TABLE_SIZE;
    else
      model_p.pulldown.size = VITableSize;
    /*
    j = 0;
    for(i = 0; i <  numLinearPts; i++)
      {
      model_p.pulldown.VIs[i] = pulldownData_p.VIs[j];
      j += pointsToSkip;
      }
    j -= pointsToSkip;
    currentMarker = i;

    if(pulldownData_p.size > numTablePts)
      {
      if(diodeDrop >= 0)
        {
        while (pulldownData_p.VIs[j].v < -diodeDrop)
          j++;
        }
      else
        {
        while (pulldownData_p.VIs[j].v > -diodeDrop)
          j++;
        }
      }
    else
      j++;

    for( i=currentMarker; i< currentMarker + numInnerPts; i++)
      {
      model_p.pulldown.VIs[i] = pulldownData_p.VIs[j];
     j++;
      }
    currentMarker = i;
    j--;

    for( i = currentMarker; i < (VITableSize -1); i++)
      {
      j+=pointsToSkip;
      if(j>pulldownData_p.size)
        j = pulldownData_p.size-1;
      model_p.pulldown.VIs[i] = pulldownData_p.VIs[j];
      }
    */
    j = 0;
    for (i = currentMarker; i < numTablePts; i++) {
      model_p.pulldown.VIs[i] = pulldownData_p.VIs[j];
      j++;
    }

    model_p.pulldown.VIs[model_p.pulldown.size - 1] =
        pulldownData_p.VIs[pulldownData_p.size - 1]; // removed -2

    if (model_p.derateVIPct != 0)

      for (i = 0; i < VITableSize; i++) {
        if (!(goodies.IS_USE_NA(model_p.pulldown.VIs[i].i.min)))
          model_p.pulldown.VIs[i].i.min -=
              model_p.pulldown.VIs[i].i.min * (model_p.derateVIPct / 100);

        if (!(goodies.IS_USE_NA(model_p.pulldown.VIs[i].i.max)))
          model_p.pulldown.VIs[i].i.max +=
              model_p.pulldown.VIs[i].i.max * (model_p.derateVIPct / 100);
      }
  } // if(pulldownData != null)
  /*
  PowerClampData
  */
  if (powerClampData_p != null) {
    setupV.setupVoltages(ConstantStuff.CURVE_TYPE_POWER_CLAMP, model_p);

    sweepStep = setupV.sweepStep;
    sweepRange = setupV.sweepRange;
    diodeDrop = setupV.diodeDrop;
    sweepStart = setupV.sweepStart;
    Vcc = setupV.Vcc;
    Gnd = setupV.Gnd;

    // numTablePts = goodies.ROUND(goodies.fabs(sweepRange/sweepStep)+1);
    numTablePts = (int)(goodies.fabs(sweepRange / sweepStep) + 1);
    model_p.power_clamp = new ibisVItable();
    model_p.power_clamp.VIs = new ibisVItableEntry[numTablePts];

    // initializing all the data structures inside power_clamp
    for (int m = 0; m < numTablePts; m++) {
      model_p.power_clamp.VIs[m] = new ibisVItableEntry();
    }

    if (numTablePts == 0)
      model_p.power_clamp.size = ConstantStuff.MAX_TABLE_SIZE;
    else
      model_p.power_clamp.size = numTablePts;

    i = numTablePts - 1;

    j = 0;
    while ((i >= 0) && (powerClampData_p.VIs[i].v >= Vcc.typ)) {
      model_p.power_clamp.VIs[j].v = Vcc.typ - powerClampData_p.VIs[i].v;
      model_p.power_clamp.VIs[j].i.typ = powerClampData_p.VIs[i].i.typ;
      model_p.power_clamp.VIs[j].i.min = powerClampData_p.VIs[i].i.min;
      model_p.power_clamp.VIs[j].i.max = powerClampData_p.VIs[i].i.max;
      i--;
      j++;
    }

    if (model_p.derateVIPct != 0)
      for (i = 0; i < numTablePts; i++) {
        if (!(goodies.IS_USE_NA(model_p.power_clamp.VIs[i].i.min)))
          model_p.power_clamp.VIs[i].i.min -=
              model_p.power_clamp.VIs[i].i.min * (model_p.derateVIPct / 100);

        if (!(goodies.IS_USE_NA(model_p.power_clamp.VIs[i].i.max)))
          model_p.power_clamp.VIs[i].i.max +=
              model_p.power_clamp.VIs[i].i.max * (model_p.derateVIPct / 100);
      }
  }

  /*
  GndClampData
  */
  if (gndClampData_p != null) {
    setupV.setupVoltages(ConstantStuff.CURVE_TYPE_GND_CLAMP, model_p);
    sweepStep = setupV.sweepStep;
    sweepRange = setupV.sweepRange;
    diodeDrop = setupV.diodeDrop;
    sweepStart = setupV.sweepStart;
    Vcc = setupV.Vcc;
    Gnd = setupV.Gnd;

    //  numTablePts = goodies.ROUND(goodies.fabs(sweepRange/sweepStep)+1);
    numTablePts = (int)(goodies.fabs(sweepRange / sweepStep) + 1);
    //	only initialize when needed - null otherwise(in ibismodel.java)
    model_p.gnd_clamp = new ibisVItable();
    model_p.gnd_clamp.VIs = new ibisVItableEntry[numTablePts];

    // initializing all the data structures inside gnd_clamp
    for (int m = 0; m < numTablePts; m++) {
      model_p.gnd_clamp.VIs[m] = new ibisVItableEntry();
    }

    if (numTablePts == 0)
      model_p.gnd_clamp.size = ConstantStuff.MAX_TABLE_SIZE;
    else
      model_p.gnd_clamp.size = numTablePts;

    j = 0;
    while ((j < numTablePts) && (gndClampData_p.VIs[j].v <= Vcc.typ)) {
      model_p.gnd_clamp.VIs[j] = gndClampData_p.VIs[j];
      j++;
    }

    if (model_p.derateVIPct != 0)
      for (i = 0; i < numTablePts; i++) {
        if (!(goodies.IS_USE_NA(model_p.gnd_clamp.VIs[i].i.min)))
          model_p.gnd_clamp.VIs[i].i.min -=
              model_p.gnd_clamp.VIs[i].i.min * (model_p.derateVIPct / 100);

        if (!(goodies.IS_USE_NA(model_p.gnd_clamp.VIs[i].i.max)))
          model_p.gnd_clamp.VIs[i].i.max +=
              model_p.gnd_clamp.VIs[i].i.max * (model_p.derateVIPct / 100);
      }
  }

  return 0;
} // method sortVIData
}; // class sortVIData

/*	CLASS:		sortVISeriesData
 *
 *	DESCRIPTION: Sorts VI Series data and fills the
 * 		VISeriesData tables.
 *
 */

ibisVItable VISeriesData;
ibisTypMinMax Vcc;

int sortVISeriesData() {
  ibisVItable tempVIData1 = new ibisVItable();
  ibisVItable tempVIData2 = new ibisVItable();
  int VITableSize = 0;

  if (VISeriesData.size < ConstantStuff.MAX_TABLE_SIZE)
    VITableSize = VISeriesData.size;
  else
    VITableSize = ConstantStuff.MAX_TABLE_SIZE;

  tempVIData1.VIs = new ibisVItableEntry[VITableSize];
  tempVIData2.VIs = new ibisVItableEntry[VITableSize];

  for (int m = 0; m < VITableSize; m++) {
    tempVIData1.VIs[m] = new ibisVItableEntry();
    tempVIData2.VIs[m] = new ibisVItableEntry();
  }

  for (int i = 0; i < VITableSize; i++) {
    tempVIData1.VIs[i].v = Vcc.typ - VISeriesData.VIs[i].v;
    tempVIData1.VIs[i].i = VISeriesData.VIs[i].i;
  }

  for (int i = 0; i < VITableSize; i++) {
    tempVIData2.VIs[i] = tempVIData1.VIs[VITableSize - 1 - i];
  }
  tempVIData2.size = VISeriesData.size;
  VISeriesData = tempVIData2;
  return 0;
} // method sortVISeriesData
}; // class sortVISeriesData

/*	CLASS:		analyzePin
 *
 *	DESCRIPTION:  called by analyzComponent to characterize
 * 		      each pin and run spice on them
 *
 */

ibisPin currentPin; // inout

int analyzePin(ibisPin enablePin,              // in
               ibisPin inputPin,               // in
               ibisPin pullupPin,              // in
               ibisPin pulldownPin,            // in
               ibisPin powerClampPin,          // in
               ibisPin gndClampPin,            // in
               int spiceType,                  // in
               string spiceFile,               // in
               string seriesSpiceFile,         // in
               string spiceCommand,            // in
               int iterate,                    // in
               int cleanup) // in
{
  int result = 0;
  int i = 0;
  int index = 0;
  ibisVItable pullupData = null, puDisabledData = null, pulldownData = null,
              pdDisabledData = null, powerClampData = null, gndClampData = null;

  waveTableList risingWave = new waveTableList();
  waveTableList fallingWave = new waveTableList();

  // Series
  VITableList seriesVITable = new VITableList();
  int index2 = 0;
  double currentVds = 0;
  VdsList VdsList1 = new VdsList();
  // Series

  ibisTypMinMax Vcc, VccClamp, Gnd, GndClamp, sweepStart, sweepStart_pc;
  double sweepRange = 0, sweepRange_pc = 0, sweepStep = 0, sweepStep_pc = 0,
         diodeDrop = 0, diodeDrop_pc = 0, subtractStart = 0, subtractEnd = 0;
  setupVoltages setupVoltages1 = new setupVoltages();
  sortVIData sortVIData1 = new sortVIData();
  sortVISeriesData sortSeriesData1 = new sortVISeriesData();
  //-----------Code----------------------

  generateVICurve genVICurve1 = new generateVICurve();
  generateRampData genRmpData1 = new generateRampData();
  generateWaveData genWaveData1 = new generateWaveData();

  if (currentPin.seriesModel != null) {
    if (goodies.THIS_MODEL_NEEDS_SERIES_VI_DATA(
            currentPin.seriesModel.modelType)) {
      printf("\nThis Model Needs series VI Data ..");
      setupVoltages1.setupVoltages(ConstantStuff.CURVE_TYPE_SERIES_VI,
                                   currentPin.seriesModel);

      sweepStep = setupVoltages1.sweepStep;
      sweepRange = setupVoltages1.sweepRange;
      diodeDrop = setupVoltages1.diodeDrop;
      sweepStart = setupVoltages1.sweepStart;
      Vcc = setupVoltages1.Vcc;
      Gnd = setupVoltages1.Gnd;

      VdsList1 = currentPin.seriesModel.seriesModel.series_MOSFET.vdslist;

      VdsList1.gototop();
      index2 = 0;
      VdsList1.gototop();
      while ((index2 < ConstantStuff.MAX_SERIES_TABLES) &&
             (VdsList1.current != null)) {
        genVICurve1.VIData = VdsList1.current.seriesVITable;
        currentVds = VdsList1.current.V;

        result += genVICurve1.generateVICurve(
            currentPin, enablePin, inputPin, pullupPin, pulldownPin,
            powerClampPin, gndClampPin, Vcc, Gnd, VccClamp, GndClamp,
            sweepStart, sweepRange, sweepStep,
            ConstantStuff.CURVE_TYPE_SERIES_VI, spiceType, seriesSpiceFile,
            spiceCommand, ConstantStuff.ENABLE_OUTPUT,
            ConstantStuff.OUTPUT_HIGH, iterate, cleanup, currentVds, index2);

        sortSeriesData1.VISeriesData = genVICurve1.VIData;
        sortSeriesData1.Vcc = Vcc;
        sortSeriesData1.sortVISeriesData();
        VdsList1.current.seriesVITable = sortSeriesData1.VISeriesData;
        index2++;
        VdsList1.next();
      }
    }
  }

  if (goodies.THIS_MODEL_NEEDS_PULLUP_DATA(currentPin.model.modelType)) {
    printf("\nThis Model Needs PullupData ..");
    setupVoltages1.setupVoltages(ConstantStuff.CURVE_TYPE_POWER_CLAMP,
                                 currentPin.model);

    sweepStep = setupVoltages1.sweepStep;
    sweepRange = setupVoltages1.sweepRange;
    diodeDrop = setupVoltages1.diodeDrop;
    sweepStart = setupVoltages1.sweepStart;
    VccClamp = setupVoltages1.Vcc;
    GndClamp = setupVoltages1.Gnd;

    setupVoltages1.setupVoltages(ConstantStuff.CURVE_TYPE_PULLUP,
                                 currentPin.model);

    sweepStep = setupVoltages1.sweepStep;
    sweepRange = setupVoltages1.sweepRange;
    diodeDrop = setupVoltages1.diodeDrop;
    sweepStart = setupVoltages1.sweepStart;
    Vcc = setupVoltages1.Vcc;
    Gnd = setupVoltages1.Gnd;

    result += genVICurve1.generateVICurve(
        currentPin, enablePin, inputPin, pullupPin, pulldownPin, powerClampPin,
        gndClampPin, Vcc, Gnd, VccClamp, GndClamp, sweepStart, sweepRange,
        sweepStep, ConstantStuff.CURVE_TYPE_PULLUP, spiceType, spiceFile,
        spiceCommand, ConstantStuff.ENABLE_OUTPUT, ConstantStuff.OUTPUT_HIGH,
        iterate, cleanup, 0, 0);

    pullupData = genVICurve1.VIData;

    if (enablePin != null) {
      result += genVICurve1.generateVICurve(
          currentPin, enablePin, inputPin, pullupPin, pulldownPin,
          powerClampPin, gndClampPin, Vcc, Gnd, VccClamp, GndClamp, sweepStart,
          sweepRange, sweepStep, ConstantStuff.CURVE_TYPE_DISABLED_PULLUP,
          spiceType, spiceFile, spiceCommand, ConstantStuff.DISABLE_OUTPUT,
          ConstantStuff.OUTPUT_HIGH, iterate, cleanup, 0, 0);
      puDisabledData = genVICurve1.VIData;

      /*----------------------------------------------------------------
       * If we got valid data (i.e. no errors), continue with the work
       *---------------------------------------------------------------*/
      if ((puDisabledData != null) && (pullupData != null)) {

        /*------------------------------------------------------------
         * The first thing we do is figure out the range of the power
         * clamp curve.
         *-----------------------------------------------------------*/
        setupVoltages1.setupVoltages(ConstantStuff.CURVE_TYPE_POWER_CLAMP,
                                     currentPin.model);

        // Changed code to subtract the entire 'clamp curve(power and gnd)'
        // from the pullupData to result in the new pullupData. This is
        // repeated for pullDown curve.

        i = 0;
        // debug	    printf("PullupDataSize = "+ pullupData.size);
        while (i < pullupData.size) {
          if ((goodies.IS_USE_NA(pullupData.VIs[i].i.typ)) ||
              (goodies.IS_USE_NA(puDisabledData.VIs[i].i.typ)))
            pullupData.VIs[i].i.typ = ConstantStuff.USE_NA;
          else {
            pullupData.VIs[i].i.typ -= puDisabledData.VIs[i].i.typ;
            // debug			printf("PpullupData.VIs[i].i.typ = "+
            // pullupData.VIs[i].i.typ);
          }
          if ((goodies.IS_USE_NA(pullupData.VIs[i].i.min)) ||
              (goodies.IS_USE_NA(puDisabledData.VIs[i].i.min)))
            pullupData.VIs[i].i.min = ConstantStuff.USE_NA;
          else
            pullupData.VIs[i].i.min -= puDisabledData.VIs[i].i.min;
          if ((goodies.IS_USE_NA(pullupData.VIs[i].i.max)) ||
              (goodies.IS_USE_NA(puDisabledData.VIs[i].i.max)))
            pullupData.VIs[i].i.max = ConstantStuff.USE_NA;
          else
            pullupData.VIs[i].i.max -= puDisabledData.VIs[i].i.max;

          i++;
        }
      } else if (pullupData != null) {
      }

    } // if(enablePin !=null)
  }   // if ( THIS_MODEL_NEEDS_PULLUP_DATA)

  if (goodies.THIS_MODEL_NEEDS_PULLDOWN_DATA(currentPin.model.modelType)) {
    printf("This Model Needs PulldownData ..");

    /*----------------------------------------------------------------
     * The pulldown analysis is identical to the pullup analysis, so I
     * won't comment here.
     *---------------------------------------------------------------*/
    setupVoltages1.setupVoltages(ConstantStuff.CURVE_TYPE_GND_CLAMP,
                                 currentPin.model);

    sweepStep = setupVoltages1.sweepStep;
    sweepRange = setupVoltages1.sweepRange;
    diodeDrop = setupVoltages1.diodeDrop;
    sweepStart = setupVoltages1.sweepStart;
    VccClamp = setupVoltages1.Vcc;
    GndClamp = setupVoltages1.Gnd;

    setupVoltages1.setupVoltages(ConstantStuff.CURVE_TYPE_PULLDOWN,
                                 currentPin.model);

    sweepStep = setupVoltages1.sweepStep;
    sweepRange = setupVoltages1.sweepRange;
    diodeDrop = setupVoltages1.diodeDrop;
    sweepStart = setupVoltages1.sweepStart;
    Vcc = setupVoltages1.Vcc;
    Gnd = setupVoltages1.Gnd;

    result += genVICurve1.generateVICurve(
        currentPin, enablePin, inputPin, pullupPin, pulldownPin, powerClampPin,
        gndClampPin, Vcc, Gnd, VccClamp, GndClamp, sweepStart, sweepRange,
        sweepStep, ConstantStuff.CURVE_TYPE_PULLDOWN, spiceType, spiceFile,
        spiceCommand, ConstantStuff.ENABLE_OUTPUT, ConstantStuff.OUTPUT_LOW,
        iterate, cleanup, 0, 0);
    pulldownData = genVICurve1.VIData;

    if (enablePin != null) {
      result += genVICurve1.generateVICurve(
          currentPin, enablePin, inputPin, pullupPin, pulldownPin,
          powerClampPin, gndClampPin, Vcc, Gnd, VccClamp, GndClamp, sweepStart,
          sweepRange, sweepStep, ConstantStuff.CURVE_TYPE_DISABLED_PULLDOWN,
          spiceType, spiceFile, spiceCommand, ConstantStuff.DISABLE_OUTPUT,
          ConstantStuff.OUTPUT_LOW, iterate, cleanup, 0, 0);
      pdDisabledData = genVICurve1.VIData;

      if ((pdDisabledData != null) && (pulldownData != null)) {

        setupVoltages1.setupVoltages(ConstantStuff.CURVE_TYPE_GND_CLAMP,
                                     currentPin.model);

        i = 0;
        while (i < pulldownData.size) {
          if ((goodies.IS_USE_NA(pulldownData.VIs[i].i.typ)) ||
              (goodies.IS_USE_NA(pdDisabledData.VIs[i].i.typ)))
            pulldownData.VIs[i].i.typ = ConstantStuff.USE_NA;
          else
            pulldownData.VIs[i].i.typ -= pdDisabledData.VIs[i].i.typ;
          if ((goodies.IS_USE_NA(pulldownData.VIs[i].i.min)) ||
              (goodies.IS_USE_NA(pdDisabledData.VIs[i].i.min)))
            pulldownData.VIs[i].i.min = ConstantStuff.USE_NA;
          else
            pulldownData.VIs[i].i.min -= pdDisabledData.VIs[i].i.min;
          if ((goodies.IS_USE_NA(pulldownData.VIs[i].i.max)) ||
              (goodies.IS_USE_NA(pdDisabledData.VIs[i].i.max)))
            pulldownData.VIs[i].i.max = ConstantStuff.USE_NA;
          else
            pulldownData.VIs[i].i.max -= pdDisabledData.VIs[i].i.max;
          i++;
        }
      } else if (pulldownData != null) {
      }
    }
  }

  if (goodies.THIS_MODEL_NEEDS_POWER_CLAMP_DATA(currentPin.model.modelType)) {
    printf("\nThis Model Needs Power ClampData ..");

    setupVoltages1.setupVoltages(ConstantStuff.CURVE_TYPE_PULLUP,
                                 currentPin.model);

    sweepStep = setupVoltages1.sweepStep;
    sweepRange = setupVoltages1.sweepRange;
    diodeDrop = setupVoltages1.diodeDrop;
    sweepStart = setupVoltages1.sweepStart;
    Vcc = setupVoltages1.Vcc;
    Gnd = setupVoltages1.Gnd;

    setupVoltages1.setupVoltages(ConstantStuff.CURVE_TYPE_POWER_CLAMP,
                                 currentPin.model);

    sweepStep = setupVoltages1.sweepStep;
    sweepRange = setupVoltages1.sweepRange;
    diodeDrop = setupVoltages1.diodeDrop;
    sweepStart = setupVoltages1.sweepStart;
    VccClamp = setupVoltages1.Vcc;
    GndClamp = setupVoltages1.Gnd;

    result += genVICurve1.generateVICurve(
        currentPin, enablePin, inputPin, pullupPin, pulldownPin, powerClampPin,
        gndClampPin, Vcc, Gnd, VccClamp, GndClamp, sweepStart, sweepRange,
        sweepStep, ConstantStuff.CURVE_TYPE_POWER_CLAMP, spiceType, spiceFile,
        spiceCommand, ConstantStuff.DISABLE_OUTPUT, ConstantStuff.OUTPUT_HIGH,
        iterate, cleanup, 0, 0);
    powerClampData = genVICurve1.VIData;
  }

  if (goodies.THIS_MODEL_NEEDS_GND_CLAMP_DATA(currentPin.model.modelType)) {
    printf("This Model Needs GND ClampData ..");
    setupVoltages1.setupVoltages(ConstantStuff.CURVE_TYPE_PULLDOWN,
                                 currentPin.model);

    sweepStep = setupVoltages1.sweepStep;
    sweepRange = setupVoltages1.sweepRange;
    diodeDrop = setupVoltages1.diodeDrop;
    sweepStart = setupVoltages1.sweepStart;
    Vcc = setupVoltages1.Vcc;
    Gnd = setupVoltages1.Gnd;

    setupVoltages1.setupVoltages(ConstantStuff.CURVE_TYPE_GND_CLAMP,
                                 currentPin.model);

    sweepStep = setupVoltages1.sweepStep;
    sweepRange = setupVoltages1.sweepRange;
    diodeDrop = setupVoltages1.diodeDrop;
    sweepStart = setupVoltages1.sweepStart;
    VccClamp = setupVoltages1.Vcc;
    GndClamp = setupVoltages1.Gnd;

    result += genVICurve1.generateVICurve(
        currentPin, enablePin, inputPin, pullupPin, pulldownPin, powerClampPin,
        gndClampPin, Vcc, Gnd, VccClamp, GndClamp, sweepStart, sweepRange,
        sweepStep, ConstantStuff.CURVE_TYPE_GND_CLAMP, spiceType, spiceFile,
        spiceCommand, ConstantStuff.DISABLE_OUTPUT, ConstantStuff.OUTPUT_LOW,
        iterate, cleanup, 0, 0);
    gndClampData = genVICurve1.VIData;
  }

  sortVIData1.sortVIData(currentPin.model, pullupData, pulldownData,
                         powerClampData, gndClampData);
  /*
   *
   *  Need to energize the clamp structures for these guys too!!!!!
   *
   */

  if (goodies.THIS_MODEL_NEEDS_TRANSIENT_DATA(currentPin.model.modelType)) {
    printf("This Model Needs Transient Data ..");
    setupVoltages1.setupVoltages(ConstantStuff.CURVE_TYPE_POWER_CLAMP,
                                 currentPin.model);

    sweepStep = setupVoltages1.sweepStep;
    sweepRange = setupVoltages1.sweepRange;
    diodeDrop = setupVoltages1.diodeDrop;
    sweepStart = setupVoltages1.sweepStart;
    VccClamp = setupVoltages1.Vcc;
    GndClamp = setupVoltages1.Gnd;

    setupVoltages1.setupVoltages(ConstantStuff.CURVE_TYPE_RISING_RAMP,
                                 currentPin.model);

    sweepStep = setupVoltages1.sweepStep;
    sweepRange = setupVoltages1.sweepRange;
    diodeDrop = setupVoltages1.diodeDrop;
    sweepStart = setupVoltages1.sweepStart;
    Vcc = setupVoltages1.Vcc;
    Gnd = setupVoltages1.Gnd;

    result += genRmpData1.generateRampData(
        currentPin, enablePin, inputPin, pullupPin, pulldownPin, powerClampPin,
        gndClampPin, Vcc, Gnd, VccClamp, GndClamp,
        ConstantStuff.CURVE_TYPE_RISING_RAMP, spiceType, spiceFile,
        spiceCommand, iterate, cleanup);
    result += genRmpData1.generateRampData(
        currentPin, enablePin, inputPin, pullupPin, pulldownPin, powerClampPin,
        gndClampPin, Vcc, Gnd, VccClamp, GndClamp,
        ConstantStuff.CURVE_TYPE_FALLING_RAMP, spiceType, spiceFile,
        spiceCommand, iterate, cleanup);

    risingWave = currentPin.model.risingWaveList;
    fallingWave = currentPin.model.fallingWaveList;

    index = 0;
    risingWave.gototop();
    while ((index < ConstantStuff.MAX_WAVEFORM_TABLES) &&
           (risingWave.current != null)) {
      genWaveData1.currentWave = risingWave.current;

      result += genWaveData1.generateWaveData(
          currentPin, enablePin, inputPin, pullupPin, pulldownPin,
          powerClampPin, gndClampPin, Vcc, Gnd, VccClamp, GndClamp,
          ConstantStuff.CURVE_TYPE_RISING_WAVE, spiceType, spiceFile,
          spiceCommand, iterate, cleanup, index);
      index++;
      risingWave.next();
    }

    index = 0;
    fallingWave.gototop();
    while ((index < ConstantStuff.MAX_WAVEFORM_TABLES) &&
           (fallingWave.current != null)) {
      genWaveData1.currentWave = fallingWave.current;
      result += genWaveData1.generateWaveData(
          currentPin, enablePin, inputPin, pullupPin, pulldownPin,
          powerClampPin, gndClampPin, Vcc, Gnd, VccClamp, GndClamp,
          ConstantStuff.CURVE_TYPE_FALLING_WAVE, spiceType, spiceFile,
          spiceCommand, iterate, cleanup, index);
      index++;
      fallingWave.next();
    }
  }

  return (result);
} // analyzePin method
}; // class analyzePin

/*	CLASS:		analyzeComponent
 *
 *	DESCRIPTION:  called by main program to characterize
 * 		      each component for the model.
 *
 */

cListContainer CLC;
ibisPin currentPin;

int analyzeComponent(int spiceType, int iterate, int cleanup,
                     string spiceCommand) {
  int result = 0;
  ibisPin pullupPin;
  ibisPin pulldownPin;
  ibisPin powerClampPin;
  ibisPin gndClampPin;
  ibisPin enablePin_P = new ibisPin();
  ibisPin inputPin = new ibisPin();

  ibisComponent componentOut = new ibisComponent();
  findSupplyPins findSupplyPins1 = new findSupplyPins();
  getMatchingPin getMatchingPin1 = new getMatchingPin();
  analyzePin analyzePin1 = new analyzePin();
  analyzePin analyzePin2 = new analyzePin();
  ibisComponent componentIn; // = compC.component;
  pinsList tempPinsList = new pinsList();

  CLC.cListCont.gototop();
  for (int i1 = 0; i1 < CLC.cListCont.count; i1++) {
    componentIn = CLC.cListCont.current;
    tempPinsList = componentIn.pList;
    tempPinsList.gototop();

    if (componentIn.pList != null) {
      printf("\n++++\nAnalyzing component " + componentIn.component);

      componentIn.pList.gototop();
      for (int i = 0; i < componentIn.pList.count; i++) {
        currentPin = componentIn.pList.current;

        printf("\nAnalyzing pin '" + currentPin.pinName + "'");
        printf("modelName for above pin " + currentPin.modelName);
        enablePin_P = null;
        inputPin = null;

        /*------------------------------------------------------
         * If this pin needs analysis and it has not yet been
         * analyzed, find its power, ground, enable and input pins, and call
         * analyzePin to generate the appropriate model curves.
         *-----------------------------------------------------*/

        // series comment
        // there might be cases when the normal model has been analyzed, but
        // the series model has not
        if ((goodies.THIS_PIN_NEEDS_ANALYSIS(currentPin.modelName)) &&
            (currentPin.model.hasBeenAnalyzed == 0)) {
          printf("THIS_PIN_NEEDS_ANALYSIS");

          result = findSupplyPins1.findPins(currentPin, tempPinsList,
                                            componentIn.hasPinMapping);
          pullupPin = findSupplyPins1.pullupPin;
          pulldownPin = findSupplyPins1.pulldownPin;
          powerClampPin = findSupplyPins1.powerClampPin;
          gndClampPin = findSupplyPins1.gndClampPin;

          componentIn.pList.current = currentPin;

          if (result == 0) {
            if (!currentPin.enablePin.equalsIgnoreCase("")) {
              enablePin_P = getMatchingPin1.getMatchingPin(currentPin.enablePin,
                                                           componentIn.pList);

              componentIn.pList.current = currentPin;
              if (enablePin_P ==
                  null) // If it is STILL null, it wasnt in the pin list
              {
                printf("Could'nt find enable pin for " +
                       currentPin.pinName); // modify for refined use
                result++;
              }
            } // if enable pin != ""
            if (!currentPin.inputPin.equalsIgnoreCase("")) {
              inputPin = getMatchingPin1.getMatchingPin(currentPin.inputPin,
                                                        componentIn.pList);

              componentIn.pList.current = currentPin;
              if (inputPin ==
                  null) // If it is STILL null, it wasnt in the pin list
              {
                printf("Could'nt find input pin for " +
                       currentPin.pinName); // modify for refined use
                result++;
              }
            } // if enable pin != ""
            if (result == 0) {
              printf("start analyzing pin .. " + currentPin.pinName);

              analyzePin1.currentPin = currentPin;
              result = analyzePin1.analyzePin(
                  enablePin_P, inputPin, pullupPin, pulldownPin, powerClampPin,
                  gndClampPin, spiceType, componentIn.spiceFile,
                  componentIn.seriesSpiceFile, spiceCommand, iterate, cleanup);
              currentPin = analyzePin1.currentPin;
            }
            if (result > 0) {
              printf("Error in Analysis for Pin " +
                     currentPin.pinName); // modify for refined use
            }                             // if (result)
            else
              currentPin.model.hasBeenAnalyzed++;
          } // if (!result)
        }   // if this pin needs analysis
        componentIn.pList.next();
      } // for
    }   // if(componentIn.pins!=null)
    else {
      printf(
          ". Please specify the pin list using the [Pin] Keyword"); // modify
                                                                    // for
                                                                    // refined
                                                                    // use
      result++;
    }

    CLC.cListCont.next();
  } // for

  return (result);
} // public ibisComponent analyzeComponent()

