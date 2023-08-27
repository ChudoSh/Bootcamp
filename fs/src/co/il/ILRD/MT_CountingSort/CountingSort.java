package co.il.ILRD.MT_CountingSort;

public class CountingSort {
    static int NUM_THREADS = 5;
    private enum Status{
        Fail (-1),
        Success (0);

        private final int status;
        private Status(int status){
            this.status = status;
        }

        private int getStatus(){
            return this.status;
        }
    }

   public int mtCountingSort(int[] arr){

      return Status.Success.getStatus();
   }

   private static class myCounting extends Thread {
        @Override
        public void run(){

        }
   }

    public static void main(String[] args) {

    }
}
