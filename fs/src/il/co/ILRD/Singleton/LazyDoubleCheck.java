package il.co.ILRD.Singleton;

public class LazyDoubleCheck {
    private static volatile LazyDoubleCheck lazyDoubleCheck;

    private LazyDoubleCheck() {
    }

    public static synchronized LazyDoubleCheck getInstance() {
        if (null == lazyDoubleCheck) {
            synchronized (LazyDoubleCheck.class){
                if (null == lazyDoubleCheck){
                    lazyDoubleCheck = new LazyDoubleCheck();
                }
            }
        }
        return lazyDoubleCheck;
    }
}
