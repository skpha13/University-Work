package test.functional;

import functional.Rectangle;
import functional.SquareFI;

public class TestSquare {

    public static void main(String[] args) {
        int a = 5;

        SquareFI s1 = (int x) -> x * x;
        int area = s1.calculate(a);
        System.out.println("Area of square is: " + area);

        SquareFI s2 = (int x) -> 4 * x;
        int perimeter = s2.calculate(a);
        System.out.println("Perimeter of square is: " + perimeter);

        Rectangle s3 = (int x, int y) -> x * y;
        int area_r = s3.calculate(a, 7);
        System.out.println("Area of a rectangle is: " + area_r);

        Rectangle s4 = (int x, int y) -> 2 * (x + y);
        int perimeter_r = s4.calculate(a, 7);
        System.out.println("Perimeter of a rectangle is: " + perimeter_r);

    }
}
