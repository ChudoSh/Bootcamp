package il.co.ILRD.Quizzes_and_Exams.JavaQuizzes.Quiz7;

import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;

public class Test {
    public static void main(String[] args) {
//        Derived d = new Derived();
        Map<String, String> premiumPhone = new HashMap<String, String>();
        premiumPhone.put("Apple", "iPhone");
        premiumPhone.put("HTC", "HTC one");
        premiumPhone.put("Samsung", "S5");

        Iterator iterator = premiumPhone.keySet().iterator();

        while (iterator.hasNext()) {
            System.out.println(premiumPhone.get(iterator.next()));
            premiumPhone.put("Sony", "Xperia Z");
        }
    }
}
