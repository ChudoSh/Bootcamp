package il.co.ILRD.design_patterns.decorator;

public class PizzaStore {
    public static void main(String[] args) {
        Pizza myPizza = new PeppyPaneer();
        System.out.println("the price of " + myPizza.getDecoration() + " is " + myPizza.getPrice());

        myPizza = new JalapenoTopping(myPizza);
        System.out.println("the price of " + myPizza.getDecoration() + " is " + myPizza.getPrice());
    }
}

