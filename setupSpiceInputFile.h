/*     */ import java.io.BufferedReader;
/*     */ import java.io.BufferedWriter;
/*     */ import java.io.File;
/*     */ import java.io.FileReader;
/*     */ import java.io.FileWriter;
/*     */ import java.io.IOException;
/*     */ import java.io.PrintWriter;
/*     */ import java.util.StringTokenizer;
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ class setupSpiceInputFile
/*     */ {
/*     */   public int setupSpiceInputFile(int iterate, int spiceType, String spiceInputFile, String headerLine, String spiceFile, String modelFile, String extSpiceCmdFile, String loadBuffer, String inputBuffer, String powerBuffer, String temperatureBuffer, String analysisBuffer) {
/* 382 */     File spiceInFile_p = new File(spiceInputFile);
/*     */ 
/*     */ 
/*     */     
/*     */     try {
/* 387 */       boolean fileExists = spiceInFile_p.exists();
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */       
/* 393 */       String headerLine2 = "*Spice Deck created by S2IBIS3 Version 1.1 \n*North Carolina State University ";
/*     */       
/* 395 */       PrintWriter spiceInWriter = new PrintWriter(new BufferedWriter(
/* 396 */             new FileWriter(spiceInFile_p)));
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */       
/* 402 */       if (iterate == 0 || !fileExists) {
/*     */         
/* 404 */         File tempFile_p = new File(spiceFile);
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */         
/* 410 */         if (!spiceInFile_p.canWrite()) {
/*     */           
/* 412 */           System.out.println("Unable to open " + spiceInputFile + " for writing");
/* 413 */           return 1;
/*     */         } 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */         
/* 420 */         spiceInWriter.println(String.valueOf(headerLine) + headerLine2);
/* 421 */         if (spiceInWriter.checkError()) {
/*     */           
/* 423 */           System.out.println("Error while writing header lines ");
/* 424 */           spiceInWriter.close();
/* 425 */           return 1;
/*     */         } 
/*     */ 
/*     */ 
/*     */         
/* 430 */         if (!tempFile_p.canRead()) {
/*     */           
/* 432 */           System.out.println("Unable to open " + spiceFile + " for reading");
/* 433 */           spiceInWriter.close();
/* 434 */           return 1;
/*     */         } 
/* 436 */         BufferedReader tempReader = new BufferedReader(new FileReader(tempFile_p)); String lineBuffer;
/* 437 */         while ((lineBuffer = tempReader.readLine()) != null) {
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */           
/* 446 */           String firstArg = null;
/* 447 */           StringTokenizer st1 = new StringTokenizer(lineBuffer);
/* 448 */           int cnt = st1.countTokens();
/* 449 */           if (cnt != 0) {
/*     */             
/* 451 */             firstArg = st1.nextToken();
/* 452 */             if (!firstArg.equalsIgnoreCase(".end") && !firstArg.equals("*"))
/* 453 */               spiceInWriter.println(lineBuffer); 
/* 454 */             if (spiceInWriter.checkError()) {
/*     */               
/* 456 */               System.out.println("Error copying " + spiceFile);
/* 457 */               spiceInWriter.close();
/* 458 */               tempReader.close();
/* 459 */               return 1;
/*     */             } 
/*     */           } 
/*     */         } 
/*     */         try {
/* 464 */           tempReader.close();
/*     */         }
/* 466 */         catch (IOException e) {
/* 467 */           System.out.println("Error " + e.toString() + " while closing " + spiceFile);
/* 468 */           spiceInWriter.close();
/* 469 */           return 1;
/*     */         } 
/*     */ 
/*     */ 
/*     */ 
/*     */         
/* 475 */         if (!modelFile.equals("") && !modelFile.equalsIgnoreCase("NA")) {
/*     */           
/* 477 */           tempFile_p = new File(modelFile);
/*     */           
/* 479 */           if (!tempFile_p.canRead()) {
/*     */             
/* 481 */             System.out.println("Unable to open " + modelFile + " for reading");
/* 482 */             spiceInWriter.close();
/* 483 */             return 1;
/*     */           } 
/*     */           
/* 486 */           tempReader = new BufferedReader(new FileReader(tempFile_p)); String lineBuffer1;
/* 487 */           while ((lineBuffer1 = tempReader.readLine()) != null) {
/*     */             
/* 489 */             spiceInWriter.println(lineBuffer1);
/* 490 */             if (spiceInWriter.checkError()) {
/*     */               
/* 492 */               System.out.println("Error copying " + modelFile);
/* 493 */               spiceInWriter.close();
/* 494 */               tempReader.close();
/* 495 */               return 1;
/*     */             } 
/*     */           } 
/*     */           try {
/* 499 */             tempReader.close();
/*     */           }
/* 501 */           catch (IOException e) {
/* 502 */             System.out.println("Error " + e.toString() + " while closing " + spiceFile);
/* 503 */             spiceInWriter.close();
/* 504 */             return 1;
/*     */           } 
/*     */         } 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */         
/* 514 */         if (!extSpiceCmdFile.equals("") && !extSpiceCmdFile.equalsIgnoreCase("NA")) {
/*     */           
/* 516 */           tempFile_p = new File(extSpiceCmdFile);
/*     */           
/* 518 */           if (!tempFile_p.canRead()) {
/*     */             
/* 520 */             System.out.println("Unable to open " + extSpiceCmdFile + " for reading");
/* 521 */             spiceInWriter.close();
/* 522 */             return 1;
/*     */           } 
/*     */           
/* 525 */           tempReader = new BufferedReader(new FileReader(tempFile_p));
/*     */           
/* 527 */           spiceInWriter.println("\n"); String lineBuffer1;
/* 528 */           while ((lineBuffer1 = tempReader.readLine()) != null) {
/*     */             
/* 530 */             spiceInWriter.println(lineBuffer1);
/* 531 */             if (spiceInWriter.checkError()) {
/*     */               
/* 533 */               System.out.println("Error copying " + extSpiceCmdFile);
/* 534 */               spiceInWriter.close();
/* 535 */               tempReader.close();
/* 536 */               return 1;
/*     */             } 
/*     */           } 
/* 539 */           spiceInWriter.println("\n");
/*     */           
/*     */           try {
/* 542 */             tempReader.close();
/*     */           }
/* 544 */           catch (IOException e) {
/* 545 */             System.out.println("Error " + e.toString() + " while closing " + spiceFile);
/* 546 */             spiceInWriter.close();
/* 547 */             return 1;
/*     */           } 
/*     */         } 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */         
/* 555 */         if (spiceType == 4) {
/*     */           
/* 557 */           spiceInWriter.println("simulator lang = spectre\n");
/* 558 */           if (spiceInWriter.checkError()) {
/*     */             
/* 560 */             System.out.println("Error while writing simulator language in file " + 
/* 561 */                 spiceInFile_p);
/* 562 */             spiceInWriter.close();
/* 563 */             return 1;
/*     */           } 
/*     */         } 
/*     */ 
/*     */ 
/*     */         
/* 569 */         spiceInWriter.println(loadBuffer);
/* 570 */         if (spiceInWriter.checkError()) {
/*     */           
/* 572 */           System.out.println("Error while writing load to file " + spiceInFile_p);
/* 573 */           spiceInWriter.close();
/* 574 */           return 1;
/*     */         } 
/*     */ 
/*     */ 
/*     */ 
/*     */         
/* 580 */         spiceInWriter.println(powerBuffer);
/* 581 */         if (spiceInWriter.checkError()) {
/*     */           
/* 583 */           System.out.println("Error adding power sources to file " + spiceInFile_p);
/* 584 */           spiceInWriter.close();
/* 585 */           return 1;
/*     */         } 
/*     */ 
/*     */ 
/*     */ 
/*     */         
/* 591 */         spiceInWriter.println(" ");
/* 592 */         spiceInWriter.println(inputBuffer);
/* 593 */         if (spiceInWriter.checkError()) {
/*     */           
/* 595 */           System.out.println("Error adding input stimulus to file " + spiceInFile_p);
/* 596 */           spiceInWriter.close();
/* 597 */           return 1;
/*     */         } 
/*     */ 
/*     */ 
/*     */ 
/*     */         
/* 603 */         spiceInWriter.println(temperatureBuffer);
/* 604 */         spiceInWriter.println(s2iString.spiceOptions(spiceType));
/* 605 */         if (spiceInWriter.checkError()) {
/*     */           
/* 607 */           System.out.println("Error adding Spice options to file " + spiceInFile_p);
/* 608 */           spiceInWriter.close();
/* 609 */           return 1;
/*     */         } 
/*     */ 
/*     */ 
/*     */ 
/*     */         
/* 615 */         spiceInWriter.println(analysisBuffer);
/* 616 */         if (spiceInWriter.checkError()) {
/*     */           
/* 618 */           System.out.println("Error adding Spice analysis command to file " + spiceInFile_p);
/* 619 */           spiceInWriter.close();
/* 620 */           return 1;
/*     */         } 
/*     */ 
/*     */ 
/*     */ 
/*     */         
/* 626 */         if (spiceType != 4) {
/*     */           
/* 628 */           spiceInWriter.println(".END\n");
/* 629 */           if (spiceInWriter.checkError()) {
/*     */             
/* 631 */             System.out.println("Error completing file " + spiceInFile_p);
/* 632 */             spiceInWriter.close();
/* 633 */             return 1;
/*     */           } 
/*     */         } 
/* 636 */         spiceInWriter.close();
/*     */       }
/*     */       else {
/*     */         
/* 640 */         spiceInWriter.close();
/*     */       } 
/* 642 */     } catch (Exception ex) {
/* 643 */       System.out.println("Exception while setting file names (setupSpiceInputFile): " + 
/* 644 */           ex.toString() + ": ");
/* 645 */       ex.printStackTrace();
/*     */     } 
/*     */     
/* 648 */     return 0;
/*     */   }
/*     */ }


/* Location:              D:\IBIS\s2ibis3_v1_1\java\!\setupSpiceInputFile.class
 * Java compiler version: 8 (52.0)
 * JD-Core Version:       1.1.3
 */