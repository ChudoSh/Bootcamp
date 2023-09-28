package il.co.ILRD.refelction;

import org.junit.jupiter.api.*;

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

@TestMethodOrder(MethodOrderer.OrderAnnotation.class)
public class ReflectionTest {
    Foo foo;

    @BeforeEach
    public void InitReflection() throws InstantiationException, IllegalAccessException {
        foo = (Foo) ObjectAnalyzer.getNewInstance(Foo.class);
    }

    @Test
    public void TU1() {
        ObjectAnalyzer.printSuperClass(foo);
    }

    @Test
    public void TU2() {
        ObjectAnalyzer.printListedModifierAndInterfaces(foo);
    }

    @Test
    public void TU3() {
        ObjectAnalyzer.printAllMembersInObject(foo);
    }

    @Test
    public void TU4() throws NoSuchMethodException, InvocationTargetException, InstantiationException, IllegalAccessException {
        Method m = foo.getClass().getMethod("setName", String.class);
        ObjectAnalyzer.invokeObjectMethods(m, foo,"Barchik");
        m = foo.getClass().getMethod("getName");
        System.out.println(ObjectAnalyzer.invokeObjectMethods(m, foo));
    }

}
