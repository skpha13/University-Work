package strings;

public class String_equality {

    public static void main(String[] args) {
        String s1 = new String("This is a string");
        String s2 = new String("This is a string");
        if (s1.equals(s2)) {
            System.out.println("1) => Strings are equal!");
        }
        if (s1 == s2) {
            System.out.println("1) => Strings are the same!");
        }

        String s3 = "This is a string";
        String s4 = "This is a string";
        if (s3.equals(s4)) {
            System.out.println("2) => Strings are equal!");
        }
        if (s3 == s4) {
            System.out.println("2) => Strings are the same!");
        }

        if (s1.equals(s4)) {
            System.out.println("3) => Strings are equal!");
        }
    }
}
