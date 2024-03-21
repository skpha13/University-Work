package strings;

public class String_instantiate_iterate {

    public static void main(String[] args) {
        // String literal
        String s1 = "this is a string";
        System.out.println(s1);

        // using the new keyword
        String s2 = new String("this is another string");
        System.out.println(s2);

        //iterate over string
        for (int i = 0; i < s1.length(); i++) {
            System.out.print(s1.charAt(i));
        }

        //s1.charAt(100);  //throws StringIndexOutOfBoundsException
    }
}
