package il.co.ILRD.Quizzes_and_Exams.JavaQuizzes.Quiz10;


public class MyWaitNotify {
    String myMonitorObject = "";
    boolean wasSignalled = false;

    public void doWait() {
        synchronized (myMonitorObject) {
            while (!wasSignalled) {
                try {
                    myMonitorObject.wait();
                    System.out.println("After wait");
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
            //clear signal and continue running.
            wasSignalled = false;
        }
    }

    public void doNotify() {
        synchronized (myMonitorObject) {
            wasSignalled = true;
            System.out.println("True");
            myMonitorObject.notify();
        }
    }

    public static void main(String[] args) {
        long end = System.currentTimeMillis() + 500;

        while(System.currentTimeMillis() != end){
            new Thread(new MyWaitNotify()::doWait).start();
            new Thread(new MyWaitNotify()::doNotify).start();
        }
    }
}