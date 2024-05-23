package test.functional;

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

    }
}
