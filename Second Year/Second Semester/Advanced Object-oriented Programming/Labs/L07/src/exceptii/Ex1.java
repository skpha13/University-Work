package exceptii;

public class Ex1 {
    public static void main(String[] args) {
        System.out.println("getResult: " + getResult());
        System.out.println("getExceptionResult: " + getExceptionResult());
    }

    private static int getResult() {
        try {
            return -1;
        } catch (Exception e) {
            return -2;
        } finally {
            return -3;
        }
    }

    private static int getExceptionResult() {
        try {
            throw new Exception();
        } catch (Exception e) {
            return -2;
        } finally {
            return -3;
        }
    }
}
