package il.co.ILRD.java2c;

public class LegendaryAnimal extends Cat {
    public LegendaryAnimal() {
        System.out.println("Legendary Ctor");
    }

    static {
        System.out.println("Static block Legendary Animal");
    }

    public void sayHello() {
        System.out.println("Legendary Hello!");
    }

    @Override
    protected void finalize() throws Throwable {
        System.out.println("finalize LegendaryAnimal with ID:" + this.ID);
        super.finalize();
    }

    @Override
    public String toString() {
        return "LegendaryAnimal with ID: " + ID;
    }
}
