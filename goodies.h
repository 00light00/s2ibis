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
/*     */ class goodies
/*     */ {
/*     */   public static boolean IS_USE_NA(double number) {
/* 239 */     if (number >= -1.33288736222333E20D && 
/* 240 */       number <= -1.33286736222333E20D) {
/* 241 */       return true;
/*     */     }
/* 243 */     return false;
/*     */   }
/*     */   
/*     */   public static boolean IS_NOT_USED(double number) {
/* 247 */     if (number >= -1.33387736222333005E18D && 
/* 248 */       number <= -1.33187736222333005E18D) {
/* 249 */       return true;
/*     */     }
/* 251 */     return false;
/*     */   }
/*     */   
/*     */   public static int SIGN(double a) {
/* 255 */     if (a >= 0.0D) {
/* 256 */       return 1;
/*     */     }
/* 258 */     return -1;
/*     */   }
/*     */ 
/*     */   
/*     */   public static double MIN(double a, double b) {
/* 263 */     if (a < b) {
/* 264 */       return a;
/*     */     }
/* 266 */     return b;
/*     */   }
/*     */ 
/*     */   
/*     */   public static int ROUND(double num) {
/* 271 */     return (int)(num + 0.5D);
/*     */   }
/*     */   
/*     */   public static boolean THIS_PIN_NEEDS_ANALYSIS(String modelName) {
/* 275 */     if (!modelName.equalsIgnoreCase("Power") && 
/* 276 */       !modelName.equalsIgnoreCase("GND") && 
/* 277 */       !modelName.equalsIgnoreCase("NC")) {
/* 278 */       return true;
/*     */     }
/* 280 */     return false;
/*     */   }
/*     */ 
/*     */   
/*     */   public static int VERSION_ID(int MajorRelease, int MinorRelease, int SpecificID) {
/* 285 */     return MajorRelease * 1000 + 
/* 286 */       MinorRelease * 50 + 
/* 287 */       SpecificID;
/*     */   }
/*     */ 
/*     */   
/*     */   public static boolean THIS_MODEL_NEEDS_SERIES_VI_DATA(int modelType) {
/* 292 */     if (modelType == ConstantStuff.MODEL_TYPE_SERIES || 
/* 293 */       modelType == ConstantStuff.MODEL_TYPE_SERIES_SWITCH) {
/* 294 */       return true;
/*     */     }
/* 296 */     return false;
/*     */   }
/*     */   
/*     */   public static boolean THIS_MODEL_NEEDS_PULLUP_DATA(int modelType) {
/* 300 */     if (modelType == ConstantStuff.MODEL_TYPE_OUTPUT || 
/* 301 */       modelType == ConstantStuff.MODEL_TYPE_3_STATE || 
/* 302 */       modelType == ConstantStuff.MODEL_TYPE_I_O || 
/* 303 */       modelType == ConstantStuff.MODEL_TYPE_OPEN_SOURCE || 
/* 304 */       modelType == ConstantStuff.MODEL_TYPE_I_O_OPEN_SOURCE || 
/* 305 */       modelType == ConstantStuff.MODEL_TYPE_OUTPUT_ECL || 
/* 306 */       modelType == ConstantStuff.MODEL_TYPE_I_O_ECL) {
/* 307 */       return true;
/*     */     }
/* 309 */     return false;
/*     */   }
/*     */   
/*     */   public static boolean THIS_MODEL_NEEDS_PULLDOWN_DATA(int modelType) {
/* 313 */     if (modelType == ConstantStuff.MODEL_TYPE_OUTPUT || 
/* 314 */       modelType == ConstantStuff.MODEL_TYPE_3_STATE || 
/* 315 */       modelType == ConstantStuff.MODEL_TYPE_I_O || 
/* 316 */       modelType == ConstantStuff.MODEL_TYPE_OPEN_SINK || 
/* 317 */       modelType == ConstantStuff.MODEL_TYPE_I_O_OPEN_SINK || 
/* 318 */       modelType == ConstantStuff.MODEL_TYPE_OPEN_DRAIN || 
/* 319 */       modelType == ConstantStuff.MODEL_TYPE_I_O_OPEN_DRAIN || 
/* 320 */       modelType == ConstantStuff.MODEL_TYPE_OUTPUT_ECL || 
/* 321 */       modelType == ConstantStuff.MODEL_TYPE_I_O_ECL) {
/* 322 */       return true;
/*     */     }
/* 324 */     return false;
/*     */   }
/*     */   
/*     */   public static boolean THIS_MODEL_NEEDS_POWER_CLAMP_DATA(int modelType) {
/* 328 */     if (modelType == ConstantStuff.MODEL_TYPE_INPUT || 
/* 329 */       modelType == ConstantStuff.MODEL_TYPE_3_STATE || 
/* 330 */       modelType == ConstantStuff.MODEL_TYPE_I_O || 
/* 331 */       modelType == ConstantStuff.MODEL_TYPE_I_O_OPEN_SOURCE || 
/* 332 */       modelType == ConstantStuff.MODEL_TYPE_INPUT_ECL || 
/* 333 */       modelType == ConstantStuff.MODEL_TYPE_I_O_ECL || 
/* 334 */       modelType == ConstantStuff.MODEL_TYPE_TERMINATOR) {
/* 335 */       return true;
/*     */     }
/* 337 */     return false;
/*     */   }
/*     */   
/*     */   public static boolean THIS_MODEL_NEEDS_GND_CLAMP_DATA(int modelType) {
/* 341 */     if (modelType == ConstantStuff.MODEL_TYPE_INPUT || 
/* 342 */       modelType == ConstantStuff.MODEL_TYPE_3_STATE || 
/* 343 */       modelType == ConstantStuff.MODEL_TYPE_I_O || 
/* 344 */       modelType == ConstantStuff.MODEL_TYPE_I_O_OPEN_SINK || 
/* 345 */       modelType == ConstantStuff.MODEL_TYPE_I_O_OPEN_DRAIN || 
/* 346 */       modelType == ConstantStuff.MODEL_TYPE_INPUT_ECL || 
/* 347 */       modelType == ConstantStuff.MODEL_TYPE_I_O_ECL || 
/* 348 */       modelType == ConstantStuff.MODEL_TYPE_TERMINATOR) {
/* 349 */       return true;
/*     */     }
/* 351 */     return false;
/*     */   }
/*     */   
/*     */   public static boolean THIS_MODEL_NEEDS_TRANSIENT_DATA(int modelType) {
/* 355 */     if (modelType == ConstantStuff.MODEL_TYPE_OUTPUT || 
/* 356 */       modelType == ConstantStuff.MODEL_TYPE_3_STATE || 
/* 357 */       modelType == ConstantStuff.MODEL_TYPE_I_O || 
/* 358 */       modelType == ConstantStuff.MODEL_TYPE_OPEN_SINK || 
/* 359 */       modelType == ConstantStuff.MODEL_TYPE_I_O_OPEN_SINK || 
/* 360 */       modelType == ConstantStuff.MODEL_TYPE_OPEN_DRAIN || 
/* 361 */       modelType == ConstantStuff.MODEL_TYPE_I_O_OPEN_DRAIN || 
/* 362 */       modelType == ConstantStuff.MODEL_TYPE_OPEN_SOURCE || 
/* 363 */       modelType == ConstantStuff.MODEL_TYPE_I_O_OPEN_SOURCE || 
/* 364 */       modelType == ConstantStuff.MODEL_TYPE_OUTPUT_ECL || 
/* 365 */       modelType == ConstantStuff.MODEL_TYPE_I_O_ECL) {
/* 366 */       return true;
/*     */     }
/* 368 */     return false;
/*     */   }
/*     */ 
/*     */   
/*     */   public static boolean IS_ECL(int model) {
/* 373 */     if (model == ConstantStuff.MODEL_TYPE_INPUT_ECL || 
/* 374 */       model == ConstantStuff.MODEL_TYPE_I_O_ECL || 
/* 375 */       model == ConstantStuff.MODEL_TYPE_OUTPUT_ECL) {
/* 376 */       return true;
/*     */     }
/* 378 */     return false;
/*     */   }
/*     */   
/*     */   public static double fabs(double number) {
/* 382 */     return Math.abs(number);
/*     */   }
/*     */ }


/* Location:              D:\IBIS\s2ibis3_v1_1\java\!\goodies.class
 * Java compiler version: 8 (52.0)
 * JD-Core Version:       1.1.3
 */