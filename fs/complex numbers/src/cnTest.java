import il.co.ILRD.CN.ComplexNumber;
import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

public class cnTest {
    @Test
    public void testBasicFunc(){
        ComplexNumber x = new ComplexNumber(5.0 , -4.5);
        assertEquals(5.0, x.getReal(), "Failed getReal");
        assertEquals(-4.5, x.getImaginary(), "Failed getImaginary");
        x.setImaginary(0.0);
        assertTrue(x.isReal(), "Failed isReal");
        x.setImaginary(-4.0);
        assertTrue(x.isImaginary(), "Failed isImaginary");
    }

    @Test
    public void testAdd(){
        ComplexNumber a = new ComplexNumber(5.0 , -4.5);
        ComplexNumber b = new ComplexNumber(8.0 , 2.3);
        ComplexNumber z = a.add(b);
        assertEquals(13.0, z.getReal(), "Failed real add");
        assertEquals(-2.2, z.getImaginary(), "Failed img add");
    }

    @Test
    public void testSubtract(){
        ComplexNumber a = new ComplexNumber(5.0 , -4.5);
        ComplexNumber b = new ComplexNumber(8.0 , 2.3);
        ComplexNumber z = a.subtract(b);
        assertEquals(-3.0, z.getReal(), "Failed real subtract");
        assertEquals(-6.8, z.getImaginary(), "Failed img subtract");
    }

    @Test
    public void testMultiply(){
        ComplexNumber a = new ComplexNumber(5.0 , -4.5);
        ComplexNumber b = new ComplexNumber(8.0 , 2.3);
        ComplexNumber z = a.multiply(b);
        assertEquals(50.35, z.getReal(), "Failed real multiply");
        assertEquals(-24.5, z.getImaginary(), "Failed img multiply");
    }

    @Test
    public void testDivide(){
        ComplexNumber a = new ComplexNumber(5.0 , -4.0);
        ComplexNumber b = new ComplexNumber(2.0 , 2.0);
        ComplexNumber z = a.divide(b);
        assertEquals(1.0/4.0, z.getReal(), "Failed real divide");
        assertEquals(-9.0/4.0, z.getImaginary(), "Failed img divide");
    }
    @Test
    public void testToString(){
        ComplexNumber a = new ComplexNumber(-5.0 , -4.0);
        System.out.println(a.toString());
    }
    @Test
    public void testEquals(){
        ComplexNumber a = new ComplexNumber(-5.0 , -4.0);
        ComplexNumber b = new ComplexNumber(-5.0 , -3.0);
        assertNotEquals(a, b, "Failed equals");
    }
    @Test
    public void testParse(){
        ComplexNumber z = ComplexNumber.parse("2i + 3");
        assertEquals(3.0, z.getReal(), "Failed parse");
        assertEquals(2.0, z.getImaginary(), "Failed parse");
        System.out.println(z.toString());
    }

}
