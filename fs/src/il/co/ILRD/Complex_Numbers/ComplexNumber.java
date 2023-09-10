package il.co.ILRD.Complex_Numbers;

import static java.lang.Math.pow;

public class ComplexNumber implements Comparable<ComplexNumber> {
    private double real;
    private double imaginary;

    public ComplexNumber() {
        this(0.0, 0.0);
    }

    public ComplexNumber(double real, double imaginary) {
        this.real = real;
        this.imaginary = imaginary;
    }

    public ComplexNumber add(ComplexNumber x) {
        return (new ComplexNumber(this.real + x.getReal(),
                this.imaginary + x.getImaginary()));
    }

    public ComplexNumber subtract(ComplexNumber x) {
        return (new ComplexNumber((this.real - x.getReal()),
                (this.imaginary - x.getImaginary())));
    }

    public ComplexNumber multiply(ComplexNumber x) {
        double newReal = (this.real * x.getReal()) -
                (this.imaginary * x.getImaginary());
        double newImaginary = (this.real * x.getImaginary()) +
                (this.imaginary * x.getReal());

        return (new ComplexNumber(newReal, newImaginary));
    }

    public ComplexNumber divide(ComplexNumber x) {
        ComplexNumber conjugate = new ComplexNumber(x.getReal(), -(x.getImaginary()));
        ComplexNumber numerator = this.multiply(conjugate);
        ComplexNumber denominator = x.multiply(conjugate);
        double tempReal = denominator.getReal();

        assert (0 != tempReal);

        return (new ComplexNumber(numerator.getReal() / tempReal,
                numerator.getImaginary() / tempReal));
    }

    public double getReal() {
        return (this.real);
    }

    public double getImaginary() {
        return (this.imaginary);
    }

    public void setReal(double real) {
        this.real = real;
    }

    public void setImaginary(double imaginary) {
        this.imaginary = imaginary;
    }

    public boolean isReal() {
        return (0.0 == this.imaginary);
    }

    public boolean isImaginary() {
        return (!isReal());
    }

    public static ComplexNumber parse(String toParse) {
        String[] elements = toParse.split(" ", -1);
        ComplexNumber toReturn = new ComplexNumber();
        int i = 0;

        while (!elements[i].contains("i")) {
            ++i;
        }

        toReturn.setImaginary(Double.parseDouble(elements[i].replace("i", "")));
        if (i != 0) {
            toReturn.setReal((elements[0].contentEquals("-")) ?
                    (-1 * Double.parseDouble(elements[1])) : Double.parseDouble(elements[0]));
        } else {
            toReturn.setReal(elements[i + 1].contentEquals("-") ?
                    (-1 * Double.parseDouble(elements[i + 2])) : Double.parseDouble(elements[i + 2]));
        }

        return (toReturn);
    }

    @Override
    public int compareTo(ComplexNumber x) {
        double checkCurrent = pow(this.real, 2) + pow(this.imaginary, 2);
        double checkAgainst = pow(x.getReal(), 2) + pow(x.getImaginary(), 2);

        return (Double.compare(checkCurrent, checkAgainst));
    }

    @Override
    public String toString() {
        if (0 > this.imaginary) {
            return (" " + this.real + " - " + (-1 * this.imaginary) + "i");
        }
        return (" " + this.real + " + " + this.imaginary + "i");
    }

    @Override
    public int hashCode() {
        long real = Double.doubleToLongBits(this.real); // harmonize NaN bit patterns
        long imaginary = Double.doubleToLongBits(this.imaginary);
        if (real == 1L << 63) {// convert -0.0 to +0.0
            real = 0;
        }

        if (imaginary == 1L << 63) {
            imaginary = 0;
        }
        long h = real ^ imaginary;
        return ((int) h ^ (int) (h >>> 32));
    }

    @Override
    public boolean equals(Object x) {
        if (x instanceof ComplexNumber) {
            ComplexNumber other = (ComplexNumber) x;
            return (0 == Double.compare(Double.doubleToLongBits(this.real),
                    Double.doubleToLongBits(other.real)) &&
                    0 == Double.compare(Double.doubleToLongBits(this.imaginary),
                            Double.doubleToLongBits(other.imaginary)));
        }
        return (false);
    }
}
