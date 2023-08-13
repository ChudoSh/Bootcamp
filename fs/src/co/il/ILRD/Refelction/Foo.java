package co.il.ILRD.Refelction;


import co.il.ILRD.Complex_Numbers.ComplexNumber;
import co.il.ILRD.VM.Product;
import org.junit.Before;
import org.junit.jupiter.api.BeforeEach;

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
