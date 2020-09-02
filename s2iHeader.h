/********************************************************************************
*FileName	: s2iHeader.java
*Description	: This file contains the #Define and other important
*		: declarations that are needed for s2ibis3
*		:
*		: North Carolina State University
*		: Electronics Research Laboratory
********************************************************************************

$Log: s2iHeader.java,v $
Revision 1.6  2006/03/27 18:05:09  akvarma
1. Changed SWEEP_STEP_DEFAULT to 0.01
2. Changed WAVE_POINTS_DEFAULT to 100 from 51
3. Changed MAX_FILENAME_BASE_LENGTH to 20 from 8
4. Changed VERSION_STRING to 1.1
5. Fixed pulse generation for ELDO for transient runs. Put in 'pulsewidth'
instead of 'falltime'

Revision 1.5  2005/02/24 22:33:42  akvarma
1. Changed the version string to 1.0
2. modified spice command for ELDO and to add extSpiceCmd

Revision 1.4  2004/04/13 22:55:02  akvarma
Fixed bugs. a) missing ')' in pulse line in .spi files. b) Changed modelFileTyp,
Min and Max = null to "". This is done to remove necessity of modelFile. Also
fixed setupSpiceInputFile class in s2iSpice.java. c) Fixed Rload default to 50
and not 0. d)fixed simTime default to SIM_TIME_DEFAULT and not hard code to 0.
e) Introduced HSPICE_INGOLD_DEFAULT in order to change spice display to
engineering or non engineering units in the ConstantStuff interface of this
file.

Changed current version to 0.3Beta.

Revision 1.3  2003/11/24 05:30:53  akvarma
Added series MOSFET functionality. Changed current version to 0.2Beta. fixed
convergence error. Convergence fix still works only for HSpice. Cleaned up code.

Revision 1.2  2003/07/31 23:38:50  akvarma
Revised to make RisingWave and FallingWave tables as list so that multiple
tables can be generated.

Revision 1.1  2003/07/31 23:12:34  akvarma
Initial revision


* Copyright 2003, North Carolina State University.
*
* North Carolina State University (NCSU) and the author hereby disclaim
* all implied warranties, including the implied warranties of merchant-
* ability and fitness for a particular purpose. NCSU is not liable for
* any damages incurred by the use of this software and/or documentation,
* including direct, indirect, special, incidental, or consequential
* damages.
*
* NCSU grants the bearer the right to modify, copy, and redistribute
* this software and documentation, but requests that NCSU be acknowledged
* for its contribution in the resulting product.
*
**/

#include <string>
using namespace std;
struct ConstantStuff {
  const string VERSION_STRING = "1.1";
  const int UNDEFINED = 0;
  const int OUTPUT_LOW = 0;
  const int OUTPUT_HIGH = 1;
  const int OUTPUT_FALLING = 0;
  const int OUTPUT_RISING = 1;
  const int DISABLE_OUTPUT = 0;
  const int ENABLE_OUTPUT = 1;

  const int TYP_CASE = 0;
  const int MIN_CASE = -1;
  const int MAX_CASE = 1;

  const int NUM_PTS_LINEAR_REGION = 10;

  /* ibis version 1.0 Restriction */
  const int MAX_TABLE_SIZE = 100;
  const int MAX_MANUFACTURERS_NAME_LENGTH = 40;
  const int MAX_FILENAME_BASE_LENGTH = 20;
  const string FILENAME_EXTENSION = "ibs";
  const int FILENAME_EXTENSION_LENGTH = 3;
  const int MAX_PIN_NAME_LENGTH = 5;
  const int MAX_SIGNAL_NAME_LENGTH = 20;
  const int MAX_MODEL_NAME_LENGTH = 20;
  const int MAX_R_PIN_STRING_LENGTH = 9;
  const int MAX_L_PIN_STRING_LENGTH = 9;
  const int MAX_C_PIN_STRING_LENGTH = 9;
  const int MAX_LINE_LENGTH = 80;
  const int MAX_COMPONENT_NAME_LENGTH = 40;
  const int MAX_FILENAME_LENGTH =
      MAX_FILENAME_BASE_LENGTH + 1 + FILENAME_EXTENSION_LENGTH;

  /* additional ibis version 2.0 Restriction */
  const int MAX_PACKAGE_MODEL_NAME_LENGTH = 40;
  const int MAX_PIN_MAPPING_NAME_LENGTH = 15;
  const int MAX_DFF_PIN_NAME_LENGTH = 5;
  const int MAX_INV_PIN_LEBGTH = 5;
  const int MAX_VDIFF_TYP_LENGTH = 9;
  const int MAX_TEDELAY_MAX_LENGTH = 9;
  const int MAX_WAVEFORM_TABLES = 100;
  const int MAX_SERIES_TABLES = 100;

  const int MAX_FILE_REV_LENGTH = 4;
  const int MAX_TOK_LEN = 40;
  const int MAX_DATE_STRING_LENGTH = 40;
  const int MAX_IBIS_STRING_LENGTH = 1024;
  /* Applies to all other strings such
   * as [Notes], [Disclaimer] etc.
   * The longer strings do not indicate an
   * error in the input file but they are
   * truncated to this length for internal
   * storage.
   */

  const int IBIS_PRINT_WIDTH = 80;

  const double USE_NA = -1.33287736222333E20;
  const double NOT_USED = -1.33287736222333E18;
  const double Tolerance = 1E15;
  /* VI Curve types */
  const int CURVE_TYPE_PULLUP = 0;
  const int CURVE_TYPE_PULLDOWN = 1;
  const int CURVE_TYPE_POWER_CLAMP = 2;
  const int CURVE_TYPE_GND_CLAMP = 3;
  const int CURVE_TYPE_DISABLED_PULLUP = 4;
  const int CURVE_TYPE_DISABLED_PULLDOWN = 5;
  const int CURVE_TYPE_RISING_RAMP = 6;
  const int CURVE_TYPE_FALLING_RAMP = 7;
  const int CURVE_TYPE_RISING_WAVE = 8;
  const int CURVE_TYPE_FALLING_WAVE = 9;
  /*series*/ const int CURVE_TYPE_SERIES_VI = 10;

  const int majorReleaseIncrement = 1000;
  const int minorReleaseIncrement = 50;

  const int VERSION_ONE_ZERO = goodies.VERSION_ID(1, 0, 0);
  const int VERSION_ONE_ONE = goodies.VERSION_ID(1, 1, 0);
  const int VERSION_TWO_ZERO = goodies.VERSION_ID(2, 0, 0);
  const int VERSION_TWO_ONE = goodies.VERSION_ID(2, 1, 0);

  /*s2ibis3*/ const int VERSION_THREE_TWO = goodies.VERSION_ID(3, 2, 0);

  /* Model Types */
  const int MODEL_TYPE_UNDEFINED = UNDEFINED;

  /* version 1.0 */
  const int MODEL_TYPE_INPUT = goodies.VERSION_ID(1, 0, 1);
  const int MODEL_TYPE_OUTPUT = goodies.VERSION_ID(1, 0, 2);
  const int MODEL_TYPE_OPEN_DRAIN = goodies.VERSION_ID(1, 0, 4);
  const int MODEL_TYPE_3_STATE = goodies.VERSION_ID(1, 0, 3);
  const int MODEL_TYPE_I_O = goodies.VERSION_ID(1, 0, 5);
  /* version 2.0 */
  const int MODEL_TYPE_I_O_OPEN_DRAIN = goodies.VERSION_ID(2, 0, 1);
  const int MODEL_TYPE_I_O_OPEN_SINK = goodies.VERSION_ID(2, 0, 2);
  const int MODEL_TYPE_I_O_OPEN_SOURCE = goodies.VERSION_ID(2, 0, 3);
  const int MODEL_TYPE_INPUT_ECL = goodies.VERSION_ID(2, 0, 4);
  const int MODEL_TYPE_I_O_ECL = goodies.VERSION_ID(2, 0, 5);
  const int MODEL_TYPE_TERMINATOR = goodies.VERSION_ID(2, 0, 6);
  const int MODEL_TYPE_OPEN_SINK = goodies.VERSION_ID(2, 0, 7);
  const int MODEL_TYPE_OPEN_SOURCE = goodies.VERSION_ID(2, 0, 8);
  const int MODEL_TYPE_OUTPUT_ECL = goodies.VERSION_ID(2, 0, 9);
  /* version 3.2 */
  const int MODEL_TYPE_SERIES = goodies.VERSION_ID(3, 0, 1);
  const int MODEL_TYPE_SERIES_SWITCH = goodies.VERSION_ID(3, 0, 2);

  /* Model Enable types */
  const int MODEL_ENABLE_UNDEFINED = ConstantStuff.UNDEFINED;
  /* version 1.0 */
  const int MODEL_ENABLE_ACTIVE_HIGH = goodies.VERSION_ID(1, 2, 1);
  const int MODEL_ENABLE_ACTIVE_LOW = goodies.VERSION_ID(1, 2, 2);

  /* Model Polarity types */
  const int MODEL_POLARITY_UNDEFINED = ConstantStuff.UNDEFINED;
  /* version 1.0 */
  const int MODEL_POLARITY_NON_INVERTING = goodies.VERSION_ID(1, 3, 1);
  const int MODEL_POLARITY_INVERTING = goodies.VERSION_ID(1, 3, 2);

  /* Supported Spice types */
  const int SPICE_TYPE_HSPICE = 0;
  const int SPICE_TYPE_PSPICE = 1;
  const int SPICE_TYPE_SPICE2 = 2;
  const int SPICE_TYPE_SPICE3 = 3;
  const int SPICE_TYPE_SPECTRE = 4;
  const int SPICE_TYPE_ELDO = 5;

  /* SPICE exit code (no execution errors) */
  const int SPICE_GOOD_EXIT_CODE = 0;

  /* This section supplies all of the component and model default values.
   */
  const int RLOAD_DEFAULT = 50;
  const double C_COMP_DEFAULT = 5E-12;
  const int TEMP_TYP_DEFAULT = 27;
  const int TEMP_MIN_DEFAULT = 100;
  const int TEMP_MAX_DEFAULT = 0;
  const int VOLTAGE_RANGE_TYP_DEFAULT = 5;
  const double VOLTAGE_RANGE_MIN_DEFAULT = 4.5;
  const double VOLTAGE_RANGE_MAX_DEFAULT = 5.5;
  const double SIM_TIME_DEFAULT = 10e-9;
  const int SPICE_TYPE_DEFAULT = SPICE_TYPE_HSPICE;
  const int DERATE_VI_PCT_DEFAULT = 0;
  const int DERATE_RAMP_PCT_DEFAULT = 0;
  const int CLAMP_TOLERANCE_DEFAULT = 0;
  const double R_SERIES_DEFAULT = 1E6;
  const double HSPICE_INGOLD_DEFAULT = 2;
  /*-------------------------------------------------------------------------
   *   Define some global component default values.  These go into the
   *   components if not otherwise specified.
   *------------------------------------------------------------------------*/
  const string MANUFACTURERS_NAME_DEFAULT = "Manufacturer name";
  const int R_PKG_DEFAULT = 0;
  const int L_PKG_DEFAULT = 0;
  const int C_PKG_DEFAULT = 0;

  /*-------------------------------------------------------------------------
   *   Define some global analysis defaults.  These are used in the
   *   derivations of the models.
   *
   *   Note on DIODE_DROP_DEFAULT: This should be set to a value greater
   *   than or equal to the greatest protection diode turn-on voltage in
   *   your circuit.  I picked 1.0 as the default because it's a nice round
   *   number.
   *------------------------------------------------------------------------*/
  const double LIN_RANGE_DEFAULT = 5.0;
  const double SWEEP_STEP_DEFAULT = 0.01;
  const double DIODE_DROP_DEFAULT = 1.0;
  const double ECL_SWEEP_RANGE_DEFAULT = 2.2;
  const double ECL_TERMINATION_VOLTAGE_DEFAULT = -2.0;
  const int WAVE_POINTS_DEFAULT = 100;
};
class goodies {
public:
  bool IS_USE_NA(double number) {
    if (((number) >= ConstantStuff.USE_NA - ConstantStuff.Tolerance) &&
        ((number) <= ConstantStuff.USE_NA + ConstantStuff.Tolerance))
      return (true);
    else
      return (false);
  }

  bool IS_NOT_USED(double number) {
    if (((number) >= ConstantStuff.NOT_USED - ConstantStuff.Tolerance) &&
        ((number) <= ConstantStuff.NOT_USED + ConstantStuff.Tolerance))
      return (true);
    else
      return (false);
  }

  int SIGN(double a) {
    if (a >= 0)
      return (1);
    else
      return (-1);
  } // end method SIGN

  double MIN(double a, double b) {
    if ((a) < (b))
      return (a);
    else
      return (b);
  } // end method SIGN

  int ROUND(double num) { return (int)(num + .5); } // end method ROUND

  bool THIS_PIN_NEEDS_ANALYSIS(string modelName) {
    if (!((modelName.equalsIgnoreCase("Power")) ||
          (modelName.equalsIgnoreCase("GND")) ||
          (modelName.equalsIgnoreCase("NC"))))
      return (true);
    else
      return (false);
  } // end method THIS_PIN_NEEDS_ANALYSIS

  int VERSION_ID(int MajorRelease, int MinorRelease, int SpecificID) {
    return ((MajorRelease * ConstantStuff.majorReleaseIncrement) +
            (MinorRelease * ConstantStuff.minorReleaseIncrement) + SpecificID);
  } // end method VERSION_ID

  bool THIS_MODEL_NEEDS_SERIES_VI_DATA(int modelType) {
    if ((modelType == ConstantStuff.MODEL_TYPE_SERIES) ||
        (modelType == ConstantStuff.MODEL_TYPE_SERIES_SWITCH))
      return (true);
    else
      return (false);
  } // end method THIS_MODEL_NEEDS_SERIES_VI_DATA

  bool THIS_MODEL_NEEDS_PULLUP_DATA(int modelType) {
    if ((modelType == ConstantStuff.MODEL_TYPE_OUTPUT) ||
        (modelType == ConstantStuff.MODEL_TYPE_3_STATE) ||
        (modelType == ConstantStuff.MODEL_TYPE_I_O) ||
        (modelType == ConstantStuff.MODEL_TYPE_OPEN_SOURCE) ||
        (modelType == ConstantStuff.MODEL_TYPE_I_O_OPEN_SOURCE) ||
        (modelType == ConstantStuff.MODEL_TYPE_OUTPUT_ECL) ||
        (modelType == ConstantStuff.MODEL_TYPE_I_O_ECL))
      return (true);
    else
      return (false);
  } // end method THIS_MODEL_NEEDS_PULLUP_DATA

  bool THIS_MODEL_NEEDS_PULLDOWN_DATA(int modelType) {
    if ((modelType == ConstantStuff.MODEL_TYPE_OUTPUT) ||
        (modelType == ConstantStuff.MODEL_TYPE_3_STATE) ||
        (modelType == ConstantStuff.MODEL_TYPE_I_O) ||
        (modelType == ConstantStuff.MODEL_TYPE_OPEN_SINK) ||
        (modelType == ConstantStuff.MODEL_TYPE_I_O_OPEN_SINK) ||
        (modelType == ConstantStuff.MODEL_TYPE_OPEN_DRAIN) ||
        (modelType == ConstantStuff.MODEL_TYPE_I_O_OPEN_DRAIN) ||
        (modelType == ConstantStuff.MODEL_TYPE_OUTPUT_ECL) ||
        (modelType == ConstantStuff.MODEL_TYPE_I_O_ECL))
      return (true);
    else
      return (false);
  } // end method THIS_MODEL_NEEDS_PULLDOWN_DATA

  bool THIS_MODEL_NEEDS_POWER_CLAMP_DATA(int modelType) {
    if ((modelType == ConstantStuff.MODEL_TYPE_INPUT) ||
        (modelType == ConstantStuff.MODEL_TYPE_3_STATE) ||
        (modelType == ConstantStuff.MODEL_TYPE_I_O) ||
        (modelType == ConstantStuff.MODEL_TYPE_I_O_OPEN_SOURCE) ||
        (modelType == ConstantStuff.MODEL_TYPE_INPUT_ECL) ||
        (modelType == ConstantStuff.MODEL_TYPE_I_O_ECL) ||
        (modelType == ConstantStuff.MODEL_TYPE_TERMINATOR))
      return (true);
    else
      return (false);
  } // end method THIS_MODEL_NEEDS_POWER_CLAMP_DATA

  bool THIS_MODEL_NEEDS_GND_CLAMP_DATA(int modelType) {
    if ((modelType == ConstantStuff.MODEL_TYPE_INPUT) ||
        (modelType == ConstantStuff.MODEL_TYPE_3_STATE) ||
        (modelType == ConstantStuff.MODEL_TYPE_I_O) ||
        (modelType == ConstantStuff.MODEL_TYPE_I_O_OPEN_SINK) ||
        (modelType == ConstantStuff.MODEL_TYPE_I_O_OPEN_DRAIN) ||
        (modelType == ConstantStuff.MODEL_TYPE_INPUT_ECL) ||
        (modelType == ConstantStuff.MODEL_TYPE_I_O_ECL) ||
        (modelType == ConstantStuff.MODEL_TYPE_TERMINATOR))
      return (true);
    else
      return (false);
  } // end method THIS_MODEL_NEEDS_GND_CLAMP_DATA

  bool THIS_MODEL_NEEDS_TRANSIENT_DATA(int modelType) {
    if ((modelType == ConstantStuff.MODEL_TYPE_OUTPUT) ||
        (modelType == ConstantStuff.MODEL_TYPE_3_STATE) ||
        (modelType == ConstantStuff.MODEL_TYPE_I_O) ||
        (modelType == ConstantStuff.MODEL_TYPE_OPEN_SINK) ||
        (modelType == ConstantStuff.MODEL_TYPE_I_O_OPEN_SINK) ||
        (modelType == ConstantStuff.MODEL_TYPE_OPEN_DRAIN) ||
        (modelType == ConstantStuff.MODEL_TYPE_I_O_OPEN_DRAIN) ||
        (modelType == ConstantStuff.MODEL_TYPE_OPEN_SOURCE) ||
        (modelType == ConstantStuff.MODEL_TYPE_I_O_OPEN_SOURCE) ||
        (modelType == ConstantStuff.MODEL_TYPE_OUTPUT_ECL) ||
        (modelType == ConstantStuff.MODEL_TYPE_I_O_ECL))
      return (true);
    else
      return (false);
  } // end method THIS_MODEL_NEEDS_TRANSIENT_DATA

  bool IS_ECL(int model) {
    if ((model == ConstantStuff.MODEL_TYPE_INPUT_ECL) ||
        (model == ConstantStuff.MODEL_TYPE_I_O_ECL) ||
        (model == ConstantStuff.MODEL_TYPE_OUTPUT_ECL))
      return (true);
    else
      return (false);
  }

  double fabs(double number) { return (Math.abs((double)number)); }

  /******************************************************************************
  CLASS: s2iString
  ******************************************************************************/
} class s2iString {
  string[] SIsuffixString = {"f", "p", "n", "u", "m", "", "k", "M", "G", "T"};

  string[] spiceNameString = {"HSpice", "PSpice",  "SPICE2",
                              "Spice3", "Spectre", "ELDO"};

  string[] VIDataBeginMarker = {"transfer", "DC TRANSFER", "X",
                                "Index",    "Values",      "X "};

  string[] tranDataBeginMarker = {"analysis", "TIME",   "X",
                                  "Index",    "Values", "X "};

  string[] abortMarker = {"aborted", "ABORT",      "ABORT",
                          "aborted", "terminated", "ERROR"};

  string[] convergenceMarker = {"convergence failure", // only one that is valid
                                "convergence failure", "convergence failure",
                                "convergence failure", "convergence failure",
                                "convergence failure"};

  string[] VIDataEndMarker = {"y", "", "Y", "CPU", "", "Y"};

  string[] curveNameString = {"pullup",
                              "pulldown",
                              "power clamp",
                              "ground clamp",
                              "pullup (output disabled)",
                              "pulldown (output disabled)",
                              "rising ramp",
                              "falling ramp",
                              "rising waveform",
                              "falling waveform",
                              "Series VI"};

  string[] spiceFileTypPrefix = {"put", "pdt", "pct", "gct", "dut", "ddt",
                                 "rut", "rdt", "a",   "x",   "vit"};

  string[] spiceFileMinPrefix = {"pun", "pdn", "pcn", "gcn", "dun", "ddn",
                                 "run", "rdn", "b",   "y",   "vin"};

  string[] spiceFileMaxPrefix = {"pux", "pdx", "pcx", "gcx", "dux", "ddx",
                                 "rux", "rdx", "c",   "z",   "vix"};

  string[] dummyNodeName = {"dum17854", "dum39538", "dum94195", "dum75762",
                            "dum58413", "dum80979", "dum01321", "dum46040",
                            "dum23607", "dum62286"};

  string indString(int aspiceType, string var1, string var2, string var3,
                   double L_dut) {
    string[] indString = {var1 + " " + var2 + " " + var3 + "  " + L_dut + "\n",
                          var1 + " " + var2 + " " + var3 + "  " + L_dut + "\n",
                          var1 + " " + var2 + " " + var3 + "  " + L_dut + "\n",
                          var1 + " " + var2 + " " + var3 + "  " + L_dut + "\n",
                          var1 + " " + var2 + " " + var3 + "  " +
                              "inductor l=" + L_dut + "\n",
                          var1 + " " + var2 + " " + var3 + "  " + L_dut + "\n"};
    return (indString[aspiceType]);
  }

  string resString(int aspiceType, string var1, string var2, string var3,
                   double R_dut) {
    string[] resString = {var1 + " " + var2 + " " + var3 + "  " + R_dut + "\n",
                          var1 + " " + var2 + " " + var3 + "  " + R_dut + "\n",
                          var1 + " " + var2 + " " + var3 + "  " + R_dut + "\n",
                          var1 + " " + var2 + " " + var3 + "  " + R_dut + "\n",
                          var1 + " " + var2 + " " + var3 + "  " +
                              "resistor r=" + R_dut + "\n",
                          var1 + " " + var2 + " " + var3 + "  " + R_dut + "\n"};
    return (resString[aspiceType]);
  }

  string capString(int aspiceType, string var1, string var2, string var3,
                   double C_dut) {
    string[] capString = {var1 + " " + var2 + " " + var3 + "  " + C_dut + "\n",
                          var1 + " " + var2 + " " + var3 + "  " + C_dut + "\n",
                          var1 + " " + var2 + " " + var3 + "  " + C_dut + "\n",
                          var1 + " " + var2 + " " + var3 + "  " + C_dut + "\n",
                          var1 + " " + var2 + " " + var3 + "  " +
                              "capacitor c=" + C_dut + "\n",
                          var1 + " " + var2 + " " + var3 + "  " + C_dut + "\n"};
    return (capString[aspiceType]);
  }

  string defaultSpiceCommand(int aspiceType, string aspiceInFile,
                             string aspiceOutFile, string aspiceMsgFile) {
    string[] defaultSpCommand = {
        "hspice " + aspiceInFile + " >" +
            aspiceOutFile, // +" 2>"+aspiceMsgFile,
        "pspice " + aspiceInFile + " " + aspiceOutFile + " /D0",
        "spice " + aspiceInFile + " " + aspiceOutFile,
        "spice3 -b " + aspiceInFile + " >" + aspiceOutFile + "  2>" +
            aspiceMsgFile,
        "spectre -f nutascii -c 132 " + aspiceInFile + "  -r " + aspiceOutFile +
            "  >" + aspiceMsgFile,
        "eldo -b -i " + aspiceInFile + "  -o " + aspiceOutFile + " -silent"};
    return defaultSpCommand[aspiceType];
  }

  string spiceCommandForWin(int aspiceType, string aspiceInFile,
                            string aspiceOutFile, string aspiceMsgFile) {
    string[] spCommandForWin = {
        "hspice -i " + aspiceInFile + " -o " + aspiceOutFile,
        "pspice " + aspiceInFile + " " + aspiceOutFile + " /D0",
        "spice " + aspiceInFile + " " + aspiceOutFile,
        "spice3 -b " + aspiceInFile + " >" + aspiceOutFile + "  2>" +
            aspiceMsgFile,
        "spectre -f nutascii -c 132 " + aspiceInFile + "  -r " + aspiceOutFile +
            "  >" + aspiceMsgFile,
        "eldo -i " + aspiceInFile + "  -o " + aspiceOutFile + " -silent"};
    return spCommandForWin[aspiceType];
  }

  string temperatureString(int aspiceType, double atemp) {
    string[] tempString = {".TEMP " + atemp + "\n",
                           ".TEMP " + atemp + "\n",
                           ".TEMP " + atemp + "\n",
                           ".OPTIONS TEMP=" + atemp + "\n",
                           "setTemp options temp=" + atemp + "\n",
                           ".TEMP " + atemp + "\n"};
    return tempString[aspiceType];
  }

  string spiceOptions(int aspiceType) {
    string[] optionString = {
        //  		       ".OPTIONS INGOLD=2\n",
        ".OPTIONS INGOLD=" + ConstantStuff.HSPICE_INGOLD_DEFAULT + "\n",
        "",
        "",
        "",
        "saveOptions options save=selected\n",
        ""};
    return optionString[aspiceType];
  }

public:
  string DCSrcString(int aspiceType, string var1, string nodeName, string var2,
                     double var3) {
    string[] srcString = {
        var1 + " " + nodeName + " " + var2 + " DC " + var3 + "\n",
        var1 + " " + nodeName + " " + var2 + " DC " + var3 + "\n",
        var1 + " " + nodeName + " " + var2 + " DC " + var3 + "\n",
        var1 + " " + nodeName + " " + var2 + " DC " + var3 + "\n",
        var1 + " " + nodeName + " " + var2 + " " +
            "vsource type=dc dc=" + var3 + "\n",
        var1 + " " + nodeName + " " + var2 + " DC " + var3 + "\n"};
    return srcString[aspiceType];
  }

public:
  string tranSrcString(int aspiceType, string var1, string nodeName,
                       string var2, double V1, double V2, double risetime,
                       double falltime, double pulsewidth, double period) {
    string[] tsrcString = {
        var1 + " " + nodeName + " " + var2 + " PULSE(" + V1 + " " + V2 + " 0 " +
            risetime + " " + falltime + " " + pulsewidth + " " + period + ")\n",
        var1 + " " + nodeName + " " + var2 + " PULSE(" + V1 + " " + V2 + " 0 " +
            risetime + " " + falltime + " " + pulsewidth + " " + period + ")\n",
        var1 + " " + nodeName + " " + var2 + " PULSE(" + V1 + " " + V2 + " 0 " +
            risetime + " " + falltime + " " + pulsewidth + " " + period + ")\n",
        var1 + " " + nodeName + " " + var2 + " PULSE(" + V1 + " " + V2 + " 0 " +
            risetime + " " + falltime + " " + pulsewidth + " " + period + ")\n",
        var1 + " " + nodeName + " " + var2 + " " +
            "vsource type=pulse dc=0 val0=" + V1 + " val1=" + V2 +
            " delay=0 rise=" + risetime + " fall=" + falltime +
            " width =" + pulsewidth + " period=" + period + "\n",
        var1 + " " + nodeName + " " + var2 + " PULSE(" + V1 + " " + V2 + " 0 " +
            risetime + " " + falltime + " " + pulsewidth + " " + period +
            ")\n"};
    return tsrcString[aspiceType];
  }

}; // class s2iString

/******************************************************************************
CLASS: ibisSeriesModel
******************************************************************************/
class ibisSeriesModel {
  bool OnState; // only valid for Series Switch Model Types
  ibisTypMinMax RSeriesOn = new ibisTypMinMax();
  ibisTypMinMax LSeriesOn = new ibisTypMinMax();
  ibisTypMinMax CSeriesOn = new ibisTypMinMax();
  ibisTypMinMax RlSeriesOn = new ibisTypMinMax();
  ibisTypMinMax RcSeriesOn = new ibisTypMinMax();
  seriesMosfet series_MOSFET = new seriesMosfet();

  bool OffState; // only valid for Series Switch Model Types
  ibisTypMinMax RSeriesOff = new ibisTypMinMax();
  ibisTypMinMax LSeriesOff = new ibisTypMinMax();
  ibisTypMinMax CSeriesOff = new ibisTypMinMax();
  ibisTypMinMax RlSeriesOff = new ibisTypMinMax();
  ibisTypMinMax RcSeriesOff = new ibisTypMinMax();

  int series_type;

  // constructor
public:
  ibisSeriesModel() {
    OnState = false;
    OffState = false;
  }
}; // class ibisSeriesModel

// still have to take care of [series Current]

class seriesMosfet {
  VdsList vdslist = new VdsList(); // max of 100 Vds values are permitted
}

class Vds {
  double V;
  ibisVItable seriesVITable; // every value of VDs means a VI table.
  Vds next;
  // constructor for Vds class
public:
  Vds() { V = 0; }

public:
  void setnext(Vds nextVds) { next = nextVds; } // setnext

public:
  Vds getnext() { return (next); } // getnext
}

class VdsList {
  int count;
  Vds head;
  Vds tail;
  Vds current;

  // constructor
public:
  VdsList() {
    head = null;
    tail = null;
    current = null;
    count = 0;
  } // constructor

public:
  void add(Vds VdsFromParser) {
    Vds temp;
    count++;
    temp = VdsFromParser;
    // insert at head of list
    temp.setnext(head);
    head = temp;
    if (tail == null) {
      tail = temp;
    }
    current = temp;
  } // add

public:
  void gototop() {
    // sets current to point to thetop of the list
    current = head;
  } // gototop

public:
  void next() {
    if (current != null) {
      current = current.getnext();
    }
  } // next

}; // class VdsList

/******************************************************************************
CLASS: ibisModel
******************************************************************************/
class ibisModel {
  int thisModelProcessed;
  int hasBeenAnalyzed;
  int polarity;
  int modelType;
  int noModel;
  string modelFileTyp; // declared as TypMinMax class
  string modelFileMin;
  string modelFileMax;
  string extSpiceCmdFile; // for 0.4beta
  string modelName;
  int enable;
  double Vinl;
  double Vinh;
  double Vmeas;
  double Cref;
  double Rref;
  double Vref;
  double Rload;
  double derateRampPct;
  double derateVIPct;
  double clampTol;
  double simTime;

  ibisTypMinMax c_comp = new ibisTypMinMax();
  ibisTypMinMax tempRange = new ibisTypMinMax();
  ibisTypMinMax voltageRange = new ibisTypMinMax();
  ibisTypMinMax pullupRef = new ibisTypMinMax();
  ibisTypMinMax pulldownRef = new ibisTypMinMax();
  ibisTypMinMax powerClampRef = new ibisTypMinMax();
  ibisTypMinMax gndClampRef = new ibisTypMinMax();
  ibisTypMinMax Rgnd = new ibisTypMinMax();
  ibisTypMinMax Rpower = new ibisTypMinMax();
  ibisTypMinMax Rac = new ibisTypMinMax();
  ibisTypMinMax Cac = new ibisTypMinMax();
  ibisTypMinMax vil = new ibisTypMinMax();
  ibisTypMinMax vih = new ibisTypMinMax();
  ibisTypMinMax tr = new ibisTypMinMax();
  ibisTypMinMax tf = new ibisTypMinMax();
  ibisVItable pulldown = new ibisVItable();
  ibisVItable pullup = new ibisVItable();
  ibisVItable gnd_clamp = new ibisVItable();
  ibisVItable power_clamp = new ibisVItable();
  waveTableList risingWaveList = new waveTableList();
  waveTableList fallingWaveList = new waveTableList();
  ibisRamp ramp = new ibisRamp();
  // Series
  ibisSeriesModel seriesModel = new ibisSeriesModel();
  // Series
  ibisModel next;

  // constructor for ibisModel class
public:
  ibisModel() {
    thisModelProcessed = 0;
    hasBeenAnalyzed = 0;
    noModel = 0;
    polarity = 0;
    modelName = null;
    modelFileTyp = "";
    modelFileMin = "";
    modelFileMax = "";
    extSpiceCmdFile = ""; // for 0.4beta
    modelType = 0;
    enable = 0;
    Vinl = ConstantStuff.USE_NA;
    Vinh = ConstantStuff.USE_NA;
    Vmeas = ConstantStuff.USE_NA;
    Cref = ConstantStuff.USE_NA;
    Rref = ConstantStuff.USE_NA;
    Vref = ConstantStuff.USE_NA;
    Rload = ConstantStuff.USE_NA;
    derateRampPct = ConstantStuff.USE_NA;
    derateVIPct = ConstantStuff.USE_NA;
    clampTol = ConstantStuff.USE_NA;
    simTime = ConstantStuff.USE_NA;
    gnd_clamp = null;
    power_clamp = null;
    pullup = null;
    pulldown = null;

  } // constructor for ibisModel class
public:
  void setnext(ibisModel nextmod) { next = nextmod; } // setnext

public:
  ibisModel getnext() { return (next); } // getnext

}; // class ibisModel

/******************************************************************************
CLASS: modelsList
******************************************************************************/
class modelsList {
  int count;
  ibisModel head;
  ibisModel tail;
  ibisModel current = new ibisModel();

  // constructor
public:
  modelsList() {
    head = null;
    tail = null;
    current = null;
    count = 0;
  } // constructor

public:
  void add(ibisModel modelFromParser) {
    ibisModel temp;
    count++;
    temp = modelFromParser;
    // insert at head of list
    temp.setnext(head);
    head = temp;
    if (tail == null) {
      tail = temp;
    }
    current = temp;
  } // add

public:
  void gototop() {
    // sets current to point to thetop of the list
    current = head;
  } // gototop

public:
  void next() {
    if (current != null) {
      current = current.getnext();
    }
  } // next

}; // class modelsList

/******************************************************************************
CLASS:ibisPin
******************************************************************************/
class ibisPin {
  float NA_float = 0;
  string spiceNodeName;
  string pinName;
  string signalName;
  string modelName;
  string inputPin;
  string enablePin;
  string pullupRef;
  string pulldownRef;
  string powerClampRef;
  string gndClampRef;
  double R_pin;
  double L_pin;
  double C_pin;
  ibisModel model;
  // series
  /*Each pin could potentially have 2 models associated with them.
  A 'regular' model and a series model. The regular model is obtained
  from the [Pin] table whereas the series model is obtained from the
  [series pin mapping] table. The seriesModel data is transfered in
  copySeriesPinToPins()
  */
  ibisModel seriesModel;
  string seriesPin2name;
  string fnTableGp;
  // series
  ibisPin nextPin;
  // constructor for ibisPin class
public:
  ibisPin() {
    spiceNodeName = null;
    pinName = null;
    modelName = null;
    signalName = null;
    enablePin = "";
    inputPin = "";
    pullupRef = null;
    pulldownRef = null;
    powerClampRef = null;
    gndClampRef = null;
    seriesPin2name = null;
    seriesModel = null;
    R_pin = ConstantStuff.NOT_USED;
    C_pin = ConstantStuff.NOT_USED;
    L_pin = ConstantStuff.NOT_USED;

  } // constructor for ibisPin class
public:
  void setnext(ibisPin nextPin1) { nextPin = nextPin1; } // setnext

public:
  ibisPin getnext() { return (nextPin); } // getnext

}; // class ibisPin

/******************************************************************************
CLASS: pinsList:
******************************************************************************/
class pinsList {
  // int count;
  int count;
  ibisPin head;
  ibisPin tail;
  ibisPin current;

  // constructor
public:
  pinsList() {
    head = null;
    tail = null;
    current = null;
    count = 0;
  } // constructor

public:
  void add(ibisPin pinFromParser) {
    ibisPin temp;
    count++;
    temp = pinFromParser;
    // insert at head of list
    temp.setnext(head);
    head = temp;
    if (tail == null) {
      tail = temp;
    }
    current = temp;
  } // add
public:
  void gototop() {
    // sets current to poit to thetop of the list
    current = head;
  } // gototop
public:
  void next() {
    if (current != null) {
      current = current.getnext();
    }
  } // next

}; // class pinsList

/******************************************************************************
CLASS: ibisPinMap:
******************************************************************************/
class ibisPinMap {
  string pinName;
  string pullupRef;
  string pulldownRef;
  string powerClampRef;
  string gndClampRef;
  ibisPinMap nextPinMap;

public:
  ibisPinMap() {
    pinName = "";
    pullupRef = "";
    pulldownRef = "";
    powerClampRef = "";
    gndClampRef = "";
  } // constructor

public:
  void setnext(ibisPinMap nextPinMap1) { nextPinMap = nextPinMap1; } // setnext

public:
  ibisPinMap getnext() { return (nextPinMap); } // getnext

}; // class ibisPinMaP

/******************************************************************************
CLASS: pinMapList:
******************************************************************************/
class pinMapList {
  int count;
  ibisPinMap head;
  ibisPinMap tail;
  ibisPinMap current;

  // constructor
public:
  pinMapList() {
    head = null;
    tail = null;
    current = null;
    count = 0;
  } // constructor

public:
  void add(ibisPinMap newPinMap) {
    ibisPinMap temp;
    count++;
    temp = newPinMap;

    // insert at head of list
    temp.setnext(head);
    head = temp;
    if (tail == null) {
      tail = temp;
    }
    current = temp;
  } // add

public:
  void gototop() {
    // sets current to point to the top of the list
    current = head;
  } // gototop

public:
  void next() {
    if (current != null) {
      current = current.getnext();
    }
  } // next

}; // class pinMapList

/******************************************************************************
CLASS: ibisDiffPin:
******************************************************************************/
class ibisDiffPin {
  string pinName;
  string invPin;
  double vdiff;
  double tdelay_typ;
  double tdelay_min;
  double tdelay_max;
  ibisDiffPin nextDiffPin;

public:
  ibisDiffPin() {
    pinName = "";
    invPin = "";
    vdiff = 0;
    tdelay_typ = ConstantStuff.NOT_USED;
    tdelay_min = ConstantStuff.NOT_USED;
    tdelay_max = ConstantStuff.NOT_USED;
  } // constructor

public:
  void setnext(ibisDiffPin nextDiffPin1) {
    nextDiffPin = nextDiffPin1;
  } // setnext

public:
  ibisDiffPin getnext() { return (nextDiffPin); } // getnext

}

/******************************************************************************
CLASS: diffPinList:
******************************************************************************/
class diffPinList {
  int count;
  ibisDiffPin head;
  ibisDiffPin tail;
  ibisDiffPin current;

  // constructor
public:
  diffPinList() {
    head = null;
    tail = null;
    current = null;
    count = 0;
  } // constructor

public:
  void add(ibisDiffPin newDiffPin) {
    ibisDiffPin temp;
    count++;
    temp = newDiffPin;

    // insert at head of list
    temp.setnext(head);
    head = temp;
    if (tail == null) {
      tail = temp;
    }
    current = temp;
  } // add

public:
  void gototop() {
    // sets current to poit to thetop of the list
    current = head;
  } // gototop

public:
  void next() {
    if (current != null) {
      current = current.getnext();
    }
  } // next

}; // class diffPinList

/******************************************************************************
CLASS:ibisSeriesPin
******************************************************************************/
class ibisSeriesPin {
  string seriesPinName;
  string seriesPin2name;
  string modelName;
  string fnTableGp;
  ibisModel seriesModel;
  ibisSeriesPin nextSeriesPin;

  // constructor for ibisSeriesPin class
public:
  ibisSeriesPin() {
    seriesPinName = null;
    seriesPin2name = null;
    modelName = null;
    fnTableGp = null;
  } // constructor for ibisPin class
public:
  void setnext(ibisSeriesPin nextSeriesPin1) {
    nextSeriesPin = nextSeriesPin1;
  } // setnext

public:
  ibisSeriesPin getnext() { return (nextSeriesPin); } // getnext

}; // class ibisSeriesPin

/******************************************************************************
CLASS: seriesPinsList:
******************************************************************************/
class seriesPinsList {
  int count;
  ibisSeriesPin head;
  ibisSeriesPin tail;
  ibisSeriesPin current;

  // constructor
public:
  seriesPinsList() {
    head = null;
    tail = null;
    current = null;
    count = 0;
  } // constructor

public:
  void add(ibisSeriesPin seriesPinFromParser) {
    ibisSeriesPin temp;
    count++;
    temp = seriesPinFromParser;
    // insert at head of list
    temp.setnext(head);
    head = temp;
    if (tail == null) {
      tail = temp;
    }
    current = temp;
  } // add
public:
  void gototop() {
    // sets current to poit to thetop of the list
    current = head;
  } // gototop
public:
  void next() {
    if (current != null) {
      current = current.getnext();
    }
  } // next

}; // class seriesPinsList

/******************************************************************************
CLASS:seriesSwitchGroup
******************************************************************************/
class seriesSwitchGroup {
  string state; // off or on
  string[] groupNames;
  seriesSwitchGroup nextSeriesGp;

  // constructor for ibisSeriesPin class
public:
  seriesSwitchGroup() {
    state = null;
    groupNames = null;
  } // constructor for ibisPin class
public:
  void setnext(seriesSwitchGroup nextSeriesGp1) {
    nextSeriesGp = nextSeriesGp1;
  } // setnext

public:
  seriesSwitchGroup getnext() { return (nextSeriesGp); } // getnext

}; // class seriesSwitchGroup

/******************************************************************************
CLASS: seriesSwitchGpList:
******************************************************************************/
class seriesSwitchGpList {
  int count;
  seriesSwitchGroup head;
  seriesSwitchGroup tail;
  seriesSwitchGroup current;

  // constructor
public:
  seriesSwitchGpList() {
    head = null;
    tail = null;
    current = null;
    count = 0;
  } // constructor

public:
  void add(seriesSwitchGroup seriesSwitchGpFromParser) {
    seriesSwitchGroup temp;
    count++;
    temp = seriesSwitchGpFromParser;
    // insert at head of list
    temp.setnext(head);
    head = temp;
    if (tail == null) {
      tail = temp;
    }
    current = temp;
  } // add
public:
  void gototop() {
    // sets current to poit to thetop of the list
    current = head;
  } // gototop
public:
  void next() {
    if (current != null) {
      current = current.getnext();
    }
  } // next

}; // class seriesSwitchGpList

/******************************************************************************
CLASS: ibisComponent:
******************************************************************************/
class ibisComponent {
  int thisComponentProcessed;
  bool hasPinMapping;
  string component;
  string packageModel;
  string manufacturer;
  string spiceFile;
  // Series
  string seriesSpiceFile;
  // Series
  double Rload;
  double derateRampPct;
  double derateVIPct;
  double clampTol;
  double simTime;
  ibisTypMinMax c_comp = new ibisTypMinMax();
  ibisTypMinMax tempRange = new ibisTypMinMax();
  ibisTypMinMax voltageRange = new ibisTypMinMax();
  ibisTypMinMax pullupRef = new ibisTypMinMax();
  ibisTypMinMax pulldownRef = new ibisTypMinMax();
  ibisTypMinMax powerClampRef = new ibisTypMinMax();
  ibisTypMinMax gndClampRef = new ibisTypMinMax();
  ibisTypMinMax vil = new ibisTypMinMax();
  ibisTypMinMax vih = new ibisTypMinMax();
  ibisTypMinMax tr = new ibisTypMinMax();
  ibisTypMinMax tf = new ibisTypMinMax();
  modelsList mList = new modelsList();
  pinsList pList; // 		= new pinsList();
  pinMapList pmList = new pinMapList();

  ibisPackage pinParasitics = new ibisPackage();
  diffPinList dpList = new diffPinList();
  seriesPinsList spList = new seriesPinsList();
  seriesSwitchGpList ssgList = new seriesSwitchGpList();

  ibisComponent next; // next item in the linked list

  // constructor for ibisComponent class
public:
  ibisComponent() {
    thisComponentProcessed = 0;
    hasPinMapping = false;
    component = null;
    packageModel = null;
    manufacturer = null;
    spiceFile = null;
    Rload = ConstantStuff.USE_NA;
    derateRampPct = ConstantStuff.USE_NA;
    derateVIPct = ConstantStuff.USE_NA;
    clampTol = ConstantStuff.USE_NA;
    simTime = ConstantStuff.USE_NA;
    dpList = null;
    spList = null;
  } // constructor for ibisComponent class
public:
  void setnext(ibisComponent nextmod) { next = nextmod; } // setnext

public:
  ibisComponent getnext() { return (next); } // getnext

}; // class ibisComponent

/******************************************************************************
CLASS: componentList:
******************************************************************************/
class componentList {
  int count;
  ibisComponent head;
  ibisComponent tail;
  ibisComponent current;

  // constructor
public:
  componentList() {
    head = null;
    tail = null;
    current = null;
    count = 0;
  } // constructor

public:
  void add(ibisComponent componentFromParser) {
    ibisComponent temp;
    count++;
    temp = componentFromParser;
    // insert at head of list
    temp.setnext(head);
    head = temp;
    if (tail == null) {
      tail = temp;
    }
    current = temp;
  } // add

public:
  void gototop() {
    // sets current to poit to thetop of the list
    current = head;
  } // gototop

public:
  void next() {
    if (current != null) {
      current = current.getnext();
    }
  } // next

}; // class componentList

/******************************************************************************
CLASS: cListContainer
******************************************************************************/
class cListContainer {
  componentList cListCont; // =  new componentList();
}

/******************************************************************************
CLASS: ibisWaveTable
******************************************************************************/
class ibisWaveTable {
  double R_fixture, V_fixture, V_fixture_min, V_fixture_max, L_fixture,
      C_fixture, R_dut, L_dut, C_dut;
  int size;
  ibisWaveTableEntry[] waveData;
  ibisWaveTable nextWaveTable; // next item in the linked list

  // constructor for ibisWavetable class
public:
  ibisWaveTable() {
    R_fixture = ConstantStuff.USE_NA;
    V_fixture = ConstantStuff.USE_NA;
    V_fixture_min = ConstantStuff.USE_NA;
    V_fixture_max = ConstantStuff.USE_NA;
    L_fixture = ConstantStuff.USE_NA;
    C_fixture = ConstantStuff.USE_NA;
    R_dut = ConstantStuff.USE_NA;
    L_dut = ConstantStuff.USE_NA;
    C_dut = ConstantStuff.USE_NA;

  } // constructor for ibisWavetable class

public:
  void setnext(ibisWaveTable nextWaveTable1) {
    nextWaveTable = nextWaveTable1;
  } // setnext

public:
  ibisWaveTable getnext() { return (nextWaveTable); } // getnext

}; // class ibisWaveTable

/******************************************************************************
CLASS: waveTableList
******************************************************************************/
class waveTableList {
  // int count;
  int count;
  ibisWaveTable head;
  ibisWaveTable tail;
  ibisWaveTable current;

  // constructor
public:
  waveTableList() {
    head = null;
    tail = null;
    current = null;
    count = 0;
  } // constructor

public:
  void add(ibisWaveTable newWaveTable) {
    ibisWaveTable temp;
    count++;
    temp = new ibisWaveTable();
    temp = newWaveTable;

    // insert at head of list
    temp.setnext(head);
    head = temp;
    if (tail == null) {
      tail = temp;
    }
    current = temp;
  } // add

public:
  void gototop() {
    // sets current to poit to thetop of the list
    current = head;
  } // gototop

public:
  void next() {
    if (current != null) {
      current = current.getnext();
    }
  } // next

}; // class waveTableList

/******************************************************************************
CLASS: ibisTypMinMax
******************************************************************************/
class ibisTypMinMax {
  double typ, min, max;
  // constructor for ibisTypMinMax class
public:
  ibisTypMinMax() {
    typ = ConstantStuff.USE_NA;
    min = ConstantStuff.USE_NA;
    max = ConstantStuff.USE_NA;
  } // constructor for ibisTypMnMax class
}; // class ibistypMinMax

/******************************************************************************
CLASS: ibisPackage
******************************************************************************/
class ibisPackage {
  ibisTypMinMax R_pkg = new ibisTypMinMax();
  ibisTypMinMax L_pkg = new ibisTypMinMax();
  ibisTypMinMax C_pkg = new ibisTypMinMax();
}; // class ibisPackage

/******************************************************************************
CLASS: ibisRamp
******************************************************************************/
class ibisRamp {
  ibisTypMinMax dv_r = new ibisTypMinMax();
  ibisTypMinMax dt_r = new ibisTypMinMax();
  ibisTypMinMax dv_f = new ibisTypMinMax();
  ibisTypMinMax dt_f = new ibisTypMinMax();
}

/******************************************************************************
CLASS: ibisVItableEntry
******************************************************************************/
class ibisVItableEntry {
  double v;
  ibisTypMinMax i = new ibisTypMinMax();
}

/******************************************************************************
CLASS: ibisWavetableEntry
******************************************************************************/
class ibisWaveTableEntry {
  double t;
  ibisTypMinMax v = new ibisTypMinMax();
}

/******************************************************************************
CLASS: ibisVItable
******************************************************************************/
class ibisVItable {
  int size;
  ibisVItableEntry[] VIs;

  // series
  ibisVItable nextVITable;

public:
  ibisVItable() { size = 0; } // constructor

public:
  void setnext(ibisVItable nextVITable1) {
    nextVITable = nextVITable1;
  } // setnext

public:
  ibisVItable getnext() { return (nextVITable); } // getnext
  // series

}

/******************************************************************************
CLASS: VItableList
******************************************************************************/
class VITableList {
  int count;
  ibisVItable head;
  ibisVItable tail;
  ibisVItable current;

  // constructor
public:
  VITableList() {
    head = null;
    tail = null;
    current = null;
    count = 0;
  } // constructor

public:
  void add(ibisVItable newVITable) {
    ibisVItable temp;
    count++;
    temp = new ibisVItable();
    temp = newVITable;

    // insert at head of list
    temp.setnext(head);
    head = temp;
    if (tail == null) {
      tail = temp;
    }
    current = temp;
  } // add

public:
  void gototop() {
    // sets current to poit to thetop of the list
    current = head;
  } // gototop

public:
  void next() {
    if (current != null) {
      current = current.getnext();
    }
  } // next
}

/******************************************************************************
CLASS: ibisTOP

******************************************************************************/
class ibisTOP {
  int ibisVersion, iterate, cleanup, summarize, spiceType;
  string thisFileName, fileRev, date, source, notes, disclaimer, copyright,
      spiceCommand;
  componentList cList = new componentList();

public:
  ibisTOP() {
    ibisVersion = 0;
    iterate = 0;
    cleanup = 0;
    summarize = 0;
    spiceType = 0;
    thisFileName = ""; // null;
    fileRev = "";      // null;
    // date		= "";//null;
    source = "";     // null;
    notes = "";      // null;
    disclaimer = ""; // null;
    copyright = "";  // null;
    spiceCommand = "";
    // components	= null;
  }
}; // class ibisTOP

/******************************************************************************
CLASS: ibisGlobal
******************************************************************************/
class ibisGlobal {
  string commentChar;
  ibisTypMinMax tempRange = new ibisTypMinMax();
  ibisTypMinMax voltageRange = new ibisTypMinMax();
  ibisTypMinMax pullupRef = new ibisTypMinMax();
  ibisTypMinMax pulldownRef = new ibisTypMinMax();
  ibisTypMinMax powerClampRef = new ibisTypMinMax();
  ibisTypMinMax gndClampRef = new ibisTypMinMax();
  ibisTypMinMax c_comp = new ibisTypMinMax();
  ibisTypMinMax vil = new ibisTypMinMax();
  ibisTypMinMax vih = new ibisTypMinMax();
  ibisTypMinMax tr = new ibisTypMinMax();
  ibisTypMinMax tf = new ibisTypMinMax();
  double Rload, derateVIPct, derateRampPct, clampTol, simTime;
  ibisPackage pinParasitics = new ibisPackage();

public:
  ibisGlobal() {
    commentChar = null;
    Rload = ConstantStuff.USE_NA; // 0;
    derateVIPct = 0;
    derateRampPct = 0;
    clampTol = 0;
    simTime = ConstantStuff.USE_NA; // 0;
  }
}; // class ibisGlobal
