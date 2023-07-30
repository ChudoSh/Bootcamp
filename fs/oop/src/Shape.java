abstract class Shape {
    protected String color;
    protected Boolean fill;

    public Shape() {
        this.color = "Green";
        this.fill = true;
    }

    public Shape(String color, Boolean fill) {
        this.color = color;
        this.fill = fill;
    }

    public String getColor() {
        return (this.color);
    }

    public Boolean isFilled() {
        return (this.fill);
    }

    public void setColor(String color) {
        this.color = color;
    }

    public void setFilled(Boolean fill) {
        this.fill = fill;
    }

    @Override public String toString() {
        String result = "A shape with color " + this.color + " and is ";
        return (this.fill ? result + "filled." : result + "not filled.");
    }
    abstract public double getArea();
    abstract public double getPerimeter();
}

