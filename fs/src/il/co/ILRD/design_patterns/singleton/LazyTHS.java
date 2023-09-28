package il.co.ILRD.design_patterns.singleton;

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
