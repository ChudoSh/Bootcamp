package il.co.ILRD.design_patterns.singleton;

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
