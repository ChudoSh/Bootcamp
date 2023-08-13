package co.il.ILRD.Singleton;

public class LazyNotTHS {
    private static LazyNotTHS lazyNotTHS;

    private LazyNotTHS() {
    }

    public static LazyNotTHS getInstance() {
        return (null == lazyNotTHS) ? (lazyNotTHS = new LazyNotTHS()) : lazyNotTHS;
    }
}
