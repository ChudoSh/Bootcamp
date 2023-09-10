package il.co.ILRD.Quizzes_and_Exams.DS3Exam;

import java.util.LinkedList;

public class Exer9 {
   public void arrangeListByPivot(int pivot, LinkedList<Integer> dll){
       for (Integer i : dll){
           if(i.compareTo(pivot) >= 0){
               dll.addLast(i);
           } else if(i.compareTo(pivot) < 0){
               dll.addFirst(i);
           }
       }
   }
}
