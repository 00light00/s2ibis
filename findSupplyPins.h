/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ class findSupplyPins
/*     */ {
/*     */   ibisPin pullupPin;
/*     */   ibisPin pulldownPin;
/*     */   ibisPin powerClampPin;
/*     */   ibisPin gndClampPin;
/*     */   
/*     */   int findPins(ibisPin currentPin, pinsList pinList, boolean hasPinMapping) {
/* 331 */     pinsList tempPList = new pinsList();
/*     */ 
/*     */     
/* 334 */     if (hasPinMapping) {
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */       
/* 343 */       if (!currentPin.pullupRef.equalsIgnoreCase("NC")) {
/*     */         
/* 345 */         pinList.gototop();
/*     */         
/* 347 */         tempPList = pinList;
/* 348 */         while (tempPList != null && ((
/* 349 */           !tempPList.current.modelName.equalsIgnoreCase("POWER") && 
/* 350 */           !tempPList.current.modelName.equalsIgnoreCase("GND")) || 
/* 351 */           !tempPList.current.pullupRef.equalsIgnoreCase(currentPin.pullupRef)))
/* 352 */           tempPList.next(); 
/* 353 */         if (tempPList == null) {
/*     */           
/* 355 */           System.out.println("No Power or Ground pin");
/* 356 */           return 1;
/*     */         } 
/*     */         
/* 359 */         this.pullupPin = tempPList.current;
/*     */       } else {
/*     */         
/* 362 */         this.pullupPin = null;
/*     */       } 
/*     */ 
/*     */       
/* 366 */       if (!currentPin.pulldownRef.equalsIgnoreCase("NC")) {
/*     */         
/* 368 */         pinList.gototop();
/* 369 */         tempPList = pinList;
/* 370 */         while (tempPList != null && ((
/* 371 */           !tempPList.current.modelName.equalsIgnoreCase("POWER") && 
/* 372 */           !tempPList.current.modelName.equalsIgnoreCase("GND")) || 
/* 373 */           !tempPList.current.pulldownRef.equalsIgnoreCase(currentPin.pulldownRef)))
/* 374 */           tempPList.next(); 
/* 375 */         if (tempPList == null) {
/*     */           
/* 377 */           System.out.println("No Power or Ground pin");
/* 378 */           return 1;
/*     */         } 
/*     */         
/* 381 */         this.pulldownPin = tempPList.current;
/*     */       } else {
/*     */         
/* 384 */         this.pulldownPin = null;
/*     */       } 
/*     */ 
/*     */       
/* 388 */       if (!currentPin.powerClampRef.equalsIgnoreCase("NC")) {
/*     */         
/* 390 */         pinList.gototop();
/* 391 */         tempPList = pinList;
/* 392 */         while (tempPList != null && ((
/* 393 */           !tempPList.current.modelName.equalsIgnoreCase("POWER") && 
/* 394 */           !tempPList.current.modelName.equalsIgnoreCase("GND")) || 
/* 395 */           !tempPList.current.pullupRef.equalsIgnoreCase(currentPin.powerClampRef)))
/* 396 */           tempPList.next(); 
/* 397 */         if (tempPList == null) {
/*     */           
/* 399 */           System.out.println("No Power or Ground pin");
/* 400 */           return 1;
/*     */         } 
/*     */         
/* 403 */         this.powerClampPin = tempPList.current;
/*     */       } else {
/*     */         
/* 406 */         this.powerClampPin = null;
/*     */       } 
/*     */ 
/*     */       
/* 410 */       if (!currentPin.gndClampRef.equalsIgnoreCase("NC")) {
/*     */         
/* 412 */         pinList.gototop();
/* 413 */         tempPList = pinList;
/* 414 */         while (tempPList != null && ((
/* 415 */           !tempPList.current.modelName.equalsIgnoreCase("POWER") && 
/* 416 */           !tempPList.current.modelName.equalsIgnoreCase("GND")) || 
/* 417 */           !tempPList.current.pulldownRef.equalsIgnoreCase(currentPin.gndClampRef)))
/* 418 */           tempPList.next(); 
/* 419 */         if (tempPList == null) {
/*     */           
/* 421 */           System.out.println("No Power or Ground pin");
/* 422 */           return 1;
/*     */         } 
/*     */         
/* 425 */         this.gndClampPin = tempPList.current;
/*     */       } else {
/*     */         
/* 428 */         this.gndClampPin = null;
/*     */       
/*     */       }
/*     */ 
/*     */     
/*     */     }
/*     */     else {
/*     */       
/* 436 */       pinList.gototop();
/* 437 */       tempPList = pinList;
/* 438 */       while (tempPList != null && 
/* 439 */         !tempPList.current.modelName.equalsIgnoreCase("POWER"))
/* 440 */         tempPList.next(); 
/* 441 */       if (tempPList == null) {
/*     */         
/* 443 */         System.out.println("No Power pin for component. Please specify");
/* 444 */         System.out.println(" at least one pin with model name POWER");
/* 445 */         return 1;
/*     */       } 
/*     */ 
/*     */       
/* 449 */       System.out.println("Power pin for component available. Proceeding further ..");
/* 450 */       this.pullupPin = tempPList.current;
/* 451 */       this.powerClampPin = tempPList.current;
/*     */ 
/*     */ 
/*     */ 
/*     */       
/* 456 */       pinList.gototop();
/* 457 */       tempPList = pinList;
/* 458 */       while (tempPList != null && 
/* 459 */         !tempPList.current.modelName.equalsIgnoreCase("GND"))
/* 460 */         tempPList.next(); 
/* 461 */       if (tempPList == null) {
/*     */         
/* 463 */         System.out.println("No GND pin for component. Please specify ");
/* 464 */         System.out.println(" at least one pin with model name GND");
/* 465 */         return 1;
/*     */       } 
/*     */ 
/*     */       
/* 469 */       System.out.println("GND pin for component available. Proceeding further ..");
/* 470 */       this.gndClampPin = tempPList.current;
/* 471 */       this.pulldownPin = tempPList.current;
/*     */     } 
/*     */ 
/*     */     
/* 475 */     return 0;
/*     */   }
/*     */ }


/* Location:              D:\IBIS\s2ibis3_v1_1\java\!\findSupplyPins.class
 * Java compiler version: 8 (52.0)
 * JD-Core Version:       1.1.3
 */