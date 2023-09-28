package il.co.ILRD.design_patterns.factory;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.util.function.Function;

import static org.junit.jupiter.api.Assertions.*;

public class FactoryTest {
    Creator<String, InfinityStudent, InfinityStudent> factory;

    @BeforeEach
    public void init() {
        factory = new Creator<>();
    }

    @Test
    public void TU1() {
        factory.add("Cyber", stringInfinityStudentFunction -> new InfinityStudent(1111, "Barchik", 27, "Cyber"));
        factory.add("Software", stringInfinityStudentFunction -> new InfinityStudent(2222, "MariaBias", 27, "Software"));
        factory.add("DevOps", stringInfinityStudentFunction -> new InfinityStudent(3333, "Daniluchka", 27, "DevOps"));

        InfinityStudent bar = factory.create("Cyber");
        InfinityStudent maria = factory.create("Software");
        InfinityStudent daniel = factory.create("DevOps");

        assertEquals(1111, bar.getId(), "Lambda fail");
        assertEquals(2222, maria.getId(), "Lambda fail");
        assertEquals(3333, daniel.getId(), "Lambda fail");
    }
    @Test
    public void TU2() {
        factory.add("Cyber", new Function<InfinityStudent, InfinityStudent>() {
            @Override
            public InfinityStudent apply(InfinityStudent toInsert) {
                return new InfinityStudent(1111, "Barchik", 27, "Cyber");
            }
        });
        factory.add("Software", new Function<InfinityStudent, InfinityStudent>() {
            @Override
            public InfinityStudent apply(InfinityStudent toInsert) {
                return new InfinityStudent(2222, "MariaBias", 27, "Software");
            }
        });

        factory.add("DevOps", new Function<InfinityStudent, InfinityStudent>() {
            @Override
            public InfinityStudent apply(InfinityStudent toInsert) {
                return new InfinityStudent(3333, "Daniluchka", 27, "DevOps");
            }
        });

        InfinityStudent bar = factory.create("Cyber");
        InfinityStudent maria = factory.create("Software");
        InfinityStudent daniel = factory.create("DevOps");

        assertEquals(1111, bar.getId(), "Anonymous fail");
        assertEquals(2222, maria.getId(), "Anonymous fail");
        assertEquals(3333, daniel.getId(), "Anonymous fail");
    }
    @Test
    public void TU3() {
        Creator<String,String,String> staticFactory = new Creator<>();
        staticFactory.add("FooBar", FooBar::foobarMethod);

        assertEquals("Static" + null, staticFactory.create("FooBar"));

        String data = " with value";
        assertEquals("Static" + data, staticFactory.create("FooBar", data));

    }
    @Test
    public void TU4() {
        Creator<String, Integer, Boolean> factory = new Creator<>();
        factory.add("instance", new InfinityStudent(2222, "MariaBias", 27, "Software")::isIdPrime);

        assertTrue(factory.create("instance", 222), "Instance fail");
    }

    @Test
    public void TU5() {
        factory.add("CreateCyber", InfinityStudent::new);
        factory.add("CyberBarchik", stringInfinityStudentFunction -> new InfinityStudent(1111, "Barchik", 27, "Cyber"));

        InfinityStudent bar = factory.create("CreateCyber",factory.create("CyberBarchik"));

        assertEquals("Barchik", bar.getName(), "Constructor fail");
    }

    public static class FooBar implements Function<String, String>{
        public FooBar(){

        }
        public FooBar(String s) {
        }

        public static String foobarMethod(String s){
            return "Static" + s;
        }

        public String barfooMethod(String s){
            return "Instance" + s;
        }

        @Override
        public String apply(String s) {
            return "this is apply" + s;
        }
    }
}
