package test.singleton;

import singleton.Singleton;

public class TestSingleton {
    public static void main(String[] args) {
        Singleton s1 = Singleton.getInstance();
        Singleton s2 = Singleton.getInstance();
        System.out.println("s1 == s2: " + (s1 == s2));
    }
}
