package co.il.ILRD.VM;

public enum Coin {
    AGOROT(10),
    HALF(50),
    SHEKEL(100),
    SHNEKEL(200),
    HAMESH(500),
    ESER(1000);

    private final int value;

    Coin(int value) {
        this.value = value;
    }

    public int getValue() {
        return this.value;
    }
}
