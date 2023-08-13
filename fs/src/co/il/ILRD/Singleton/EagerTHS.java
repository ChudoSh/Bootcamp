package co.il.ILRD.Singleton;
import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

public class EagerTHS {
    private static final EagerTHS eagerThs = new EagerTHS();

    private EagerTHS() {
    }

    public static synchronized EagerTHS getInstance() {
        return eagerThs;
    }

    public static void main(String[] args) {

    }
}
