public class Quiz3 {
    public void Foo() {
        System.out.println("constructor called");
    }

    static {
        System.out.println("static initializer called");
    }

    {
        System.out.println("instance initializer called");
    }

    public static void main (String[]args){
        new Foo();
        new Foo();
    }

}
