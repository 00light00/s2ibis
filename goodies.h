
#ifndef _GOODIES
#define _GOODIES

#include "ConstantStuff.h"

class goodies
{
public:
  static bool IS_USE_NA(double number) {
    if (number >= -1.33288736222333E20D &&
      number <= -1.33286736222333E20D) {
      return true;
    }
    return false;
  }

  static bool IS_NOT_USED(double number) {
    if (number >= -1.33387736222333005E18D &&
      number <= -1.33187736222333005E18D) {
      return true;
    }
    return false;
  }

  static int SIGN(double a) {
    if (a >= 0.0D) {
      return 1;
    }
    return -1;
  }


  static double MIN(double a, double b) {
    if (a < b) {
      return a;
    }
    return b;
  }


  static int ROUND(double num) {
    return (int)(num + 0.5D);
  }

  static bool THIS_PIN_NEEDS_ANALYSIS(String modelName) {
    if (!modelName.equalsIgnoreCase("Power") &&
      !modelName.equalsIgnoreCase("GND") &&
      !modelName.equalsIgnoreCase("NC")) {
      return true;
    }
    return false;
  }


  static int VERSION_ID(int MajorRelease, int MinorRelease, int SpecificID) {
    return MajorRelease * 1000 +
      MinorRelease * 50 +
      SpecificID;
  }


  static bool THIS_MODEL_NEEDS_SERIES_VI_DATA(int modelType) {
    if (modelType == ConstantStuff.MODEL_TYPE_SERIES ||
      modelType == ConstantStuff.MODEL_TYPE_SERIES_SWITCH) {
      return true;
    }
    return false;
  }

  static bool THIS_MODEL_NEEDS_PULLUP_DATA(int modelType) {
    if (modelType == ConstantStuff.MODEL_TYPE_OUTPUT ||
      modelType == ConstantStuff.MODEL_TYPE_3_STATE ||
      modelType == ConstantStuff.MODEL_TYPE_I_O ||
      modelType == ConstantStuff.MODEL_TYPE_OPEN_SOURCE ||
      modelType == ConstantStuff.MODEL_TYPE_I_O_OPEN_SOURCE ||
      modelType == ConstantStuff.MODEL_TYPE_OUTPUT_ECL ||
      modelType == ConstantStuff.MODEL_TYPE_I_O_ECL) {
      return true;
    }
    return false;
  }

  static bool THIS_MODEL_NEEDS_PULLDOWN_DATA(int modelType) {
    if (modelType == ConstantStuff.MODEL_TYPE_OUTPUT ||
      modelType == ConstantStuff.MODEL_TYPE_3_STATE ||
      modelType == ConstantStuff.MODEL_TYPE_I_O ||
      modelType == ConstantStuff.MODEL_TYPE_OPEN_SINK ||
      modelType == ConstantStuff.MODEL_TYPE_I_O_OPEN_SINK ||
      modelType == ConstantStuff.MODEL_TYPE_OPEN_DRAIN ||
      modelType == ConstantStuff.MODEL_TYPE_I_O_OPEN_DRAIN ||
      modelType == ConstantStuff.MODEL_TYPE_OUTPUT_ECL ||
      modelType == ConstantStuff.MODEL_TYPE_I_O_ECL) {
      return true;
    }
    return false;
  }

  static bool THIS_MODEL_NEEDS_POWER_CLAMP_DATA(int modelType) {
    if (modelType == ConstantStuff.MODEL_TYPE_INPUT ||
      modelType == ConstantStuff.MODEL_TYPE_3_STATE ||
      modelType == ConstantStuff.MODEL_TYPE_I_O ||
      modelType == ConstantStuff.MODEL_TYPE_I_O_OPEN_SOURCE ||
      modelType == ConstantStuff.MODEL_TYPE_INPUT_ECL ||
      modelType == ConstantStuff.MODEL_TYPE_I_O_ECL ||
      modelType == ConstantStuff.MODEL_TYPE_TERMINATOR) {
      return true;
    }
    return false;
  }

  static bool THIS_MODEL_NEEDS_GND_CLAMP_DATA(int modelType) {
    if (modelType == ConstantStuff.MODEL_TYPE_INPUT ||
      modelType == ConstantStuff.MODEL_TYPE_3_STATE ||
      modelType == ConstantStuff.MODEL_TYPE_I_O ||
      modelType == ConstantStuff.MODEL_TYPE_I_O_OPEN_SINK ||
      modelType == ConstantStuff.MODEL_TYPE_I_O_OPEN_DRAIN ||
      modelType == ConstantStuff.MODEL_TYPE_INPUT_ECL ||
      modelType == ConstantStuff.MODEL_TYPE_I_O_ECL ||
      modelType == ConstantStuff.MODEL_TYPE_TERMINATOR) {
      return true;
    }
    return false;
  }

  static bool THIS_MODEL_NEEDS_TRANSIENT_DATA(int modelType) {
    if (modelType == ConstantStuff.MODEL_TYPE_OUTPUT ||
      modelType == ConstantStuff.MODEL_TYPE_3_STATE ||
      modelType == ConstantStuff.MODEL_TYPE_I_O ||
      modelType == ConstantStuff.MODEL_TYPE_OPEN_SINK ||
      modelType == ConstantStuff.MODEL_TYPE_I_O_OPEN_SINK ||
      modelType == ConstantStuff.MODEL_TYPE_OPEN_DRAIN ||
      modelType == ConstantStuff.MODEL_TYPE_I_O_OPEN_DRAIN ||
      modelType == ConstantStuff.MODEL_TYPE_OPEN_SOURCE ||
      modelType == ConstantStuff.MODEL_TYPE_I_O_OPEN_SOURCE ||
      modelType == ConstantStuff.MODEL_TYPE_OUTPUT_ECL ||
      modelType == ConstantStuff.MODEL_TYPE_I_O_ECL) {
      return true;
    }
    return false;
  }


  static bool IS_ECL(int model) {
    if (model == ConstantStuff.MODEL_TYPE_INPUT_ECL ||
      model == ConstantStuff.MODEL_TYPE_I_O_ECL ||
      model == ConstantStuff.MODEL_TYPE_OUTPUT_ECL) {
      return true;
    }
    return false;
  }

  static double fabs(double number) {
    return Math.abs(number);
  }
};

#endif
