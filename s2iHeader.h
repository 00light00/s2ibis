#ifndef S2IHEADER_H
#define S2IHEADER_H
#include <bits/stdc++.h>
using namespace std;

struct ConstantStuff {
  static const string VERSION_STRING;
  static const int UNDEFINED;
  static const int OUTPUT_LOW;
  static const int OUTPUT_HIGH;
  static const int OUTPUT_FALLING;
  static const int OUTPUT_RISING;
  static const int DISABLE_OUTPUT;
  static const int ENABLE_OUTPUT;

  static const int TYP_CASE;
  static const int MIN_CASE;
  static const int MAX_CASE;

  static const int NUM_PTS_LINEAR_REGION;

  /* ibis version 1.0 Restriction */
  static const int MAX_TABLE_SIZE;
  static const int MAX_MANUFACTURERS_NAME_LENGTH;
  static const int MAX_FILENAME_BASE_LENGTH;
  static const string FILENAME_EXTENSION;
  static const int FILENAME_EXTENSION_LENGTH;
  static const int MAX_PIN_NAME_LENGTH;
  static const int MAX_SIGNAL_NAME_LENGTH;
  static const int MAX_MODEL_NAME_LENGTH;
  static const int MAX_R_PIN_STRING_LENGTH;
  static const int MAX_L_PIN_STRING_LENGTH;
  static const int MAX_C_PIN_STRING_LENGTH;
  static const int MAX_LINE_LENGTH;
  static const int MAX_COMPONENT_NAME_LENGTH;
  static const int MAX_FILENAME_LENGTH;

  /* additional ibis version 2.0 Restriction */
  static const int MAX_PACKAGE_MODEL_NAME_LENGTH;
  static const int MAX_PIN_MAPPING_NAME_LENGTH;
  static const int MAX_DFF_PIN_NAME_LENGTH;
  static const int MAX_INV_PIN_LEBGTH;
  static const int MAX_VDIFF_TYP_LENGTH;
  static const int MAX_TEDELAY_MAX_LENGTH;
  static const int MAX_WAVEFORM_TABLES;
  static const int MAX_SERIES_TABLES;

  static const int MAX_FILE_REV_LENGTH;
  static const int MAX_TOK_LEN;
  static const int MAX_DATE_STRING_LENGTH;
  static const int MAX_IBIS_STRING_LENGTH;
  /* Applies to all other strings such
   * as [Notes], [Disclaimer] etc.
   * The longer strings do not indicate an
   * error in the input file but they are
   * truncated to this length for internal
   * storage.
   */

  static const int IBIS_PRINT_WIDTH;

  static const double USE_NA;
  static const double NOT_USED;
  static const double Tolerance;
  /* VI Curve types */
  static const int CURVE_TYPE_PULLUP;
  static const int CURVE_TYPE_PULLDOWN;
  static const int CURVE_TYPE_POWER_CLAMP;
  static const int CURVE_TYPE_GND_CLAMP;
  static const int CURVE_TYPE_DISABLED_PULLUP;
  static const int CURVE_TYPE_DISABLED_PULLDOWN;
  static const int CURVE_TYPE_RISING_RAMP;
  static const int CURVE_TYPE_FALLING_RAMP;
  static const int CURVE_TYPE_RISING_WAVE;
  static const int CURVE_TYPE_FALLING_WAVE;
  /*series*/
  static const int CURVE_TYPE_SERIES_VI;

  static const int majorReleaseIncrement;
  static const int minorReleaseIncrement;

  static const int VERSION_ONE_ZERO;
  static const int VERSION_ONE_ONE;
  static const int VERSION_TWO_ZERO;
  static const int VERSION_TWO_ONE;

  /*s2ibis3*/
  static const int VERSION_THREE_TWO;

  /* Model Types */
  static const int MODEL_TYPE_UNDEFINED;

  /* version 1.0 */
  static const int MODEL_TYPE_INPUT;
  static const int MODEL_TYPE_OUTPUT;
  static const int MODEL_TYPE_OPEN_DRAIN;
  static const int MODEL_TYPE_3_STATE;
  static const int MODEL_TYPE_I_O;
  /* version 2.0 */
  static const int MODEL_TYPE_I_O_OPEN_DRAIN;
  static const int MODEL_TYPE_I_O_OPEN_SINK;
  static const int MODEL_TYPE_I_O_OPEN_SOURCE;
  static const int MODEL_TYPE_INPUT_ECL;
  static const int MODEL_TYPE_I_O_ECL;
  static const int MODEL_TYPE_TERMINATOR;
  static const int MODEL_TYPE_OPEN_SINK;
  static const int MODEL_TYPE_OPEN_SOURCE;
  static const int MODEL_TYPE_OUTPUT_ECL;
  /* version 3.2 */
  static const int MODEL_TYPE_SERIES;
  static const int MODEL_TYPE_SERIES_SWITCH;

  /* Model Enable types */
  static const int MODEL_ENABLE_UNDEFINED;
  /* version 1.0 */
  static const int MODEL_ENABLE_ACTIVE_HIGH;
  static const int MODEL_ENABLE_ACTIVE_LOW;

  /* Model Polarity types */
  static const int MODEL_POLARITY_UNDEFINED;
  /* version 1.0 */
  static const int MODEL_POLARITY_NON_INVERTING;
  static const int MODEL_POLARITY_INVERTING;

  /* Supported Spice types */
  static const int SPICE_TYPE_HSPICE;
  static const int SPICE_TYPE_PSPICE;
  static const int SPICE_TYPE_SPICE2;
  static const int SPICE_TYPE_SPICE3;
  static const int SPICE_TYPE_SPECTRE;
  static const int SPICE_TYPE_ELDO;

  /* SPICE exit code (no execution errors) */
  static const int SPICE_GOOD_EXIT_CODE;

  /* This section supplies all of the component and model default values.
   */
  static const int RLOAD_DEFAULT;
  static const double C_COMP_DEFAULT;
  static const int TEMP_TYP_DEFAULT;
  static const int TEMP_MIN_DEFAULT;
  static const int TEMP_MAX_DEFAULT;
  static const int VOLTAGE_RANGE_TYP_DEFAULT;
  static const double VOLTAGE_RANGE_MIN_DEFAULT;
  static const double VOLTAGE_RANGE_MAX_DEFAULT;
  static const double SIM_TIME_DEFAULT;
  static const int SPICE_TYPE_DEFAULT;
  static const int DERATE_VI_PCT_DEFAULT;
  static const int DERATE_RAMP_PCT_DEFAULT;
  static const int CLAMP_TOLERANCE_DEFAULT;
  static const double R_SERIES_DEFAULT;
  static const double HSPICE_INGOLD_DEFAULT;
  /*-------------------------------------------------------------------------
   *   Define some global component default values.  These go into the
   *   components if not otherwise specified.
   *------------------------------------------------------------------------*/
  static const string MANUFACTURERS_NAME_DEFAULT;
  static const int R_PKG_DEFAULT;
  static const int L_PKG_DEFAULT;
  static const int C_PKG_DEFAULT;

  /*-------------------------------------------------------------------------
   *   Define some global analysis defaults.  These are used in the
   *   derivations of the models.
   *
   *   Note on DIODE_DROP_DEFAULT: This should be set to a value greater
   *   than or equal to the greatest protection diode turn-on voltage in
   *   your circuit.  I picked 1.0 as the default because it's a nice round
   *   number.
   *------------------------------------------------------------------------*/
  static const double LIN_RANGE_DEFAULT;
  static const double SWEEP_STEP_DEFAULT;
  static const double DIODE_DROP_DEFAULT;
  static const double ECL_SWEEP_RANGE_DEFAULT;
  static const double ECL_TERMINATION_VOLTAGE_DEFAULT;
  static const int WAVE_POINTS_DEFAULT;
};

struct goodies {
  static bool IS_USE_NA(double number);
  static bool IS_NOT_USED(double number);
  static int SIGN(double a);
  static double MIN(double a, double b);
  static int ROUND(double num);
  static bool THIS_PIN_NEEDS_ANALYSIS(string modelName);
  static int VERSION_ID(int MajorRelease, int MinorRelease, int SpecificID);
  static bool THIS_MODEL_NEEDS_SERIES_VI_DATA(int modelType);
  static bool THIS_MODEL_NEEDS_PULLUP_DATA(int modelType);
  static bool THIS_MODEL_NEEDS_PULLDOWN_DATA(int modelType);
  static bool THIS_MODEL_NEEDS_POWER_CLAMP_DATA(int modelType);
  static bool THIS_MODEL_NEEDS_GND_CLAMP_DATA(int modelType);
  static bool THIS_MODEL_NEEDS_TRANSIENT_DATA(int modelType);
  static bool IS_ECL(int model);
};
#endif // S2IHEADER_H
