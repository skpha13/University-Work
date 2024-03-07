package basics;

public class TestClassStructure {

    public static void main(String[] args) {
        ClassStructure firstClassStructure = new ClassStructure();
        System.out.println("a = " + firstClassStructure.getA());
        System.out.println("counter = " + ClassStructure.getCounter());

        ClassStructure secondClassStructure = new ClassStructure();
        System.out.println("a = " + secondClassStructure.getA());
        System.out.println("counter = " + ClassStructure.getCounter());

    }
}