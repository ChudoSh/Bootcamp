package il.co.ILRD.Quizzes_and_Exams.JavaExam.Q34;

public class Sum {
    public int sumOf(int n) {
        Integer sum = 0; //unnecessary autoboxing
        for (Integer i = 1; i <= n; ++i) { // unnecessary autoboxing
            sum += i; //autoboxing
        }
        return sum;//autoboxing
    }

    public static void main(String[] args) {
        Sum s = new Sum();

        System.out.println(s.sumOf(2));
    }
}
