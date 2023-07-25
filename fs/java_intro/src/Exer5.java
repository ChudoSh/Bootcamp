
public class Exer5 {
    public static void main(String[] args)
    {
        printStackFrame(0);
    }

    public static void printStackFrame(int counter){

        if (10 == counter)
        {
            return;
        }

        System.out.println("Free memory (bytes): " +
                            Runtime.getRuntime().freeMemory());
        System.out.println("This is the " + counter + " Stack frame");
         printStackFrame(++counter);

    }
}
