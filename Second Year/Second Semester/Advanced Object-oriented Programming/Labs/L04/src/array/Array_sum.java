package array;

public class Array_sum {

    public static void main(String[] args) {

        float[] values = {10.0f, 20.0f, 15.0f};
        // after we declare the array name, we can use an open bracket
        // and then just list the values and enclose it
        // => It automatically allocates the right number of spaces,
        // in this case, three, and initializes the value in each space
        float sum = 0.0f;

        for (int i = 0; i < values.length; i++) {
            sum += values[i];
        }

        System.out.println(sum);
    }

}
