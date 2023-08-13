package co.il.ILRD.VM;

import java.util.ArrayList;
import java.util.List;

public class VendingMachine {
    //*******************************Fields*************************************
    private final VMDisplay vmDisplay;
    private final ArrayList<VMSlot> vmSlots;
    private int currentCredit;
    private VMState currentState = VMState.OFF;
    private VMSlot currentSlot;

    //******************************Constructor*********************************
    public VendingMachine(VMDisplay display, List<Product> productList) {
        this.vmDisplay = display;
        int size = productList.size();
        this.vmSlots = new ArrayList<>();
        int i = 0;

        for (Product currentProduct : productList) {
            VMSlot slot = new VMSlot(currentProduct, i,
                    currentProduct.getPrice());
            this.vmSlots.add(slot);
            ++i;
        }
    }

    //*************************Getters & Setters********************************
    public int getCurrentState() {
        return this.currentState.ordinal();
    }

    private void setCurrentState(VMState newState) {
        this.currentState = newState;
    }

    public int getCurrentCredit() {
        return this.currentCredit;
    }

    private void setCurrentCredit(int newCredit) {
        this.currentCredit += newCredit;
    }

    private VMSlot getSlotFromList(int productCode) {
        return this.vmSlots.get(productCode);
    }

    private void setCurrentSlot(VMSlot slot) {
        assert (null != slot);
        this.currentSlot = slot;
    }

    private VMSlot getCurrentSlot() {
        return this.currentSlot;
    }

    private void runDisplay(String message) {
        this.vmDisplay.display(message);
    }

    ///*******************Additional methods************************************
    private void dispenseProduct() {
        vmDisplay.display("Product dispensed: " +
                this.currentSlot.getProduct().getName());
    }

    private void checkEnoughMoneyToPurchase() {
        if (this.getCurrentCredit() >= this.currentSlot.getProductPrice()) {
            this.dispenseProduct();
            this.returnChange();
            this.setCurrentState(VMState.WAITING_FOR_SELECTION);
        } else {
            vmDisplay.display("Please insert " +
                    (this.currentSlot.getProductPrice() - this.currentCredit));
            this.setCurrentState(VMState.WAITING_FOR_MONEY);
        }
    }

    private void returnChange() {
        this.vmDisplay.display("Your change is: " +
                (this.currentCredit - this.currentSlot.getProductPrice()));
        this.currentCredit = 0;
    }

    //****************************User space************************************
    public void on() {
        this.currentState.on(this);
    }

    public void off() {
        this.currentState.off(this);
    }

    public void insertCoin(Coin coin) {
        this.currentState.insertCoin(this, coin);
    }

    public void selectProduct(int productCode) {
        this.currentState.selectProduct(this, productCode);
    }

    public void cancel() {
        this.currentState.cancel(this);
    }

    //**********************************Dev space*******************************
    private enum VMState {
        OFF {
            @Override
            public void on(VendingMachine vm) {
                vm.runDisplay("Machine is now on, please select your product");
                vm.setCurrentState(WAITING_FOR_SELECTION);
            }

            @Override
            public void off(VendingMachine vm) {
            }

            @Override
            public void insertCoin(VendingMachine vm, Coin coin) {
            }

            @Override
            public void selectProduct(VendingMachine vm, int productCode) {
            }

            @Override
            public void cancel(VendingMachine vm) {
            }
        },
        WAITING_FOR_SELECTION {
            public void insertCoin(VendingMachine vm, Coin coin) {
                vm.setCurrentCredit(coin.getValue());
                vm.runDisplay("Your new balance is: " + vm.getCurrentCredit());
            }
        },
        WAITING_FOR_MONEY {
            public void insertCoin(VendingMachine vm, Coin coin) {
                vm.setCurrentCredit(coin.getValue());
                vm.runDisplay("Your new balance is: " + vm.getCurrentCredit());
                vm.checkEnoughMoneyToPurchase();
            }
        };

        public void on(VendingMachine vm) {
            vm.runDisplay("Machine is already on");
        }

        public void off(VendingMachine vm) {
            vm.runDisplay("Machine turned off; " + vm.getCurrentCredit() + " cash has been returned, bye bye");
            vm.setCurrentCredit(0);
            vm.setCurrentState(OFF);
        }

        abstract public void insertCoin(VendingMachine vm, Coin coin);

        public void selectProduct(VendingMachine vm, int productCode) {
            vm.setCurrentSlot(vm.getSlotFromList(productCode));
            vm.runDisplay("A new product selected: " + vm.getCurrentSlot().getProduct().getName());
            vm.checkEnoughMoneyToPurchase();
        }

        public void cancel(VendingMachine vm) {
            vm.runDisplay("Ordered cancelled; " +
                    vm.getCurrentCredit() +
                    " cash has been return - your credit now is 0");
            vm.setCurrentCredit(-1 * vm.getCurrentCredit());
            vm.setCurrentState(WAITING_FOR_SELECTION);
        }
    }

    //********************************VMSlot class******************************
    private static class VMSlot {
        private VMSlot(Product product, int productCode, int price) {
            this.product = product;
            this.productCode = productCode;
            this.price = price * 2;
        }

        private final Product product;
        private final int productCode;
        private final int price;

        private Product getProduct() {
            return this.product;
        }

        private int getProductPrice() {
            return this.price;
        }
    }
}


