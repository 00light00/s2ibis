/*******************************************************************************
*File Name	: s2ibis3.h
*Description	: This is the file containing the main routine for s2ibis3
*		:  
********************************************************************************
********************************************************************************

Revision 2.0  2020/08/31 12:00:00  Peior_wu@realsil
c++ version

transplant from s2ibis3.java
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

#include <iostream>
#include <string>
#include <regex>
using namespace std;

#include "ibisGlobal.h"
#include "ibisTOP.h"
#include "cListContainer.h"


int main(int argv, char* args[]) {

    string		inputFileName	=  "";
    ibisTOP	ibisHead;
    ibisGlobal	ibisGlobal;
    cListContainer cListCont;
    istream 	inStream;
 
 /**--------------------------------------------------------------------
 *  Check to see if someone used the "-h" or "-help" switch anywhere.
 *--------------------------------------------------------------------*/
 for (int i = 0; i < argv; i++ )
     if ( args[i].equalsIgnoreCase("-h") )
         {
         printf( "\nUsage: s2ibis3 input_filename\n\n");
         return 0;
         }
 /**--------------------------------------------------------------------
 *   Print a header line.
 *--------------------------------------------------------------------*/
 printf( "s2ibis3 v"+ConstantStuff.VERSION_STRING +
                     " -- North Carolina State University\n");
 if (  ConstantStuff.VERSION_STRING.endsWith("BETA") )
     printf( "*** This is a beta release -- use with caution! ***\n" );

 /**--------------------------------------------------------------------
 *   Get the input filename, either from the argument list or from stdin.
 *--------------------------------------------------------------------*/
 if( args.length >= 1 )
    {
    inputFileName = args[0];
    }
 else
     {
     System.out.print("input file: ");
     BufferedReader fileNameBuffer = 
                    new BufferedReader(new InputStreamReader(System.in));
     inputFileName = fileNameBuffer.readLine();
     }

 /**--------------------------------------------------------------------
 *   Read the input file and proceed with analysis if no errors.
 *--------------------------------------------------------------------*/
 s2iReader s2ibisRead = new s2iReader();
 s2ibisRead.inFile = inputFileName;
 s2ibisRead.main(args);
 ibisHead =s2ibisRead.ibisStruct;
 ibisGlobal = s2ibisRead.ibisGlobal;
 /**----------------------------------------------------------------
 *   Complete the internal data structure.
 *----------------------------------------------------------------*/
 completeDataStructures cmpDataStr = new completeDataStructures();
 cmpDataStr.ibis = ibisHead;
 cmpDataStr.completeDataStructures( ibisGlobal);
 
 /*-------------------------------------------------------------
 *   Go through each component, analyzing each one as we go.
 *------------------------------------------------------------*/
 analyzeComponent analyzeComp = new analyzeComponent();
 cListCont.cListCont = cmpDataStr.ibis.cList;
 cListCont.cListCont.gototop();
 printf("\n");
 analyzeComp.CLC = cListCont;
 analyzeComp.analyzeComponent( ibisHead.spiceType,ibisHead.iterate,
   				ibisHead.cleanup,ibisHead.spiceCommand);   
 
   printf("This File Name = "+ibisHead.thisFileName);
   printf("Date = "+ibisHead.date);
 
    /******************************************
        Print the result
    ******************************************/
    cListCont.cListCont.gototop();
    s2ibisPrint s2iPrint = new s2ibisPrint();
    s2iPrint.ibisHead = ibisHead;
    s2iPrint.printMain();

    return 0;

 }		//method main
}		//class s2ibis3
