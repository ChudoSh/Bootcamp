package co.il.ILRD.Quizzes_and_Exams.JavaExam.Q36;
import java.util.HashMap;

public class Calculator {
    HashMap<String, Operator> mapOperator = new HashMap<>();

    public Calculator() {
        this.addOperator("addition", (int a, int b) -> {
            return (a + b);
        });
        this.addOperator("subtraction", new Operator() {
            @Override
            public int operate(int a, int b) {
                return a - b;
            }
        });

        this.addOperator("multiplication", new Multiplication());
        this.addOperator("division", this::divide);
    }

    interface Operator {
        int operate(int a, int b);
    }

    public void addOperator(String key, Operator o) {
        mapOperator.put(key, o);
    }

    public int operate(String key, int a, int b) {
        return mapOperator.get(key).operate(a, b);
    }

    private static class Multiplication implements Operator {
        @Override
        public int operate(int a, int b) {
            return a * b;
        }
    }

    private int divide(int a, int b) {
        class Division implements Operator {
            @Override
            public int operate(int a, int b) {
                if (0 == b) {
                    throw new IllegalArgumentException();
                }

                return a / b;
            }
        }

        return new Division().operate(a, b);
    }

    public static void main(String[] args) {
        Calculator calc = new Calculator();
        int sum = calc.operate("addition", 3, 4);
        int sub = calc.operate("subtraction", 4, 3);
        int mul = calc.operate("multiplication", 3, 4);
        int dev = calc.operate("division", 8, 2);

        System.out.println(sum);
        System.out.println(sub);
        System.out.println(mul);
        System.out.println(dev);
    }
}
