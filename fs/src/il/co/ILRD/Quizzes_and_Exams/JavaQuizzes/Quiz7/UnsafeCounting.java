package il.co.ILRD.Quizzes_and_Exams.JavaQuizzes.Quiz7;

public class UnsafeCounting implements Runnable{
    private static int cnt = 0; // global counter

    public void run() {
        int i = 0;
//        int localCnt = 0;

//        for (i = 0; i < 100; ++i) {
//            localCnt = cnt;
//            ++localCnt;
//            cnt = localCnt;
//        }
        for (i = 0; i < 100; ++i) {
            ++cnt;
        }
    }

    public static void main(String[] args) {
        Thread first = new Thread(new UnsafeCounting());
        Thread second = new Thread(new UnsafeCounting());
        first.start();
        second.start();
        try {
            first.join();
            second.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        System.out.println("The counter is - " + UnsafeCounting.cnt);
    }
}