package co.il.ILRD.VM;

import org.junit.jupiter.api.*;

import java.util.ArrayList;
import java.util.List;

import static org.junit.jupiter.api.Assertions.*;

@TestMethodOrder(MethodOrderer.OrderAnnotation.class)
public class VMTest {
    List<Product> Items;
    VendingMachine vm;

    @BeforeEach
    public void InitVM(){
        Items = new ArrayList<>();
        Items.add(new Item("Lays", 200));
        Items.add(new Item("Cheetos", 400));
        Items.add(new Item("Bamba", 500));
        Items.add(new Item("Bisli", 1000));
        vm = new VendingMachine(new Display(), Items);
    }

    @Test
    @Order(1)
    public void basicFuncTest(){
        System.out.println("Basic test");
        vm.on();
        vm.selectProduct(1);
        vm.insertCoin(Coin.ESER);
        vm.off();
    }

    @Test
    @Order(2)
    public void basicCancelOne(){
        System.out.println("Cancel 1 test");
        vm.on();
        vm.selectProduct(1);
        vm.cancel();
        vm.insertCoin(Coin.ESER);
        vm.selectProduct(2);
        vm.off();
    }

    @Test
    @Order(3)
    public void basicCancelTwo(){
        System.out.println("Cancel 2 test");
        vm.on();
        vm.selectProduct(1);
        vm.insertCoin(Coin.HAMESH);
        vm.insertCoin(Coin.SHNEKEL);
        vm.selectProduct(3);
        vm.off();
    }

    @Test
    @Order(4)
    public void basicOff(){
        System.out.println("Off test");
        vm.on();
        vm.insertCoin(Coin.HAMESH);
        vm.off();
    }


    @Test
    @Order(5)
    void on() {
        assertEquals(0, this.vm.getCurrentState());
        this.vm.on();
        assertEquals(1, this.vm.getCurrentState());
        this.vm.on();
        assertEquals(1, this.vm.getCurrentState());
        this.vm.selectProduct(1);
        assertEquals(2, this.vm.getCurrentState());
        this.vm.on();
        assertEquals(2, this.vm.getCurrentState());
    }

    @Test
    @Order(6)
    void off() {
        assertEquals(0, this.vm.getCurrentState());
        this.vm.off();
        assertEquals(0, this.vm.getCurrentState());
        this.vm.on();
        assertEquals(1, this.vm.getCurrentState());
        this.vm.off();
        assertEquals(0, this.vm.getCurrentState());
        this.vm.on();
        this.vm.selectProduct(1);
        assertEquals(2, this.vm.getCurrentState());
        this.vm.off();
        assertEquals(0, this.vm.getCurrentState());

    }

    @Test
    @Order(7)
    void insertCoin() {
        assertEquals(0, this.vm.getCurrentState());
        this.vm.on();
        assertEquals(1, this.vm.getCurrentState());
        this.vm.insertCoin(Coin.HALF);
        this.vm.insertCoin(Coin.HALF);
        this.vm.insertCoin(Coin.HALF);
        assertEquals(1, this.vm.getCurrentState());
        assertEquals(150,this.vm.getCurrentCredit());
        this.vm.insertCoin(Coin.HAMESH);
        assertEquals(650,this.vm.getCurrentCredit());
        assertEquals(1, this.vm.getCurrentState());
        this.vm.selectProduct(1);
        assertEquals(1, this.vm.getCurrentState());
        this.vm.selectProduct(1);
        assertEquals(2, this.vm.getCurrentState());
        this.vm.insertCoin(Coin.SHNEKEL);
        this.vm.insertCoin(Coin.HALF);
        assertEquals(250,this.vm.getCurrentCredit());
    }

    @Test
    @Order(8)
    void selectProduct() {
        assertEquals(0, this.vm.getCurrentState());
        this.vm.selectProduct(1);
        assertEquals(0, this.vm.getCurrentState());
        this.vm.on();
        assertEquals(1, this.vm.getCurrentState());
        this.vm.insertCoin(Coin.HALF);
        this.vm.insertCoin(Coin.HALF);
        this.vm.insertCoin(Coin.HALF);
        this.vm.selectProduct(1);
        assertEquals(2, this.vm.getCurrentState());
        this.vm.insertCoin(Coin.SHNEKEL);
        this.vm.insertCoin(Coin.HALF);
        assertEquals(1, this.vm.getCurrentState());
        this.vm.selectProduct(2);
        this.vm.insertCoin(Coin.HAMESH);
        assertEquals(2, this.vm.getCurrentState());
        this.vm.selectProduct(1);
        assertEquals(1, this.vm.getCurrentState());
    }

    @Test
    @Order(9)
    void cancel() {
        assertEquals(0, this.vm.getCurrentState());
        this.vm.cancel();
        assertEquals(0, this.vm.getCurrentState());
        this.vm.on();
        assertEquals(1, this.vm.getCurrentState());
        this.vm.insertCoin(Coin.HALF);
        this.vm.insertCoin(Coin.HALF);
        this.vm.insertCoin(Coin.HALF);
        this.vm.cancel();
        assertEquals(1, this.vm.getCurrentState());
        assertEquals(0, this.vm.getCurrentCredit());
        this.vm.selectProduct(2);
        assertEquals(2, this.vm.getCurrentState());
        this.vm.cancel();
        assertEquals(1, this.vm.getCurrentState());
    }
        private class Item implements Product {

        private String name;
        private int price;

        public Item(String name, int price){
            assertNotNull(name,"Name is null");
            assertTrue(0 < price, "Price is 0 or less");
            this.name = name;
            this.price = price;
        }

        @Override
        public String getName() {
            return this.name;
        }

        @Override
        public void setName(String name) {
            assert(null != name);
            this.name = name;
        }

        @Override
        public int getPrice() {
            return this.price;
        }

        @Override
        public void setPrice(int price) {
            assert(0 <= price);
            this.price = price;

        }
    }

    private class Display implements VMDisplay{

        public Display(){}
        @Override
        public void display(String message) {
            System.out.println(message);
        }
    }

}
