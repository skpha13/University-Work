package pao.sample.view;

import pao.sample.exceptions.InvalidDataException;
import pao.sample.model.Entity1;
import pao.sample.service.SampleService;

import java.util.Scanner;

public class ConsoleApp {

    private Scanner s = new Scanner(System.in);
    private SampleService service = new SampleService();

    public static void main(String args[]) {
        ConsoleApp app = new ConsoleApp();
        while (true) {
            app.showMenu();
            int option = app.readOption();
            app.execute(option);
        }
    }

    private void showMenu() {
        System.out.println
                ("   _____                                               _____                 \n" +
                        "  /  _  \\__  _  __ ____   __________   _____   ____   /  _  \\ ______ ______  \n" +
                        " /  /_\\  \\ \\/ \\/ // __ \\ /  ___/  _ \\ /     \\_/ __ \\ /  /_\\  \\\\____ \\\\____ \\ \n" +
                        "/    |    \\     /\\  ___/ \\___ (  <_> )  Y Y  \\  ___//    |    \\  |_> >  |_> >\n" +
                        "\\____|__  /\\/\\_/  \\___  >____  >____/|__|_|  /\\___  >____|__  /   __/|   __/ \n" +
                        "        \\/            \\/     \\/            \\/     \\/        \\/|__|   |__|    ");
        System.out.println("What do you want to do?");
        System.out.println("1. add entity");
        System.out.println("2. list entities with age over ...");
        System.out.println("3. exit");
    }

    private int readOption() {
        try {
            int option = readInt();
            if (option >= 1 && option <= 3) {
                return option;
            }
        } catch (InvalidDataException invalid) {
            // nothing to do, as it's handled below
        }
        System.out.println("Invalid option. Try again");
        return readOption();
    }

    private void execute(int option) {
        switch (option) {
            case 1:
                // add entity
                addEntity();
                break;
            case 2:
                // list entities
                listEntities();
                break;
            case 3:
                System.exit(0);
        }
    }

    private int readInt() throws InvalidDataException {
        String line = s.nextLine();
        if (line.matches("^\\d+$")) {
            return Integer.parseInt(line);
        } else {
            throw new InvalidDataException("Invalid number");
        }
    }

    private void listEntities() {
        System.out.println("Filter entries by age over: ");
        int age = -1;
        while (age < 0) {
            try {
                age = readInt();
            } catch (InvalidDataException invalidAge) {
                System.out.println("Invalid age");
            }
        }

        System.out.println("Entities:\n---------------------");
        for (Entity1 e : service.getAllEntitiesWithAgeOver(age)) {
            System.out.println(e.getSampleName() + " (" + e.getAge() + " years)");
        }


    }

    private void addEntity() {
        System.out.print("Name: ");
        String name = s.nextLine();
        System.out.print("Age: ");
        String ageString = s.nextLine();
        if (ageString.matches("^\\d+$")) {
            try {
                service.registerNewEntity(name, Integer.parseInt(ageString));
            } catch (InvalidDataException invalidData) {
                System.out.println(invalidData.getMessage());
            }
        } else {
            System.out.println("Invalid age!");
        }
    }
}
