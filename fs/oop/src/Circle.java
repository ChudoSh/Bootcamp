public class Circle extends Shape {
    protected double radius;

    public Circle() {
        this.radius = 1.0;
    }

    public Circle(double radius) {
        this.radius = radius;
    }

    public Circle(double radius, String color, Boolean fill) {
        this.radius = radius;
        this.setColor(color);
        this.setFilled(fill);
    }

    public void setRadius(double radius) {
        this.radius = radius;
    }

    public double getRadius() {
        return (radius);
    }

    public double getArea() {
        return (Math.PI * this.radius * this.radius);
    }

    public double getPerimeter() {
        return (Math.PI * this.radius * 2);
    }

    @Override
    public String toString() {
        return ("A circle with radius = " + this.radius +
                " which is a subclass of " + super.toString());
    }

}
