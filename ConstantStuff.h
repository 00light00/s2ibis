#ifndef _CONSTANSTUFF
#define _CONSTANSTUFF

#include <string.h>
#include "goodies.h"
#define String std::string

const String VERSION_STRING = "1.1";
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
const int MAX_TABLE_SIZE = 100;
const int MAX_MANUFACTURERS_NAME_LENGTH = 40;
const int MAX_FILENAME_BASE_LENGTH = 20;
const String FILENAME_EXTENSION = "ibs";
const int FILENAME_EXTENSION_LENGTH = 3;
const int MAX_PIN_NAME_LENGTH = 5;
const int MAX_SIGNAL_NAME_LENGTH = 20;
const int MAX_MODEL_NAME_LENGTH = 20;
const int MAX_R_PIN_STRING_LENGTH = 9;
const int MAX_L_PIN_STRING_LENGTH = 9;
const int MAX_C_PIN_STRING_LENGTH = 9;
const int MAX_LINE_LENGTH = 80;
const int MAX_COMPONENT_NAME_LENGTH = 40;
const int MAX_FILENAME_LENGTH = 24;
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
const int IBIS_PRINT_WIDTH = 80;
const double USE_NA = -1.33287736222333E20D;
const double NOT_USED = -1.33287736222333005E18D;
const double Tolerance = 1.0E15D;
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
const int CURVE_TYPE_SERIES_VI = 10;
const int majorReleaseIncrement = 1000;
const int minorReleaseIncrement = 50;
const int VERSION_ONE_ZERO = goodies.VERSION_ID(1, 0, 0);
const int VERSION_ONE_ONE = goodies.VERSION_ID(1, 1, 0);
const int VERSION_TWO_ZERO = goodies.VERSION_ID(2, 0, 0);
const int VERSION_TWO_ONE = goodies.VERSION_ID(2, 1, 0);

const int VERSION_THREE_TWO = goodies.VERSION_ID(3, 2, 0);


const int MODEL_TYPE_UNDEFINED = 0;


const int MODEL_TYPE_INPUT = goodies.VERSION_ID(1, 0, 1);
const int MODEL_TYPE_OUTPUT = goodies.VERSION_ID(1, 0, 2);
const int MODEL_TYPE_OPEN_DRAIN = goodies.VERSION_ID(1, 0, 4);
const int MODEL_TYPE_3_STATE = goodies.VERSION_ID(1, 0, 3);
const int MODEL_TYPE_I_O = goodies.VERSION_ID(1, 0, 5);

const int MODEL_TYPE_I_O_OPEN_DRAIN = goodies.VERSION_ID(2, 0, 1);
const int MODEL_TYPE_I_O_OPEN_SINK = goodies.VERSION_ID(2, 0, 2);
const int MODEL_TYPE_I_O_OPEN_SOURCE = goodies.VERSION_ID(2, 0, 3);
const int MODEL_TYPE_INPUT_ECL = goodies.VERSION_ID(2, 0, 4);
const int MODEL_TYPE_I_O_ECL = goodies.VERSION_ID(2, 0, 5);
const int MODEL_TYPE_TERMINATOR = goodies.VERSION_ID(2, 0, 6);
const int MODEL_TYPE_OPEN_SINK = goodies.VERSION_ID(2, 0, 7);
const int MODEL_TYPE_OPEN_SOURCE = goodies.VERSION_ID(2, 0, 8);
const int MODEL_TYPE_OUTPUT_ECL = goodies.VERSION_ID(2, 0, 9);

const int MODEL_TYPE_SERIES = goodies.VERSION_ID(3, 0, 1);
const int MODEL_TYPE_SERIES_SWITCH = goodies.VERSION_ID(3, 0, 2);


const int MODEL_ENABLE_UNDEFINED = 0;


const int MODEL_ENABLE_ACTIVE_HIGH = goodies.VERSION_ID(1, 2, 1);
const int MODEL_ENABLE_ACTIVE_LOW = goodies.VERSION_ID(1, 2, 2);


const int MODEL_POLARITY_UNDEFINED = 0;

const int MODEL_POLARITY_NON_INVERTING = goodies.VERSION_ID(1, 3, 1);
const int MODEL_POLARITY_INVERTING = goodies.VERSION_ID(1, 3, 2);
const int SPICE_TYPE_HSPICE = 0;
const int SPICE_TYPE_PSPICE = 1;
const int SPICE_TYPE_SPICE2 = 2;
const int SPICE_TYPE_SPICE3 = 3;
const int SPICE_TYPE_SPECTRE = 4;
const int SPICE_TYPE_ELDO = 5;
const int SPICE_GOOD_EXIT_CODE = 0;
const int RLOAD_DEFAULT = 50;
const double C_COMP_DEFAULT = 5.0E-12D;
const int TEMP_TYP_DEFAULT = 27;
const int TEMP_MIN_DEFAULT = 100;
const int TEMP_MAX_DEFAULT = 0;
const int VOLTAGE_RANGE_TYP_DEFAULT = 5;
const double VOLTAGE_RANGE_MIN_DEFAULT = 4.5D;
const double VOLTAGE_RANGE_MAX_DEFAULT = 5.5D;
const double SIM_TIME_DEFAULT = 1.0E-8D;
const int SPICE_TYPE_DEFAULT = 0;
const int DERATE_VI_PCT_DEFAULT = 0;
const int DERATE_RAMP_PCT_DEFAULT = 0;
const int CLAMP_TOLERANCE_DEFAULT = 0;
const double R_SERIES_DEFAULT = 1000000.0D;
const double HSPICE_INGOLD_DEFAULT = 2.0D;
const String MANUFACTURERS_NAME_DEFAULT = "Manufacturer name";
const int R_PKG_DEFAULT = 0;
const int L_PKG_DEFAULT = 0;
const int C_PKG_DEFAULT = 0;
const double LIN_RANGE_DEFAULT = 5.0D;
const double SWEEP_STEP_DEFAULT = 0.01D;
const double DIODE_DROP_DEFAULT = 1.0D;
const double ECL_SWEEP_RANGE_DEFAULT = 2.2D;
const double ECL_TERMINATION_VOLTAGE_DEFAULT = -2.0D;
const int WAVE_POINTS_DEFAULT = 100;


#endif
