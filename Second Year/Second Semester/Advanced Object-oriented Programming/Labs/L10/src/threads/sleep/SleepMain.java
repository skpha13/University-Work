package threads.sleep;

import java.util.Arrays;
import java.util.List;

public class SleepMain {

    public static void main(String[] args) throws InterruptedException {
        List<String> info = Arrays.asList("Hello", "there", "Hi", "again!");
        for (String s : info) {
            //Pause for 2 seconds
            Thread.sleep(2000);

            //Print a message
            System.out.println(s);
        }
    }
}
