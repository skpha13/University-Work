package strings;

public class Concatenation {

    /*Rules:
        If both operands are numeric, + means numeric addition.
        If either operand is a String, + means concatenation.
        The expression is evaluated left to right.*/
    public static void main(String[] args) {
        System.out.println(1 + 2);           // 3
        System.out.println("a" + "b");       // ab
        System.out.println("a" + "b" + 3);   // ab3
        System.out.println(1 + 2 + "c");     // 3c
        System.out.println("c" + 1 + 2);     // c12
        System.out.println("c" + null);      // cnull

        int three = 3;
        String four = "4";
        System.out.println(1 + 2 + three + four); // 64
    }

}
