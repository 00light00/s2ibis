/*    */ import java.io.IOException;
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
/*    */ class s2iReader
/*    */ {
/*    */   static String inFile;
/* 55 */   static ibisTOP ibisStruct = new ibisTOP();
/* 56 */   static ibisGlobal ibisGlobal = new ibisGlobal();
/*    */ 
/*    */   
/*    */   public static void main(String[] args) throws IOException {
/* 60 */     s2iParser parser = new s2iParser();
/* 61 */     parser.Sp2iParse(inFile);
/* 62 */     parser.ibis.cList = parser.cList;
/* 63 */     ibisStruct = parser.ibis;
/* 64 */     ibisGlobal = parser.global;
/*    */   }
/*    */ }


/* Location:              D:\IBIS\s2ibis3_v1_1\java\!\s2iReader.class
 * Java compiler version: 8 (52.0)
 * JD-Core Version:       1.1.3
 */