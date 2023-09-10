package il.co.ILRD.Quizzes_and_Exams.JavaQuizzes;

public class Quiz2 {

    public static class Point{
        private int x = 0, y;

        public Point(int x, int y){
            this.x = x;
            this.y = y;
        }
        public Point(){
            this(0 , 0);

        }
    }

    public static void main(String[] args) {
        StringBuffer strBuffer = new StringBuffer("This, That, etc.!");
        System.out.println(strBuffer.replace(12, 15, "etcetera"));

        Boolean b = null;
//        System.out.println(b ? true : false);
    }
}