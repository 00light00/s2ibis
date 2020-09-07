#include "ConstantStuff.h"

bool goodies::IS_USE_NA(double number) {
  if (((number) >= ConstantStuff::USE_NA - ConstantStuff::Tolerance) &&
      ((number) <= ConstantStuff::USE_NA + ConstantStuff::Tolerance))
    return (true);
  else
    return (false);
}

bool goodies::IS_NOT_USED(double number) {
  if (((number) >= ConstantStuff::NOT_USED - ConstantStuff::Tolerance) &&
      ((number) <= ConstantStuff::NOT_USED + ConstantStuff::Tolerance))
    return (true);
  else
    return (false);
}

int goodies::SIGN(double a) {
  if (a >= 0)
    return (1);
  else
    return (-1);
} // end method SIGN

double goodies::MIN(double a, double b) {
  if ((a) < (b))
    return (a);
  else
    return (b);
} // end method SIGN

int goodies::ROUND(double num) { return (int)(num + .5); } // end method ROUND

bool goodies::THIS_PIN_NEEDS_ANALYSIS(string modelName) {
  if (!((!modelName.compare("POWER")) || (!modelName.compare("GND")) ||
        (!modelName.compare("NC"))))
    return (true);
  else
    return (false);
} // end method THIS_PIN_NEEDS_ANALYSIS

int goodies::VERSION_ID(int MajorRelease, int MinorRelease, int SpecificID) {
  return ((MajorRelease * ConstantStuff::majorReleaseIncrement) +
          (MinorRelease * ConstantStuff::minorReleaseIncrement) + SpecificID);
} // end method VERSION_ID

bool goodies::THIS_MODEL_NEEDS_SERIES_VI_DATA(int modelType) {
  if ((modelType == ConstantStuff::MODEL_TYPE_SERIES) ||
      (modelType == ConstantStuff::MODEL_TYPE_SERIES_SWITCH))
    return (true);
  else
    return (false);
} // end method THIS_MODEL_NEEDS_SERIES_VI_DATA

bool goodies::THIS_MODEL_NEEDS_PULLUP_DATA(int modelType) {
  if ((modelType == ConstantStuff::MODEL_TYPE_OUTPUT) ||
      (modelType == ConstantStuff::MODEL_TYPE_3_STATE) ||
      (modelType == ConstantStuff::MODEL_TYPE_I_O) ||
      (modelType == ConstantStuff::MODEL_TYPE_OPEN_SOURCE) ||
      (modelType == ConstantStuff::MODEL_TYPE_I_O_OPEN_SOURCE) ||
      (modelType == ConstantStuff::MODEL_TYPE_OUTPUT_ECL) ||
      (modelType == ConstantStuff::MODEL_TYPE_I_O_ECL))
    return (true);
  else
    return (false);
} // end method THIS_MODEL_NEEDS_PULLUP_DATA

bool goodies::THIS_MODEL_NEEDS_PULLDOWN_DATA(int modelType) {
  if ((modelType == ConstantStuff::MODEL_TYPE_OUTPUT) ||
      (modelType == ConstantStuff::MODEL_TYPE_3_STATE) ||
      (modelType == ConstantStuff::MODEL_TYPE_I_O) ||
      (modelType == ConstantStuff::MODEL_TYPE_OPEN_SINK) ||
      (modelType == ConstantStuff::MODEL_TYPE_I_O_OPEN_SINK) ||
      (modelType == ConstantStuff::MODEL_TYPE_OPEN_DRAIN) ||
      (modelType == ConstantStuff::MODEL_TYPE_I_O_OPEN_DRAIN) ||
      (modelType == ConstantStuff::MODEL_TYPE_OUTPUT_ECL) ||
      (modelType == ConstantStuff::MODEL_TYPE_I_O_ECL))
    return (true);
  else
    return (false);
} // end method THIS_MODEL_NEEDS_PULLDOWN_DATA

bool goodies::THIS_MODEL_NEEDS_POWER_CLAMP_DATA(int modelType) {
  if ((modelType == ConstantStuff::MODEL_TYPE_INPUT) ||
      (modelType == ConstantStuff::MODEL_TYPE_3_STATE) ||
      (modelType == ConstantStuff::MODEL_TYPE_I_O) ||
      (modelType == ConstantStuff::MODEL_TYPE_I_O_OPEN_SOURCE) ||
      (modelType == ConstantStuff::MODEL_TYPE_INPUT_ECL) ||
      (modelType == ConstantStuff::MODEL_TYPE_I_O_ECL) ||
      (modelType == ConstantStuff::MODEL_TYPE_TERMINATOR))
    return (true);
  else
    return (false);
} // end method THIS_MODEL_NEEDS_POWER_CLAMP_DATA

bool goodies::THIS_MODEL_NEEDS_GND_CLAMP_DATA(int modelType) {
  if ((modelType == ConstantStuff::MODEL_TYPE_INPUT) ||
      (modelType == ConstantStuff::MODEL_TYPE_3_STATE) ||
      (modelType == ConstantStuff::MODEL_TYPE_I_O) ||
      (modelType == ConstantStuff::MODEL_TYPE_I_O_OPEN_SINK) ||
      (modelType == ConstantStuff::MODEL_TYPE_I_O_OPEN_DRAIN) ||
      (modelType == ConstantStuff::MODEL_TYPE_INPUT_ECL) ||
      (modelType == ConstantStuff::MODEL_TYPE_I_O_ECL) ||
      (modelType == ConstantStuff::MODEL_TYPE_TERMINATOR))
    return (true);
  else
    return (false);
} // end method THIS_MODEL_NEEDS_GND_CLAMP_DATA

bool goodies::THIS_MODEL_NEEDS_TRANSIENT_DATA(int modelType) {
  if ((modelType == ConstantStuff::MODEL_TYPE_OUTPUT) ||
      (modelType == ConstantStuff::MODEL_TYPE_3_STATE) ||
      (modelType == ConstantStuff::MODEL_TYPE_I_O) ||
      (modelType == ConstantStuff::MODEL_TYPE_OPEN_SINK) ||
      (modelType == ConstantStuff::MODEL_TYPE_I_O_OPEN_SINK) ||
      (modelType == ConstantStuff::MODEL_TYPE_OPEN_DRAIN) ||
      (modelType == ConstantStuff::MODEL_TYPE_I_O_OPEN_DRAIN) ||
      (modelType == ConstantStuff::MODEL_TYPE_OPEN_SOURCE) ||
      (modelType == ConstantStuff::MODEL_TYPE_I_O_OPEN_SOURCE) ||
      (modelType == ConstantStuff::MODEL_TYPE_OUTPUT_ECL) ||
      (modelType == ConstantStuff::MODEL_TYPE_I_O_ECL))
    return (true);
  else
    return (false);
} // end method THIS_MODEL_NEEDS_TRANSIENT_DATA

bool goodies::IS_ECL(int model) {
  if ((model == ConstantStuff::MODEL_TYPE_INPUT_ECL) ||
      (model == ConstantStuff::MODEL_TYPE_I_O_ECL) ||
      (model == ConstantStuff::MODEL_TYPE_OUTPUT_ECL))
    return (true);
  else
    return (false);
}
