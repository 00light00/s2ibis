#ifndef _CONSTANSTUFF
#define _CONSTANSTUFF

interface ConstantStuff
{
  static final String VERSION_STRING = "1.1";
  static final int UNDEFINED = 0;
  static final int OUTPUT_LOW = 0;
  static final int OUTPUT_HIGH = 1;
  static final int OUTPUT_FALLING = 0;
  static final int OUTPUT_RISING = 1;
  static final int DISABLE_OUTPUT = 0;
  static final int ENABLE_OUTPUT = 1;
  static final int TYP_CASE = 0;
  static final int MIN_CASE = -1;
  static final int MAX_CASE = 1;
  static final int NUM_PTS_LINEAR_REGION = 10;
  static final int MAX_TABLE_SIZE = 100;
  static final int MAX_MANUFACTURERS_NAME_LENGTH = 40;
  static final int MAX_FILENAME_BASE_LENGTH = 20;
  static final String FILENAME_EXTENSION = "ibs";
  static final int FILENAME_EXTENSION_LENGTH = 3;
  static final int MAX_PIN_NAME_LENGTH = 5;
  static final int MAX_SIGNAL_NAME_LENGTH = 20;
  static final int MAX_MODEL_NAME_LENGTH = 20;
  static final int MAX_R_PIN_STRING_LENGTH = 9;
  static final int MAX_L_PIN_STRING_LENGTH = 9;
  static final int MAX_C_PIN_STRING_LENGTH = 9;
  static final int MAX_LINE_LENGTH = 80;
  static final int MAX_COMPONENT_NAME_LENGTH = 40;
  static final int MAX_FILENAME_LENGTH = 24;
  static final int MAX_PACKAGE_MODEL_NAME_LENGTH = 40;
  static final int MAX_PIN_MAPPING_NAME_LENGTH = 15;
  static final int MAX_DFF_PIN_NAME_LENGTH = 5;
  static final int MAX_INV_PIN_LEBGTH = 5;
  static final int MAX_VDIFF_TYP_LENGTH = 9;
  static final int MAX_TEDELAY_MAX_LENGTH = 9;
  static final int MAX_WAVEFORM_TABLES = 100;
  static final int MAX_SERIES_TABLES = 100;
  static final int MAX_FILE_REV_LENGTH = 4;
  static final int MAX_TOK_LEN = 40;
  static final int MAX_DATE_STRING_LENGTH = 40;
  static final int MAX_IBIS_STRING_LENGTH = 1024;
  static final int IBIS_PRINT_WIDTH = 80;
  static final double USE_NA = -1.33287736222333E20D;
  static final double NOT_USED = -1.33287736222333005E18D;
  static final double Tolerance = 1.0E15D;
  static final int CURVE_TYPE_PULLUP = 0;
  static final int CURVE_TYPE_PULLDOWN = 1;
  static final int CURVE_TYPE_POWER_CLAMP = 2;
  static final int CURVE_TYPE_GND_CLAMP = 3;
  static final int CURVE_TYPE_DISABLED_PULLUP = 4;
  static final int CURVE_TYPE_DISABLED_PULLDOWN = 5;
  static final int CURVE_TYPE_RISING_RAMP = 6;
  static final int CURVE_TYPE_FALLING_RAMP = 7;
  static final int CURVE_TYPE_RISING_WAVE = 8;
  static final int CURVE_TYPE_FALLING_WAVE = 9;
  static final int CURVE_TYPE_SERIES_VI = 10;
  static final int majorReleaseIncrement = 1000;
  static final int minorReleaseIncrement = 50;
  static final int VERSION_ONE_ZERO = goodies.VERSION_ID(1, 0, 0);
  static final int VERSION_ONE_ONE = goodies.VERSION_ID(1, 1, 0);
  static final int VERSION_TWO_ZERO = goodies.VERSION_ID(2, 0, 0);
  static final int VERSION_TWO_ONE = goodies.VERSION_ID(2, 1, 0);

  static final int VERSION_THREE_TWO = goodies.VERSION_ID(3, 2, 0);


  static final int MODEL_TYPE_UNDEFINED = 0;


  static final int MODEL_TYPE_INPUT = goodies.VERSION_ID(1, 0, 1);
  static final int MODEL_TYPE_OUTPUT = goodies.VERSION_ID(1, 0, 2);
  static final int MODEL_TYPE_OPEN_DRAIN = goodies.VERSION_ID(1, 0, 4);
  static final int MODEL_TYPE_3_STATE = goodies.VERSION_ID(1, 0, 3);
  static final int MODEL_TYPE_I_O = goodies.VERSION_ID(1, 0, 5);

  static final int MODEL_TYPE_I_O_OPEN_DRAIN = goodies.VERSION_ID(2, 0, 1);
  static final int MODEL_TYPE_I_O_OPEN_SINK = goodies.VERSION_ID(2, 0, 2);
  static final int MODEL_TYPE_I_O_OPEN_SOURCE = goodies.VERSION_ID(2, 0, 3);
  static final int MODEL_TYPE_INPUT_ECL = goodies.VERSION_ID(2, 0, 4);
  static final int MODEL_TYPE_I_O_ECL = goodies.VERSION_ID(2, 0, 5);
  static final int MODEL_TYPE_TERMINATOR = goodies.VERSION_ID(2, 0, 6);
  static final int MODEL_TYPE_OPEN_SINK = goodies.VERSION_ID(2, 0, 7);
  static final int MODEL_TYPE_OPEN_SOURCE = goodies.VERSION_ID(2, 0, 8);
  static final int MODEL_TYPE_OUTPUT_ECL = goodies.VERSION_ID(2, 0, 9);

  static final int MODEL_TYPE_SERIES = goodies.VERSION_ID(3, 0, 1);
  static final int MODEL_TYPE_SERIES_SWITCH = goodies.VERSION_ID(3, 0, 2);


  static final int MODEL_ENABLE_UNDEFINED = 0;


  static final int MODEL_ENABLE_ACTIVE_HIGH = goodies.VERSION_ID(1, 2, 1);
  static final int MODEL_ENABLE_ACTIVE_LOW = goodies.VERSION_ID(1, 2, 2);


  static final int MODEL_POLARITY_UNDEFINED = 0;

  static final int MODEL_POLARITY_NON_INVERTING = goodies.VERSION_ID(1, 3, 1);
  static final int MODEL_POLARITY_INVERTING = goodies.VERSION_ID(1, 3, 2);
  static final int SPICE_TYPE_HSPICE = 0;
  static final int SPICE_TYPE_PSPICE = 1;
  static final int SPICE_TYPE_SPICE2 = 2;
  static final int SPICE_TYPE_SPICE3 = 3;
  static final int SPICE_TYPE_SPECTRE = 4;
  static final int SPICE_TYPE_ELDO = 5;
  static final int SPICE_GOOD_EXIT_CODE = 0;
  static final int RLOAD_DEFAULT = 50;
  static final double C_COMP_DEFAULT = 5.0E-12D;
  static final int TEMP_TYP_DEFAULT = 27;
  static final int TEMP_MIN_DEFAULT = 100;
  static final int TEMP_MAX_DEFAULT = 0;
  static final int VOLTAGE_RANGE_TYP_DEFAULT = 5;
  static final double VOLTAGE_RANGE_MIN_DEFAULT = 4.5D;
  static final double VOLTAGE_RANGE_MAX_DEFAULT = 5.5D;
  static final double SIM_TIME_DEFAULT = 1.0E-8D;
  static final int SPICE_TYPE_DEFAULT = 0;
  static final int DERATE_VI_PCT_DEFAULT = 0;
  static final int DERATE_RAMP_PCT_DEFAULT = 0;
  static final int CLAMP_TOLERANCE_DEFAULT = 0;
  static final double R_SERIES_DEFAULT = 1000000.0D;
  static final double HSPICE_INGOLD_DEFAULT = 2.0D;
  static final String MANUFACTURERS_NAME_DEFAULT = "Manufacturer name";
  static final int R_PKG_DEFAULT = 0;
  static final int L_PKG_DEFAULT = 0;
  static final int C_PKG_DEFAULT = 0;
  static final double LIN_RANGE_DEFAULT = 5.0D;
  static final double SWEEP_STEP_DEFAULT = 0.01D;
  static final double DIODE_DROP_DEFAULT = 1.0D;
  static final double ECL_SWEEP_RANGE_DEFAULT = 2.2D;
  static final double ECL_TERMINATION_VOLTAGE_DEFAULT = -2.0D;
  static final int WAVE_POINTS_DEFAULT = 100;
};

#endif
