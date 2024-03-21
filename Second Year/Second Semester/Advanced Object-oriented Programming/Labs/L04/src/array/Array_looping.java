package array;

public class Array_looping {

    public static void main(String[] args) {
        int[] array = new int[3];  // allocates place in memory for 3 int type values

        array[0] = 10;      // access using index, count from zero
        array[1] = 11;
        array[2] = 12;

       //array[3] = 5;       // this will throw an exception => ArrayIndexOutOfBoundsException

        //for loop
        for (int i = 0; i < array.length; i++) {
            System.out.println(array[i]);
        }

        //for each loop
        for (int value : array) {
            System.out.println(value);
        }

        System.out.println("Length: " + array.length);      // length of the allocated array => 3

        int[] emptyArray = new int[3];
        System.out.println("Length: " + emptyArray.length);     // => 3
        System.out.println("Not initialised value: " + emptyArray[0]);  // => default value: 0 for int

    }
}
