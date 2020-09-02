/*******************************************************************************
*File Name	: s2ispice.java
*Description	: This file contains all of the Spice interface code for s2ibis3
*		:
*		: North Carolina State University
*		: Electronics Research Laboratory
********************************************************************************

Classes:
-------------------------------------------------
setupPwrAndTempCmds		getSpiceVIData
setupDCSweepCommands		create_VItable
setupTranCommands		generateVICurve
setupSpiceFileName		spiceVT
setupSpiceInputFile		getSpiceRampData
setPinDC			generateRampData
setPinTran			getSpiceWaveData
StreamGobbler			binParams
callSpice			binTranData
checkForAbort			generateWaveData
runSpiceAgain			VIDataContainer

$Log: s2ispice.java,v $
Revision 1.7  2006/03/27 18:00:36  akvarma
Fix min and max portions of generateRampData() to use
min and max process corner, instead of typ. -- Done by Mike LaBonte
(milabont@cisco.com) Commented out a redundant System.out line (//debug)

Revision 1.6  2005/02/24 22:41:48  akvarma
1. Cleanup code
2. Make use of Streamgobbler
3. Special Processing for ELDO
4. Fixed the 'if' loop for wave and ramp (generateRampData and generateWaveData)
so that callSpice is checked before it checks for abort.
5. Added code to include extSpiceCmd
6. Fixed Version_string
7.Added code for extSpiceCmdFile

Revision 1.5  2004/04/20 18:09:43  akvarma
added code to deal with *.ic0 files for hspice when using 'cleanup'

Revision 1.4  2004/04/17 21:05:15  akvarma
model file is not needed for simulations. It is an optional choice for the user.
Fixed the above bug.
Also - previously hardcoded enableOutput to be = 1. changed it to 'enableOutput'

Revision 1.3  2003/11/24 05:17:08  akvarma
Added series MOSFET functionality. Changed to get the -ve I value. Hspice output
data is negative, hence have to negate I values to get the correct value.

Revision 1.2  2003/08/04 16:53:56  akvarma
Cleaned up code.
Removed error because of non-creation of .msg files in HSPICE - converted to
warning.

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
*/

// import java.text.*;
// import java.io.*;
// import java.util.*;
// import java.lang.string.* ;
// import java.awt.List;
// import java.math.*;

#include <string>
using namespace std;
#include "s2iHeader.h"

/******************************************************************************
CLASS: setupPwrAndTempCmds
******************************************************************************/

class setupPwrAndTempCmds {
public:
  string powerBuffer;
  string temperatureBuffer;
  void setupPwrAndTempCmds(int curveType, int spiceType, ibisPin powerPin,
                           ibisPin gndPin, ibisPin powerClampPin,
                           ibisPin gndClampPin, double Vcc, double Gnd,
                           double VccClamp, double GndClamp,
                           double temperature) {
    string dummyBuffer;
    if ((curveType == ConstantStuff.CURVE_TYPE_POWER_CLAMP) ||
        (curveType == ConstantStuff.CURVE_TYPE_GND_CLAMP)) {
      if (powerClampPin != null) {
        // debug     printf("powerClampPin.spiceNodeName
        // "+powerClampPin.spiceNodeName);

        if (spiceType == ConstantStuff.SPICE_TYPE_SPECTRE)
          powerBuffer = "VCLMPS2I " + powerClampPin.spiceNodeName + " 0 " +
                        " vsource type=dc dc=" + VccClamp + "\n";
        else
          powerBuffer = "VCLMPS2I " + powerClampPin.spiceNodeName + " 0 " +
                        " DC " + VccClamp + "\n";

        if ((powerPin != null) &&
            !(powerClampPin.spiceNodeName.equalsIgnoreCase(
                powerPin.spiceNodeName))) {
          if (spiceType == ConstantStuff.SPICE_TYPE_SPECTRE)
            dummyBuffer = "VCCS2I " + powerPin.spiceNodeName + " 0 " +
                          " vsource type=dc dc=" + Vcc + "\n";
          else
            dummyBuffer = "VCCS2I " + powerPin.spiceNodeName + " 0 " + " DC " +
                          Vcc + "\n";

          powerBuffer = powerBuffer + dummyBuffer;
        }
      } else {
        if (powerPin != null) {
          if (spiceType == ConstantStuff.SPICE_TYPE_SPECTRE)
            powerBuffer = "VCCS2I " + powerPin.spiceNodeName + " 0 " +
                          " vsource type=dc dc=" + Vcc + "\n";
          else
            powerBuffer = "VCCS2I " + powerPin.spiceNodeName + " 0 " + " DC " +
                          Vcc + "\n";
        }
      }
      if (gndClampPin != null) {
        if (spiceType == ConstantStuff.SPICE_TYPE_SPECTRE)
          dummyBuffer = "VGCLMPS2I " + gndClampPin.spiceNodeName + " 0 " +
                        " vsource type=dc dc=" + GndClamp + "\n";
        else
          dummyBuffer = "VGCLMPS2I " + gndClampPin.spiceNodeName + " 0 " +
                        " DC " + GndClamp + "\n";

        powerBuffer = powerBuffer + dummyBuffer;
        if ((gndPin != null) && !(gndClampPin.spiceNodeName.equalsIgnoreCase(
                                    gndPin.spiceNodeName))) {
          if (spiceType == ConstantStuff.SPICE_TYPE_SPECTRE)
            dummyBuffer = "VGNDS2I " + gndPin.spiceNodeName + " 0 " +
                          " vsource type=dc dc=" + Gnd + "\n";
          else
            dummyBuffer =
                "VGNDS2I " + gndPin.spiceNodeName + " 0 " + " DC " + Gnd + "\n";

          powerBuffer = powerBuffer + dummyBuffer;
        }
      } else {
        if (gndPin != null) {
          if (spiceType == ConstantStuff.SPICE_TYPE_SPECTRE)
            dummyBuffer = "VGNDS2I " + gndPin.spiceNodeName + " 0 " +
                          " vsource type=dc dc=" + Gnd + "\n";
          else
            dummyBuffer =
                "VGNDS2I " + gndPin.spiceNodeName + " 0 " + " DC " + Gnd + "\n";
        }
      }
    } // if(curveType)
    else if (curveType == ConstantStuff.CURVE_TYPE_SERIES_VI) {
      if (powerPin != null) {
        if (spiceType == ConstantStuff.SPICE_TYPE_SPECTRE)
          powerBuffer = "VCCS2I " + powerPin.spiceNodeName + " 0 " +
                        " vsource type=dc dc=" + Vcc + "\n";
        else
          powerBuffer =
              "VCCS2I " + powerPin.spiceNodeName + " 0 " + " DC " + Vcc + "\n";
      }
      if (gndPin != null) {
        if (spiceType == ConstantStuff.SPICE_TYPE_SPECTRE)
          dummyBuffer = "VGNDS2I " + gndPin.spiceNodeName + " 0 " +
                        " vsource type=dc dc=" + Gnd + "\n";
        else
          dummyBuffer =
              "VGNDS2I " + gndPin.spiceNodeName + " 0 " + " DC " + Gnd + "\n";

        powerBuffer = powerBuffer + dummyBuffer;
      }

    } else {
      if (powerPin != null) {
        if (spiceType == ConstantStuff.SPICE_TYPE_SPECTRE)
          powerBuffer = "VCCS2I " + powerPin.spiceNodeName + " 0 " +
                        " vsource type=dc dc=" + Vcc + "\n";
        else
          powerBuffer =
              "VCCS2I " + powerPin.spiceNodeName + " 0 " + " DC " + Vcc + "\n";

        if ((powerClampPin != null) &&
            !(powerClampPin.spiceNodeName.equalsIgnoreCase(
                powerPin.spiceNodeName))) {
          if (spiceType == ConstantStuff.SPICE_TYPE_SPECTRE)
            dummyBuffer = "VCLMPS2I " + powerClampPin.spiceNodeName + " 0 " +
                          " vsource type=dc dc=" + VccClamp + "\n";
          else
            dummyBuffer = "VCLMPS2I " + powerClampPin.spiceNodeName + " 0 " +
                          " DC " + VccClamp + "\n";

          powerBuffer = powerBuffer + dummyBuffer;
        }
      } else {
        if (powerClampPin != null) {
          if (spiceType == ConstantStuff.SPICE_TYPE_SPECTRE)
            powerBuffer = "VCLMPS2I " + powerClampPin.spiceNodeName + " 0 " +
                          " vsource type=dc dc=" + VccClamp + "\n";
          else
            powerBuffer = "VCLMPS2I " + powerClampPin.spiceNodeName + " 0 " +
                          " DC " + VccClamp + "\n";
        }
      }
      if (gndPin != null) {
        if (spiceType == ConstantStuff.SPICE_TYPE_SPECTRE)
          dummyBuffer = "VGNDS2I " + gndPin.spiceNodeName + " 0 " +
                        " vsource type=dc dc=" + Gnd + "\n";
        else
          dummyBuffer =
              "VGNDS2I " + gndPin.spiceNodeName + " 0 " + " DC " + Gnd + "\n";

        powerBuffer = powerBuffer + dummyBuffer;
        if ((gndClampPin != null) &&
            !(gndClampPin.spiceNodeName.equalsIgnoreCase(
                gndPin.spiceNodeName))) {
          if (spiceType == ConstantStuff.SPICE_TYPE_SPECTRE)
            dummyBuffer = "VGCLMPS2I " + gndClampPin.spiceNodeName + " 0 " +
                          " vsource type=dc dc=" + GndClamp + "\n";
          else
            dummyBuffer = "VGCLMPS2I " + gndClampPin.spiceNodeName + " 0 " +
                          " DC " + GndClamp + "\n";

          powerBuffer = powerBuffer + dummyBuffer;
        }
      } else {
        if (gndClampPin != null) {
          if (spiceType == ConstantStuff.SPICE_TYPE_SPECTRE)
            dummyBuffer = "VGCLMPS2I " + gndClampPin.spiceNodeName + " 0 " +
                          " vsource type=dc dc=" + GndClamp + "\n";
          else
            dummyBuffer = "VGCLMPS2I " + gndClampPin.spiceNodeName + " 0 " +
                          " DC " + GndClamp + "\n";
        }
      }
    } // else

    temperatureBuffer = s2iString.temperatureString(spiceType, temperature);
  } // method setupPwrAndTempCmds
};  // class setupPwrAndTempCmds

/******************************************************************************
CLASS: setupDCSweepCommands
******************************************************************************/

class setupDCSweepCommands {
public:
  string setupDCSweepCommands(int curveType, int spiceType, double sweepStart,
                              double sweepEnd, double sweepStep) {
    string analysisBuffer;
    string dummyBuffer = null;
    if (spiceType == ConstantStuff.SPICE_TYPE_SPECTRE) {
      analysisBuffer = "DCsweep dc dev= VOUTS2I param=dc start=" + sweepStart +
                       " stop=" + sweepEnd + " step=" + sweepStep +
                       " save=selected\n";
      if (curveType == ConstantStuff.CURVE_TYPE_SERIES_VI)
        dummyBuffer = "save VDS:currents\n";
      else
        dummyBuffer = "save VOUTS2I:currents\n";
    } else {
      analysisBuffer = ".DC VOUTS2I " + sweepStart + " " + sweepEnd + " " +
                       sweepStep + " \n";
      if (curveType == ConstantStuff.CURVE_TYPE_SERIES_VI)
        dummyBuffer = ".PRINT DC I(VDS)\n";
      else
        dummyBuffer = ".PRINT DC I(VOUTS2I)\n";
    }
    analysisBuffer = analysisBuffer + dummyBuffer;

    return analysisBuffer;
  } // method setupDCSweepCommands
};  // class setupDCSweepCommands

/******************************************************************************
CLASS: setupTranCommands
******************************************************************************/

class setupTranCommands {
public:
  string setupTranCommands(int spiceType, double simTime, string outputNode) {
    string analysisBuffer;
    string dummyBuffer = null;
    string nodeNameBuffer = null;
    int dummy = 0;
    nodeNameBuffer = outputNode;
    if (spiceType == ConstantStuff.SPICE_TYPE_SPECTRE) {
      analysisBuffer = "tran_run tran step=" + simTime / 100 +
                       " start=0 stop=" + simTime + " save=selected\n";
      dummyBuffer = "save " + nodeNameBuffer + "\n";
    } else {
      analysisBuffer = ".TRAN " + simTime / 100 + " " + simTime + " \n";
      dummyBuffer = ".PRINT TRAN V(" + nodeNameBuffer + ")\n";
    }
    analysisBuffer = analysisBuffer + dummyBuffer;
    return analysisBuffer;
  } // method setupTranCommands
};  // class setupTranCommands

/******************************************************************************
CLASS: setupSpiceFileNames
******************************************************************************/

class setupSpiceFileNames {
public:
  string spiceInFile = null;
  string spiceOutFile = null;
  string spiceMsgFile = null;

  void setupSpiceFileNames(string afileNamePrefix, string aPinName) {
    string prependThis = afileNamePrefix + aPinName;
    spiceInFile = prependThis + ".spi";
    spiceOutFile = prependThis + ".out";
    spiceMsgFile = prependThis + ".msg";
  }
}; // class setupSpiceFileName

/******************************************************************************
CLASS: setupSpiceInputFile
******************************************************************************/

class setupSpiceInputFile {

public:
  int setupSpiceInputFile(int iterate,              // IN
                          int spiceType,            // IN
                          string spiceInputFile,    // IN
                          string headerLine,        // IN
                          string spiceFile,         // IN
                          string modelFile,         // IN
                          string extSpiceCmdFile,   // IN for 0.4beta
                          string loadBuffer,        // IN
                          string inputBuffer,       // IN
                          string powerBuffer,       // IN
                          string temperatureBuffer, // IN
                          string analysisBuffer) {  // IN
    string headerLine2;
    string lineBuffer;
    string lineBuffer1;
    string token;
    string token_p;
    string temp_p;
    File spiceInFile_p = new File(spiceInputFile);
    File tempFile_p;
    bool fileExists;

    try {
      fileExists = spiceInFile_p.exists();

      /*
      New for 0.4beta
      */

      headerLine2 = "*Spice Deck created by S2IBIS3 Version " +
                    ConstantStuff.VERSION_STRING +
                    " \n*North Carolina State University ";
      PrintWriter spiceInWriter =
          new PrintWriter(new BufferedWriter(new FileWriter(spiceInFile_p)));

      /*-------------------------------------------------------------------------
       *   Only set up the file if iterate is not set or if the file does not
       *   already exist.
       *------------------------------------------------------------------------*/
      if ((iterate == 0) || !(fileExists)) {
        tempFile_p = new File(spiceFile);

        /*-------------------------------------------------------------------------
         *	Check to make sure we can open the file for writing.  If not,
         *	return an error.  If so, begin creating the spice file.
         *--------------------------------------------------------------------*/
        if (!(spiceInFile_p.canWrite())) {
          printf("Unable to open " + spiceInputFile + " for writing");
          return 1;
        } else {
          /*-----------------------------------------------------------------
           *   First, print out the header information.
           *----------------------------------------------------------------*/
          spiceInWriter.println(headerLine + headerLine2);
          if (spiceInWriter.checkError()) {
            printf("Error while writing header lines ");
            spiceInWriter.close();
            return 1;
          }
          /*-----------------------------------------------------------------
           *   Next, copy the component spice file to the spice input file.
           *----------------------------------------------------------------*/
          if (!(tempFile_p.canRead())) {
            printf("Unable to open " + spiceFile + " for reading");
            spiceInWriter.close();
            return 1;
          }
          BufferedReader tempReader =
              new BufferedReader(new FileReader(tempFile_p));
          while ((lineBuffer = tempReader.readLine()) != null) {
            /*-------------------------------------------------------------
             *	We need to check two conditions:  if the first token
             *	of the line is a *, we don't write the line because
             *	it's a comment; and if the first token of the line is
             *	the .end card, we don't write it, because there's more
             *	stuff to add.
             *------------------------------------------------------------*/
            string firstArg = null;
            StringTokenizer st1 = new StringTokenizer(lineBuffer);
            int cnt = st1.countTokens();
            if (cnt != 0) {
              firstArg = st1.nextToken();
              if (!(firstArg.equalsIgnoreCase(".end")) &&
                  !(firstArg.equals("*")))
                spiceInWriter.println(lineBuffer);
              if (spiceInWriter.checkError()) {
                printf("Error copying " + spiceFile);
                spiceInWriter.close();
                tempReader.close();
                return 1;
              }
            }
          } // while
          try {
            tempReader.close();
          } catch (IOException e) {
            printf("Error " + e.toString() + " while closing " + spiceFile);
            spiceInWriter.close();
            return 1;
          }
          /*-----------------------------------------------------------------
           *   Next, copy the model file to the spice input file.  However,
           *   we only want to do this if a model file has been specified.
           *----------------------------------------------------------------*/
          if (!((modelFile.equals("")) ||
                (modelFile.equalsIgnoreCase("NA")))) // fixed 03/13/04
          {
            tempFile_p = new File(modelFile);

            if (!(tempFile_p.canRead())) {
              printf("Unable to open " + modelFile + " for reading");
              spiceInWriter.close();
              return 1;
            }
            //	   BufferedReader
            tempReader = new BufferedReader(new FileReader(tempFile_p));
            while ((lineBuffer1 = tempReader.readLine()) != null) {
              spiceInWriter.println(lineBuffer1);
              if (spiceInWriter.checkError()) {
                printf("Error copying " + modelFile);
                spiceInWriter.close();
                tempReader.close();
                return 1;
              }
            } // while
            try {
              tempReader.close();
            } catch (IOException e) {
              printf("Error " + e.toString() + " while closing " + spiceFile);
              spiceInWriter.close();
              return 1;
            }
          }
          /*
          New for 0.4beta
          */
          /*-----------------------------------------------------------------
           *   Next, copy the external spice command file to the spice input
           *file. However,we only want to do this if a model file has been
           *specified.
           *----------------------------------------------------------------*/
          if (!((extSpiceCmdFile.equals("")) ||
                (extSpiceCmdFile.equalsIgnoreCase("NA")))) {
            tempFile_p = new File(extSpiceCmdFile);

            if (!(tempFile_p.canRead())) {
              printf("Unable to open " + extSpiceCmdFile + " for reading");
              spiceInWriter.close();
              return 1;
            }
            //	   BufferedReader
            tempReader = new BufferedReader(new FileReader(tempFile_p));

            spiceInWriter.println("\n");
            while ((lineBuffer1 = tempReader.readLine()) != null) {
              spiceInWriter.println(lineBuffer1);
              if (spiceInWriter.checkError()) {
                printf("Error copying " + extSpiceCmdFile);
                spiceInWriter.close();
                tempReader.close();
                return 1;
              }
            } // while
            spiceInWriter.println("\n");

            try {
              tempReader.close();
            } catch (IOException e) {
              printf("Error " + e.toString() + " while closing " + spiceFile);
              spiceInWriter.close();
              return 1;
            }
          }

          /*-----------------------------------------------------------------
           *   If this is a Spectre sim, set the sim lang to spectre.
           *----------------------------------------------------------------*/
          if (spiceType == ConstantStuff.SPICE_TYPE_SPECTRE) {
            spiceInWriter.println("simulator lang = spectre\n");
            if (spiceInWriter.checkError()) {
              printf("Error while writing simulator language in file " +
                     spiceInFile_p);
              spiceInWriter.close();
              return 1;
            }
          }
          /*-----------------------------------------------------------------
           *   Next, copy the the load buffer to the spice input file.
           *----------------------------------------------------------------*/
          spiceInWriter.println(loadBuffer);
          if (spiceInWriter.checkError()) {
            printf("Error while writing load to file " + spiceInFile_p);
            spiceInWriter.close();
            return 1;
          }
          /*-----------------------------------------------------------------
           *   Next, copy the the power source command buffer to the spice
           *   input file.
           *----------------------------------------------------------------*/
          spiceInWriter.println(powerBuffer);
          if (spiceInWriter.checkError()) {
            printf("Error adding power sources to file " + spiceInFile_p);
            spiceInWriter.close();
            return 1;
          }
          /*-----------------------------------------------------------------
           *   Next, copy the the input stimulus command buffer to the spice
           *   input file.
           *----------------------------------------------------------------*/
          spiceInWriter.println(" ");
          spiceInWriter.println(inputBuffer);
          if (spiceInWriter.checkError()) {
            printf("Error adding input stimulus to file " + spiceInFile_p);
            spiceInWriter.close();
            return 1;
          }
          /*-----------------------------------------------------------------
           *   Next, copy the the temperature command buffer and the options
           *   string to the spice input file.
           *----------------------------------------------------------------*/
          spiceInWriter.println(temperatureBuffer);
          spiceInWriter.println(s2iString.spiceOptions(spiceType));
          if (spiceInWriter.checkError()) {
            printf("Error adding Spice options to file " + spiceInFile_p);
            spiceInWriter.close();
            return 1;
          }
          /*-----------------------------------------------------------------
           *   Next, copy the the analysis command buffer and the VI print
           *   string to the spice input file.
           *----------------------------------------------------------------*/
          spiceInWriter.println(analysisBuffer);
          if (spiceInWriter.checkError()) {
            printf("Error adding Spice analysis command to file " +
                   spiceInFile_p);
            spiceInWriter.close();
            return 1;
          }
          /*-----------------------------------------------------------------
           *   Finally, write the Spice .END command to the file and close it.
           *   (As long as it's not a Spectre file....)
           *----------------------------------------------------------------*/
          if (spiceType != ConstantStuff.SPICE_TYPE_SPECTRE) {
            spiceInWriter.println(".END\n");
            if (spiceInWriter.checkError()) {
              printf("Error completing file " + spiceInFile_p);
              spiceInWriter.close();
              return 1;
            }
          }
          spiceInWriter.close();
        } // else for  (if(!(spiceInFile_p.canWrite())))
      } else
        spiceInWriter.close();
    } catch (Exception ex) {
      printf("Exception while setting file names (setupSpiceInputFile): " +
             ex.toString() + ": ");
      ex.printStackTrace();
    }

    return 0;
  } // method
};  // class setupSpiceInputFile

/******************************************************************************
CLASS: setPinTran
******************************************************************************/

class setPinTran {

public:
  string setPinTran(ibisPin pin, int pinType, int outputRising,
                    string nodeLabel, int analyze_case, int spiceType) {
    string pinBuffer = null;
    double Vil = 0, Vih = 0, risetime = 0, falltime = 0, pulsewidth = 0,
           period = 0;
    string sourceName;
    sourceName = "V" + nodeLabel + "S2I";
    if (analyze_case == ConstantStuff.TYP_CASE) {
      Vil = pin.model.vil.typ;
      Vih = pin.model.vih.typ;
      risetime = pin.model.tr.typ;
      falltime = pin.model.tf.typ;

    } else if (analyze_case == ConstantStuff.MIN_CASE) {
      if (goodies.IS_USE_NA(pin.model.vil.min))
        Vil = pin.model.vil.typ;
      else
        Vil = pin.model.vil.min;

      if (goodies.IS_USE_NA(pin.model.vih.min))
        Vih = pin.model.vih.typ;
      else
        Vih = pin.model.vih.min;

      if (goodies.IS_USE_NA(pin.model.tr.min))
        risetime = pin.model.tr.typ;
      else
        risetime = pin.model.tr.min;

      if (goodies.IS_USE_NA(pin.model.tf.min))
        falltime = pin.model.tf.typ;
      else
        falltime = pin.model.tf.min;
    }

    else {
      if (goodies.IS_USE_NA(pin.model.vil.max))
        Vil = pin.model.vil.typ;
      else
        Vil = pin.model.vil.max;

      if (goodies.IS_USE_NA(pin.model.vih.max))
        Vih = pin.model.vih.typ;
      else
        Vih = pin.model.vih.max;

      if (goodies.IS_USE_NA(pin.model.tr.max))
        risetime = pin.model.tr.typ;
      else
        risetime = pin.model.tr.max;

      if (goodies.IS_USE_NA(pin.model.tf.max))
        falltime = pin.model.tf.typ;
      else
        falltime = pin.model.tf.max;
    }

    pulsewidth = 2 * (pin.model.simTime);
    period = 2 * (risetime + falltime + pulsewidth);

    if ((pinType == ConstantStuff.MODEL_POLARITY_INVERTING) ||
        (pinType == ConstantStuff.MODEL_ENABLE_ACTIVE_LOW)) {
      if (outputRising == 1)
        pinBuffer = s2iString.tranSrcString(
            spiceType, sourceName, pin.spiceNodeName, "0", Vih, Vil, risetime,
            falltime, pulsewidth, period);
      else
        pinBuffer = s2iString.tranSrcString(
            spiceType, sourceName, pin.spiceNodeName, "0", Vil, Vih, risetime,
            falltime, pulsewidth, period);
    } else {
      if (outputRising == 1)
        pinBuffer = s2iString.tranSrcString(
            spiceType, sourceName, pin.spiceNodeName, "0", Vil, Vih, risetime,
            falltime, pulsewidth, period);
      else
        pinBuffer = s2iString.tranSrcString(
            spiceType, sourceName, pin.spiceNodeName, "0", Vih, Vil, risetime,
            falltime, pulsewidth, period);
    }
    return (pinBuffer);
  } // method setPinTran
};  // class setPinTran

/******************************************************************************
CLASS: setPinDC
******************************************************************************/

class setPinDC {
public:
  string setPinDC(ibisPin pin, int pinType, int outputActive, string nodeLabel,
                  int analyze_case, int spiceType) {
    string pinBuffer = null;
    double Vil = 0, Vih = 0;
    string sourceName;
    sourceName = "V" + nodeLabel + "S2I";
    if (analyze_case == ConstantStuff.TYP_CASE) {
      Vil = pin.model.vil.typ;
      Vih = pin.model.vih.typ;
    } else if (analyze_case == ConstantStuff.MIN_CASE) {
      if (goodies.IS_USE_NA(pin.model.vil.min))
        Vil = pin.model.vil.typ;
      else
        Vil = pin.model.vil.min;

      if (goodies.IS_USE_NA(pin.model.vih.min))
        Vih = pin.model.vih.typ;
      else
        Vih = pin.model.vih.min;
    } else {
      if (goodies.IS_USE_NA(pin.model.vil.max))
        Vil = pin.model.vil.typ;
      else
        Vil = pin.model.vil.max;

      if (goodies.IS_USE_NA(pin.model.vih.max))
        Vih = pin.model.vih.typ;
      else
        Vih = pin.model.vih.max;
    }

    if ((pinType == ConstantStuff.MODEL_POLARITY_INVERTING) ||
        (pinType == ConstantStuff.MODEL_ENABLE_ACTIVE_LOW)) {
      if (outputActive == 1) {
        if (nodeLabel.equalsIgnoreCase("gate")) {
          if (spiceType == ConstantStuff.SPICE_TYPE_SPECTRE)
            pinBuffer =
                sourceName + " " + "Vg" + " 0 vsource type=dc dc= " + Vil;
          else
            pinBuffer = sourceName + " " + "Vg" + " 0 DC " + Vil;
        } else {
          if (spiceType == ConstantStuff.SPICE_TYPE_SPECTRE)
            pinBuffer = sourceName + " " + pin.spiceNodeName +
                        " 0 vsource type=dc dc= " + Vil;
          else
            pinBuffer = sourceName + " " + pin.spiceNodeName + " 0 DC " + Vil;
        }
      } else {
        if (nodeLabel.equalsIgnoreCase("gate")) {
          if (spiceType == ConstantStuff.SPICE_TYPE_SPECTRE)
            pinBuffer =
                sourceName + " " + "Vg" + " 0 vsource type=dc dc= " + Vih;
          else
            pinBuffer = sourceName + " " + "Vg" + " 0 DC " + Vih;
        } else {
          if (spiceType == ConstantStuff.SPICE_TYPE_SPECTRE)
            pinBuffer = sourceName + " " + pin.spiceNodeName +
                        " 0 vsource type=dc dc= " + Vih;
          else
            pinBuffer = sourceName + " " + pin.spiceNodeName + " 0 DC " + Vih;
        }
      }
    } else {
      if (outputActive == 1) {
        if (nodeLabel.equalsIgnoreCase("gate")) {
          if (spiceType == ConstantStuff.SPICE_TYPE_SPECTRE)
            pinBuffer =
                sourceName + " " + "Vg" + " 0 vsource type=dc dc= " + Vih;
          else
            pinBuffer = sourceName + " " + "Vg" + " 0 DC " + Vih;
        } else {
          if (spiceType == ConstantStuff.SPICE_TYPE_SPECTRE)
            pinBuffer = sourceName + " " + pin.spiceNodeName +
                        " 0 vsource type=dc dc= " + Vih;
          else
            pinBuffer = sourceName + " " + pin.spiceNodeName + " 0 DC " + Vih;
        }
      } else {
        if (nodeLabel.equalsIgnoreCase("gate")) {
          if (spiceType == ConstantStuff.SPICE_TYPE_SPECTRE)
            pinBuffer =
                sourceName + " " + "Vg" + " 0 vsource type=dc dc= " + Vil;
          else
            pinBuffer = sourceName + " " + "Vg" + " 0 DC " + Vil;
        } else {
          if (spiceType == ConstantStuff.SPICE_TYPE_SPECTRE)
            pinBuffer = sourceName + " " + pin.spiceNodeName +
                        " 0 vsource type=dc dc= " + Vil;
          else
            pinBuffer = sourceName + " " + pin.spiceNodeName + " 0 DC " + Vil;
        }
      }
    }
    return (pinBuffer);

  } // method setPinDC
};  // class setPinDC

/******************************************************************************
CLASS: StreamGobbler
******************************************************************************/

// Class used by the 'callSpice class.
class StreamGobbler extends Thread {
  InputStream is;
  string type;

  StreamGobbler(InputStream is, string type) {
    this.is = is;
    this.type = type;
  }

public:
  void run() {
    try {
      InputStreamReader isr = new InputStreamReader(is);
      BufferedReader br = new BufferedReader(isr);
      string line = null;
      while ((line = br.readLine()) != null) {
        //		 printf(type + ">" + line);
      }
    } catch (IOException ioe) {
      ioe.printStackTrace();
    }
  }
}

/******************************************************************************
CLASS: callSpice
******************************************************************************/

class callSpice {
public:
  int callSpice(int iterate,
                string spiceCommand, // in from the user
                int spiceType, string spiceInFile, string spiceOutFile,
                string spiceMsgFile) {
    string shellFileName = s2iString.spiceNameString[spiceType] + ".sh";
    string batFileName = s2iString.spiceNameString[spiceType] + "_run.bat";
    string pathSep = System.getProperty("path.separator");

    File tempFile_p = new File(spiceOutFile);

    string commandBuffer;
    int status = 0;

    if (!spiceCommand.equals("")) {
      Object[] args = {spiceInFile, spiceOutFile, spiceMsgFile};
      MessageFormat mf = new MessageFormat(spiceCommand);
      commandBuffer = mf.format(args);
    } else
      commandBuffer = s2iString.defaultSpiceCommand(spiceType, spiceInFile,
                                                    spiceOutFile, spiceMsgFile);

    if ((iterate != 1) || !(tempFile_p.canRead())) {
      printf("Starting " + s2iString.spiceNameString[spiceType] +
             " job with input " + spiceInFile);
      try {
        if (pathSep.charAt(0) == ':') // figure out OS - solaris
        {
          File shell_p = new File(shellFileName);
          PrintWriter out_shell =
              new PrintWriter(new BufferedWriter(new FileWriter(shell_p)));

          out_shell.println(commandBuffer);
          out_shell.close();

          Runtime rt = Runtime.getRuntime();
          Process proc = rt.exec("sh " + shellFileName);

          // any error message?
          StreamGobbler errorGobbler =
              new StreamGobbler(proc.getErrorStream(), "ERROR");
          // any output?
          StreamGobbler opGobbler =
              new StreamGobbler(proc.getInputStream(), "OUTPUT");
          proc.waitFor();
          status = proc.exitValue();
        } else if (pathSep.charAt(0) == ';') // figure out OS - Windows
        {
          File bat_p = new File(batFileName);
          PrintWriter out_bat =
              new PrintWriter(new BufferedWriter(new FileWriter(bat_p)));

          commandBuffer = s2iString.spiceCommandForWin(
              spiceType, spiceInFile, spiceOutFile, spiceMsgFile);

          out_bat.println(commandBuffer);
          if (spiceType == ConstantStuff.SPICE_TYPE_HSPICE)
            out_bat.println("move " + spiceOutFile + ".lis " + spiceOutFile);

          out_bat.close();

          Runtime rt = Runtime.getRuntime();
          Process proc = rt.exec(batFileName);

          // any error message?
          StreamGobbler errorGobbler =
              new StreamGobbler(proc.getErrorStream(), "ERROR");
          // any output?
          StreamGobbler opGobbler =
              new StreamGobbler(proc.getInputStream(), "OUTPUT");

          errorGobbler.start();
          opGobbler.start();

          int exitVal = proc.waitFor();

          status = proc.exitValue();
        }

        if ((status != ConstantStuff.SPICE_GOOD_EXIT_CODE) ||
            (pathSep.charAt(0) == ';')) {
          return 1;
        } else
          return 0;

      } catch (Exception ex) {
        printf("Exception while running Spice: " + ex.toString());
      }
    } else {
      printf("[iterate] set and file " + spiceOutFile + " exists");
      printf("Skipping Run");
    }
    return 0;

  } // method callSpice
};  // class callSpice

/***************************************************************
CLASS: checkForConvergence
* checkForConvergence checks the outFile to see if the spice run has encountered
* a convergence problem.
* Returns a 1 if non convergnece detected - else returns 0
***************************************************************/
class checkForConvergence {
public:
  int checkForConvergence(int spiceType,       // IN
                          string spiceOutFile) // IN
  {
    File tempFile_p;
    string lineBuffer;
    int convergenceOccur;
    BufferedReader tempReader;

    /**Look for Convergence Strings in the Out File
     */
    tempFile_p = new File(spiceOutFile);
    // BufferedReader
    try {
      tempReader = new BufferedReader(new FileReader(tempFile_p));
      while ((lineBuffer = tempReader.readLine()) != null) {
        convergenceOccur =
            lineBuffer.indexOf(s2iString.convergenceMarker[spiceType]);
        if (convergenceOccur != -1) {
          printf("Found '" + s2iString.convergenceMarker[spiceType] + "' in " +
                 tempFile_p);
          tempReader.close();
          return 1;
        }
      }
    } catch (IOException e1) {
      printf("Error " + e1.toString()); //+" while closing "+ spiceOutFile);
      return 1;
    }

    return 0;
  }

}; // class checkForConvergence
/***************************************************************
CLASS: checkForAbort
* checkForAbort checks the outFile or the msgFile to see if
* the spice run has encountered  an abort problem.
* Returns a 1 if abort detected - else returns 0
***************************************************************/
class checkForAbort {
public:
  int checkForAbort(int spiceType,       // IN
                    string spiceOutFile, // IN
                    string spiceMsgFile) // IN
  {
    File tempFile_p;
    string lineBuffer;
    int abortOccur;
    BufferedReader tempReader;

    /**Look for Abort Strings in the Out File
     */
    tempFile_p = new File(spiceOutFile);
    // BufferedReader
    try {
      tempReader = new BufferedReader(new FileReader(tempFile_p));
      if (tempFile_p.canRead()) {

        while ((lineBuffer = tempReader.readLine()) != null) {
          abortOccur = lineBuffer.indexOf(s2iString.abortMarker[spiceType]);
          if (abortOccur != -1) {
            printf("Found " + s2iString.abortMarker[spiceType] + " in " +
                   tempFile_p);
            tempReader.close();
            return 1;
          }
        }
        try {
          tempReader.close();
        } catch (IOException e) {
          printf("Error " + e.toString() + " while closing " + spiceOutFile);
          return 1;
        }
      } else {
        printf("Unable to open " + tempFile_p + " for reading");
        return 1;
      }
    } catch (IOException e1) {
      printf("Error " + e1.toString());
      printf("Error in running " + s2iString.spiceNameString[spiceType]);
      System.exit(1);
    }

    /**Look for Abort Strings in the Msg File
     */
    tempFile_p = new File(spiceMsgFile);
    // BufferedReader
    if (!(spiceType == ConstantStuff.SPICE_TYPE_ELDO))
      try {
        tempReader = new BufferedReader(new FileReader(tempFile_p));
        if (tempFile_p.canRead()) {

          while ((lineBuffer = tempReader.readLine()) != null) {
            abortOccur = lineBuffer.indexOf(s2iString.abortMarker[spiceType]);
            if (abortOccur != -1) {
              tempReader.close();
              return 1;
            }
          }
          try {
            tempReader.close();
          } catch (IOException e) {
            printf("Error " + e.toString() + " while closing " + spiceMsgFile);
            return 1;
          }
        }
      } catch (IOException e1) {
        printf("Warning ... " +
               e1.toString()); //+" while closing "+ spiceOutFile);
      }
    return 0;
  } // method checkForAbort
};  // class checkForAbort

/******************************************************************
CLASS: runSpiceAgain
* runSpiceAgain is called from the generate*Curve methods - once
* an abort is detected and consecutively a Non-Convergence was detected.
* It runs DCSweepCommands again - with new sweepStart and sweepEnd - as
* input by the user. Then it calls spice and runs the simulations again.
* Returns a 1 if abort and non-convergence detected during spice run -
* else returns 0.
***************************************************************/
class runSpiceAgain {
  double sweepStart, sweepEnd;

public:
  int runSpiceAgain(int curveType, int spiceType, double sweepStep,
                    string spiceInFile, string spiceOutFile,
                    string spiceMsgFile, int iterate, string headerLine,
                    string spiceCommand, string spiceFile, string modelFileTyp,
                    string extSpiceCmdFile, string loadBuffer,
                    string inputBuffer, string powerBuffer,
                    string temperatureBuffer) {
    double newSweepStart = 0, newSweepEnd = sweepEnd;
    string yes_no = "y";
    string user_in_string = "";
    string analysisBuffer = null;
    BigDecimal bdSS, bdSE;
    /**--------------------------------------------------------------------
     *   Get the sweepStart and sweepEnd from stdin - if the user choose to.
     *--------------------------------------------------------------------*/
    bdSS = new BigDecimal(sweepStart);
    printf("Current sweepStart = " +
           bdSS.setScale(2, BigDecimal.ROUND_HALF_UP));
    bdSE = new BigDecimal(sweepEnd);
    printf("Current sweepEnd = " + bdSE.setScale(2, BigDecimal.ROUND_HALF_UP));
    printf("Would you like to specifiy a different sweep range? [y/n] ");
    BufferedReader user_in =
        new BufferedReader(new InputStreamReader(System.in));
    setupDCSweepCommands setupDCSweepCmd = new setupDCSweepCommands();
    setupSpiceInputFile setSpInFile = new setupSpiceInputFile();
    callSpice callSpice1 = new callSpice();
    checkForAbort checkAbort = new checkForAbort();
    checkForConvergence chkConvergence = new checkForConvergence();

    yes_no = user_in.readLine();
    if ((yes_no.equalsIgnoreCase("y")) || (yes_no.equalsIgnoreCase("yes")) ||
        (yes_no.equalsIgnoreCase(""))) {
      System.out.print("New sweepStart (default:0) :");
      user_in_string = user_in.readLine();
      if (!(user_in_string.equalsIgnoreCase(""))) {
        try {
          newSweepStart = Double.parseDouble(user_in_string);
        } catch (Exception ex1) {
          printf("Faulty input - assuming default value");
          newSweepStart = 0;
        }
      } else
        newSweepStart = 0;

      System.out.print("New sweepEnd (default:" +
                       bdSE.setScale(2, BigDecimal.ROUND_HALF_UP) + ") :");
      user_in_string = user_in.readLine();
      if (!(user_in_string.equalsIgnoreCase(""))) {
        try {
          newSweepEnd = Double.parseDouble(user_in_string);
        } catch (Exception ex1) {
          printf("Faulty input - assuming default value");
          newSweepEnd = sweepEnd;
        }
      } else
        newSweepEnd = sweepEnd;

      bdSS = new BigDecimal(newSweepStart);
      bdSE = new BigDecimal(newSweepEnd);

      printf("New sweepStart = " + bdSS.setScale(2, BigDecimal.ROUND_HALF_UP));
      printf("New sweepEnd = " + bdSE.setScale(2, BigDecimal.ROUND_HALF_UP));
      sweepStart = newSweepStart;
      sweepEnd = newSweepEnd;
      analysisBuffer = setupDCSweepCmd.setupDCSweepCommands(
          curveType, spiceType, newSweepStart, newSweepEnd, sweepStep);

      if (setSpInFile.setupSpiceInputFile(
              iterate, spiceType, spiceInFile, headerLine, spiceFile,
              modelFileTyp, extSpiceCmdFile, loadBuffer, inputBuffer,
              powerBuffer, temperatureBuffer, analysisBuffer) == 1) {
        printf("Couldn't set up Spice File for " +
               s2iString.curveNameString[curveType] + " curve");
        return 1;
      }

      // callSpice returns 1(error)
      if (callSpice1.callSpice(iterate, spiceCommand, spiceType, spiceInFile,
                               spiceOutFile, spiceMsgFile) == 1) {
        // checkForAbort
        int returnFromAbort =
            checkAbort.checkForAbort(spiceType, spiceOutFile, spiceMsgFile);
        if (returnFromAbort == 1) {
          printf("See file " + spiceMsgFile + " for information.");
          printf("Curve " + s2iString.curveNameString[curveType] +
                 " not generated.");
          if (chkConvergence.checkForConvergence(spiceType, spiceOutFile) ==
              1) {
            printf("Spice run aborted CONVERENCE ISSUE detected.  ");
            return 1;
          }
        }
      }
    } else {
      printf("You entered '" + yes_no + "'");
      printf("Error in executing " + s2iString.spiceNameString[spiceType]);
      printf("Fatal Error. Exiting. ");
      System.exit(1);
      return 1;
    }
    return 0;
  } // method runSpiceAgain
};  // class runSpiceAgain

/******************************************************************************
CLASS: getSpiceVIData
******************************************************************************/

class getSpiceVIData {
public:
  int getSpiceVIData(VIDataContainer VIC, // IN
                     int tableSize,       // IN
                     int spiceType,       // IN
                     string spiceOutFile, // IN
                     string command) {    // IN
    File outFile_p = new File(spiceOutFile);
    string lineBuffer;
    double[][] tempData = new double[300][2];
    int rowIndex = 0, i = 0, j, numRead = 0;
    bool flag = false;
    bool flag_eldo = true; // changed for beta0.4
    double temp_double = 0;
    if (!(outFile_p.canRead())) {
      printf("Unable to open " + spiceOutFile + " for reading");
      return 1;
    }

    try {
      BufferedReader SpiceReader =
          new BufferedReader(new FileReader(outFile_p));

      /*------------------------------------------------------------------------
       *   Read lines until we hit the data begin marker or EOF.  If it's EOF,
       *   return an error.
       *-----------------------------------------------------------------------*/
      while (((lineBuffer = SpiceReader.readLine()) != null) &&
             (lineBuffer.indexOf(s2iString.VIDataBeginMarker[spiceType]) < 0))
        ;
      if (lineBuffer.indexOf(s2iString.VIDataBeginMarker[spiceType]) < 0) {
        printf("Data begin marker '" + s2iString.VIDataBeginMarker[spiceType] +
               "'");
        printf("not found in output file " + spiceOutFile);
        SpiceReader.close();
        return 1;
      }
      /*Special processing for ELDO*/
      if (spiceType == ConstantStuff.SPICE_TYPE_ELDO) {
        while (
            ((lineBuffer = SpiceReader.readLine()) != null) &&
            (!(lineBuffer.startsWith(s2iString.VIDataBeginMarker[spiceType]))))
          ;

        if (!(lineBuffer.startsWith(s2iString.VIDataBeginMarker[spiceType]))) {
          printf("Data begin marker '" +
                 s2iString.VIDataBeginMarker[spiceType] + "'");
          printf("not found in output file " + spiceOutFile);
          SpiceReader.close();
          return 1;
        }
      }
      /*------------------------------------------------------------------------
       *   We're now at the line before the start of the VI data.
       *   Read lines until we get to the actual VI table.
       *   No VIEndDataMarker is needed now as now we analyze the first
       *   token of the linebuffer and analyze it. Analysis is done by
       *   converting the tokens(Which are strings) to double.
       *   If the tokens are real strings, there will be an exception thrown.
       *   If there is an exception, We skip that line and move to the next line
       *-----------------------------------------------------------------------*/
      while (((lineBuffer = SpiceReader.readLine()) != null) && flag_eldo)
        if (lineBuffer != null) {
          StringTokenizer st2 = new StringTokenizer(lineBuffer);
          int cnt = st2.countTokens();
          if (cnt != 0) {
            string temp = st2.nextToken();
            try {
              temp_double = Double.parseDouble(temp);
              flag = true;
            } catch (Exception ex1) {
              if (ex1.toString().length() == 0) {
              } else {
                flag = false;
                if (spiceType == ConstantStuff.SPICE_TYPE_ELDO)
                  flag_eldo = false;
              }
            }
          }
          if ((cnt == 2) && flag) {
            /*use temp_double here as the first column is the voltage
            column and it has already been converted to double
            */
            tempData[rowIndex][0] = temp_double;
            tempData[rowIndex][1] = -Double.parseDouble(st2.nextToken());
            rowIndex++;
          }
          if (((cnt == 3) || (cnt == 4)) && flag) {
            //		As we dont want the first column from the 4 columns..
            //		..we skip the temp_double and go to the nextToken.
            //		convert string to double using Double.parseDouble
            tempData[rowIndex][0] = Double.parseDouble(st2.nextToken());
            st2.nextToken(); // to get the -ve I value.
            tempData[rowIndex][1] = -Double.parseDouble(st2.nextToken());
            rowIndex++;
          }
        }
      SpiceReader.close(); // 0.4Beta
    } catch (Exception ex) {
      printf("Exception while collecting spice data from out files "
             "(getSpiceVIData): " +
             ex.toString());
    }

    int newSize;
    if (command.equalsIgnoreCase("typ")) {
      VIC.VIData2.size = rowIndex;        // +1;		//0909
      for (j = 0; j <= rowIndex - 1; j++) // 0909 added the -1.
      {
        VIC.VIData2.VIs[j].v = tempData[j][0];
        VIC.VIData2.VIs[j].i.typ = tempData[j][1];
        VIC.VIData2.VIs[j].i.min = 0;
        VIC.VIData2.VIs[j].i.max = 0;
      }
    } else if (command.equalsIgnoreCase("min"))
      for (j = 0; j < rowIndex; j++)
        VIC.VIData2.VIs[j].i.min = tempData[j][1];
    else
      for (j = 0; j < rowIndex; j++)
        VIC.VIData2.VIs[j].i.max = tempData[j][1];

    return 0;
  }
}; // class  getSpiceVIData

/******************************************************************************
CLASS: create_VItable
******************************************************************************/

class create_VItable {
  LinkedHashMap LHM;
}; // class create_VItable

/******************************************************************************
CLASS: generateVICurve
******************************************************************************/

class generateVICurve {
  ibisVItable VIData; // out

public:
  int generateVICurve(ibisPin currentPin, // rest are all in
                      ibisPin enablePin, ibisPin inputPin, ibisPin powerPin,
                      ibisPin gndPin, ibisPin powerClampPin,
                      ibisPin gndClampPin, ibisTypMinMax Vcc, ibisTypMinMax Gnd,
                      ibisTypMinMax VccClamp, ibisTypMinMax GndClamp,
                      ibisTypMinMax sweepStart, double sweepRange,
                      double sweepStep, int curveType, int spiceType,
                      string spiceFile, string spiceCommand, int enableOutput,
                      int outputHigh, int iterate, int cleanup,
                      // series
                      double Vds, int index
                      // series
  ) {
    ibisModel model;
    double sweepEnd = 0;
    int numTablePoints = 0;
    string loadBuffer = null, headerLine = null, inputBuffer = null,
           powerBuffer = null, dummyBuffer = null, temperatureBuffer = null,
           analysisBuffer = null;

    string spiceInFile = null, spiceOutFile = null, spiceMsgFile = null,
           namePrefixBuffer = null;
    model = currentPin.model;
    numTablePoints = goodies.ROUND(sweepRange / sweepStep) + 2;
    printf("CurrentPin is .. " + currentPin.pinName);

    VIDataContainer VICont = new VIDataContainer();
    VICont.VIData2.VIs = new ibisVItableEntry[numTablePoints];

    for (int m = 0; m < numTablePoints; m++) {
      VICont.VIData2.VIs[m] = new ibisVItableEntry();
      VICont.VIData2.VIs[m].v = ConstantStuff.USE_NA;
      VICont.VIData2.VIs[m].i.typ = ConstantStuff.USE_NA;
      VICont.VIData2.VIs[m].i.min = ConstantStuff.USE_NA;
      VICont.VIData2.VIs[m].i.max = ConstantStuff.USE_NA;
    }

    create_VItable VITable = new create_VItable();

    // series
    if (curveType == ConstantStuff.CURVE_TYPE_SERIES_VI)
      loadBuffer = s2iString.DCSrcString(spiceType, "VOUTS2I",
                                         currentPin.seriesPin2name, "0", 0);
    else
      loadBuffer = s2iString.DCSrcString(spiceType, "VOUTS2I",
                                         currentPin.spiceNodeName, "0", 0);

    /*----------------------------------------------------
     *    Set up for the typ run, and do the run
     *----------------------------------------------------*/
    printf("Do the TYP run in GenerateVITable ");
    sweepEnd = sweepStart.typ + sweepRange;
    headerLine = "*Typ " + s2iString.curveNameString[curveType] +
                 " curve for model " + model.modelName + "\n";

    setPinDC setPinDC1 = new setPinDC();

    if (curveType == ConstantStuff.CURVE_TYPE_SERIES_VI) {
      inputBuffer =
          setPinDC1.setPinDC(inputPin, model.polarity, outputHigh, "gate",
                             ConstantStuff.TYP_CASE, spiceType);
      if (spiceType == ConstantStuff.SPICE_TYPE_SPECTRE)
        inputBuffer = inputBuffer + "\nVDS " + currentPin.pinName + " " +
                      currentPin.seriesPin2name +
                      " vsource type=dc dc= " + Vds + "\n";
      else
        inputBuffer = inputBuffer + "\nVDS " + currentPin.pinName + " " +
                      currentPin.seriesPin2name + " DC " + Vds + "\n";
    } else {
      if (enablePin != null)
        inputBuffer =
            setPinDC1.setPinDC(enablePin, model.enable, enableOutput, "ENA",
                               ConstantStuff.TYP_CASE, spiceType);
      else
        inputBuffer = "";

      if (inputPin != null) {
        dummyBuffer =
            setPinDC1.setPinDC(inputPin, model.polarity, outputHigh, "IN",
                               ConstantStuff.TYP_CASE, spiceType);
        inputBuffer = inputBuffer + "\n" + dummyBuffer;
      }
    }

    setupPwrAndTempCmds setupPwrTmpCmd = new setupPwrAndTempCmds();
    setupPwrTmpCmd.setupPwrAndTempCmds(
        curveType, spiceType, powerPin, gndPin, powerClampPin, gndClampPin,
        Vcc.typ, Gnd.typ, VccClamp.typ, GndClamp.typ, model.tempRange.typ);
    powerBuffer = setupPwrTmpCmd.powerBuffer;
    temperatureBuffer = setupPwrTmpCmd.temperatureBuffer;

    setupDCSweepCommands setupDCSweepCmd = new setupDCSweepCommands();
    analysisBuffer = setupDCSweepCmd.setupDCSweepCommands(
        curveType, spiceType, sweepStart.typ, sweepEnd, sweepStep);

    setupSpiceFileNames setSpFlNames1 = new setupSpiceFileNames();

    // series
    if (curveType == ConstantStuff.CURVE_TYPE_SERIES_VI) {
      if (index < 10)
        namePrefixBuffer =
            s2iString.spiceFileTypPrefix[curveType] + "0" + index;
      else
        namePrefixBuffer = s2iString.spiceFileTypPrefix[curveType] + index;

      setSpFlNames1.setupSpiceFileNames(namePrefixBuffer, currentPin.pinName);
    } else
      setSpFlNames1.setupSpiceFileNames(s2iString.spiceFileTypPrefix[curveType],
                                        currentPin.pinName);
    spiceInFile = setSpFlNames1.spiceInFile;
    spiceOutFile = setSpFlNames1.spiceOutFile;
    spiceMsgFile = setSpFlNames1.spiceMsgFile;

    setupSpiceInputFile setSpInFile = new setupSpiceInputFile();
    if (setSpInFile.setupSpiceInputFile(
            iterate, spiceType, spiceInFile, headerLine, spiceFile,
            model.modelFileTyp, model.extSpiceCmdFile, loadBuffer, inputBuffer,
            powerBuffer, temperatureBuffer, analysisBuffer) == 1) {
      printf("Couldn't set up Spice File for " +
             s2iString.curveNameString[curveType] + " curve");
      return 1;
    }

    callSpice callSpice1 = new callSpice();
    getSpiceVIData VIData1 = new getSpiceVIData();
    checkForAbort checkAbort = new checkForAbort();
    runSpiceAgain runSpiceAgain = new runSpiceAgain();
    checkForConvergence chkConvergence = new checkForConvergence();
    // callSpice returns 1(error)
    if (callSpice1.callSpice(iterate, spiceCommand, spiceType, spiceInFile,
                             spiceOutFile, spiceMsgFile) == 1) {
      // checkForAbort
      int returnFromAbort =
          checkAbort.checkForAbort(spiceType, spiceOutFile, spiceMsgFile);

      if (returnFromAbort == 1) {
        printf("Spice run (TYP) aborted.  ");
        printf("See file " + spiceMsgFile + " for information.");
        printf("Curve " + s2iString.curveNameString[curveType] +
               " not generated.");
        if (chkConvergence.checkForConvergence(spiceType, spiceOutFile) == 1) {
          printf("Spice run aborted NON CONVERENCE detected.  ");
          runSpiceAgain.sweepStart = sweepStart.typ;
          runSpiceAgain.sweepEnd = sweepEnd;
          while (runSpiceAgain.runSpiceAgain(
                     curveType, spiceType, sweepStep, spiceInFile, spiceOutFile,
                     spiceMsgFile, iterate, headerLine, spiceCommand, spiceFile,
                     model.modelFileTyp, model.extSpiceCmdFile, loadBuffer,
                     inputBuffer, powerBuffer, temperatureBuffer) != 0)
            printf("Rerun simulations.. ");
        } else {
          printf("--- ");
          return 1;
        }
      }
    }
    // else
    if (VIData1.getSpiceVIData(VICont, numTablePoints, spiceType, spiceOutFile,
                               "typ") == 1) {
      printf("Curve " + s2iString.curveNameString[curveType] +
             " not generated.\n");
      return 1;
    }
    if (cleanup == 1) {
      File inFile = new File(spiceInFile);
      File outFile = new File(spiceOutFile);
      File msgFile = new File(spiceMsgFile);
      if (!inFile.delete())
        printf("Can't remove file " + spiceInFile);
      if (!outFile.delete())
        printf("Can't remove file " + spiceOutFile);

      if (!((spiceType == ConstantStuff.SPICE_TYPE_ELDO) ||
            (spiceType == ConstantStuff.SPICE_TYPE_HSPICE)))
        if (!msgFile.delete())
          printf("Can't remove file " + spiceMsgFile);

      if (spiceType == ConstantStuff.SPICE_TYPE_HSPICE) {
        spiceOutFile = s2iString.spiceFileTypPrefix[curveType] +
                       currentPin.pinName + ".st0";
        File outFile2 = new File(spiceOutFile);
        if (!outFile2.delete())
          printf("Can't remove .st0 file " + spiceOutFile);
      }
    }
    /*----------------------------------------------------
     *    Set up for the min run, and do the run
     *----------------------------------------------------*/
    printf("Do the min run in GenerateVITable ");
    sweepEnd = sweepStart.min + sweepRange;
    headerLine = "*Min " + s2iString.curveNameString[curveType] +
                 " curve for model " + model.modelName + "\n";

    if (curveType == ConstantStuff.CURVE_TYPE_SERIES_VI) {
      inputBuffer =
          setPinDC1.setPinDC(inputPin, model.polarity, outputHigh, "gate",
                             ConstantStuff.MIN_CASE, spiceType);
      if (spiceType == ConstantStuff.SPICE_TYPE_SPECTRE)
        inputBuffer = inputBuffer + "\nVDS " + currentPin.pinName + " " +
                      currentPin.seriesPin2name +
                      " vsource type=dc dc= " + Vds + "\n";
      else
        inputBuffer = inputBuffer + "\nVDS " + currentPin.pinName + " " +
                      currentPin.seriesPin2name + " DC " + Vds + "\n";
    } else {
      if (enablePin != null)
        inputBuffer =
            setPinDC1.setPinDC(enablePin, model.enable, enableOutput, "ENA",
                               ConstantStuff.MIN_CASE, spiceType);
      else
        inputBuffer = "";

      if (inputPin != null) {
        dummyBuffer =
            setPinDC1.setPinDC(inputPin, model.polarity, outputHigh, "IN",
                               ConstantStuff.MIN_CASE, spiceType);
        inputBuffer = inputBuffer + "\n" + dummyBuffer;
      }
    }

    setupPwrTmpCmd.setupPwrAndTempCmds(
        curveType, spiceType, powerPin, gndPin, powerClampPin, gndClampPin,
        Vcc.min, Gnd.min, VccClamp.min, GndClamp.min, model.tempRange.min);
    powerBuffer = setupPwrTmpCmd.powerBuffer;
    temperatureBuffer = setupPwrTmpCmd.temperatureBuffer;

    analysisBuffer = setupDCSweepCmd.setupDCSweepCommands(
        curveType, spiceType, sweepStart.min, sweepEnd, sweepStep);
    if (curveType == ConstantStuff.CURVE_TYPE_SERIES_VI) {
      if (index < 10)
        namePrefixBuffer =
            s2iString.spiceFileMinPrefix[curveType] + "0" + index;
      else
        namePrefixBuffer = s2iString.spiceFileMinPrefix[curveType] + index;

      setSpFlNames1.setupSpiceFileNames(namePrefixBuffer, currentPin.pinName);
    } else
      setSpFlNames1.setupSpiceFileNames(s2iString.spiceFileMinPrefix[curveType],
                                        currentPin.pinName);
    spiceInFile = setSpFlNames1.spiceInFile;
    spiceOutFile = setSpFlNames1.spiceOutFile;
    spiceMsgFile = setSpFlNames1.spiceMsgFile;

    if (setSpInFile.setupSpiceInputFile(
            iterate, spiceType, spiceInFile, headerLine, spiceFile,
            model.modelFileMin, model.extSpiceCmdFile, loadBuffer, inputBuffer,
            powerBuffer, temperatureBuffer, analysisBuffer) == 1) {
      printf("Couldn't set up Spice File for " +
             s2iString.curveNameString[curveType]);
      return 1;
    }

    if (callSpice1.callSpice(iterate, spiceCommand, spiceType, spiceInFile,
                             spiceOutFile, spiceMsgFile) == 1) {
      // checkForAbort
      int returnFromAbort =
          checkAbort.checkForAbort(spiceType, spiceOutFile, spiceMsgFile);
      if (returnFromAbort == 1) {
        printf("Spice run (MIN) aborted.  ");
        printf("See file " + spiceMsgFile + " for information.");
        printf("Curve " + s2iString.curveNameString[curveType] +
               " not generated.");
        if (chkConvergence.checkForConvergence(spiceType, spiceOutFile) == 1) {
          printf("Spice run aborted NON CONVERENCE detected.  ");
          runSpiceAgain.sweepStart = sweepStart.min;
          runSpiceAgain.sweepEnd = sweepEnd;
          while (runSpiceAgain.runSpiceAgain(
                     curveType, spiceType, sweepStep, spiceInFile, spiceOutFile,
                     spiceMsgFile, iterate, headerLine, spiceCommand, spiceFile,
                     model.modelFileTyp, model.extSpiceCmdFile, loadBuffer,
                     inputBuffer, powerBuffer, temperatureBuffer) != 0)
            printf("Rerun simulations.. ");
        }
      }
    }
    if (VIData1.getSpiceVIData(VICont, numTablePoints, spiceType, spiceOutFile,
                               "min") == 1) {
      printf("Curve " + s2iString.curveNameString[curveType] +
             " not generated.\n");
      return 1;
    }
    if (cleanup == 1) {
      File inFile = new File(spiceInFile);
      File outFile = new File(spiceOutFile);
      File msgFile = new File(spiceMsgFile);
      if (!inFile.delete())
        printf("Can't remove file " + spiceInFile);
      if (!outFile.delete())
        printf("Can't remove file " + spiceOutFile);
      if (!((spiceType == ConstantStuff.SPICE_TYPE_ELDO) ||
            (spiceType == ConstantStuff.SPICE_TYPE_HSPICE)))
        if (!msgFile.delete())
          printf("Can't remove file " + spiceMsgFile);

      if (spiceType == ConstantStuff.SPICE_TYPE_HSPICE) {
        spiceOutFile = s2iString.spiceFileMinPrefix[curveType] +
                       currentPin.pinName + ".st0";
        File outFile2 = new File(spiceOutFile);
        outFile2.delete();
      }
    }
    /*----------------------------------------------------
     *    Set up for the max run, and do the run
     *----------------------------------------------------*/
    printf("Do the max run in GenerateVITable ");
    sweepEnd = sweepStart.max + sweepRange;
    headerLine = "*Max " + s2iString.curveNameString[curveType] +
                 " curve for model " + model.modelName + "\n";
    if (curveType == ConstantStuff.CURVE_TYPE_SERIES_VI) {
      inputBuffer =
          setPinDC1.setPinDC(inputPin, model.polarity, outputHigh, "gate",
                             ConstantStuff.MAX_CASE, spiceType);
      if (spiceType == ConstantStuff.SPICE_TYPE_SPECTRE)
        inputBuffer = inputBuffer + "\nVDS " + currentPin.pinName + " " +
                      currentPin.seriesPin2name +
                      " vsource type=dc dc= " + Vds + "\n";
      else
        inputBuffer = inputBuffer + "\nVDS " + currentPin.pinName + " " +
                      currentPin.seriesPin2name + " DC " + Vds + "\n";
    } else {
      if (enablePin != null)
        inputBuffer =
            setPinDC1.setPinDC(enablePin, model.enable, enableOutput, "ENA",
                               ConstantStuff.MAX_CASE, spiceType);
      else
        inputBuffer = "";

      if (inputPin != null) {
        dummyBuffer =
            setPinDC1.setPinDC(inputPin, model.polarity, outputHigh, "IN",
                               ConstantStuff.MAX_CASE, spiceType);
        inputBuffer = inputBuffer + "\n" + dummyBuffer;
      }
    }

    setupPwrTmpCmd.setupPwrAndTempCmds(
        curveType, spiceType, powerPin, gndPin, powerClampPin, gndClampPin,
        Vcc.max, Gnd.max, VccClamp.max, GndClamp.max, model.tempRange.max);
    powerBuffer = setupPwrTmpCmd.powerBuffer;
    temperatureBuffer = setupPwrTmpCmd.temperatureBuffer;

    analysisBuffer = setupDCSweepCmd.setupDCSweepCommands(
        curveType, spiceType, sweepStart.max, sweepEnd, sweepStep);

    if (curveType == ConstantStuff.CURVE_TYPE_SERIES_VI) {
      if (index < 10)
        namePrefixBuffer =
            s2iString.spiceFileMaxPrefix[curveType] + "0" + index;
      else
        namePrefixBuffer = s2iString.spiceFileMaxPrefix[curveType] + index;

      setSpFlNames1.setupSpiceFileNames(namePrefixBuffer, currentPin.pinName);
    } else
      setSpFlNames1.setupSpiceFileNames(s2iString.spiceFileMaxPrefix[curveType],
                                        currentPin.pinName);
    spiceInFile = setSpFlNames1.spiceInFile;
    spiceOutFile = setSpFlNames1.spiceOutFile;
    spiceMsgFile = setSpFlNames1.spiceMsgFile;

    if (setSpInFile.setupSpiceInputFile(
            iterate, spiceType, spiceInFile, headerLine, spiceFile,
            model.modelFileMax, model.extSpiceCmdFile, loadBuffer, inputBuffer,
            powerBuffer, temperatureBuffer, analysisBuffer) == 1) {
      printf("Couldn't set up Spice File for " +
             s2iString.curveNameString[curveType]);
      return 1;
    }

    if (callSpice1.callSpice(iterate, spiceCommand, spiceType, spiceInFile,
                             spiceOutFile, spiceMsgFile) == 1) {
      // checkForAbort
      int returnFromAbort =
          checkAbort.checkForAbort(spiceType, spiceOutFile, spiceMsgFile);
      if (returnFromAbort == 1) {
        printf("Spice run (MAX) aborted.  ");
        printf("See file " + spiceMsgFile + " for information.");
        printf("Curve " + s2iString.curveNameString[curveType] +
               " not generated.");
        if (chkConvergence.checkForConvergence(spiceType, spiceOutFile) == 1) {
          printf("Spice run aborted NON CONVERENCE detected.  ");

          runSpiceAgain.sweepStart = sweepStart.max;
          runSpiceAgain.sweepEnd = sweepEnd;
          while (runSpiceAgain.runSpiceAgain(
                     curveType, spiceType, sweepStep, spiceInFile, spiceOutFile,
                     spiceMsgFile, iterate, headerLine, spiceCommand, spiceFile,
                     model.modelFileTyp, model.extSpiceCmdFile, loadBuffer,
                     inputBuffer, powerBuffer, temperatureBuffer) != 0)
            printf("Rerun simulations.. ");
        }
      }
    }
    if (VIData1.getSpiceVIData(VICont, numTablePoints, spiceType, spiceOutFile,
                               "max") == 1) {
      printf("Curve " + s2iString.curveNameString[curveType] +
             " not generated.\n");
      return 1;
    }
    if (cleanup == 1) {
      File inFile = new File(spiceInFile);
      File outFile = new File(spiceOutFile);
      File msgFile = new File(spiceMsgFile);
      if (!inFile.delete())
        printf("Can't remove file " + spiceInFile);
      if (!outFile.delete())
        printf("Can't remove file " + spiceOutFile);

      if (!((spiceType == ConstantStuff.SPICE_TYPE_ELDO) ||
            (spiceType == ConstantStuff.SPICE_TYPE_HSPICE)))
        if (!msgFile.delete())
          printf("Can't remove file " + spiceMsgFile);

      if (spiceType == ConstantStuff.SPICE_TYPE_HSPICE) {
        spiceOutFile = s2iString.spiceFileMaxPrefix[curveType] +
                       currentPin.pinName + ".st0";
        File outFile2 = new File(spiceOutFile);
        outFile2.delete();
      }
    }

    // Convert LinkedHashMap to a 2D Array.
    VIData = VICont.VIData2;
    return (0);
  } // end method generateVICurve
} // end class generateVICurve

/******************************************************************************
CLASS: spiceVT
******************************************************************************/

class spiceVT {
  double v = 0;
  double t = 0;
}

/******************************************************************************
CLASS: getSpiceRampData
******************************************************************************/

class getSpiceRampData {
public:
  int getSpiceRampData(ibisModel model, int curveType, int spiceType,
                       string spiceOutFile, string command) {
    File outFile_p = new File(spiceOutFile);
    string lineBuffer;
    double t0 = 0, t1 = 0, t20 = 0, t80 = 0, v0 = 0, v1 = 0, v20 = 0, v80 = 0;
    int row = 0;
    int key1 = 0;
    bool flag = false;
    bool flag_eldo = true; // changed for beta 0.4
    double temp_double = 0;
    spiceVT V = new spiceVT();
    LinkedHashMap rampData = new LinkedHashMap();
    /************code**********************************/

    if (!(outFile_p.canRead())) {
      printf("Unable to open " + spiceOutFile + " for reading");
      return 1;
    }

    try {
      BufferedReader SpiceReader =
          new BufferedReader(new FileReader(outFile_p));
      /*------------------------------------------------------------------------
       *	Read lines until we hit the data begin marker or EOF.  If it's
       *EOF, return an error.
       *-----------------------------------------------------------------------*/
      while (((lineBuffer = SpiceReader.readLine()) != null) &&
             (lineBuffer.indexOf(s2iString.tranDataBeginMarker[spiceType]) < 0))
        ;
      if (lineBuffer.indexOf(s2iString.tranDataBeginMarker[spiceType]) < 0) {
        printf("Data begin marker '" +
               s2iString.tranDataBeginMarker[spiceType] + "'");
        printf("not found in output file " + spiceOutFile);
        SpiceReader.close();
        return 1;
      }
      /*Special processing for ELDO*/
      if (spiceType == ConstantStuff.SPICE_TYPE_ELDO) {
        while (
            ((lineBuffer = SpiceReader.readLine()) != null) &&
            (!(lineBuffer.startsWith(s2iString.VIDataBeginMarker[spiceType]))))
          ;

        if (!(lineBuffer.startsWith(s2iString.VIDataBeginMarker[spiceType]))) {
          printf("Data begin marker '" +
                 s2iString.VIDataBeginMarker[spiceType] + "'");
          printf("not found in output file " + spiceOutFile);
          SpiceReader.close();
          return 1;
        }
      }

      /*------------------------------------------------------------------------
       *   We're now at the line before the start of the VI data.
       *   Read lines until we get to the actual VI table.
       *   No tranEndDataMarker is needed now as now we analyze the first
       *   token of the linebuffer and analyze it. Analysis is done by
       *   converting the tokens(Which are strings) to double.
       *   If the tokens are real strings, there will be an exception thrown.
       *   If there is an exception, We skip that line and move to the next line
       *-----------------------------------------------------------------------*/
      while (((lineBuffer = SpiceReader.readLine()) != null) && flag_eldo)
        if (lineBuffer != null) {
          StringTokenizer st3 = new StringTokenizer(lineBuffer);
          int cnt = st3.countTokens();
          if (cnt != 0) {
            string temp = st3.nextToken();
            try {
              temp_double = Double.parseDouble(temp);
              flag = true;
              row++;
            } catch (Exception ex1) {
              if (ex1.toString().length() == 0) {
              } else
                flag = false;
              if (spiceType == ConstantStuff.SPICE_TYPE_ELDO)
                flag_eldo = false;
            }
          }
          if ((cnt == 2) && flag) {
            /*use temp_double here as the first column is the voltage
            column and it has already been converted to double
            */
            V.t = temp_double;
            V.v = Double.parseDouble(st3.nextToken());
            rampData.put(new Integer(row), V);
            V = new spiceVT();
          }
          if ((cnt == 3) && flag) {
            //   	       As we dont want the first column from the 3
            //   columns..
            //   	       ..we skip the temp_double and go to the
            //   nextToken.
            // convert string to double using Double.parseDouble
            V.t = Double.parseDouble(st3.nextToken());
            V.v = Double.parseDouble(st3.nextToken());
            rampData.put(new Integer(row), V);
            V = new spiceVT();
          }
        } // while
      spiceVT V1;
      spiceVT[] rampArray = new spiceVT[rampData.size()];
      for (Iterator key = rampData.keySet().iterator(),
                    value = rampData.values().iterator();
           key.hasNext();) {
        key.next();
        V1 = (spiceVT)value.next();
        rampArray[key1] = V1;
        V1 = new spiceVT();
        key1++;
      }
      v0 = rampArray[0].v;
      t0 = rampArray[0].t;
      v1 = rampArray[rampData.size() - 1].v;
      t1 = rampArray[rampData.size() - 1].t;

      v20 = v0 + 0.2 * (v1 - v0);
      v80 = v0 + 0.8 * (v1 - v0);
      double v_int = 0, t_int = 0;
      bool t20_done = false;
      bool t80_done = false;
      if (v1 < v0)
        for (int k = 0; k < key1; k++) {
          if (!t20_done)
            if (rampArray[k].v > v20) {
              v_int = rampArray[k].v;
              t_int = rampArray[k].t;
            } else {
              t20 = t_int + ((v20 - v_int) * (rampArray[k].t - t_int) /
                             (rampArray[k].v - v_int));
              t20_done = true;
            }
          if (!t80_done)
            if (rampArray[k].v > v80) {
              v_int = rampArray[k].v;
              t_int = rampArray[k].t;
            } else {
              t80 = t_int + ((v80 - v_int) * (rampArray[k].t - t_int) /
                             (rampArray[k].v - v_int));
              t80_done = true;
            }
        }
      else
        for (int k = 0; k < key1; k++) {
          if (!t20_done)
            if (rampArray[k].v < v20) {
              v_int = rampArray[k].v;
              t_int = rampArray[k].t;
            } else {
              t20 = t_int + ((v20 - v_int) * (rampArray[k].t - t_int) /
                             (rampArray[k].v - v_int));
              t20_done = true;
            }
          if (!t80_done)
            if (rampArray[k].v < v80) {
              v_int = rampArray[k].v;
              t_int = rampArray[k].t;
            } else {
              t80 = t_int + ((v80 - v_int) * (rampArray[k].t - t_int) /
                             (rampArray[k].v - v_int));
              t80_done = true;
            }
        }

      /*------------------------------------------------------------------------
       *   Now we figure out where we want the data to go, munge it up, and
       *   store it.
       *-----------------------------------------------------------------------*/
      if (curveType == ConstantStuff.CURVE_TYPE_RISING_RAMP) {
        if (command.equalsIgnoreCase("typ")) {
          model.ramp.dv_r.typ = v80 - v20;
          model.ramp.dt_r.typ = t80 - t20;
        } else if (command.equalsIgnoreCase("min")) {
          model.ramp.dv_r.min = v80 - v20;
          model.ramp.dt_r.min = t80 - t20;
          model.ramp.dt_r.min -=
              model.ramp.dt_r.min * model.derateRampPct / 100;
        } else {
          model.ramp.dv_r.max = v80 - v20;
          model.ramp.dt_r.max = t80 - t20;
          model.ramp.dt_r.max +=
              model.ramp.dt_r.max * model.derateRampPct / 100;
        }
      } else {
        if (command.equalsIgnoreCase("typ")) {
          model.ramp.dv_f.typ = v20 - v80;
          model.ramp.dt_f.typ = t80 - t20;
        } else if (command.equalsIgnoreCase("min")) {
          model.ramp.dv_f.min = v20 - v80;
          model.ramp.dt_f.min = t80 - t20;
          model.ramp.dt_f.min -=
              model.ramp.dt_r.min * model.derateRampPct / 100;
        } else {
          model.ramp.dv_f.max = v20 - v80;
          model.ramp.dt_f.max = t80 - t20;
          model.ramp.dt_f.max +=
              model.ramp.dt_r.max * model.derateRampPct / 100;
        }
      }
      SpiceReader.close();
    } catch (Exception ex) {
      printf("Exception while collecting spice data from out files "
             "(getSpiceRampData): " +
             ex.toString());
      ex.printStackTrace();
    }
    return 0;
  } // end method getSpiceRampData
} // end class getSpiceRampData

/******************************************************************************
CLASS: generateRampData
******************************************************************************/

class generateRampData {
public:
  int generateRampData(ibisPin currentPin, ibisPin enablePin, ibisPin inputPin,
                       ibisPin powerPin, ibisPin gndPin, ibisPin powerClampPin,
                       ibisPin gndClampPin, ibisTypMinMax Vcc,
                       ibisTypMinMax Gnd, ibisTypMinMax VccClamp,
                       ibisTypMinMax GndClamp, int curveType, int spiceType,
                       string spiceFile, string spiceCommand, int iterate,
                       int cleanup) {
    ibisModel model_p;
    string headerLine, loadBuffer, inputBuffer, dummyBuffer, powerBuffer,
        temperatureBuffer, analysisBuffer, spiceInFile, spiceOutFile,
        spiceMsgFile, hspiceIcFile, hspiceIc0File;
    int outputState = 0;

    model_p = currentPin.model;

    if (curveType == ConstantStuff.CURVE_TYPE_RISING_RAMP)
      outputState = ConstantStuff.OUTPUT_RISING;
    else
      outputState = ConstantStuff.OUTPUT_FALLING;

    /*------------------------------------------------------------------------
     *   Attach the load to the output and the proper termination voltage.
     *-----------------------------------------------------------------------*/
    if ((model_p.modelType == ConstantStuff.MODEL_TYPE_OPEN_DRAIN) ||
        (model_p.modelType == ConstantStuff.MODEL_TYPE_OPEN_SINK) ||
        (model_p.modelType == ConstantStuff.MODEL_TYPE_I_O_OPEN_DRAIN) ||
        (model_p.modelType == ConstantStuff.MODEL_TYPE_I_O_OPEN_SINK)) {
      loadBuffer =
          s2iString.resString(spiceType, "RLOADS2I", currentPin.spiceNodeName,
                              powerPin.spiceNodeName, model_p.Rload);
    } else if ((model_p.modelType == ConstantStuff.MODEL_TYPE_OPEN_SOURCE) ||
               (model_p.modelType ==
                ConstantStuff.MODEL_TYPE_I_O_OPEN_SOURCE)) {
      loadBuffer =
          s2iString.resString(spiceType, "RLOADS2I", currentPin.spiceNodeName,
                              gndPin.spiceNodeName, model_p.Rload);
    } else if ((model_p.modelType == ConstantStuff.MODEL_TYPE_OUTPUT_ECL) ||
               (model_p.modelType == ConstantStuff.MODEL_TYPE_I_O_ECL)) {
      loadBuffer =
          s2iString.resString(spiceType, "RLOADS2I", currentPin.spiceNodeName,
                              s2iString.dummyNodeName[0], model_p.Rload);
      dummyBuffer = s2iString.DCSrcString(
          spiceType, "VTERMS2I", s2iString.dummyNodeName[0],
          powerPin.spiceNodeName,
          ConstantStuff.ECL_TERMINATION_VOLTAGE_DEFAULT);
      loadBuffer = loadBuffer + dummyBuffer;
    } else if (curveType == ConstantStuff.CURVE_TYPE_RISING_RAMP) {
      loadBuffer =
          s2iString.resString(spiceType, "RLOADS2I", currentPin.spiceNodeName,
                              gndPin.spiceNodeName, model_p.Rload);
    } else {
      loadBuffer =
          s2iString.resString(spiceType, "RLOADS2I", currentPin.spiceNodeName,
                              powerPin.spiceNodeName, model_p.Rload);
    }
    /*------------------------------------------------------------------------
     *   Set up for the typ run, and do the run.
     *-----------------------------------------------------------------------*/
    headerLine = "*Typ " + s2iString.curveNameString[curveType] +
                 " curve for model " + model_p.modelName + "\n";

    setPinDC setPinDC1 = new setPinDC();
    if (enablePin != null)
      inputBuffer = setPinDC1.setPinDC(enablePin, model_p.enable,
                                       ConstantStuff.ENABLE_OUTPUT, "ENA",
                                       ConstantStuff.TYP_CASE, spiceType);
    else
      inputBuffer = "";

    setPinTran setPinTran1 = new setPinTran();
    if (inputPin != null) {
      dummyBuffer =
          setPinTran1.setPinTran(inputPin, model_p.polarity, outputState, "IN",
                                 ConstantStuff.TYP_CASE, spiceType);
      inputBuffer = inputBuffer + "\n" + dummyBuffer;
    }

    setupPwrAndTempCmds setupPwrTmpCmd = new setupPwrAndTempCmds();
    setupPwrTmpCmd.setupPwrAndTempCmds(
        curveType, spiceType, powerPin, gndPin, powerClampPin, gndClampPin,
        Vcc.typ, Gnd.typ, VccClamp.typ, GndClamp.typ, model_p.tempRange.typ);
    powerBuffer = setupPwrTmpCmd.powerBuffer;
    temperatureBuffer = setupPwrTmpCmd.temperatureBuffer;

    setupTranCommands setupTranCmd = new setupTranCommands();
    analysisBuffer = setupTranCmd.setupTranCommands(spiceType, model_p.simTime,
                                                    currentPin.spiceNodeName);

    setupSpiceFileNames setSpFlNames1 = new setupSpiceFileNames();
    setSpFlNames1.setupSpiceFileNames(s2iString.spiceFileTypPrefix[curveType],
                                      currentPin.pinName);
    spiceInFile = setSpFlNames1.spiceInFile;
    spiceOutFile = setSpFlNames1.spiceOutFile;
    spiceMsgFile = setSpFlNames1.spiceMsgFile;

    setupSpiceInputFile setSpInFile = new setupSpiceInputFile();
    if (setSpInFile.setupSpiceInputFile(
            iterate, spiceType, spiceInFile, headerLine, spiceFile,
            model_p.modelFileTyp, model_p.extSpiceCmdFile, loadBuffer,
            inputBuffer, powerBuffer, temperatureBuffer, analysisBuffer) == 1) {
      return 1;
    }

    callSpice callSpice1 = new callSpice();
    checkForAbort checkAbort = new checkForAbort();
    getSpiceRampData RampData1 = new getSpiceRampData();

    if (callSpice1.callSpice(iterate, spiceCommand, spiceType, spiceInFile,
                             spiceOutFile, spiceMsgFile) == 1) {
      // checkForAbort
      int returnFromAbort =
          checkAbort.checkForAbort(spiceType, spiceOutFile, spiceMsgFile);
      if (returnFromAbort == 1) {
        printf("Spice run (TYP) aborted.  ");
        printf("See file " + spiceMsgFile + " for information.");
        printf("Curve " + s2iString.curveNameString[curveType] +
               " not generated.");
        printf("--- ");
        return 1;
      }
    }

    RampData1.getSpiceRampData(model_p, curveType, spiceType, spiceOutFile,
                               "typ");

    if (cleanup == 1) {
      File inFile = new File(spiceInFile);
      File outFile = new File(spiceOutFile);
      File msgFile = new File(spiceMsgFile);
      if (!inFile.delete())
        printf("Can't remove file " + spiceInFile);
      if (!outFile.delete())
        printf("Can't remove file " + spiceOutFile);
      if (!((spiceType == ConstantStuff.SPICE_TYPE_ELDO) ||
            (spiceType == ConstantStuff.SPICE_TYPE_HSPICE)))
        if (!msgFile.delete())
          printf("Can't remove file " + spiceMsgFile);

      if (spiceType == ConstantStuff.SPICE_TYPE_HSPICE) {
        spiceOutFile = s2iString.spiceFileTypPrefix[curveType] +
                       currentPin.pinName + ".st0";
        File outFile2 = new File(spiceOutFile);
        if (!outFile2.delete())
          printf("Can't remove .st0 file " + spiceOutFile);

        hspiceIcFile = s2iString.spiceFileTypPrefix[curveType] +
                       currentPin.pinName + ".ic";
        File outFile3 = new File(hspiceIcFile);
        outFile3.delete();
        hspiceIc0File = s2iString.spiceFileTypPrefix[curveType] +
                        currentPin.pinName + ".ic0";
        File outFile4 = new File(hspiceIc0File);
        outFile4.delete();
      }
    }

    /*------------------------------------------------------------------------
     *   Set up for the min run, and do the run.
     *-----------------------------------------------------------------------*/
    headerLine = "*Min " + s2iString.curveNameString[curveType] +
                 " curve for model " + model_p.modelName + "\n";

    if (enablePin != null)
      inputBuffer = setPinDC1.setPinDC(enablePin, model_p.enable,
                                       ConstantStuff.ENABLE_OUTPUT, "ENA",
                                       ConstantStuff.MIN_CASE, spiceType);
    else
      inputBuffer = "";

    if (inputPin != null) {
      dummyBuffer =
          setPinTran1.setPinTran(inputPin, model_p.polarity, outputState, "IN",
                                 ConstantStuff.MIN_CASE, spiceType);
      inputBuffer = inputBuffer + "\n" + dummyBuffer;
    }

    setupPwrTmpCmd.setupPwrAndTempCmds(
        curveType, spiceType, powerPin, gndPin, powerClampPin, gndClampPin,
        Vcc.min, Gnd.min, VccClamp.min, GndClamp.min, model_p.tempRange.min);
    powerBuffer = setupPwrTmpCmd.powerBuffer;
    temperatureBuffer = setupPwrTmpCmd.temperatureBuffer;

    analysisBuffer = setupTranCmd.setupTranCommands(spiceType, model_p.simTime,
                                                    currentPin.spiceNodeName);

    setSpFlNames1.setupSpiceFileNames(s2iString.spiceFileMinPrefix[curveType],
                                      currentPin.pinName);
    spiceInFile = setSpFlNames1.spiceInFile;
    spiceOutFile = setSpFlNames1.spiceOutFile;
    spiceMsgFile = setSpFlNames1.spiceMsgFile;

    if (setSpInFile.setupSpiceInputFile(
            iterate, spiceType, spiceInFile, headerLine, spiceFile,
            model_p.modelFileMin, model_p.extSpiceCmdFile, loadBuffer,
            inputBuffer, powerBuffer, temperatureBuffer, analysisBuffer) == 1)
      return 1;

    if (callSpice1.callSpice(iterate, spiceCommand, spiceType, spiceInFile,
                             spiceOutFile, spiceMsgFile) == 1) {
      // checkForAbort
      int returnFromAbort =
          checkAbort.checkForAbort(spiceType, spiceOutFile, spiceMsgFile);
      if (returnFromAbort == 1) {
        printf("Spice run (MIN) aborted.  ");
        printf("See file " + spiceMsgFile + " for information.");
        printf("Curve " + s2iString.curveNameString[curveType] +
               " not generated.");
      }
    }

    RampData1.getSpiceRampData(model_p, curveType, spiceType, spiceOutFile,
                               "min");

    if (cleanup == 1) {
      File inFile = new File(spiceInFile);
      File outFile = new File(spiceOutFile);
      File msgFile = new File(spiceMsgFile);
      if (!inFile.delete())
        printf("Can't remove file " + spiceInFile);
      if (!outFile.delete())
        printf("Can't remove file " + spiceOutFile);
      if (!((spiceType == ConstantStuff.SPICE_TYPE_ELDO) ||
            (spiceType == ConstantStuff.SPICE_TYPE_HSPICE)))
        if (!msgFile.delete())
          printf("Can't remove file " + spiceMsgFile);

      if (spiceType == ConstantStuff.SPICE_TYPE_HSPICE) {
        spiceOutFile = s2iString.spiceFileMinPrefix[curveType] +
                       currentPin.pinName + ".st0";
        File outFile2 = new File(spiceOutFile);
        if (!outFile2.delete())
          printf("Can't remove .st0 file " + spiceOutFile);

        hspiceIcFile = s2iString.spiceFileMinPrefix[curveType] +
                       currentPin.pinName + ".ic";
        File outFile3 = new File(hspiceIcFile);
        outFile3.delete();
        hspiceIc0File = s2iString.spiceFileMinPrefix[curveType] +
                        currentPin.pinName + ".ic0";
        File outFile4 = new File(hspiceIc0File);
        outFile4.delete();
      }
    }

    /*------------------------------------------------------------------------
     *   Set up for the max run, and do the run.
     *-----------------------------------------------------------------------*/
    headerLine = "*Max " + s2iString.curveNameString[curveType] +
                 " curve for model " + model_p.modelName + "\n";

    if (enablePin != null)
      inputBuffer = setPinDC1.setPinDC(enablePin, model_p.enable,
                                       ConstantStuff.ENABLE_OUTPUT, "ENA",
                                       ConstantStuff.MAX_CASE, spiceType);
    else
      inputBuffer = "";

    if (inputPin != null) {
      dummyBuffer =
          setPinTran1.setPinTran(inputPin, model_p.polarity, outputState, "IN",
                                 ConstantStuff.MAX_CASE, spiceType);
      inputBuffer = inputBuffer + "\n" + dummyBuffer;
    }

    setupPwrTmpCmd.setupPwrAndTempCmds(
        curveType, spiceType, powerPin, gndPin, powerClampPin, gndClampPin,
        Vcc.max, Gnd.max, VccClamp.max, GndClamp.max, model_p.tempRange.max);
    powerBuffer = setupPwrTmpCmd.powerBuffer;
    temperatureBuffer = setupPwrTmpCmd.temperatureBuffer;

    analysisBuffer = setupTranCmd.setupTranCommands(spiceType, model_p.simTime,
                                                    currentPin.spiceNodeName);

    setSpFlNames1.setupSpiceFileNames(s2iString.spiceFileMaxPrefix[curveType],
                                      currentPin.pinName);
    spiceInFile = setSpFlNames1.spiceInFile;
    spiceOutFile = setSpFlNames1.spiceOutFile;
    spiceMsgFile = setSpFlNames1.spiceMsgFile;

    if (setSpInFile.setupSpiceInputFile(
            iterate, spiceType, spiceInFile, headerLine, spiceFile,
            model_p.modelFileMax, model_p.extSpiceCmdFile, loadBuffer,
            inputBuffer, powerBuffer, temperatureBuffer, analysisBuffer) == 1) {
      return 1;
    }

    if (callSpice1.callSpice(iterate, spiceCommand, spiceType, spiceInFile,
                             spiceOutFile, spiceMsgFile) == 1) {
      // checkForAbort
      int returnFromAbort =
          checkAbort.checkForAbort(spiceType, spiceOutFile, spiceMsgFile);
      if (returnFromAbort == 1) {
        printf("Spice run (MAX) aborted.  ");
        printf("See file " + spiceMsgFile + " for information.");
        printf("Curve " + s2iString.curveNameString[curveType] +
               " not generated.");
      }
    }
    RampData1.getSpiceRampData(model_p, curveType, spiceType, spiceOutFile,
                               "max");

    if (cleanup == 1) {
      File inFile = new File(spiceInFile);
      File outFile = new File(spiceOutFile);
      File msgFile = new File(spiceMsgFile);
      if (!inFile.delete())
        printf("Can't remove file " + spiceInFile);
      if (!outFile.delete())
        printf("Can't remove file " + spiceOutFile);
      if (!((spiceType == ConstantStuff.SPICE_TYPE_ELDO) ||
            (spiceType == ConstantStuff.SPICE_TYPE_HSPICE)))
        if (!msgFile.delete())
          printf("Can't remove file " + spiceMsgFile);

      if (spiceType == ConstantStuff.SPICE_TYPE_HSPICE) {
        spiceOutFile = s2iString.spiceFileMaxPrefix[curveType] +
                       currentPin.pinName + ".st0";
        File outFile2 = new File(spiceOutFile);
        if (!outFile2.delete())
          printf("Can't remove .st0 file " + spiceOutFile);

        hspiceIcFile = s2iString.spiceFileMaxPrefix[curveType] +
                       currentPin.pinName + ".ic";
        File outFile3 = new File(hspiceIcFile);
        outFile3.delete();
        hspiceIc0File = s2iString.spiceFileMaxPrefix[curveType] +
                        currentPin.pinName + ".ic0";
        File outFile4 = new File(hspiceIc0File);
        outFile4.delete();
      }
    }
    return (0);
  }
} // end class generateRampData

/******************************************************************************
CLASS: getSpiceWaveData
******************************************************************************/

class getSpiceWaveData {
  ibisWaveTable wave_p;

public:
  int getSpiceWaveData(double simTime, int spiceType, string spiceOutFile,
                       string command) {
    File outFile_p = new File(spiceOutFile);
    string lineBuffer;
    double t = 0, v = 0, binTime = 0, vLastBin = 0, tLastBin = 0, vInterp = 0,
           tInterp = 0, vInterpBin = 0, tInterpBin = 0;
    int numRead = 0, i = 0, row = 0;
    int key1 = 0;
    bool flag = false;
    bool flag_eldo = true; // changed for beta0.4
    double temp_double = 0;
    spiceVT V = new spiceVT();
    binParams binParam1 = new binParams();
    LinkedHashMap waveData = new LinkedHashMap();

    binTime = simTime / (ConstantStuff.WAVE_POINTS_DEFAULT - 1);
    if (!(outFile_p.canRead())) {
      printf("Unable to open " + spiceOutFile + " for reading");
      return 1;
    }
    try {
      BufferedReader SpiceReader =
          new BufferedReader(new FileReader(outFile_p));
      /*-----------------------------------------------------------------------
       *   Read lines until we hit the data begin marker or EOF.  If it's EOF,
       *   return an error.
       *----------------------------------------------------------------------*/
      while (((lineBuffer = SpiceReader.readLine()) != null) &&
             (lineBuffer.indexOf(s2iString.tranDataBeginMarker[spiceType]) < 0))
        ;
      if (lineBuffer.indexOf(s2iString.tranDataBeginMarker[spiceType]) < 0) {
        printf("Data begin marker " + s2iString.tranDataBeginMarker[spiceType]);
        printf("not found in output file " + spiceOutFile);
        SpiceReader.close();
        return 1;
      }
      /*Special processing for ELDO*/
      if (spiceType == ConstantStuff.SPICE_TYPE_ELDO) {
        while (
            ((lineBuffer = SpiceReader.readLine()) != null) &&
            (!(lineBuffer.startsWith(s2iString.VIDataBeginMarker[spiceType]))))
          ;

        if (!(lineBuffer.startsWith(s2iString.VIDataBeginMarker[spiceType]))) {
          printf("Data begin marker '" +
                 s2iString.VIDataBeginMarker[spiceType] + "'");
          printf("not found in output file " + spiceOutFile);
          SpiceReader.close();
          return 1;
        }
      }

      /*----------------------------------------------------------------------
       *   We're now at the line before the start of the VI data.
       *   Read lines until we get to the actual VI table.
       *   No tranEndDataMarker is needed now as now we analyze the first token
       *   of the linebuffer and analyze it. Analysis is done by converting
       *   the tokens(Which are strings) to double.If the tokens
       *   are real strings, there will be an exception thrown.If there
       *   is an exception, We skip that line and move to the next line
       *---------------------------------------------------------------------*/
      while (((lineBuffer = SpiceReader.readLine()) != null) && flag_eldo)
        if (lineBuffer != null) {
          StringTokenizer st = new StringTokenizer(lineBuffer);
          int cnt = st.countTokens();
          if (cnt != 0) {
            string temp = st.nextToken();
            try {
              temp_double = Double.parseDouble(temp);
              flag = true;
              row++;
            } catch (Exception ex1) {
              if (ex1.toString().length() == 0) {
              } else
                flag = false;
              if (spiceType == ConstantStuff.SPICE_TYPE_ELDO)
                flag_eldo = false;
            }
          }
          if ((cnt == 2) && flag) {
            /*use temp_double here as the first column is the voltage
            column and it has already been converted to double
            */
            V.t = temp_double;
            V.v = Double.parseDouble(st.nextToken());
            waveData.put(new Integer(row), V);
            V = new spiceVT();
          }
          if ((cnt == 3) && flag) {
            //		As we dont want the first column from the 4 columns..
            //		..we skip the temp_double and go to the nextToken.
            // convert string to double using Double.parseDouble
            V.t = Double.parseDouble(st.nextToken());
            V.v = Double.parseDouble(st.nextToken());
            waveData.put(new Integer(row), V);
            V = new spiceVT();
          }
        } // while
      spiceVT V1;
      spiceVT[] waveArray = new spiceVT[waveData.size()];
      for (Iterator key = waveData.keySet().iterator(),
                    value = waveData.values().iterator();
           key.hasNext();) {
        key.next();
        V1 = (spiceVT)value.next();
        waveArray[key1] = V1;
        V1 = new spiceVT();
        key1++;
      }
      /*------------------------------------------------------------------------
       *   Now we need to initialize some variables that we'll use while
       *   we're binning the transient data. We also need to go ahead and
       *   zeroize the first table entry - (Doing that in the generateWaveData).
       *-----------------------------------------------------------------------*/
      binParam1.numPointsInBin = 0; // old code has =1 as it already reads the
      binParam1.runningSum = v;     // first value - before the loop begins.
      binParam1.lastBin = goodies.ROUND(t / binTime);

      /*------------------------------------------------------------------------
       *   Now we read until we no longer get the correct number of columns.  We
       *   use a method similar to that found in getSpiceVIData.  While we do
       *   this, we're going to bin the points to construct a curve with
       *   evenly spaced time values.
       *-----------------------------------------------------------------------*/
      binTranData binTranData1 = new binTranData();

      for (int k = 0; k < key1; k++) {
        binTranData1.binTranData(waveArray[k].t, waveArray[k].v, simTime,
                                 binTime, command, binParam1, wave_p);
      }

      /*--------------------------------------------------------------------
       *   Put the last data point into the wave table, and do any necessary
       *   interpolations.
       *-------------------------------------------------------------------*/
      vLastBin = binParam1.runningSum / binParam1.numPointsInBin;
      tLastBin = simTime;

      if (command.equalsIgnoreCase("typ")) {
        wave_p.waveData[binParam1.lastBin].t = tLastBin;
        wave_p.waveData[binParam1.lastBin].v.typ = vLastBin;
      } else if (command.equalsIgnoreCase("min"))
        wave_p.waveData[binParam1.lastBin].v.min = vLastBin;
      else
        wave_p.waveData[binParam1.lastBin].v.max = vLastBin;

      if (binParam1.lastBin != binParam1.interpBin) {
        tInterpBin = wave_p.waveData[binParam1.interpBin].t;
        if (command.equalsIgnoreCase("typ"))
          vInterpBin = wave_p.waveData[binParam1.interpBin].v.typ;
        else if (command.equalsIgnoreCase("min"))
          vInterpBin = wave_p.waveData[binParam1.interpBin].v.min;
        else
          vInterpBin = wave_p.waveData[binParam1.interpBin].v.max;
        for (i = binParam1.interpBin + 1; i < binParam1.lastBin; i++) {
          tInterp = i * binTime;
          vInterp = vInterpBin + (tInterp - tInterpBin) * (v - vInterpBin) /
                                     (t - tInterpBin);
          if (command.equalsIgnoreCase("typ")) {
            wave_p.waveData[i].t = tInterp;
            wave_p.waveData[i].v.typ = vInterp;
          } else if (command.equalsIgnoreCase("min"))
            wave_p.waveData[i].v.min = vInterp;
          else
            wave_p.waveData[i].v.max = vInterp;
        }
      }

      SpiceReader.close();

    } catch (Exception ex) {
      printf("Exception while collecting spice data from out files "
             "(getSpiceWaveData): " +
             ex.toString());
    }
    return 0;

  } // end method getSpiceWaveData
} // end class getSpiceWaveData

/******************************************************************************
CLASS: binParams
******************************************************************************/

class binParams {
  int lastBin = 0;
  int interpBin = 0;
  double runningSum = 0;
  int numPointsInBin = 0;
} // end class binParams

/******************************************************************************
CLASS: binTranData
******************************************************************************/

class binTranData {
public:
  void binTranData(double t, double v, double simTime, double binTime,
                   string command, binParams binParam1, ibisWaveTable wave_p) {
    int currentBin = 0, i = 0;
    double vLastBin = 0, tLastBin = 0, vInterp = 0, tInterp = 0, vInterpBin = 0,
           tInterpBin = 0;
    currentBin = goodies.ROUND(t / binTime);
    if (currentBin == binParam1.lastBin) {
      /*--------------------------------------------------------
       *	If we're still in the last bin, just add this data
       *	point to the running sum and continue.
       *-------------------------------------------------------*/
      binParam1.runningSum += v;
      binParam1.numPointsInBin += 1;
    } else {
      /*--------------------------------------------------------
       *   If we've changed bins, we have some work to do.  First,
       *   we compute the average of all the points in the last bin,
       *   and assign this value to the appropriate spot in the
       *   wave table.
       *-------------------------------------------------------*/
      vLastBin = binParam1.runningSum / binParam1.numPointsInBin;
      tLastBin = binParam1.lastBin * binTime;
      if (command.equalsIgnoreCase("typ")) {
        wave_p.waveData[binParam1.lastBin].t = tLastBin;
        wave_p.waveData[binParam1.lastBin].v.typ = vLastBin;
      } else if (command.equalsIgnoreCase("min"))
        wave_p.waveData[binParam1.lastBin].v.min = vLastBin;
      else
        wave_p.waveData[binParam1.lastBin].v.max = vLastBin;

      /*--------------------------------------------------------
       *   Now we need to check if we've missed any bins.  If we
       *   have, we're just going to linearly interpolate
       *   between the two adjacent points (for however many bins
       *   it takes) to get data points in the empty bins.
       *-------------------------------------------------------*/
      if (binParam1.lastBin != binParam1.interpBin) {
        tInterpBin = wave_p.waveData[binParam1.interpBin].t;
        if (command.equalsIgnoreCase("typ"))
          vInterpBin = wave_p.waveData[binParam1.interpBin].v.typ;
        else if (command.equalsIgnoreCase("min"))
          vInterpBin = wave_p.waveData[binParam1.interpBin].v.min;
        else
          vInterpBin = wave_p.waveData[binParam1.interpBin].v.max;
        for (i = binParam1.interpBin + 1; i < binParam1.lastBin; i++) {
          tInterp = i * binTime;
          vInterp = vInterpBin + (tInterp - tInterpBin) * (v - vInterpBin) /
                                     (t - tInterpBin);

          if (command.equalsIgnoreCase("typ")) {
            wave_p.waveData[i].t = tLastBin;
            wave_p.waveData[i].v.typ = vLastBin;
          } else if (command.equalsIgnoreCase("min"))
            wave_p.waveData[i].v.min = vLastBin;
          else
            wave_p.waveData[i].v.max = vLastBin;
        }
      }

      if (currentBin > (binParam1.lastBin + 1))
        binParam1.interpBin = binParam1.lastBin;
      else
        binParam1.interpBin = currentBin;
      /*--------------------------------------------------------
       *   Finally, we reset our counters and running sum.
       *-------------------------------------------------------*/
      binParam1.lastBin = currentBin;
      binParam1.runningSum = v;
      binParam1.numPointsInBin = 1;
    } // else
  }   // end method binTranData
} // end class binTranData

/******************************************************************************
CLASS: generateWaveData
******************************************************************************/

class generateWaveData {
  ibisWaveTable currentWave; // inout
public:
  int generateWaveData(ibisPin currentPin, // rest in
                       ibisPin enablePin, ibisPin inputPin, ibisPin powerPin,
                       ibisPin gndPin, ibisPin powerClampPin,
                       ibisPin gndClampPin, ibisTypMinMax Vcc,
                       ibisTypMinMax Gnd, ibisTypMinMax VccClamp,
                       ibisTypMinMax GndClamp, int curveType, int spiceType,
                       string spiceFile, string spiceCommand, int iterate,
                       int cleanup, int index) {
    ibisModel model_p;
    string headerLine, inputBuffer, loadBuffer, dummyBuffer, namePrefixBuffer,
        powerBuffer, temperatureBuffer, analysisBuffer, spiceInFile,
        spiceOutFile, spiceMsgFile, hspiceIcFile, hspiceIc0File, outputNodeName;
    string[] nodeList = new string[11];
    int outputState = 0, nodeIndex = 0, i = 0;
    model_p = currentPin.model;

    currentWave.waveData =
        new ibisWaveTableEntry[ConstantStuff.WAVE_POINTS_DEFAULT];
    currentWave.size = ConstantStuff.WAVE_POINTS_DEFAULT;

    // Initialize the current Wave
    for (int m = 0; m < ConstantStuff.WAVE_POINTS_DEFAULT; m++) {
      currentWave.waveData[m] = new ibisWaveTableEntry();
    }

    if (curveType == ConstantStuff.CURVE_TYPE_RISING_WAVE)
      outputState = ConstantStuff.OUTPUT_RISING;
    else
      outputState = ConstantStuff.OUTPUT_FALLING;
    /*------------------------------------------------------------------------
     *   Attach the load to the output.  This is both simpler and more
     *   complex than for the ramp--there are no special cases for different
     *   types of circuits, but there may be variable numbers of parasitics
     *   to attach.  Ugh.  We start by building a list of node names--the
     *   first node name in the list is the current pin's node, and the rest
     *   are the dummy node names from s2istrng.h.
     *-----------------------------------------------------------------------*/
    nodeList[0] = currentPin.spiceNodeName;
    for (i = 1; i < 11; i++)
      nodeList[i] = s2iString.dummyNodeName[i - 1];

    /*------------------------------------------------------------------------
     *   Now we attach the __dut parasitics.  The measurement port comes between
     *   the dut stuff and the fixture parasitics, so we'll save that node name.
     *-----------------------------------------------------------------------*/
    loadBuffer = "";
    if (!(goodies.IS_USE_NA(currentWave.L_dut))) {
      dummyBuffer =
          s2iString.indString(spiceType, "LDUTS2I", nodeList[nodeIndex],
                              nodeList[++nodeIndex], currentWave.L_dut);
      loadBuffer = loadBuffer + dummyBuffer;
    }

    if (!(goodies.IS_USE_NA(currentWave.R_dut))) {
      dummyBuffer =
          s2iString.resString(spiceType, "RDUTS2I", nodeList[nodeIndex],
                              nodeList[++nodeIndex], currentWave.R_dut);
      loadBuffer = loadBuffer + dummyBuffer;
    }

    if (!(goodies.IS_USE_NA(currentWave.C_dut))) {

      dummyBuffer = s2iString.capString(
          spiceType, "CDUTS2I", nodeList[nodeIndex], "0", currentWave.C_dut);
      loadBuffer = loadBuffer + dummyBuffer;
    }

    outputNodeName = nodeList[nodeIndex];

    /*------------------------------------------------------------------------
     *   Now attach the fixture parasitics.  We'll attach v_fixture later.
     *-----------------------------------------------------------------------*/
    if (!(goodies.IS_USE_NA(currentWave.L_fixture))) {
      dummyBuffer =
          s2iString.indString(spiceType, "LFIXS2I", nodeList[nodeIndex],
                              nodeList[++nodeIndex], currentWave.L_fixture);
      loadBuffer = loadBuffer + dummyBuffer;
    }

    if (!(goodies.IS_USE_NA(currentWave.C_fixture))) {
      dummyBuffer =
          s2iString.capString(spiceType, "CFIXS2I", nodeList[nodeIndex], "0",
                              currentWave.C_fixture);
      loadBuffer = loadBuffer + dummyBuffer;
    }

    /*------------------------------------------------------------------------
     *   R_fixture is always attached...
     *-----------------------------------------------------------------------*/
    dummyBuffer =
        s2iString.resString(spiceType, "RFIXS2I", nodeList[nodeIndex],
                            nodeList[++nodeIndex], currentWave.R_fixture);
    loadBuffer = loadBuffer + dummyBuffer;

    /*------------------------------------------------------------------------
     *   Set up for the typ run, and do the run.  This is where we'll attach
     *   V_fixture and the enable and input signals, since they may change
     *   with the min and max runs.
     *-----------------------------------------------------------------------*/

    headerLine = "*Typ " + s2iString.curveNameString[curveType] +
                 " curve for model " + model_p.modelName + "\n";

    setPinDC setPinDC1 = new setPinDC();
    if (enablePin != null)
      inputBuffer = setPinDC1.setPinDC(enablePin, model_p.enable,
                                       ConstantStuff.ENABLE_OUTPUT, "ENA",
                                       ConstantStuff.TYP_CASE, spiceType);
    else
      inputBuffer = "";

    setPinTran setPinTran1 = new setPinTran();
    if (inputPin != null) {
      dummyBuffer =
          setPinTran1.setPinTran(inputPin, model_p.polarity, outputState, "IN",
                                 ConstantStuff.TYP_CASE, spiceType);
      inputBuffer = inputBuffer + "\n" + dummyBuffer;
    }

    dummyBuffer = s2iString.DCSrcString(
        spiceType, "VFIXS2I", nodeList[nodeIndex], "0", currentWave.V_fixture);
    inputBuffer = inputBuffer + "\n" + dummyBuffer;

    setupPwrAndTempCmds setupPwrTmpCmd = new setupPwrAndTempCmds();
    setupPwrTmpCmd.setupPwrAndTempCmds(
        curveType, spiceType, powerPin, gndPin, powerClampPin, gndClampPin,
        Vcc.typ, Gnd.typ, VccClamp.typ, GndClamp.typ, model_p.tempRange.typ);
    powerBuffer = setupPwrTmpCmd.powerBuffer;
    temperatureBuffer = setupPwrTmpCmd.temperatureBuffer;

    setupTranCommands setupTranCmd = new setupTranCommands();
    analysisBuffer = setupTranCmd.setupTranCommands(spiceType, model_p.simTime,
                                                    outputNodeName);

    if (index < 10)
      namePrefixBuffer = s2iString.spiceFileTypPrefix[curveType] + "0" + index;
    else
      namePrefixBuffer = s2iString.spiceFileTypPrefix[curveType] + index;

    setupSpiceFileNames setSpFlNames1 = new setupSpiceFileNames();
    setSpFlNames1.setupSpiceFileNames(namePrefixBuffer, currentPin.pinName);
    spiceInFile = setSpFlNames1.spiceInFile;
    spiceOutFile = setSpFlNames1.spiceOutFile;
    spiceMsgFile = setSpFlNames1.spiceMsgFile;

    setupSpiceInputFile setSpInFile = new setupSpiceInputFile();
    if (setSpInFile.setupSpiceInputFile(
            iterate, spiceType, spiceInFile, headerLine, spiceFile,
            model_p.modelFileTyp, model_p.extSpiceCmdFile, loadBuffer,
            inputBuffer, powerBuffer, temperatureBuffer, analysisBuffer) == 1) {
      return 1;
    }

    callSpice callSpice1 = new callSpice();
    checkForAbort checkAbort = new checkForAbort();

    if (callSpice1.callSpice(iterate, spiceCommand, spiceType, spiceInFile,
                             spiceOutFile, spiceMsgFile) == 1) {
      // checkForAbort
      int returnFromAbort =
          checkAbort.checkForAbort(spiceType, spiceOutFile, spiceMsgFile);
      if (returnFromAbort == 1) {
        printf("Spice run (TYP) aborted.  ");
        printf("See file " + spiceMsgFile + " for information.");
        printf("Curve " + s2iString.curveNameString[curveType] +
               " not generated.");
        printf("--- ");
        return 1;
      }
    }
    // initializing the first element of the array = 0 here instead of
    // 'getspiceWaveData'
    currentWave.waveData[0].t = 0;
    currentWave.waveData[0].v.typ = 0;
    currentWave.waveData[0].v.min = 0;
    currentWave.waveData[0].v.max = 0;

    getSpiceWaveData WaveData1 = new getSpiceWaveData();
    WaveData1.wave_p = currentWave;
    WaveData1.getSpiceWaveData(model_p.simTime, spiceType, spiceOutFile, "typ");
    currentWave = WaveData1.wave_p;

    if (cleanup == 1) {
      File inFile = new File(spiceInFile);
      File outFile = new File(spiceOutFile);
      File msgFile = new File(spiceMsgFile);
      if (!inFile.delete())
        printf("Can't remove file " + spiceInFile);
      if (!outFile.delete())
        printf("Can't remove file " + spiceOutFile);
      if (!((spiceType == ConstantStuff.SPICE_TYPE_ELDO) ||
            (spiceType == ConstantStuff.SPICE_TYPE_HSPICE)))
        if (!msgFile.delete())
          printf("Can't remove file " + spiceMsgFile);

      if (spiceType == ConstantStuff.SPICE_TYPE_HSPICE) {
        spiceOutFile = namePrefixBuffer + currentPin.pinName + ".st0";
        File outFile2 = new File(spiceOutFile);
        outFile2.delete();

        hspiceIcFile = namePrefixBuffer + currentPin.pinName + ".ic";
        File outFile3 = new File(hspiceIcFile);
        outFile3.delete();
        hspiceIc0File = namePrefixBuffer + currentPin.pinName + ".ic0";
        File outFile4 = new File(hspiceIc0File);
        outFile4.delete();
      }
    }

    /*------------------------------------------------------------------------
     *   Set up for the min run, and do the run.
     *-----------------------------------------------------------------------*/
    headerLine = "*Min " + s2iString.curveNameString[curveType] +
                 " curve for model " + model_p.modelName + "\n";

    if (enablePin != null)
      inputBuffer = setPinDC1.setPinDC(enablePin, model_p.enable,
                                       ConstantStuff.ENABLE_OUTPUT, "ENA",
                                       ConstantStuff.MIN_CASE, spiceType);
    else
      inputBuffer = "";

    if (inputPin != null) {
      dummyBuffer =
          setPinTran1.setPinTran(inputPin, model_p.polarity, outputState, "IN",
                                 ConstantStuff.MIN_CASE, spiceType);
      inputBuffer = inputBuffer + "\n" + dummyBuffer;
    }

    if (!(goodies.IS_USE_NA(currentWave.V_fixture_min))) {
      dummyBuffer =
          s2iString.DCSrcString(spiceType, "VFIXS2I", nodeList[nodeIndex], "0",
                                currentWave.V_fixture_min);
      inputBuffer = inputBuffer + "\n" + dummyBuffer;
    } else {
      dummyBuffer =
          s2iString.DCSrcString(spiceType, "VFIXS2I", nodeList[nodeIndex], "0",
                                currentWave.V_fixture);
      inputBuffer = inputBuffer + "\n" + dummyBuffer;
    }

    setupPwrTmpCmd.setupPwrAndTempCmds(
        curveType, spiceType, powerPin, gndPin, powerClampPin, gndClampPin,
        Vcc.min, Gnd.min, VccClamp.min, GndClamp.min, model_p.tempRange.min);
    powerBuffer = setupPwrTmpCmd.powerBuffer;
    temperatureBuffer = setupPwrTmpCmd.temperatureBuffer;

    analysisBuffer = setupTranCmd.setupTranCommands(spiceType, model_p.simTime,
                                                    outputNodeName);

    if (index < 10)
      namePrefixBuffer = s2iString.spiceFileMinPrefix[curveType] + "0" + index;
    else
      namePrefixBuffer = s2iString.spiceFileMinPrefix[curveType] + index;

    setSpFlNames1.setupSpiceFileNames(namePrefixBuffer, currentPin.pinName);
    spiceInFile = setSpFlNames1.spiceInFile;
    spiceOutFile = setSpFlNames1.spiceOutFile;
    spiceMsgFile = setSpFlNames1.spiceMsgFile;

    if (setSpInFile.setupSpiceInputFile(
            iterate, spiceType, spiceInFile, headerLine, spiceFile,
            model_p.modelFileMin, model_p.extSpiceCmdFile, loadBuffer,
            inputBuffer, powerBuffer, temperatureBuffer, analysisBuffer) == 1)
      return 1;

    if (callSpice1.callSpice(iterate, spiceCommand, spiceType, spiceInFile,
                             spiceOutFile, spiceMsgFile) == 1) {
      // checkForAbort
      int returnFromAbort =
          checkAbort.checkForAbort(spiceType, spiceOutFile, spiceMsgFile);
      if (returnFromAbort == 1) {
        printf("Spice run (MIN) aborted.  ");
        printf("See file " + spiceMsgFile + " for information.");
        printf("Curve " + s2iString.curveNameString[curveType] +
               " not generated.");
      }
    }

    WaveData1.wave_p = currentWave;
    WaveData1.getSpiceWaveData(model_p.simTime, spiceType, spiceOutFile, "min");
    currentWave = WaveData1.wave_p;
    if (cleanup == 1) {
      File inFile = new File(spiceInFile);
      File outFile = new File(spiceOutFile);
      File msgFile = new File(spiceMsgFile);
      if (!inFile.delete())
        printf("Can't remove file " + spiceInFile);
      if (!outFile.delete())
        printf("Can't remove file " + spiceOutFile);
      if (!((spiceType == ConstantStuff.SPICE_TYPE_ELDO) ||
            (spiceType == ConstantStuff.SPICE_TYPE_HSPICE)))
        if (!msgFile.delete())
          printf("Can't remove file " + spiceMsgFile);

      if (spiceType == ConstantStuff.SPICE_TYPE_HSPICE) {
        spiceOutFile = namePrefixBuffer + currentPin.pinName + ".st0";
        File outFile2 = new File(spiceOutFile);
        outFile2.delete();

        hspiceIcFile = namePrefixBuffer + currentPin.pinName + ".ic";
        File outFile3 = new File(hspiceIcFile);
        outFile3.delete();
        hspiceIc0File = namePrefixBuffer + currentPin.pinName + ".ic0";
        File outFile4 = new File(hspiceIc0File);
        outFile4.delete();
      }
    }

    /*------------------------------------------------------------------------
     *   Set up for the max run, and do the run.
     *-----------------------------------------------------------------------*/
    headerLine = "*Max " + s2iString.curveNameString[curveType] +
                 " curve for model " + model_p.modelName + "\n";

    if (enablePin != null)
      inputBuffer = setPinDC1.setPinDC(enablePin, model_p.enable,
                                       ConstantStuff.ENABLE_OUTPUT, "ENA",
                                       ConstantStuff.MAX_CASE, spiceType);
    else
      inputBuffer = "";

    if (inputPin != null) {
      dummyBuffer =
          setPinTran1.setPinTran(inputPin, model_p.polarity, outputState, "IN",
                                 ConstantStuff.MAX_CASE, spiceType);
      inputBuffer = inputBuffer + "\n" + dummyBuffer;
    }

    if (!(goodies.IS_USE_NA(currentWave.V_fixture_max))) {
      dummyBuffer =
          s2iString.DCSrcString(spiceType, "VFIXS2I", nodeList[nodeIndex], "0",
                                currentWave.V_fixture_max);
      inputBuffer = inputBuffer + "\n" + dummyBuffer;
    } else {
      dummyBuffer =
          s2iString.DCSrcString(spiceType, "VFIXS2I", nodeList[nodeIndex], "0",
                                currentWave.V_fixture);
      inputBuffer = inputBuffer + "\n" + dummyBuffer;
    }

    setupPwrTmpCmd.setupPwrAndTempCmds(
        curveType, spiceType, powerPin, gndPin, powerClampPin, gndClampPin,
        Vcc.max, Gnd.max, VccClamp.max, GndClamp.max, model_p.tempRange.max);
    powerBuffer = setupPwrTmpCmd.powerBuffer;
    temperatureBuffer = setupPwrTmpCmd.temperatureBuffer;

    analysisBuffer = setupTranCmd.setupTranCommands(spiceType, model_p.simTime,
                                                    outputNodeName);

    if (index < 10)
      namePrefixBuffer = s2iString.spiceFileMaxPrefix[curveType] + "0" + index;
    else
      namePrefixBuffer = s2iString.spiceFileMaxPrefix[curveType] + index;

    setSpFlNames1.setupSpiceFileNames(namePrefixBuffer, currentPin.pinName);
    spiceInFile = setSpFlNames1.spiceInFile;
    spiceOutFile = setSpFlNames1.spiceOutFile;
    spiceMsgFile = setSpFlNames1.spiceMsgFile;

    if (setSpInFile.setupSpiceInputFile(
            iterate, spiceType, spiceInFile, headerLine, spiceFile,
            model_p.modelFileMax, model_p.extSpiceCmdFile, loadBuffer,
            inputBuffer, powerBuffer, temperatureBuffer, analysisBuffer) == 1)
      return 1;

    if (callSpice1.callSpice(iterate, spiceCommand, spiceType, spiceInFile,
                             spiceOutFile, spiceMsgFile) == 1) {
      // checkForAbort
      int returnFromAbort =
          checkAbort.checkForAbort(spiceType, spiceOutFile, spiceMsgFile);
      if (returnFromAbort == 1) {
        printf("Spice run (MAX) aborted.  ");
        printf("See file " + spiceMsgFile + " for information.");
        printf("Curve " + s2iString.curveNameString[curveType] +
               " not generated.");
      }
    }

    WaveData1.wave_p = currentWave;
    WaveData1.getSpiceWaveData(model_p.simTime, spiceType, spiceOutFile, "max");
    currentWave = WaveData1.wave_p;

    if (cleanup == 1) {
      File inFile = new File(spiceInFile);
      File outFile = new File(spiceOutFile);
      File msgFile = new File(spiceMsgFile);
      if (!inFile.delete())
        printf("Can't remove file " + spiceInFile);
      if (!outFile.delete())
        printf("Can't remove file " + spiceOutFile);
      if (!((spiceType == ConstantStuff.SPICE_TYPE_ELDO) ||
            (spiceType == ConstantStuff.SPICE_TYPE_HSPICE)))
        if (!msgFile.delete())
          printf("Can't remove file " + spiceMsgFile);

      if (spiceType == ConstantStuff.SPICE_TYPE_HSPICE) {
        spiceOutFile = namePrefixBuffer + currentPin.pinName + ".st0";
        File outFile2 = new File(spiceOutFile);
        outFile2.delete();

        hspiceIcFile = namePrefixBuffer + currentPin.pinName + ".ic";
        File outFile3 = new File(hspiceIcFile);
        outFile3.delete();
        hspiceIc0File = namePrefixBuffer + currentPin.pinName + ".ic0";
        File outFile4 = new File(hspiceIc0File);
        outFile4.delete();
      }
    }

    return 0;
  } // end method generateWaveData
} // end class generateWaveData

/******************************************************************************
CLASS: VIDataContainer
******************************************************************************/

class VIDataContainer {
  ibisVItable VIData2 = new ibisVItable();
}
/*******************FOR TESTING PURPOSES ONLY*************/
class s2ispice {

public:
  void main(string[] args) {
    try {
      LinkedHashMap LHM = new LinkedHashMap();
      getSpiceVIData VI = new getSpiceVIData();
      callSpice spice = new callSpice();
      ibisVItable VIData2 = new ibisVItable();

      VIDataContainer VICont = new VIDataContainer();
      VICont.VIData2.VIs = new ibisVItableEntry[100];
      for (int m = 0; m < 100; m++) {
        VICont.VIData2.VIs[m] = new ibisVItableEntry();
      }

      spice.callSpice(0, "", 0, "test1.spi", "test1.out", "test1.msg");

      VI.getSpiceVIData(VICont, 100, 4, "pdxout.out", "typ"); // putout.lis");
      VI.getSpiceVIData(VICont, 100, 4, "pdxout1.out", "min");
      VI.getSpiceVIData(VICont, 100, 4, "pdxout2.out", "max");

      for (int b = 0; b < 100; b++) {
        printf("ARRAY  :" + VICont.VIData2.VIs[b].v + " ," +
               VICont.VIData2.VIs[b].i.typ);
        printf("ARRAY2 :" + VICont.VIData2.VIs[b].v + " ," +
               VICont.VIData2.VIs[b].i.min);
        printf("ARRAY3 :" + VICont.VIData2.VIs[b].v + " ," +
               VICont.VIData2.VIs[b].i.max);
      }
    } catch (Exception ex) {
      printf("Exception2 while setting file names: " + ex.toString());
    }
  }
}
