package strings;

public class String_methods {

    public static void main(String[] args) {
        String s1 = "this is a String";

        s1.toUpperCase();
        System.out.println(s1); //this is a String

        String s2 = s1.toUpperCase();
        System.out.println(s2); //THIS IS A STRING

        System.out.println(s1.replace('s', '$')); //thi$ i$ a String
        System.out.println("Length: " + s1.length()); //Length: 16
        System.out.println(s1 + s2); //this is a StringTHIS IS A STRING
        System.out.println(s1.concat(s2)); //this is a StringTHIS IS A STRING
        System.out.println(s1.indexOf('S')); //10

        String[] strings = s1.split(" "); //["this", "is", "a", "String"]
        for (int i = 0; i < strings.length; i++) {
            System.out.println(strings[i]);
        }
        String substring = s1.substring(5, 10);
        System.out.println("Substring: '" + substring +"'");

    }
}
