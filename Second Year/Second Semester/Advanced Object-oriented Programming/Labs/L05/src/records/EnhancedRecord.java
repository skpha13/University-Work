package records;

public record EnhancedRecord(String name, int age) {
    //private String email; //Instance field is NOT allowed !!!

    /*{
        System.out.println("instance initialization block NOT allowed");
    }*/

    private static String surname; //static field is allowed

    public void method1() {} //non-static method is allowed

    public static void method2() {} //static method is allowed

    // static block is allowed
    static {
        System.out.println("static block allowed");
    }

}
