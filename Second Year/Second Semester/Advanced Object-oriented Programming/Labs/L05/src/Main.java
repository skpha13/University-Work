import interfaces.custom.Application;
import interfaces.custom.TcpStackProtocol;

public class Main {
    public static void main(String[] args) {
        TcpStackProtocol pc01 = new Application("abcde");
        System.out.println(pc01.calculateIPv4());
    }
}