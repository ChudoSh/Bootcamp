package il.co.ILRD.design_patterns.decorator;

public class ToppingTypes {
}

class FreshTomatoTopping extends ToppingDecorator{
    public FreshTomatoTopping(Pizza pizza){
        super(pizza);
    }

    @Override
    public String getDecoration() {
        return pizza.getDecoration() + " with Fresh Tomato";
    }

    @Override
    public int getPrice() {
        return pizza.getPrice() + 1;
    }
}

/*---------------------------------------------*/

class PaneerTopping extends ToppingDecorator{
    public PaneerTopping(Pizza pizza){
        super(pizza);
    }

    @Override
    public String getDecoration() {
        return pizza.getDecoration() + " with Paneer";
    }

    @Override
    public int getPrice() {
        return pizza.getPrice() + 2;
    }
}

/*---------------------------------------------*/

class JalapenoTopping extends ToppingDecorator{
    public JalapenoTopping(Pizza pizza){
        super(pizza);
    }

    @Override
    public String getDecoration() {
        return pizza.getDecoration() + " with Jalapeno";
    }

    @Override
    public int getPrice() {
        return pizza.getPrice() + 4;
    }
}

/*---------------------------------------------*/

class CapsicumTopping extends ToppingDecorator{
    public CapsicumTopping(Pizza pizza){
        super(pizza);
    }

    @Override
    public String getDecoration() {
        return pizza.getDecoration() + " with Capsicum";
    }

    @Override
    public int getPrice() {
        return pizza.getPrice() + 3;
    }
}

/*---------------------------------------------*/

class BBQTopping extends ToppingDecorator{
    public BBQTopping(Pizza pizza){
        super(pizza);
    }

    @Override
    public String getDecoration() {
        return pizza.getDecoration() + " with BBQ";
    }

    @Override
    public int getPrice() {
        return pizza.getPrice() + 5;
    }
}
