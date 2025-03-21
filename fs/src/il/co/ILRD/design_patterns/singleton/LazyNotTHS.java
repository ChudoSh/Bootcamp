package il.co.ILRD.design_patterns.singleton;

public class LazyNotTHS {
    private static LazyNotTHS lazyNotTHS;

    private LazyNotTHS() {
    }

    public static LazyNotTHS getInstance() {
        if (null == lazyNotTHS) {
            lazyNotTHS = new LazyNotTHS();
        }

        return lazyNotTHS;
    }
}
