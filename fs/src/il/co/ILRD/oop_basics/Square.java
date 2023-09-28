package il.co.ILRD.oop_basics;

public class Square extends Rectangle {
    public Square() {
        super.length = 1;
        super.width = 1;
    }

    public Square(double side) {
        super.length = side;
        super.width = side;
    }

    public Square(double side, String color, Boolean fill) {
        super.length = side;
        super.width = side;
        this.setColor(color);
        this.setFilled(fill);
    }

    public void setSide(double side) {
        super.length = side;
        super.width = side;
    }

    @Override public void setWidth(double side) {
        setSide(side);
    }
    @Override public void setLength(double side) {
        setSide(side);
    }
    public double getSide() {
        return (this.getWidth());
    }

    @Override
    public String toString() {
        return ("A square with side = " + getSide() +
                " which is a subclass of " + super.toString());
    }
}
