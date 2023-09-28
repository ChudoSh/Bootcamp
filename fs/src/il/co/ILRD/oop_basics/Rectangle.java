package il.co.ILRD.oop_basics;

public class Rectangle extends Shape {
    protected double width;
    protected double length;

    public Rectangle() {
        this.width = 1.0;
        this.length = 1.0;
    }

    public Rectangle(double width, double length) {
        this.width = width;
        this.length = length;
    }

    public Rectangle(double width, double length, String color, Boolean fill) {
        this.width = width;
        this.length = length;
        this.setColor(color);
        this.setFilled(fill);
    }

    public void setWidth(double width) {
        this.width = width;
    }

    public double getWidth() {
        return (width);
    }

    public void setLength(double length) {
        this.length = length;
    }

    public double getLength() {
        return (length);
    }

    public double getArea() {
        return (this.width * this.length);
    }

    public double getPerimeter() {
        return ((this.width + this.length) * 2);
    }

    @Override
    public String toString() {
        return ("A rectangle with width = " + this.width +
                " and this length = " + this.length +
                " which is a subclass of " + super.toString());
    }
}
