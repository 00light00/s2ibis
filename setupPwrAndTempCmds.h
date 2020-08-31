/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ class setupPwrAndTempCmds
/*     */ {
/*     */   String powerBuffer;
/*     */   String temperatureBuffer;
/*     */   
/*     */   public void setupPwrAndTempCmds(int curveType, int spiceType, ibisPin powerPin, ibisPin gndPin, ibisPin powerClampPin, ibisPin gndClampPin, double Vcc, double Gnd, double VccClamp, double GndClamp, double temperature) {
/*  99 */     if (curveType == 2 || 
/* 100 */       curveType == 3) {
/*     */       
/* 102 */       if (powerClampPin != null) {
/*     */ 
/*     */ 
/*     */         
/* 106 */         if (spiceType == 4) {
/* 107 */           this.powerBuffer = "VCLMPS2I " + powerClampPin.spiceNodeName + " 0 " + 
/* 108 */             " vsource type=dc dc=" + VccClamp + "\n";
/*     */         } else {
/* 110 */           this.powerBuffer = "VCLMPS2I " + powerClampPin.spiceNodeName + " 0 " + 
/* 111 */             " DC " + VccClamp + "\n";
/*     */         } 
/* 113 */         if (powerPin != null && 
/* 114 */           !powerClampPin.spiceNodeName.equalsIgnoreCase(powerPin.spiceNodeName)) {
/*     */           String dummyBuffer;
/* 116 */           if (spiceType == 4) {
/* 117 */             dummyBuffer = "VCCS2I " + powerPin.spiceNodeName + " 0 " + 
/* 118 */               " vsource type=dc dc=" + Vcc + "\n";
/*     */           } else {
/* 120 */             dummyBuffer = "VCCS2I " + powerPin.spiceNodeName + " 0 " + 
/* 121 */               " DC " + Vcc + "\n";
/*     */           } 
/* 123 */           this.powerBuffer = String.valueOf(this.powerBuffer) + dummyBuffer;
/*     */         
/*     */         }
/*     */       
/*     */       }
/* 128 */       else if (powerPin != null) {
/*     */         
/* 130 */         if (spiceType == 4) {
/* 131 */           this.powerBuffer = "VCCS2I " + powerPin.spiceNodeName + " 0 " + 
/* 132 */             " vsource type=dc dc=" + Vcc + "\n";
/*     */         } else {
/* 134 */           this.powerBuffer = "VCCS2I " + powerPin.spiceNodeName + " 0 " + 
/* 135 */             " DC " + Vcc + "\n";
/*     */         } 
/*     */       } 
/* 138 */       if (gndClampPin != null) {
/*     */         String dummyBuffer;
/* 140 */         if (spiceType == 4) {
/* 141 */           dummyBuffer = "VGCLMPS2I " + gndClampPin.spiceNodeName + " 0 " + 
/* 142 */             " vsource type=dc dc=" + GndClamp + "\n";
/*     */         } else {
/* 144 */           dummyBuffer = "VGCLMPS2I " + gndClampPin.spiceNodeName + " 0 " + 
/* 145 */             " DC " + GndClamp + "\n";
/*     */         } 
/* 147 */         this.powerBuffer = String.valueOf(this.powerBuffer) + dummyBuffer;
/* 148 */         if (gndPin != null && 
/* 149 */           !gndClampPin.spiceNodeName.equalsIgnoreCase(gndPin.spiceNodeName))
/*     */         {
/* 151 */           if (spiceType == 4) {
/* 152 */             dummyBuffer = "VGNDS2I " + gndPin.spiceNodeName + " 0 " + 
/* 153 */               " vsource type=dc dc=" + Gnd + "\n";
/*     */           } else {
/* 155 */             dummyBuffer = "VGNDS2I " + gndPin.spiceNodeName + " 0 " + 
/* 156 */               " DC " + Gnd + "\n";
/*     */           } 
/* 158 */           this.powerBuffer = String.valueOf(this.powerBuffer) + dummyBuffer;
/*     */         
/*     */         }
/*     */       
/*     */       }
/* 163 */       else if (gndPin != null) {
/*     */         
/* 165 */         if (spiceType == 4) {
/* 166 */           String dummyBuffer = "VGNDS2I " + gndPin.spiceNodeName + " 0 " + 
/* 167 */             " vsource type=dc dc=" + Gnd + "\n";
/*     */         } else {
/* 169 */           String str = "VGNDS2I " + gndPin.spiceNodeName + " 0 " + 
/* 170 */             " DC " + Gnd + "\n";
/*     */         }
/*     */       
/*     */       } 
/* 174 */     } else if (curveType == 10) {
/*     */       
/* 176 */       if (powerPin != null)
/*     */       {
/* 178 */         if (spiceType == 4) {
/* 179 */           this.powerBuffer = "VCCS2I " + powerPin.spiceNodeName + " 0 " + 
/* 180 */             " vsource type=dc dc=" + Vcc + "\n";
/*     */         } else {
/* 182 */           this.powerBuffer = "VCCS2I " + powerPin.spiceNodeName + " 0 " + 
/* 183 */             " DC " + Vcc + "\n";
/*     */         }  } 
/* 185 */       if (gndPin != null) {
/*     */         String dummyBuffer;
/* 187 */         if (spiceType == 4) {
/* 188 */           dummyBuffer = "VGNDS2I " + gndPin.spiceNodeName + 
/* 189 */             " 0 " + " vsource type=dc dc=" + Gnd + "\n";
/*     */         } else {
/* 191 */           dummyBuffer = "VGNDS2I " + gndPin.spiceNodeName + 
/* 192 */             " 0 " + " DC " + Gnd + "\n";
/*     */         } 
/* 194 */         this.powerBuffer = String.valueOf(this.powerBuffer) + dummyBuffer;
/*     */       }
/*     */     
/*     */     }
/*     */     else {
/*     */       
/* 200 */       if (powerPin != null) {
/*     */         
/* 202 */         if (spiceType == 4) {
/* 203 */           this.powerBuffer = "VCCS2I " + powerPin.spiceNodeName + " 0 " + 
/* 204 */             " vsource type=dc dc=" + Vcc + "\n";
/*     */         } else {
/* 206 */           this.powerBuffer = "VCCS2I " + powerPin.spiceNodeName + " 0 " + 
/* 207 */             " DC " + Vcc + "\n";
/*     */         } 
/* 209 */         if (powerClampPin != null && 
/* 210 */           !powerClampPin.spiceNodeName.equalsIgnoreCase(powerPin.spiceNodeName)) {
/*     */           String dummyBuffer;
/* 212 */           if (spiceType == 4) {
/* 213 */             dummyBuffer = "VCLMPS2I " + powerClampPin.spiceNodeName + 
/* 214 */               " 0 " + " vsource type=dc dc=" + VccClamp + "\n";
/*     */           } else {
/* 216 */             dummyBuffer = "VCLMPS2I " + powerClampPin.spiceNodeName + 
/* 217 */               " 0 " + " DC " + VccClamp + "\n";
/*     */           } 
/* 219 */           this.powerBuffer = String.valueOf(this.powerBuffer) + dummyBuffer;
/*     */         
/*     */         }
/*     */       
/*     */       }
/* 224 */       else if (powerClampPin != null) {
/*     */         
/* 226 */         if (spiceType == 4) {
/* 227 */           this.powerBuffer = "VCLMPS2I " + powerClampPin.spiceNodeName + 
/* 228 */             " 0 " + " vsource type=dc dc=" + VccClamp + "\n";
/*     */         } else {
/* 230 */           this.powerBuffer = "VCLMPS2I " + powerClampPin.spiceNodeName + 
/* 231 */             " 0 " + " DC " + VccClamp + "\n";
/*     */         } 
/*     */       } 
/* 234 */       if (gndPin != null) {
/*     */         String dummyBuffer;
/* 236 */         if (spiceType == 4) {
/* 237 */           dummyBuffer = "VGNDS2I " + gndPin.spiceNodeName + 
/* 238 */             " 0 " + " vsource type=dc dc=" + Gnd + "\n";
/*     */         } else {
/* 240 */           dummyBuffer = "VGNDS2I " + gndPin.spiceNodeName + 
/* 241 */             " 0 " + " DC " + Gnd + "\n";
/*     */         } 
/* 243 */         this.powerBuffer = String.valueOf(this.powerBuffer) + dummyBuffer;
/* 244 */         if (gndClampPin != null && 
/* 245 */           !gndClampPin.spiceNodeName.equalsIgnoreCase(gndPin.spiceNodeName))
/*     */         {
/* 247 */           if (spiceType == 4) {
/* 248 */             dummyBuffer = "VGCLMPS2I " + gndClampPin.spiceNodeName + 
/* 249 */               " 0 " + " vsource type=dc dc=" + GndClamp + "\n";
/*     */           } else {
/* 251 */             dummyBuffer = "VGCLMPS2I " + gndClampPin.spiceNodeName + 
/* 252 */               " 0 " + " DC " + GndClamp + "\n";
/*     */           } 
/* 254 */           this.powerBuffer = String.valueOf(this.powerBuffer) + dummyBuffer;
/*     */         
/*     */         }
/*     */       
/*     */       }
/* 259 */       else if (gndClampPin != null) {
/*     */         
/* 261 */         if (spiceType == 4) {
/* 262 */           String dummyBuffer = "VGCLMPS2I " + gndClampPin.spiceNodeName + " 0 " + 
/* 263 */             " vsource type=dc dc=" + GndClamp + "\n";
/*     */         } else {
/* 265 */           String str = "VGCLMPS2I " + gndClampPin.spiceNodeName + 
/* 266 */             " 0 " + " DC " + GndClamp + "\n";
/*     */         } 
/*     */       } 
/*     */     } 
/*     */     
/* 271 */     this.temperatureBuffer = s2iString.temperatureString(spiceType, temperature);
/*     */   }
/*     */ }


/* Location:              D:\IBIS\s2ibis3_v1_1\java\!\setupPwrAndTempCmds.class
 * Java compiler version: 8 (52.0)
 * JD-Core Version:       1.1.3
 */