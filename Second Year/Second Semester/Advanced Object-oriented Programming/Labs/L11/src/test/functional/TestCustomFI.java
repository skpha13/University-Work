package test.functional;

import functional.CustomFI;

public class TestCustomFI {
    public static void main(String[] args) {
        CustomFI customFI = (a, b, c) -> a + b + c;

        int sum = customFI.sum(1, 3, 5);
        System.out.println(sum);
    }
}
