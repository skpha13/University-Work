package exercitii;

import java.lang.reflect.Array;
import java.util.HashMap;

public class Exercitii {
    public static void main(String[] args) {

//      ================= EX1 =================
        String[][] strings1 = {
                {"aebcDIDID", "aebcdidid"},
                {"Ana are mere SI pere", "ana are mere si pere"},
                {"test", "test1"}
        };
        boolean[] values1 = {
            true, true, false
        };

        System.out.println("EXERCISE 1 TESTS:");
        for (int i=0; i<strings1.length; i++) {
            if (compareStrings(strings1[i][0], strings1[i][1]) == values1[i])
                System.out.println("\tTEST " + (i + 1) + ": PASSED");
            else
                System.out.println("\tTEST " + (i + 1) + ": FAILED");
        }
//      =======================================

//      ================= EX2 =================
        System.out.println("EXERCISE 2 TESTS:");
        String[] strings2 = {
                "This is 1 string",
                "This is another test",
                "12312313",
                "-1",
                ""
        };
        for (var item: strings2) {
            findProperties(item);
        }
//      =======================================

//      ================= EX3 =================
        System.out.println("EXERCISE 3 TESTS:");
        String[] strings3 = {
                "This is string",
                "This is another test",
                "abracadabra",
                ""
        };
        for (var item: strings3) {
            countOccurences(item);
        }
//      =======================================

//      ================= EX4 =================
        Integer[] arr1 = {1,2,3,4,4,213,2,3,123,1,1};
        Character[] arr2 = {'s', 'a', 's', 'a'};

        System.out.println("EXERCISE 4 TESTS:");
        if (removeDuplicates(arr1) == 6)
            System.out.println("\tTEST 1: PASSED");
        else
            System.out.println("\tTEST 1: FAILED");

        if (removeDuplicates(arr2) == 2)
            System.out.println("\tTEST 2: PASSED");
        else
            System.out.println("\tTEST 2: FAILED");

//      =======================================
    }

    private static boolean compareStrings(String str1, String str2) {
        return str1.equalsIgnoreCase(str2);
    }

    private static void findProperties(String str) {
        String vowels = "aeiouAEIOU";
        int vowelsCount = 0, consonantsCount = 0, digitCount = 0, spacesCount = 0;

        for (int i=0; i<str.length(); i++) {
            char ch = str.charAt(i);

            if (ch == ' ') {
                spacesCount ++;
                continue;
            }

            if (Character.isDigit(ch)) {
                digitCount ++;
                continue;
            }

            if (vowels.indexOf(ch) != -1)
                vowelsCount ++;
            else if (Character.isLetter(ch))
                consonantsCount ++;
        }

        System.out.println("Vowels: " + vowelsCount + "\n" +
                            "Consonants: " + consonantsCount + "\n" +
                            "Digits: " + digitCount + "\n" +
                            "Spaces: " + spacesCount + "\n"
        );
    }

    private static void countOccurences(String str) {
        int[] frequency = new int[256];

        for (char letter: str.toCharArray()) {
            if (Character.isLetter(letter))
                frequency[letter] ++;
        }

        for (int i=0; i<frequency.length; i++)
            if (frequency[i] > 0)
                System.out.println((char)i + ": " + frequency[i]);
        System.out.println();
    }

    private static <T> int removeDuplicates(T[] arr) {
        if (arr.length == 0)
            return 0;

        HashMap<T, Boolean> mmap = new HashMap<>();

        for (var item: arr) {
            mmap.put(item, true);
        }

        return mmap.size();
    }
}
