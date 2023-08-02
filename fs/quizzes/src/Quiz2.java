public class Quiz2 {
    private int x = 0, y;

    public Quiz2(int x, int y){
        this.x = x;
        this.y = y;
    }
    public Quiz2(){
        this(0 , 0);
    }
    public static void main(String[] args) {
        StringBuffer strBuffer = new StringBuffer("This, That, etc.!");
        System.out.println(strBuffer.replace(12, 15, "etcetera"));

        Boolean b = null;
        System.out.println(b ? true : false);
    }
}