import java.util.Vector;

public class Pascal(){
      private static Vector<Vector<Long>> triangle = new Vector<>();

      private static int getNbLines(){
         return triangle.size();
      }

      /**
       * Method returns the binomnial coeff
       * @param n
       * @param k
       * @return binomnial coeff or -1 if there is an error
       */
      public static Long getBinomCoeff(int n, int k){
         if (k < 0 || k > n) {
            return -1L; // Retourne -1 en cas d'erreur
         }
    
         if (n == 0 || k == 0 || n == k) {
            return 1L;
         }
    
         Long result = triangle.get(n).get(k);
         if (result != null) {
            return result;
         }
         
         // Calcul du coefficient binomial en utilisant la récursivité
         result = getBinomCoeff(n - 1, k - 1) + getBinomCoeff(n - 1, k);
         triangle.get(n).set(k, result);
         
         return result;
      }

      private static void inceaseSizeTriangle(int n){
         while (getNbLines() <= n) {
            Vector<Long> newRow = new Vector<>();
            for (int i = 0; i <= getNbLines(); i++) {
               newRow.add(null);
            }
            triangle.add(newRow);
         }
      }

      public static void printTrianle(){
         for (int i = 0; i < getNbLines(); i++) {
            for (int j = 0; j <= i; j++) {
               System.out.print(getBinomCoeff(i, j) + " ");
            }
            System.out.println();
         }
      }
   }