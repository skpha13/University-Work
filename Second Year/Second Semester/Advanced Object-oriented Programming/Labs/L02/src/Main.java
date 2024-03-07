import javax.xml.crypto.Data;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Objects;
import java.util.Scanner;

class Output {
    public int code;
    public POJO data;

    Output(int code, POJO data) {
        this.code = code;
        this.data = data;
    }
}

class ReadFromKeyboard {
    private static final Scanner input = new Scanner(System.in);

    public Output readFromKeyboard() {
        System.out.println("Enter command >>> ");
        String readString = input.nextLine();

        switch (readString.toLowerCase()) {
            case "help":
                return help();
            case "create":
                return create();
            case "read":
                return read();
            case "update":
                return update();
            case "delete":
                return delete();
            case "quit":
                return quit();
            default:
                System.out.println("Unknown command\n");
                return new Output(0, null);
        }
    }
    public Output help() {
        System.out.println("Command received: help\n\n\tAccepted commands:\n\t\thelp: Instructions on how to use the application" +
                "\n\t\tcreate: Create a new user" +
                "\n\t\tread: Read a user from keyboard" +
                "\n\t\tupdate: Update data. Can receive two parameters: username and sold" +
                "\n\t\tdelete: Delete the user's data.  Receive the username" +
                "\n\t\tquit: Close the application.\n");
        return new Output(0, null);
    }

    public Output create() {
        System.out.println("Command received: create");

        System.out.println("Enter user: ");
        String user = input.nextLine();

        System.out.println("Enter sold: ");
        int sold = input.nextInt();

        input.nextLine();

        return new Output(1, new POJO(user, sold));
    }

    public Output read() {
        System.out.println("Command received: read");

        return new Output(2, null);
    }

    public Output update() {
        System.out.println("Command received: update");

        System.out.println("Enter user: ");
        String user = input.nextLine();

        System.out.println("Enter sold: ");
        int sold = input.nextInt();

        input.nextLine();

        return new Output(3, new POJO(user, sold));
    }

    public Output delete() {
        System.out.println("Command received: delete");

        System.out.println("Enter user: ");
        String user = input.nextLine();

        return new Output(4, new POJO(user, 0));
    }

    public Output quit() {
        return new Output(-1, null);
    }
}

class POJO {
    private String user;
    private int sold;

    POJO() {
        this.user = "Unknown";
        this.sold = 0;
    }

    POJO(String user, int sold) {
        this.user = user;
        this.sold = sold;
    }

    @Override
    public String toString() {
        return "POJO{" +
                "user='" + user + '\'' +
                ", sold=" + sold +
                '}';
    }

    public String getUser() {
        return this.user;
    }
}

class DataStorage {
    private static DataStorage instance;
    private static ArrayList<POJO> storage = new ArrayList<>();
    private static ReadFromKeyboard reader;

    private DataStorage() {
        reader = new ReadFromKeyboard();
    }

    public static DataStorage getInstance() {
        if (instance == null)
            instance = new DataStorage();

        return instance;
    }

    public void engine() {
        while (true) {
            Output output = reader.readFromKeyboard();

            switch (output.code) {
                case -1:
                    return;
                case 0:
                    break;
                case 1:
                    storage.add(output.data);
                    break;
                case 2:
                    for (var iterator: storage) {
                        System.out.print(iterator + " ");
                    }
                    System.out.println();
                    break;
                case 3:
                    for (var iterator: storage) {
                        if (Objects.equals(iterator.getUser(), output.data.getUser())){
                            storage.remove(iterator);
                            storage.add(output.data);
                        }
                    }
                    break;
                case 4:
                    storage.removeIf(iterator -> Objects.equals(iterator.getUser(), output.data.getUser()));
                    break;
            }
        }
    }
}

public class Main {
    public static void main(String[] args) {
        DataStorage storage = DataStorage.getInstance();
        storage.engine();
    }
}