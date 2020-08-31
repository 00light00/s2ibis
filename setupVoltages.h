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
/*     */ class setupVoltages
/*     */ {
/*     */   double sweepStep;
/*     */   double sweepRange;
/*     */   double diodeDrop;
/*  76 */   ibisTypMinMax sweepStart = new ibisTypMinMax();
/*  77 */   ibisTypMinMax Vcc = new ibisTypMinMax();
/*  78 */   ibisTypMinMax Gnd = new ibisTypMinMax();
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */   
/*     */   public void setupVoltages(int curveType, ibisModel model) {
/*  89 */     ibisTypMinMax pullupRef, pulldownRef, powerClampRef, gndClampRef, zeros = new ibisTypMinMax();
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */     
/*  96 */     zeros.typ = 0.0D;
/*  97 */     zeros.min = 0.0D;
/*  98 */     zeros.max = 0.0D;
/*     */     
/* 100 */     if (goodies.IS_USE_NA(model.pullupRef.typ)) {
/* 101 */       pullupRef = model.voltageRange;
/*     */     } else {
/* 103 */       pullupRef = model.pullupRef;
/*     */     } 
/* 105 */     if (goodies.IS_USE_NA(model.pulldownRef.typ)) {
/* 106 */       pulldownRef = zeros;
/*     */     } else {
/* 108 */       pulldownRef = model.pulldownRef;
/*     */     } 
/* 110 */     if (goodies.IS_USE_NA(model.powerClampRef.typ)) {
/* 111 */       powerClampRef = model.voltageRange;
/*     */     } else {
/* 113 */       powerClampRef = model.powerClampRef;
/*     */     } 
/* 115 */     if (goodies.IS_USE_NA(model.gndClampRef.typ)) {
/* 116 */       gndClampRef = zeros;
/*     */     } else {
/* 118 */       gndClampRef = model.gndClampRef;
/*     */     } 
/* 120 */     if (goodies.IS_ECL(model.modelType)) {
/*     */       
/* 122 */       this.diodeDrop = 0.0D;
/*     */       
/* 124 */       this.Vcc.typ = pullupRef.typ;
/* 125 */       this.Vcc.min = pullupRef.min;
/* 126 */       this.Vcc.max = pullupRef.max;
/*     */       
/* 128 */       if (goodies.IS_USE_NA(model.gndClampRef.typ)) {
/*     */         
/* 130 */         if (this.Vcc.typ >= 4.5D && this.Vcc.typ <= 5.5D)
/*     */         {
/* 132 */           this.Gnd.typ = 0.0D;
/* 133 */           this.Gnd.min = 0.0D;
/* 134 */           this.Gnd.max = 0.0D;
/*     */         }
/*     */         else
/*     */         {
/* 138 */           this.Vcc.typ -= 5.2D;
/* 139 */           this.Vcc.min -= 5.2D;
/* 140 */           this.Vcc.max -= 5.2D;
/*     */         }
/*     */       
/*     */       } else {
/*     */         
/* 145 */         this.Gnd.typ = gndClampRef.typ;
/* 146 */         this.Gnd.min = gndClampRef.min;
/* 147 */         this.Gnd.max = gndClampRef.max;
/*     */       } 
/*     */       
/* 150 */       if (curveType == 2)
/*     */       {
/* 152 */         this.sweepStart.typ = powerClampRef.typ;
/* 153 */         this.sweepStart.min = powerClampRef.min;
/* 154 */         this.sweepStart.max = powerClampRef.max;
/*     */         
/* 156 */         this.sweepRange = 2.2D;
/* 157 */         this.sweepStep = 0.01D;
/*     */       
/*     */       }
/* 160 */       else if (curveType == 3)
/*     */       {
/* 162 */         gndClampRef.typ -= 2.2D;
/* 163 */         this.sweepStart.min = this.sweepStart.typ;
/* 164 */         this.sweepStart.max = this.sweepStart.typ;
/*     */         
/* 166 */         this.sweepRange = powerClampRef.typ - this.sweepStart.typ;
/* 167 */         if (this.sweepRange < 0.0D) {
/* 168 */           this.sweepStep = -0.01D;
/*     */         } else {
/* 170 */           this.sweepStep = 0.01D;
/*     */ 
/*     */         
/*     */         }
/*     */ 
/*     */       
/*     */       }
/*     */       else
/*     */       {
/*     */         
/* 180 */         pullupRef.typ -= 2.2D;
/* 181 */         this.sweepStart.min = this.sweepStart.typ;
/* 182 */         this.sweepStart.max = this.sweepStart.typ;
/*     */         
/* 184 */         if (curveType == 0 || 
/* 185 */           curveType == 4) {
/*     */           
/* 187 */           double maxOffset = this.Vcc.max - this.Vcc.typ;
/* 188 */           double minOffset = this.Vcc.min - this.Vcc.typ;
/*     */           
/* 190 */           this.sweepStart.max += maxOffset;
/* 191 */           this.sweepStart.min += minOffset;
/*     */         } 
/*     */         
/* 194 */         this.sweepRange = 2.2D;
/* 195 */         this.sweepStep = 0.01D;
/*     */       }
/*     */     
/*     */     }
/*     */     else {
/*     */       
/* 201 */       if (model.modelType == ConstantStuff.MODEL_TYPE_INPUT || 
/* 202 */         model.modelType == ConstantStuff.MODEL_TYPE_TERMINATOR || 
/* 203 */         model.modelType == ConstantStuff.MODEL_TYPE_SERIES || 
/* 204 */         model.modelType == ConstantStuff.MODEL_TYPE_SERIES_SWITCH) {
/* 205 */         linRange = powerClampRef.typ - gndClampRef.typ;
/*     */       } else {
/* 207 */         linRange = pullupRef.typ - pulldownRef.typ;
/* 208 */       }  double linRange = goodies.MIN(linRange, 5.0D);
/*     */       
/* 210 */       if (curveType == 3 || 
/* 211 */         curveType == 2) {
/*     */         
/* 213 */         this.Vcc.typ = powerClampRef.typ;
/* 214 */         this.Vcc.min = powerClampRef.min;
/* 215 */         this.Vcc.max = powerClampRef.max;
/*     */         
/* 217 */         this.Gnd.typ = gndClampRef.typ;
/* 218 */         this.Gnd.min = gndClampRef.min;
/* 219 */         this.Gnd.max = gndClampRef.max;
/*     */         
/* 221 */         if (curveType == 3) {
/*     */           
/* 223 */           gndClampRef.typ -= linRange;
/* 224 */           this.sweepStart.min = this.sweepStart.typ;
/* 225 */           this.sweepStart.max = this.sweepStart.typ;
/*     */           
/* 227 */           this.sweepRange = powerClampRef.typ - this.sweepStart.typ;
/*     */         }
/*     */         else {
/*     */           
/* 231 */           this.sweepStart.typ = powerClampRef.typ;
/* 232 */           this.sweepStart.min = powerClampRef.min;
/* 233 */           this.sweepStart.max = powerClampRef.max;
/*     */           
/* 235 */           this.sweepRange = linRange;
/*     */         } 
/*     */         
/* 238 */         if (this.sweepRange < 0.0D)
/*     */         {
/* 240 */           this.sweepStep = -0.01D;
/* 241 */           this.diodeDrop = -1.0D;
/*     */         }
/*     */         else
/*     */         {
/* 245 */           this.sweepStep = 0.01D;
/* 246 */           this.diodeDrop = 1.0D;
/*     */ 
/*     */         
/*     */         }
/*     */ 
/*     */       
/*     */       }
/*     */       else {
/*     */ 
/*     */         
/* 256 */         this.Vcc.typ = pullupRef.typ;
/* 257 */         this.Vcc.min = pullupRef.min;
/* 258 */         this.Vcc.max = pullupRef.max;
/*     */         
/* 260 */         this.Gnd.typ = pulldownRef.typ;
/* 261 */         this.Gnd.min = pulldownRef.min;
/* 262 */         this.Gnd.max = pulldownRef.max;
/*     */ 
/*     */         
/* 265 */         if (curveType == 10) {
/* 266 */           this.sweepStart.typ = pulldownRef.typ;
/*     */         } else {
/* 268 */           pulldownRef.typ -= linRange;
/*     */         } 
/*     */         
/* 271 */         this.sweepStart.min = this.sweepStart.typ;
/* 272 */         this.sweepStart.max = this.sweepStart.typ;
/*     */         
/* 274 */         if (curveType == 0 || 
/* 275 */           curveType == 4) {
/*     */           
/* 277 */           double maxOffset = this.Vcc.max - this.Vcc.typ;
/* 278 */           double minOffset = this.Vcc.min - this.Vcc.typ;
/*     */           
/* 280 */           this.sweepStart.max += maxOffset;
/* 281 */           this.sweepStart.min += minOffset;
/*     */         } 
/*     */         
/* 284 */         if (curveType == 10) {
/* 285 */           this.sweepRange = pullupRef.typ;
/*     */         } else {
/* 287 */           this.sweepRange = pullupRef.typ + linRange - this.sweepStart.typ;
/*     */         } 
/*     */         
/* 290 */         if (this.sweepRange < 0.0D) {
/*     */           
/* 292 */           this.sweepStep = -0.01D;
/* 293 */           this.diodeDrop = -1.0D;
/*     */         }
/*     */         else {
/*     */           
/* 297 */           this.sweepStep = 0.01D;
/* 298 */           this.diodeDrop = 1.0D;
/*     */         } 
/*     */       } 
/*     */     } 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */     
/* 309 */     double sweepStepInc = this.sweepStep;
/* 310 */     while (goodies.ROUND(this.sweepRange / this.sweepStep) >= 100 || this.sweepStep < 0.01D)
/* 311 */       this.sweepStep += sweepStepInc; 
/*     */   }
/*     */ }


/* Location:              D:\IBIS\s2ibis3_v1_1\java\!\setupVoltages.class
 * Java compiler version: 8 (52.0)
 * JD-Core Version:       1.1.3
 */