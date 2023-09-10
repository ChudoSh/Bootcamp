package il.co.ILRD.Singleton;

public class EagerTHS {
    private static final EagerTHS eagerThs = new EagerTHS();

    private EagerTHS() {
    }

    public static EagerTHS getInstance() {
        return eagerThs;
    }
}
