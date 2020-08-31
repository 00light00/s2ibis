/*    */ 
/*    */ 
/*    */ 
/*    */ 
/*    */ 
/*    */ 
/*    */ 
/*    */ 
/*    */ 
/*    */ 
/*    */ 
/*    */ 
/*    */ 
/*    */ 
/*    */ 
/*    */ 
/*    */ 
/*    */ 
/*    */ 
/*    */ 
/*    */ 
/*    */ 
/*    */ 
/*    */ 
/*    */ 
/*    */ 
/*    */ 
/*    */ 
/*    */ 
/*    */ 
/*    */ 
/*    */ 
/*    */ 
/*    */ 
/*    */ 
/*    */ 
/*    */ 
/*    */ 
/*    */ 
/*    */ 
/*    */ 
/*    */ 
/*    */ 
/*    */ 
/*    */ 
/*    */ 
/*    */ 
/*    */ 
/*    */ 
/*    */ 
/*    */ 
/*    */ 
/*    */ 
/*    */ 
/*    */ 
/*    */ 
/*    */ 
/*    */ 
/*    */ 
/*    */ 
/*    */ 
/*    */ 
/*    */ 
/*    */ 
/*    */ 
/*    */ 
/*    */ 
/*    */ 
/*    */ 
/*    */ 
/*    */ 
/*    */ 
/*    */ class getMatchingPin
/*    */ {
/*    */   public ibisPin getMatchingPin(String searchName, pinsList pinList) {
/* 76 */     pinList.gototop();
/* 77 */     ibisPin tempPin = new ibisPin();
/* 78 */     tempPin = pinList.current;
/*    */     
/* 80 */     if (searchName.equalsIgnoreCase(""))
/* 81 */       return null; 
/* 82 */     while (tempPin != null && 
/* 83 */       !searchName.equalsIgnoreCase(tempPin.pinName)) {
/*    */       
/* 85 */       tempPin = pinList.current;
/* 86 */       pinList.next();
/*    */     } 
/* 88 */     if (tempPin == null)
/*    */     {
/* 90 */       System.out.println("Pin " + searchName + " Not Found in pin list");
/*    */     }
/* 92 */     return tempPin;
/*    */   }
/*    */ }


/* Location:              D:\IBIS\s2ibis3_v1_1\java\!\getMatchingPin.class
 * Java compiler version: 8 (52.0)
 * JD-Core Version:       1.1.3
 */