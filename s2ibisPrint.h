/*      */ import java.io.BufferedWriter;
/*      */ import java.io.File;
/*      */ import java.io.FileWriter;
/*      */ import java.io.PrintWriter;
/*      */ import java.math.BigDecimal;
/*      */ import java.util.StringTokenizer;
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ class s2ibisPrint
/*      */ {
/*      */   ibisTOP ibisHead;
/*      */   
/*      */   public void printMain() {
/*  584 */     File outFile = new File(this.ibisHead.thisFileName);
/*      */     
/*      */     try {
/*  587 */       PrintWriter ibisWriter = new PrintWriter(new BufferedWriter(
/*  588 */             new FileWriter(outFile)));
/*      */       
/*  590 */       System.out.println("Opening file " + this.ibisHead.thisFileName + " for writing ...");
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */       
/*  596 */       if (!outFile.canWrite()) {
/*      */         
/*  598 */         System.out.println("Unable to open " + outFile + "for writing");
/*      */         
/*      */         return;
/*      */       } 
/*  602 */       print_TOP(ibisWriter);
/*  603 */       ibisWriter.close();
/*  604 */       System.out.println("done.");
/*      */     }
/*  606 */     catch (Exception ex) {
/*  607 */       System.out.println("Exception while writing ibis output file (printMain): " + 
/*  608 */           ex.toString() + ": ");
/*  609 */       ex.printStackTrace();
/*      */     } 
/*      */   }
/*      */   public void print_TOP(PrintWriter ibisWriter) {
/*  613 */     ibisComponent tempComponent = new ibisComponent();
/*  614 */     ibisComponent tempComponent2 = new ibisComponent();
/*      */ 
/*      */     
/*  617 */     ibisWriter.println("|************************************************************************");
/*  618 */     ibisWriter.println("| IBIS file " + this.ibisHead.thisFileName + 
/*  619 */         " created by s2ibis3 verion " + "1.1");
/*  620 */     ibisWriter.println("| North Carolina State University, ERL, 2006");
/*  621 */     ibisWriter.println("|************************************************************************");
/*  622 */     String version = print_IBIS_Version(ibisWriter, this.ibisHead.ibisVersion);
/*  623 */     printString(ibisWriter, "[IBIS ver]", 
/*  624 */         80, version);
/*  625 */     ibisWriter.println("[File name] " + this.ibisHead.thisFileName);
/*  626 */     ibisWriter.println("[File Rev] " + this.ibisHead.fileRev);
/*  627 */     ibisWriter.println("[Date]  " + this.ibisHead.date);
/*  628 */     if (!this.ibisHead.source.equals(""))
/*  629 */       printString(ibisWriter, "[Source]", 
/*  630 */           80, this.ibisHead.source); 
/*  631 */     if (!this.ibisHead.notes.equals(""))
/*  632 */       printString(ibisWriter, "[Notes]", 
/*  633 */           80, this.ibisHead.notes); 
/*  634 */     if (!this.ibisHead.disclaimer.equals(""))
/*  635 */       printString(ibisWriter, "[Disclaimer]", 
/*  636 */           80, this.ibisHead.disclaimer); 
/*  637 */     if (this.ibisHead.ibisVersion != ConstantStuff.VERSION_ONE_ONE && 
/*  638 */       !this.ibisHead.copyright.equals("")) {
/*  639 */       printString(ibisWriter, "[Copyright]", 
/*  640 */           80, this.ibisHead.copyright);
/*      */     }
/*      */ 
/*      */ 
/*      */ 
/*      */     
/*  646 */     componentList compListForPrint = new componentList();
/*  647 */     this.ibisHead.cList.gototop(); int i1;
/*  648 */     for (i1 = 0; i1 < this.ibisHead.cList.count; i1++) {
/*      */       
/*  650 */       tempComponent2 = this.ibisHead.cList.current;
/*  651 */       this.ibisHead.cList.next();
/*  652 */       compListForPrint.add(tempComponent2);
/*      */     } 
/*      */ 
/*      */     
/*  656 */     compListForPrint.gototop();
/*  657 */     for (i1 = 0; i1 < compListForPrint.count; i1++) {
/*      */       
/*  659 */       tempComponent2 = compListForPrint.current;
/*  660 */       printComponent(ibisWriter, tempComponent2, this.ibisHead.ibisVersion);
/*  661 */       compListForPrint.next();
/*      */     } 
/*  663 */     ibisWriter.println("[End]");
/*      */   }
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */   
/*      */   String print_IBIS_Version(PrintWriter ibisWriter, int ibisVersion) {
/*  671 */     String s = "";
/*  672 */     if (ibisVersion == ConstantStuff.VERSION_ONE_ZERO) {
/*  673 */       s = "1.0";
/*  674 */     } else if (ibisVersion == ConstantStuff.VERSION_ONE_ONE) {
/*  675 */       s = "1.1";
/*  676 */     }  if (ibisVersion == ConstantStuff.VERSION_TWO_ZERO) {
/*  677 */       s = "2.0";
/*  678 */     } else if (ibisVersion == ConstantStuff.VERSION_TWO_ONE) {
/*  679 */       s = "2.1";
/*  680 */     } else if (ibisVersion == ConstantStuff.VERSION_THREE_TWO) {
/*  681 */       s = "3.2";
/*      */     } else {
/*  683 */       s = "unknown";
/*  684 */     }  return s;
/*      */   }
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */   
/*      */   void printComponent(PrintWriter ibisWriter, ibisComponent component, int ibisVersion) {
/*  694 */     ibisModel tempModel = null;
/*  695 */     ibisPin tempPin = null;
/*  696 */     ibisSeriesPin tempSeriesPin = null;
/*  697 */     seriesSwitchGroup tempSeriesSwitchGp = null;
/*  698 */     ibisPinMap tempPinMap = null;
/*  699 */     ibisDiffPin tempDiffPin = null;
/*      */     
/*  701 */     printString(ibisWriter, "|", 80, "");
/*      */ 
/*      */     
/*  704 */     printHeader(ibisWriter, component.component, "Component");
/*  705 */     printString(ibisWriter, "[Component]", 80, component.component);
/*  706 */     printString(ibisWriter, "[Manufacturer]", 80, component.manufacturer);
/*      */ 
/*      */ 
/*      */     
/*  710 */     printString(ibisWriter, "[Package]", 80, "");
/*  711 */     printTypMinMaxHeader(ibisWriter);
/*      */     
/*  713 */     String s = Get_TypMinMax_as_String(component.pinParasitics.R_pkg, "");
/*  714 */     printString(ibisWriter, "R_pkg", 80, s);
/*  715 */     s = Get_TypMinMax_as_String(component.pinParasitics.L_pkg, "H");
/*  716 */     printString(ibisWriter, "L_pkg", 80, s);
/*      */     
/*  718 */     s = Get_TypMinMax_as_String(component.pinParasitics.C_pkg, "F");
/*  719 */     printString(ibisWriter, "C_pkg", 80, s);
/*      */     
/*  721 */     printString(ibisWriter, "|", 80, "");
/*      */ 
/*      */ 
/*      */ 
/*      */     
/*  726 */     component.pList.gototop();
/*  727 */     if (component.pList != null) {
/*      */       
/*  729 */       ibisWriter.println("[Pin]  signal_name          model_name           R_pin     L_pin     C_pin");
/*  730 */       for (int i = 0; i < component.pList.count; i++) {
/*      */         
/*  732 */         tempPin = component.pList.current;
/*  733 */         printPin(ibisWriter, tempPin);
/*  734 */         component.pList.next();
/*      */       } 
/*  736 */       printString(ibisWriter, "|", 80, "");
/*      */     } 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */     
/*  743 */     if (ibisVersion != ConstantStuff.VERSION_ONE_ONE && component.hasPinMapping) {
/*      */       
/*  745 */       component.pmList.gototop();
/*  746 */       ibisWriter.println("[Pin Mapping]  pulldown_ref    pullup_ref      gnd_clamp_ref   power_clamp_ref");
/*  747 */       printString(ibisWriter, "|", 80, "");
/*  748 */       for (int i = 0; i < component.pmList.count; i++) {
/*      */         
/*  750 */         tempPinMap = component.pmList.current;
/*  751 */         printPinMap(ibisWriter, tempPinMap);
/*  752 */         component.pmList.next();
/*      */       } 
/*  754 */       printString(ibisWriter, "|", 80, "");
/*      */     } 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */     
/*  761 */     if (ibisVersion != ConstantStuff.VERSION_ONE_ONE && component.dpList != null) {
/*      */       
/*  763 */       component.dpList.gototop();
/*  764 */       if (component.dpList.count != 0)
/*  765 */         ibisWriter.println("[Diff pin]  inv_pin  vdiff  tdelay_typ  tdelay_min  tdelay_max"); 
/*  766 */       printString(ibisWriter, "|", 80, "");
/*  767 */       for (int i = 0; i < component.dpList.count; i++) {
/*      */         
/*  769 */         tempDiffPin = component.dpList.current;
/*  770 */         printDiffPin(ibisWriter, tempDiffPin);
/*  771 */         component.dpList.next();
/*      */       } 
/*  773 */       printString(ibisWriter, "|", 80, "");
/*      */     } 
/*      */ 
/*      */ 
/*      */ 
/*      */     
/*  779 */     if (ibisVersion != ConstantStuff.VERSION_ONE_ONE && component.spList != null) {
/*      */       
/*  781 */       component.spList.gototop();
/*  782 */       if (component.spList.count != 0)
/*  783 */         ibisWriter.println("[Series Pin Mapping]  pin_2        model_name        function_table_group"); 
/*  784 */       for (int i = 0; i < component.spList.count; i++) {
/*      */         
/*  786 */         tempSeriesPin = component.spList.current;
/*  787 */         printSeriesPin(ibisWriter, tempSeriesPin);
/*  788 */         component.spList.next();
/*      */       } 
/*  790 */       printString(ibisWriter, "|", 80, "");
/*      */     } 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */     
/*  797 */     if (component.ssgList != null) {
/*      */       
/*  799 */       seriesSwitchGpList ssgListForPrint = new seriesSwitchGpList();
/*  800 */       component.ssgList.gototop();
/*  801 */       for (int j = 0; j < component.ssgList.count; j++) {
/*      */         
/*  803 */         tempSeriesSwitchGp = component.ssgList.current;
/*  804 */         component.ssgList.next();
/*  805 */         ssgListForPrint.add(tempSeriesSwitchGp);
/*      */       } 
/*      */       
/*  808 */       tempSeriesSwitchGp = new seriesSwitchGroup();
/*      */       
/*  810 */       if (component.ssgList.count != 0)
/*  811 */         ibisWriter.println("[Series Switch Groups]"); 
/*  812 */       for (int i = 0; i < ssgListForPrint.count; i++) {
/*      */         
/*  814 */         tempSeriesSwitchGp = ssgListForPrint.current;
/*  815 */         printSeriesSwitchGp(ibisWriter, tempSeriesSwitchGp);
/*  816 */         ssgListForPrint.next();
/*      */       } 
/*  818 */       printString(ibisWriter, "|", 80, "");
/*      */     } 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */     
/*  825 */     component.mList.gototop();
/*      */     
/*  827 */     for (int i1 = 0; i1 < component.mList.count; i1++) {
/*      */       
/*  829 */       tempModel = component.mList.current;
/*  830 */       if (tempModel.noModel == 0)
/*      */       {
/*  832 */         printModel(ibisWriter, tempModel, this.ibisHead.ibisVersion);
/*      */       }
/*  834 */       component.mList.next();
/*      */     } 
/*  836 */     printString(ibisWriter, "|End [Component]", 80, "");
/*      */   }
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */   
/*      */   void printDiffPin(PrintWriter ibisWriter, ibisDiffPin diffPin) {
/*  847 */     String tempBuf = diffPin.pinName;
/*  848 */     tempBuf = spaceFill(tempBuf, 12 - tempBuf.length());
/*  849 */     tempBuf = String.valueOf(tempBuf) + diffPin.invPin;
/*  850 */     tempBuf = spaceFill(tempBuf, 21 - tempBuf.length());
/*  851 */     String numBuf = Get_Double_as_String(diffPin.vdiff, "V");
/*  852 */     tempBuf = String.valueOf(tempBuf) + numBuf;
/*  853 */     tempBuf = spaceFill(tempBuf, 31 - tempBuf.length());
/*  854 */     numBuf = Get_Double_as_String(diffPin.tdelay_typ, "s");
/*  855 */     tempBuf = String.valueOf(tempBuf) + numBuf;
/*      */     
/*  857 */     if (!goodies.IS_NOT_USED(diffPin.tdelay_min)) {
/*      */       
/*  859 */       tempBuf = spaceFill(tempBuf, 43 - tempBuf.length());
/*  860 */       numBuf = Get_Double_as_String(diffPin.tdelay_min, "s");
/*  861 */       tempBuf = String.valueOf(tempBuf) + numBuf;
/*  862 */       tempBuf = spaceFill(tempBuf, 55 - tempBuf.length());
/*  863 */       numBuf = Get_Double_as_String(diffPin.tdelay_max, "s");
/*  864 */       tempBuf = String.valueOf(tempBuf) + numBuf;
/*      */     } 
/*  866 */     printString(ibisWriter, tempBuf, 80, "");
/*      */   }
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */   
/*      */   void printPinMap(PrintWriter ibisWriter, ibisPinMap pinMap) {
/*  876 */     String tempBuf = pinMap.pinName;
/*  877 */     tempBuf = spaceFill(tempBuf, 15 - tempBuf.length());
/*  878 */     tempBuf = String.valueOf(tempBuf) + pinMap.pulldownRef;
/*  879 */     tempBuf = spaceFill(tempBuf, 31 - tempBuf.length());
/*  880 */     tempBuf = String.valueOf(tempBuf) + pinMap.pullupRef;
/*  881 */     tempBuf = spaceFill(tempBuf, 47 - tempBuf.length());
/*  882 */     tempBuf = String.valueOf(tempBuf) + pinMap.gndClampRef;
/*  883 */     tempBuf = spaceFill(tempBuf, 63 - tempBuf.length());
/*  884 */     tempBuf = String.valueOf(tempBuf) + pinMap.powerClampRef;
/*      */     
/*  886 */     printString(ibisWriter, tempBuf, 80, "");
/*      */   }
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */   
/*      */   void printPin(PrintWriter ibisWriter, ibisPin pin) {
/*  899 */     if (pin.model != null)
/*  900 */     { if (pin.model.noModel == 1) {
/*  901 */         s = "|";
/*      */       } else {
/*  903 */         s = "";
/*      */       }  }
/*  905 */     else { s = ""; }
/*      */ 
/*      */     
/*  908 */     String s = String.valueOf(s) + pin.pinName;
/*  909 */     s = spaceFill(s, 7 - s.length());
/*  910 */     s = String.valueOf(s) + pin.signalName;
/*  911 */     s = spaceFill(s, 28 - s.length());
/*  912 */     s = String.valueOf(s) + pin.modelName;
/*  913 */     if (!goodies.IS_NOT_USED(pin.R_pin)) {
/*      */       
/*  915 */       s = spaceFill(s, 49 - s.length());
/*  916 */       String tempBuf = Get_Double_as_String(pin.R_pin, "");
/*  917 */       s = String.valueOf(s) + tempBuf;
/*  918 */       s = spaceFill(s, 59 - s.length());
/*  919 */       tempBuf = Get_Double_as_String(pin.L_pin, "H");
/*  920 */       s = String.valueOf(s) + tempBuf;
/*  921 */       s = spaceFill(s, 69 - s.length());
/*  922 */       tempBuf = Get_Double_as_String(pin.C_pin, "F");
/*  923 */       s = String.valueOf(s) + tempBuf;
/*      */     } 
/*  925 */     printString(ibisWriter, s, 80, "");
/*      */   }
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */   
/*      */   void printSeriesPin(PrintWriter ibisWriter, ibisSeriesPin seriesPin) {
/*  933 */     String s = "";
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */     
/*  940 */     s = String.valueOf(s) + seriesPin.seriesPinName;
/*  941 */     s = spaceFill(s, 7 - s.length());
/*  942 */     s = String.valueOf(s) + seriesPin.seriesPin2name;
/*  943 */     s = spaceFill(s, 28 - s.length());
/*  944 */     s = String.valueOf(s) + seriesPin.modelName;
/*  945 */     s = spaceFill(s, 49 - s.length());
/*  946 */     if (seriesPin.fnTableGp != null) {
/*  947 */       s = String.valueOf(s) + seriesPin.fnTableGp;
/*      */     } else {
/*  949 */       s = (new StringBuilder(String.valueOf(s))).toString();
/*      */     } 
/*  951 */     printString(ibisWriter, s, 80, "");
/*      */   }
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */   
/*      */   void printSeriesSwitchGp(PrintWriter ibisWriter, seriesSwitchGroup seriesSwitchGp) {
/*  959 */     String s = "";
/*      */ 
/*      */     
/*  962 */     s = String.valueOf(s) + seriesSwitchGp.state;
/*  963 */     for (int i = 0; i < seriesSwitchGp.groupNames.length; i++)
/*      */     {
/*  965 */       s = String.valueOf(s) + " " + seriesSwitchGp.groupNames[i];
/*      */     }
/*      */     
/*  968 */     printString(ibisWriter, s, 80, "/");
/*      */   }
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */   
/*      */   void printModel(PrintWriter ibisWriter, ibisModel model, int ibisVersion) {
/*  985 */     String s = "";
/*  986 */     String numberBuffer = "";
/*      */ 
/*      */     
/*  989 */     printHeader(ibisWriter, model.modelName, "Model");
/*  990 */     printString(ibisWriter, "[Model]", 80, model.modelName);
/*      */ 
/*      */     
/*  993 */     s = getModelTypeAsString(model.modelType);
/*  994 */     printString(ibisWriter, "Model_type", 80, s);
/*      */ 
/*      */     
/*  997 */     if (model.polarity == ConstantStuff.MODEL_POLARITY_NON_INVERTING) {
/*  998 */       s = "Non-Inverting";
/*  999 */     } else if (model.polarity == ConstantStuff.MODEL_POLARITY_INVERTING) {
/* 1000 */       s = "Inverting";
/* 1001 */     } else if (model.polarity == 0) {
/* 1002 */       s = "";
/*      */     } 
/* 1004 */     if (!s.equals("")) {
/* 1005 */       printString(ibisWriter, "Polarity      ", 80, s);
/*      */     }
/*      */ 
/*      */     
/* 1009 */     if (model.enable == ConstantStuff.MODEL_ENABLE_ACTIVE_HIGH) {
/* 1010 */       s = "Active-High";
/* 1011 */     } else if (model.enable == ConstantStuff.MODEL_ENABLE_ACTIVE_LOW) {
/* 1012 */       s = "Active-Low";
/* 1013 */     } else if (model.enable == 0) {
/* 1014 */       s = "";
/*      */     } 
/* 1016 */     if (!s.equals("")) {
/* 1017 */       printString(ibisWriter, "Enable       ", 80, s);
/*      */     }
/*      */     
/* 1020 */     if (!goodies.IS_USE_NA(model.Vinl)) {
/*      */       
/* 1022 */       s = Get_Double_as_String(model.Vinl, "V");
/* 1023 */       printString(ibisWriter, "Vinl = ", 80, s);
/*      */     } 
/*      */     
/* 1026 */     if (!goodies.IS_USE_NA(model.Vinh)) {
/*      */       
/* 1028 */       s = Get_Double_as_String(model.Vinh, "V");
/* 1029 */       printString(ibisWriter, "Vinh = ", 80, s);
/*      */     } 
/*      */     
/* 1032 */     if (ibisVersion != ConstantStuff.VERSION_ONE_ONE && 
/* 1033 */       !goodies.IS_USE_NA(model.Vmeas)) {
/*      */       
/* 1035 */       s = Get_Double_as_String(model.Vmeas, "V");
/* 1036 */       printString(ibisWriter, "Vmeas = ", 80, s);
/*      */     } 
/*      */     
/* 1039 */     if (ibisVersion != ConstantStuff.VERSION_ONE_ONE && 
/* 1040 */       !goodies.IS_USE_NA(model.Cref)) {
/*      */       
/* 1042 */       s = Get_Double_as_String(model.Cref, "F");
/* 1043 */       printString(ibisWriter, "Cref = ", 80, s);
/*      */     } 
/* 1045 */     if (ibisVersion != ConstantStuff.VERSION_ONE_ONE && 
/* 1046 */       !goodies.IS_USE_NA(model.Rref)) {
/*      */       
/* 1048 */       s = Get_Double_as_String(model.Rref, "");
/* 1049 */       printString(ibisWriter, "Rref = ", 80, s);
/*      */     } 
/* 1051 */     if (ibisVersion != ConstantStuff.VERSION_ONE_ONE && 
/* 1052 */       !goodies.IS_USE_NA(model.Vref)) {
/*      */       
/* 1054 */       s = Get_Double_as_String(model.Vref, "V");
/* 1055 */       printString(ibisWriter, "Vref = ", 80, s);
/*      */     } 
/*      */     
/* 1058 */     s = Get_TypMinMax_as_String(model.c_comp, "F");
/* 1059 */     printString(ibisWriter, "C_comp", 80, s);
/*      */     
/* 1061 */     if (ibisVersion != ConstantStuff.VERSION_ONE_ONE && 
/* 1062 */       !goodies.IS_USE_NA(model.Rgnd.typ)) {
/*      */       
/* 1064 */       s = Get_TypMinMax_as_String(model.Rgnd, "");
/* 1065 */       printString(ibisWriter, "[Rgnd]      ", 80, s);
/*      */     } 
/* 1067 */     if (ibisVersion != ConstantStuff.VERSION_ONE_ONE && 
/* 1068 */       !goodies.IS_USE_NA(model.Rpower.typ)) {
/*      */       
/* 1070 */       s = Get_TypMinMax_as_String(model.Rpower, "");
/* 1071 */       printString(ibisWriter, "[Rpower]     ", 80, s);
/*      */     } 
/* 1073 */     if (ibisVersion != ConstantStuff.VERSION_ONE_ONE && 
/* 1074 */       !goodies.IS_USE_NA(model.Rac.typ)) {
/*      */       
/* 1076 */       s = Get_TypMinMax_as_String(model.Rac, "");
/* 1077 */       printString(ibisWriter, "[Rac]     ", 80, s);
/*      */     } 
/* 1079 */     if (ibisVersion != ConstantStuff.VERSION_ONE_ONE && 
/* 1080 */       !goodies.IS_USE_NA(model.Cac.typ)) {
/*      */       
/* 1082 */       s = Get_TypMinMax_as_String(model.Cac, "F");
/* 1083 */       printString(ibisWriter, "[Cac]     ", 80, s);
/*      */     } 
/* 1085 */     printString(ibisWriter, "|", 80, "");
/* 1086 */     printString(ibisWriter, "|", 80, "");
/*      */     
/* 1088 */     if (ibisVersion != ConstantStuff.VERSION_ONE_ONE && 
/* 1089 */       !goodies.IS_USE_NA(model.tempRange.typ)) {
/*      */       
/* 1091 */       s = Get_TypMinMax_as_String(model.tempRange, "");
/* 1092 */       printString(ibisWriter, "[Temperature Range]", 80, s);
/*      */     } 
/*      */     
/* 1095 */     if (ibisVersion != ConstantStuff.VERSION_ONE_ONE && 
/* 1096 */       !goodies.IS_USE_NA(model.voltageRange.typ)) {
/*      */       
/* 1098 */       s = Get_TypMinMax_as_String(model.voltageRange, "V");
/* 1099 */       printString(ibisWriter, "[Voltage Range]     ", 
/* 1100 */           80, s);
/*      */     } 
/*      */     
/* 1103 */     if (ibisVersion != ConstantStuff.VERSION_ONE_ONE && 
/* 1104 */       !goodies.IS_USE_NA(model.pullupRef.typ)) {
/*      */       
/* 1106 */       s = Get_TypMinMax_as_String(model.pullupRef, "V");
/* 1107 */       printString(ibisWriter, "[Pullup Reference]     ", 
/* 1108 */           80, s);
/*      */     } 
/*      */     
/* 1111 */     if (ibisVersion != ConstantStuff.VERSION_ONE_ONE && 
/* 1112 */       !goodies.IS_USE_NA(model.pulldownRef.typ)) {
/*      */       
/* 1114 */       s = Get_TypMinMax_as_String(model.pulldownRef, "V");
/* 1115 */       printString(ibisWriter, "[Pulldown Reference]     ", 
/* 1116 */           80, s);
/*      */     } 
/*      */     
/* 1119 */     if (ibisVersion != ConstantStuff.VERSION_ONE_ONE && 
/* 1120 */       !goodies.IS_USE_NA(model.powerClampRef.typ)) {
/*      */       
/* 1122 */       s = Get_TypMinMax_as_String(model.powerClampRef, "V");
/* 1123 */       printString(ibisWriter, "[POWER Clamp Reference]     ", 
/* 1124 */           80, s);
/*      */     } 
/*      */     
/* 1127 */     if (ibisVersion != ConstantStuff.VERSION_ONE_ONE && 
/* 1128 */       !goodies.IS_USE_NA(model.gndClampRef.typ)) {
/*      */       
/* 1130 */       s = Get_TypMinMax_as_String(model.gndClampRef, "V");
/* 1131 */       printString(ibisWriter, "[GND Clamp Reference]     ", 
/* 1132 */           80, s);
/*      */     } 
/*      */     
/* 1135 */     if (model.pulldown != null) {
/*      */       
/* 1137 */       printString(ibisWriter, "[Pulldown]", 80, "");
/* 1138 */       print_VItable(ibisWriter, model.pulldown);
/*      */     } 
/*      */     
/* 1141 */     if (model.pullup != null) {
/*      */       
/* 1143 */       printString(ibisWriter, "[Pullup]", 80, "");
/* 1144 */       print_VItable(ibisWriter, model.pullup);
/*      */     } 
/* 1146 */     if (model.gnd_clamp != null) {
/*      */       
/* 1148 */       printString(ibisWriter, "[GND_clamp]", 80, "");
/* 1149 */       printClampTable(ibisWriter, model.gnd_clamp, model.clampTol);
/*      */     } 
/* 1151 */     if (model.power_clamp != null) {
/*      */       
/* 1153 */       printString(ibisWriter, "[POWER_clamp]", 80, "");
/* 1154 */       printClampTable(ibisWriter, model.power_clamp, model.clampTol);
/*      */     } 
/* 1156 */     if (!goodies.IS_USE_NA(model.ramp.dv_r.typ))
/*      */     {
/* 1158 */       printRamp(ibisWriter, model.ramp, model.Rload);
/*      */     }
/*      */ 
/*      */     
/* 1162 */     if (ibisVersion != ConstantStuff.VERSION_ONE_ONE) {
/*      */       
/* 1164 */       VdsList VdsList1 = model.seriesModel.series_MOSFET.vdslist;
/* 1165 */       VdsList1.gototop();
/* 1166 */       if (model.seriesModel.OnState)
/*      */       {
/* 1168 */         printString(ibisWriter, "[On]", 80, "");
/*      */       }
/* 1170 */       for (int i = 0; i < VdsList1.count; i++) {
/*      */         
/* 1172 */         ibisVItable seriesVITable = VdsList1.current.seriesVITable;
/*      */         
/* 1174 */         printString(ibisWriter, "[series MOSFET]", 80, "");
/* 1175 */         numberBuffer = Get_Double_as_String(VdsList1.current.V, "");
/* 1176 */         printString(ibisWriter, "Vds = ", 80, numberBuffer);
/* 1177 */         print_VItable(ibisWriter, VdsList1.current.seriesVITable);
/*      */         
/* 1179 */         VdsList1.next();
/*      */       } 
/* 1181 */       if (model.seriesModel.OffState)
/*      */       {
/* 1183 */         printString(ibisWriter, "[Off]", 80, "");
/*      */       }
/* 1185 */       if (ibisVersion != ConstantStuff.VERSION_ONE_ONE && 
/* 1186 */         !goodies.IS_USE_NA(model.seriesModel.RSeriesOff.typ)) {
/*      */         
/* 1188 */         s = Get_TypMinMax_as_String(model.seriesModel.RSeriesOff, "");
/* 1189 */         printString(ibisWriter, "[R Series]     ", 80, s);
/*      */       } 
/*      */     } 
/*      */ 
/*      */ 
/*      */     
/* 1195 */     if (ibisVersion != ConstantStuff.VERSION_ONE_ONE) {
/*      */       
/* 1197 */       waveTableList risingWaveL = model.risingWaveList;
/* 1198 */       waveTableList fallingWaveL = model.fallingWaveList;
/*      */       
/* 1200 */       risingWaveL.gototop();
/* 1201 */       fallingWaveL.gototop();
/*      */       int i;
/* 1203 */       for (i = 0; i < risingWaveL.count; i++) {
/*      */         
/* 1205 */         ibisWaveTable risingWave = risingWaveL.current;
/* 1206 */         printString(ibisWriter, "[Rising Waveform]", 80, "");
/* 1207 */         numberBuffer = Get_Double_as_String(risingWave.R_fixture, "");
/* 1208 */         printString(ibisWriter, "R_fixture=", 80, numberBuffer);
/* 1209 */         numberBuffer = Get_Double_as_String(risingWave.V_fixture, "");
/* 1210 */         printString(ibisWriter, "V_fixture=", 80, numberBuffer);
/*      */         
/* 1212 */         if (!goodies.IS_USE_NA(risingWave.V_fixture_min)) {
/*      */           
/* 1214 */           numberBuffer = Get_Double_as_String(risingWave.V_fixture_min, "");
/* 1215 */           printString(ibisWriter, "V_fixture_min=", 80, numberBuffer);
/*      */         } 
/* 1217 */         if (!goodies.IS_USE_NA(risingWave.V_fixture_max)) {
/*      */           
/* 1219 */           numberBuffer = Get_Double_as_String(risingWave.V_fixture_max, "");
/* 1220 */           printString(ibisWriter, "V_fixture_max=", 80, numberBuffer);
/*      */         } 
/* 1222 */         if (!goodies.IS_USE_NA(risingWave.L_fixture)) {
/*      */           
/* 1224 */           numberBuffer = Get_Double_as_String(risingWave.L_fixture, "H");
/* 1225 */           printString(ibisWriter, "L_fixture=", 80, numberBuffer);
/*      */         } 
/* 1227 */         if (!goodies.IS_USE_NA(risingWave.C_fixture)) {
/*      */           
/* 1229 */           numberBuffer = Get_Double_as_String(risingWave.C_fixture, "F");
/* 1230 */           printString(ibisWriter, "C_fixture=", 80, numberBuffer);
/*      */         } 
/* 1232 */         if (!goodies.IS_USE_NA(risingWave.R_dut)) {
/*      */           
/* 1234 */           numberBuffer = Get_Double_as_String(risingWave.R_dut, "");
/* 1235 */           printString(ibisWriter, "R_dut=", 80, numberBuffer);
/*      */         } 
/* 1237 */         if (!goodies.IS_USE_NA(risingWave.L_dut)) {
/*      */           
/* 1239 */           numberBuffer = Get_Double_as_String(risingWave.L_dut, "L");
/* 1240 */           printString(ibisWriter, "L_dut=", 80, numberBuffer);
/*      */         } 
/* 1242 */         if (!goodies.IS_USE_NA(risingWave.C_dut)) {
/*      */           
/* 1244 */           numberBuffer = Get_Double_as_String(risingWave.L_dut, "F");
/* 1245 */           printString(ibisWriter, "C_dut=", 80, numberBuffer);
/*      */         } 
/*      */         
/* 1248 */         printWaveTable(ibisWriter, risingWave);
/* 1249 */         risingWaveL.next();
/*      */       } 
/* 1251 */       for (i = 0; i < fallingWaveL.count; i++) {
/*      */         
/* 1253 */         ibisWaveTable fallingWave = fallingWaveL.current;
/* 1254 */         printString(ibisWriter, "[Falling Waveform]", 80, "");
/* 1255 */         numberBuffer = Get_Double_as_String(fallingWave.R_fixture, "");
/* 1256 */         printString(ibisWriter, "R_fixture=", 80, numberBuffer);
/* 1257 */         numberBuffer = Get_Double_as_String(fallingWave.V_fixture, "");
/* 1258 */         printString(ibisWriter, "V_fixture=", 80, numberBuffer);
/*      */         
/* 1260 */         if (!goodies.IS_USE_NA(fallingWave.V_fixture_min)) {
/*      */           
/* 1262 */           numberBuffer = Get_Double_as_String(fallingWave.V_fixture_min, "");
/* 1263 */           printString(ibisWriter, "V_fixture_min=", 80, numberBuffer);
/*      */         } 
/* 1265 */         if (!goodies.IS_USE_NA(fallingWave.V_fixture_max)) {
/*      */           
/* 1267 */           numberBuffer = Get_Double_as_String(fallingWave.V_fixture_max, "");
/* 1268 */           printString(ibisWriter, "V_fixture_max=", 80, numberBuffer);
/*      */         } 
/* 1270 */         if (!goodies.IS_USE_NA(fallingWave.L_fixture)) {
/*      */           
/* 1272 */           numberBuffer = Get_Double_as_String(fallingWave.L_fixture, "H");
/* 1273 */           printString(ibisWriter, "L_fixture=", 80, numberBuffer);
/*      */         } 
/* 1275 */         if (!goodies.IS_USE_NA(fallingWave.C_fixture)) {
/*      */           
/* 1277 */           numberBuffer = Get_Double_as_String(fallingWave.C_fixture, "F");
/* 1278 */           printString(ibisWriter, "C_fixture=", 80, numberBuffer);
/*      */         } 
/* 1280 */         if (!goodies.IS_USE_NA(fallingWave.R_dut)) {
/*      */           
/* 1282 */           numberBuffer = Get_Double_as_String(fallingWave.R_dut, "");
/* 1283 */           printString(ibisWriter, "R_dut=", 80, numberBuffer);
/*      */         } 
/* 1285 */         if (!goodies.IS_USE_NA(fallingWave.L_dut)) {
/*      */           
/* 1287 */           numberBuffer = Get_Double_as_String(fallingWave.L_dut, "L");
/* 1288 */           printString(ibisWriter, "L_dut=", 80, numberBuffer);
/*      */         } 
/* 1290 */         if (!goodies.IS_USE_NA(fallingWave.C_dut)) {
/*      */           
/* 1292 */           numberBuffer = Get_Double_as_String(fallingWave.L_dut, "F");
/* 1293 */           printString(ibisWriter, "C_dut=", 80, numberBuffer);
/*      */         } 
/*      */         
/* 1296 */         printWaveTable(ibisWriter, fallingWave);
/* 1297 */         fallingWaveL.next();
/*      */       } 
/*      */     } 
/* 1300 */     s = "|End [Model] " + model.modelName;
/* 1301 */     printString(ibisWriter, s, 80, "");
/*      */   }
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */   
/*      */   String getModelTypeAsString(int modelType) {
/* 1311 */     String s = "";
/* 1312 */     if (modelType == ConstantStuff.MODEL_TYPE_INPUT) {
/* 1313 */       s = "Input";
/* 1314 */     } else if (modelType == ConstantStuff.MODEL_TYPE_OUTPUT) {
/* 1315 */       s = "Output";
/* 1316 */     } else if (modelType == ConstantStuff.MODEL_TYPE_3_STATE) {
/* 1317 */       s = "3-state";
/* 1318 */     } else if (modelType == ConstantStuff.MODEL_TYPE_OPEN_DRAIN) {
/* 1319 */       s = "Open_drain";
/* 1320 */     } else if (modelType == ConstantStuff.MODEL_TYPE_I_O) {
/* 1321 */       s = "I/O";
/* 1322 */     } else if (modelType == ConstantStuff.MODEL_TYPE_I_O_OPEN_DRAIN) {
/* 1323 */       s = "I/O_Open_Drain";
/* 1324 */     } else if (modelType == ConstantStuff.MODEL_TYPE_I_O_OPEN_SINK) {
/* 1325 */       s = "I/O_open_sink";
/* 1326 */     } else if (modelType == ConstantStuff.MODEL_TYPE_I_O_OPEN_SOURCE) {
/* 1327 */       s = "I/O_open_source";
/* 1328 */     } else if (modelType == ConstantStuff.MODEL_TYPE_INPUT_ECL) {
/* 1329 */       s = "Input_ECL";
/* 1330 */     } else if (modelType == ConstantStuff.MODEL_TYPE_I_O_ECL) {
/* 1331 */       s = "I/O_ECL";
/* 1332 */     } else if (modelType == ConstantStuff.MODEL_TYPE_TERMINATOR) {
/* 1333 */       s = "Terminator";
/* 1334 */     } else if (modelType == ConstantStuff.MODEL_TYPE_OPEN_SINK) {
/* 1335 */       s = "Open_sink";
/* 1336 */     } else if (modelType == ConstantStuff.MODEL_TYPE_OPEN_SOURCE) {
/* 1337 */       s = "Open_Source";
/* 1338 */     } else if (modelType == ConstantStuff.MODEL_TYPE_OUTPUT_ECL) {
/* 1339 */       s = "Output_ECL";
/*      */     }
/* 1341 */     else if (modelType == ConstantStuff.MODEL_TYPE_SERIES) {
/* 1342 */       s = "Series";
/* 1343 */     } else if (modelType == ConstantStuff.MODEL_TYPE_SERIES_SWITCH) {
/* 1344 */       s = "Series_switch";
/*      */     }
/* 1346 */     else if (modelType == 0) {
/* 1347 */       s = "??undefined??";
/*      */     } else {
/* 1349 */       s = "??undefined??";
/*      */     } 
/* 1351 */     return s;
/*      */   }
/*      */ 
/*      */ 
/*      */ 
/*      */   
/*      */   int print_VItable(PrintWriter ibisWriter, ibisVItable VItable) {
/* 1358 */     int size = VItable.size;
/* 1359 */     String s = "";
/* 1360 */     String s1 = "";
/* 1361 */     if (VItable == null)
/* 1362 */       return 1; 
/* 1363 */     if (VItable.VIs == null) {
/* 1364 */       return 1;
/*      */     }
/*      */ 
/*      */     
/* 1368 */     printString(ibisWriter, "|Voltage", 80, 
/* 1369 */         "  I(typ)              I(min)              I(max)");
/* 1370 */     printString(ibisWriter, "|", 80, "");
/*      */     
/* 1372 */     for (int i = 0; i < size; i++) {
/*      */       
/* 1374 */       s = Get_TypMinMax_as_String((VItable.VIs[i]).i, "A");
/* 1375 */       BigDecimal bd = new BigDecimal((VItable.VIs[i]).v);
/* 1376 */       s1 = "  " + bd.setScale(2, 4);
/*      */       
/* 1378 */       printString(ibisWriter, s1, 80, s);
/*      */     } 
/*      */     
/* 1381 */     printString(ibisWriter, "|", 80, "");
/*      */     
/* 1383 */     return 0;
/*      */   }
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */   
/*      */   int printClampTable(PrintWriter ibisWriter, ibisVItable clampTable, double clampTol) {
/* 1392 */     int size = clampTable.size;
/* 1393 */     String s1 = "";
/* 1394 */     String s = "";
/*      */     
/* 1396 */     int lastPrinted = 0;
/*      */ 
/*      */     
/* 1399 */     if (clampTable == null)
/* 1400 */       return 1; 
/* 1401 */     if (clampTable.VIs == null) {
/* 1402 */       return 1;
/*      */     }
/* 1404 */     printString(ibisWriter, "|Voltage", 80, 
/* 1405 */         "  I(typ)              I(min)              I(max)");
/* 1406 */     printString(ibisWriter, "|", 80, "");
/*      */     
/* 1408 */     BigDecimal bd = new BigDecimal((clampTable.VIs[0]).v);
/* 1409 */     s1 = "  " + bd.setScale(2, 4);
/* 1410 */     ibisTypMinMax tempCurrent = (clampTable.VIs[0]).i;
/* 1411 */     if (goodies.fabs(tempCurrent.typ) < clampTol)
/* 1412 */       tempCurrent.typ = 0.0D; 
/* 1413 */     if (goodies.fabs(tempCurrent.min) < clampTol)
/* 1414 */       tempCurrent.min = 0.0D; 
/* 1415 */     if (goodies.fabs(tempCurrent.max) < clampTol) {
/* 1416 */       tempCurrent.max = 0.0D;
/*      */     }
/* 1418 */     s = Get_TypMinMax_as_String(tempCurrent, "A");
/* 1419 */     printString(ibisWriter, s1, 80, s);
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */     
/* 1426 */     for (int i = 1; i < size - 1; i++) {
/*      */       
/* 1428 */       tempCurrent = (clampTable.VIs[i]).i;
/* 1429 */       if (goodies.fabs(tempCurrent.typ) > clampTol || 
/* 1430 */         goodies.fabs(tempCurrent.min) > clampTol || 
/* 1431 */         goodies.fabs(tempCurrent.max) > clampTol) {
/*      */         
/* 1433 */         if (i > lastPrinted + 1) {
/*      */           
/* 1435 */           bd = new BigDecimal((clampTable.VIs[i - 1]).v);
/* 1436 */           s1 = "  " + bd.setScale(2, 4);
/* 1437 */           tempCurrent.typ = 0.0D;
/* 1438 */           tempCurrent.min = 0.0D;
/* 1439 */           tempCurrent.max = 0.0D;
/* 1440 */           s = Get_TypMinMax_as_String(tempCurrent, "A");
/* 1441 */           printString(ibisWriter, s1, 80, s);
/* 1442 */           tempCurrent = (clampTable.VIs[i]).i;
/*      */         } 
/* 1444 */         bd = new BigDecimal((clampTable.VIs[i]).v);
/* 1445 */         s1 = "  " + bd.setScale(2, 4);
/*      */         
/* 1447 */         if (goodies.fabs(tempCurrent.typ) < clampTol)
/* 1448 */           tempCurrent.typ = 0.0D; 
/* 1449 */         if (goodies.fabs(tempCurrent.min) < clampTol)
/* 1450 */           tempCurrent.min = 0.0D; 
/* 1451 */         if (goodies.fabs(tempCurrent.max) < clampTol) {
/* 1452 */           tempCurrent.max = 0.0D;
/*      */         }
/* 1454 */         s = Get_TypMinMax_as_String(tempCurrent, "A");
/* 1455 */         printString(ibisWriter, s1, 80, s);
/* 1456 */         lastPrinted = i;
/*      */       
/*      */       }
/* 1459 */       else if (i != 1 && i == lastPrinted + 1) {
/*      */         
/* 1461 */         bd = new BigDecimal((clampTable.VIs[i]).v);
/* 1462 */         s1 = "  " + bd.setScale(2, 4);
/* 1463 */         tempCurrent.typ = 0.0D;
/* 1464 */         tempCurrent.min = 0.0D;
/* 1465 */         tempCurrent.max = 0.0D;
/* 1466 */         s = Get_TypMinMax_as_String(tempCurrent, "A");
/* 1467 */         printString(ibisWriter, s1, 80, s);
/*      */       } 
/*      */     } 
/*      */     
/* 1471 */     bd = new BigDecimal((clampTable.VIs[size - 1]).v);
/* 1472 */     s1 = "  " + bd.setScale(2, 4);
/* 1473 */     tempCurrent = (clampTable.VIs[size - 1]).i;
/* 1474 */     if (goodies.fabs(tempCurrent.typ) < clampTol)
/* 1475 */       tempCurrent.typ = 0.0D; 
/* 1476 */     if (goodies.fabs(tempCurrent.min) < clampTol)
/* 1477 */       tempCurrent.min = 0.0D; 
/* 1478 */     if (goodies.fabs(tempCurrent.max) < clampTol) {
/* 1479 */       tempCurrent.max = 0.0D;
/*      */     }
/* 1481 */     s = Get_TypMinMax_as_String(tempCurrent, "A");
/* 1482 */     printString(ibisWriter, s1, 80, s);
/* 1483 */     printString(ibisWriter, "|", 80, "");
/* 1484 */     return 0;
/*      */   }
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */   
/*      */   int printWaveTable(PrintWriter ibisWriter, ibisWaveTable waveTable) {
/* 1493 */     int size = waveTable.size;
/*      */ 
/*      */ 
/*      */ 
/*      */     
/* 1498 */     if (waveTable == null)
/* 1499 */       return 1; 
/* 1500 */     if (waveTable.waveData == null) {
/* 1501 */       return 1;
/*      */     }
/* 1503 */     printString(ibisWriter, "|time ", 80, 
/* 1504 */         "  V(typ)              V(min)              V(max)");
/* 1505 */     printString(ibisWriter, "|", 80, "");
/*      */     
/* 1507 */     for (int i = 0; i < size; i++) {
/*      */       
/* 1509 */       String s1 = Get_Double_as_String_for_time((waveTable.waveData[i]).t, "S");
/* 1510 */       s1 = spaceFill(s1, 15 - s1.length());
/* 1511 */       String s = Get_TypMinMax_as_String((waveTable.waveData[i]).v, "V");
/* 1512 */       printString(ibisWriter, s1, 80, s);
/*      */     } 
/* 1514 */     printString(ibisWriter, "|", 80, "");
/* 1515 */     return 0;
/*      */   }
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */   
/*      */   void printRamp(PrintWriter ibisWriter, ibisRamp ramp, double rload) {
/* 1527 */     printString(ibisWriter, "[Ramp]", 80, "");
/* 1528 */     printString(ibisWriter, 
/* 1529 */         "| variable       typ                 min                 max", 
/* 1530 */         80, "");
/*      */ 
/*      */     
/* 1533 */     if (!goodies.IS_USE_NA(ramp.dv_r.typ)) {
/*      */       
/* 1535 */       s = Get_Double_as_String(ramp.dv_r.typ, "");
/* 1536 */       String str1 = Get_Double_as_String(ramp.dt_r.typ, "");
/* 1537 */       String dummyBuffer = "/" + str1;
/* 1538 */       s = String.valueOf(s) + dummyBuffer;
/*      */     } else {
/*      */       
/* 1541 */       s = "NA";
/* 1542 */     }  String s = spaceFill(s, 20 - s.length());
/*      */     
/* 1544 */     if (!goodies.IS_USE_NA(ramp.dv_r.min)) {
/*      */       
/* 1546 */       String str1 = Get_Double_as_String(ramp.dv_r.min, "");
/* 1547 */       s = String.valueOf(s) + str1;
/* 1548 */       str1 = Get_Double_as_String(ramp.dt_r.min, "");
/* 1549 */       String dummyBuffer = "/" + str1;
/* 1550 */       s = String.valueOf(s) + dummyBuffer;
/*      */     }
/*      */     else {
/*      */       
/* 1554 */       String dummyBuffer = "NA";
/* 1555 */       s = String.valueOf(s) + dummyBuffer;
/*      */     } 
/* 1557 */     s = spaceFill(s, 40 - s.length());
/*      */     
/* 1559 */     if (!goodies.IS_USE_NA(ramp.dv_r.max)) {
/*      */       
/* 1561 */       String str2 = Get_Double_as_String(ramp.dv_r.max, "");
/* 1562 */       s = String.valueOf(s) + str2;
/* 1563 */       str2 = Get_Double_as_String(ramp.dt_r.max, "");
/* 1564 */       String str1 = "/" + str2;
/* 1565 */       s = String.valueOf(s) + str1;
/*      */     }
/*      */     else {
/*      */       
/* 1569 */       String str = "NA";
/* 1570 */       s = String.valueOf(s) + str;
/*      */     } 
/* 1572 */     printString(ibisWriter, "dV/dt_r", 80, s);
/*      */ 
/*      */     
/* 1575 */     if (!goodies.IS_USE_NA(ramp.dv_f.typ)) {
/*      */       
/* 1577 */       s = Get_Double_as_String(ramp.dv_f.typ, "");
/* 1578 */       String str2 = Get_Double_as_String(ramp.dt_f.typ, "");
/* 1579 */       String str1 = "/" + str2;
/* 1580 */       s = String.valueOf(s) + str1;
/*      */     } else {
/*      */       
/* 1583 */       s = "NA";
/* 1584 */     }  s = spaceFill(s, 20 - s.length());
/*      */     
/* 1586 */     if (!goodies.IS_USE_NA(ramp.dv_f.min)) {
/*      */       
/* 1588 */       String str2 = Get_Double_as_String(ramp.dv_f.min, "");
/* 1589 */       s = String.valueOf(s) + str2;
/* 1590 */       str2 = Get_Double_as_String(ramp.dt_f.min, "");
/* 1591 */       String str1 = "/" + str2;
/* 1592 */       s = String.valueOf(s) + str1;
/*      */     }
/*      */     else {
/*      */       
/* 1596 */       String str = "NA";
/* 1597 */       s = String.valueOf(s) + str;
/*      */     } 
/* 1599 */     s = spaceFill(s, 40 - s.length());
/*      */     
/* 1601 */     if (!goodies.IS_USE_NA(ramp.dv_f.max)) {
/*      */       
/* 1603 */       String str2 = Get_Double_as_String(ramp.dv_f.max, "");
/* 1604 */       s = String.valueOf(s) + str2;
/* 1605 */       str2 = Get_Double_as_String(ramp.dt_f.max, "");
/* 1606 */       String str1 = "/" + str2;
/* 1607 */       s = String.valueOf(s) + str1;
/*      */     }
/*      */     else {
/*      */       
/* 1611 */       String str = "NA";
/* 1612 */       s = String.valueOf(s) + str;
/*      */     } 
/*      */     
/* 1615 */     printString(ibisWriter, "dV/dt_f", 80, s);
/* 1616 */     String numberBuffer = Get_Double_as_String(rload, "");
/* 1617 */     printString(ibisWriter, "R_load =", 80, numberBuffer);
/* 1618 */     printString(ibisWriter, "|", 80, "");
/*      */   }
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */   
/*      */   String spaceFill(String str, int numSpaces) {
/* 1628 */     for (int i = 0; i < numSpaces; i++)
/* 1629 */       str = String.valueOf(str) + " "; 
/* 1630 */     return str;
/*      */   }
/*      */ 
/*      */   
/*      */   String Get_TypMinMax_as_String(ibisTypMinMax TypMinMax, String trailStr) {
/* 1635 */     String dummyStr = "";
/* 1636 */     String s = "";
/*      */ 
/*      */     
/* 1639 */     s = "  " + Get_Double_as_String(TypMinMax.typ, trailStr);
/* 1640 */     int position = s.length();
/* 1641 */     s = spaceFill(s, 20 - position);
/* 1642 */     dummyStr = Get_Double_as_String(TypMinMax.min, trailStr);
/* 1643 */     s = String.valueOf(s) + dummyStr;
/* 1644 */     position = s.length();
/* 1645 */     s = spaceFill(s, 40 - position);
/* 1646 */     dummyStr = Get_Double_as_String(TypMinMax.max, trailStr);
/* 1647 */     s = String.valueOf(s) + dummyStr;
/* 1648 */     return s;
/*      */   }
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */   
/*      */   String Get_Double_as_String(double number, String trailStr) {
/* 1656 */     String s = "";
/* 1657 */     double exponent = 1.0E-15D;
/*      */     
/* 1659 */     int expFound = 0;
/*      */     
/* 1661 */     if (goodies.IS_USE_NA(number)) {
/* 1662 */       s = "NA";
/*      */     } else {
/*      */       
/* 1665 */       for (int i = 0; i < 9; i++) {
/*      */         
/* 1667 */         if (isExponent(number, exponent)) {
/*      */           
/* 1669 */           BigDecimal bd = new BigDecimal(number / exponent);
/*      */           
/* 1671 */           s = bd.setScale(4, 4) + s2iString.SIsuffixString[i] + trailStr;
/* 1672 */           expFound = 1;
/*      */           
/*      */           break;
/*      */         } 
/* 1676 */         exponent *= 1000.0D;
/*      */       } 
/* 1678 */       if (expFound == 0)
/* 1679 */         s = String.valueOf(number) + trailStr; 
/*      */     } 
/* 1681 */     return s;
/*      */   }
/*      */   
/*      */   String Get_Double_as_String_for_time(double number, String trailStr) {
/* 1685 */     String s = "";
/* 1686 */     double exponent = 1.0E-15D;
/*      */     
/* 1688 */     int expFound = 0;
/*      */     
/* 1690 */     if (goodies.IS_USE_NA(number)) {
/* 1691 */       s = "NA";
/*      */     } else {
/*      */       
/* 1694 */       for (int i = 0; i < 9; i++) {
/*      */         
/* 1696 */         if (isExponent(number, exponent)) {
/*      */           
/* 1698 */           BigDecimal bd = new BigDecimal(number / exponent);
/* 1699 */           s = bd.setScale(2, 4) + s2iString.SIsuffixString[i] + trailStr;
/* 1700 */           expFound = 1;
/*      */           
/*      */           break;
/*      */         } 
/* 1704 */         exponent *= 1000.0D;
/*      */       } 
/* 1706 */       if (expFound == 0)
/* 1707 */         s = String.valueOf(number) + trailStr; 
/*      */     } 
/* 1709 */     return s;
/*      */   }
/*      */ 
/*      */   
/*      */   boolean isExponent(double number, double expon) {
/* 1714 */     if (goodies.fabs(number / expon) >= 0.1D && goodies.fabs(number / expon) < 100.0D) {
/* 1715 */       return true;
/*      */     }
/* 1717 */     return false;
/*      */   }
/*      */ 
/*      */   
/*      */   void printTypMinMaxHeader(PrintWriter ibisWriter) {
/* 1722 */     printString(ibisWriter, "| variable       typ                 min                 max", 
/* 1723 */         80, "");
/*      */   }
/*      */ 
/*      */ 
/*      */   
/*      */   void printHeader(PrintWriter ibisWriter, String name, String heading) {
/* 1729 */     String spaceFill = " ";
/* 1730 */     int spacing = (62 - heading.length() + name.length()) / 2;
/* 1731 */     for (int i2 = 0; i2 < spacing; i2++) {
/* 1732 */       spaceFill = String.valueOf(spaceFill) + " ";
/*      */     }
/* 1734 */     ibisWriter.println("|************************************************************************");
/* 1735 */     printString(ibisWriter, "|", 80, String.valueOf(spaceFill) + heading + " " + name);
/* 1736 */     ibisWriter.println("|************************************************************************");
/* 1737 */     printString(ibisWriter, "|", 80, "");
/*      */   }
/*      */ 
/*      */ 
/*      */ 
/*      */ 
/*      */   
/*      */   void printString(PrintWriter ibisWriter, String indent, int width, String string) {
/* 1745 */     int j = 1;
/* 1746 */     StringTokenizer st = new StringTokenizer(string);
/*      */     
/* 1748 */     int cnt = st.countTokens();
/* 1749 */     int totalLength = 0;
/* 1750 */     String nextTok = "";
/*      */     
/* 1752 */     String newString = indent;
/* 1753 */     if (indent.length() < 8) {
/*      */       
/* 1755 */       newString = String.valueOf(newString) + " " + " ";
/* 1756 */       if (string.length() > width) {
/*      */         
/* 1758 */         for (int i = 0; i < cnt; i++) {
/*      */           
/* 1760 */           nextTok = st.nextToken();
/* 1761 */           newString = String.valueOf(newString) + " " + nextTok;
/*      */           
/* 1763 */           if (totalLength > 1024) {
/*      */             break;
/*      */           }
/* 1766 */           totalLength += nextTok.length();
/*      */           
/* 1768 */           if (newString.length() >= j * width) {
/*      */             
/* 1770 */             newString = String.valueOf(newString) + "\n  ";
/* 1771 */             j++;
/*      */           } 
/*      */         } 
/*      */       } else {
/*      */         
/* 1776 */         newString = String.valueOf(newString) + string;
/*      */       } 
/*      */     } else {
/*      */       
/* 1780 */       newString = String.valueOf(newString) + " ";
/* 1781 */       if (string.length() > width) {
/*      */         
/* 1783 */         for (int i = 0; i < cnt; i++) {
/*      */           
/* 1785 */           nextTok = st.nextToken();
/* 1786 */           newString = String.valueOf(newString) + " " + nextTok;
/* 1787 */           totalLength += nextTok.length();
/* 1788 */           if (totalLength > 1024) {
/*      */             break;
/*      */           }
/* 1791 */           if (newString.length() + 2 * j * 8 >= j * width) {
/*      */             
/* 1793 */             newString = String.valueOf(newString) + "\n  ";
/* 1794 */             j++;
/*      */           } 
/*      */         } 
/*      */       } else {
/*      */         
/* 1799 */         newString = String.valueOf(newString) + string;
/*      */       } 
/* 1801 */     }  ibisWriter.println(newString);
/*      */   }
/*      */ }


/* Location:              D:\IBIS\s2ibis3_v1_1\java\!\s2ibisPrint.class
 * Java compiler version: 8 (52.0)
 * JD-Core Version:       1.1.3
 */