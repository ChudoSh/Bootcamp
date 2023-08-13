package co.il.ILRD.Singleton;

public class LazyTHS {
    private LazyTHS() {
    }

    private static class LazyHolder {
         static final LazyTHS lazyThs = new LazyTHS();
    }

    public static LazyTHS getInstance() {
        return LazyHolder.lazyThs;
    }
}
