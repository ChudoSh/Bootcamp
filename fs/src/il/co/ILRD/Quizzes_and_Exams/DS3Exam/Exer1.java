package il.co.ILRD.Quizzes_and_Exams.DS3Exam;

import java.time.LocalDate;


public class Exer1 {
    private boolean isWildcardChanged;
    private Integer wildcard;
    private LocalDate wildcardSetTime;
    private DS myDS;

    public Exer1(int len) {
        myDS = new DS(len);
    }

    public Integer get(int i) {

        Integer result;

        if (myDS.arr.length < i) {
            return null;
        }

        // setAll() has been just called
        if (isWildcardChanged) {
            return wildcard;
        }

        if (myDS.arr[i] == null) {

            // setAll() has been previously called
            if (wildcard != null) {
                result = wildcard;
            } else {
                result = null;

            }

        } else if (myDS.arr[i].jokerSetTime == wildcardSetTime) {
            // cell value has been overridden after setAll() call
            result = myDS.arr[i].value;
        } else {
            result = wildcard;
        }

        return result;
    }

    public void setAll(int val) {
        isWildcardChanged = true;
        wildcard = val;
        wildcardSetTime = LocalDate.now();
    }

    public void set(int i, int val) {
        isWildcardChanged = false;
        myDS.arr[i] = new Node(val, wildcardSetTime);
    }

    private class Node {

        int value;
        LocalDate jokerSetTime;

        Node(int val, LocalDate jokSetTime) {
            value = val;
            jokerSetTime = jokSetTime;
        }
    }

    private class DS {

        Node[] arr;

        DS(int len) {
            arr = new Node[len];
        }
    }
}
