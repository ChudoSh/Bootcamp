package il.co.ILRD.Refelction;


import il.co.ILRD.Complex_Numbers.ComplexNumber;
import il.co.ILRD.VM.Product;

public class Foo extends ComplexNumber implements Product {
    public String name;
    public int price;

    @Override
    public String getName() {
        return this.name;
    }

    @Override
    public void setName(String name) {
        this.name = name;
    }

    @Override
    public int getPrice() {
        return this.price;
    }

    @Override
    public void setPrice(int price) {
        this.price = price;
    }
}
