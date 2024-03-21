package array;

import java.util.Arrays;
import java.util.Random;

public class Array_sort {

    public static void main(String[] args) {
        Integer[] ints = new Integer[10];

        System.out.println("Initialise array:");
        Random random = new Random();
        for (int i = 0; i < ints.length; i++) {
            ints[i] = random.nextInt(10);
            System.out.print(ints[i] + " ");
        }

        Arrays.sort(ints);      //java.util.Arrays -> useful methods for array manipulation
        System.out.println("Sorted array:");
        for (int i = 0; i < ints.length; i++) {
            System.out.print(ints[i] + " ");
        }
    }


}
