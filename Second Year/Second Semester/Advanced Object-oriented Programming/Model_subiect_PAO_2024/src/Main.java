import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.*;
import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.Scanner;

class Automobil {
    private String marca, model;
    private int capacitate;
    private double pret;

    public Automobil(String marca, String model, int capacitate, double pret) {
        this.marca = marca;
        this.model = model;
        this.capacitate = capacitate;
        this.pret = pret;
    }

    public String getMarca() {
        return marca;
    }

    public void setMarca(String marca) {
        this.marca = marca;
    }

    public String getModel() {
        return model;
    }

    public void setModel(String model) {
        this.model = model;
    }

    public int getCapacitate() {
        return capacitate;
    }

    public void setCapacitate(int capacitate) {
        this.capacitate = capacitate;
    }

    public double getPret() {
        return pret;
    }

    public void setPret(double pret) {
        this.pret = pret;
    }

    @Override
    public String toString() {
        return "Automobil{" +
                "marca='" + marca + '\'' +
                ", model='" + model + '\'' +
                ", capacitate=" + capacitate +
                ", pret=" + pret +
                '}';
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Automobil automobil = (Automobil) o;
        return capacitate == automobil.capacitate && Double.compare(pret, automobil.pret) == 0 && Objects.equals(marca, automobil.marca) && Objects.equals(model, automobil.model);
    }

    @Override
    public int hashCode() {
        return Objects.hash(marca, model, capacitate, pret);
    }
}

class FirExecutare extends Thread {
    public static int count = 0;
    private String filePath, cuv;

    public FirExecutare(String filePath, String cuv) {
        this.filePath = filePath;
        this.cuv = cuv;
    }

    synchronized public static void add() {
        count ++;
    }

    @Override
    public void run() {
        Scanner br = null;
        try {
            br = new Scanner(new FileReader(filePath));
        } catch (FileNotFoundException e) {
            throw new RuntimeException(e);
        }

        String line;
        while(br.hasNextLine()) {
            line = br.nextLine();
            String[] words = line.split("[ ,.!?]+");

            for (String word: words) {
                if(word.equals(cuv))
                    add();
            }
        }

        br.close();
    }
}

public class Main {
    public static void streams() {
        ArrayList<Automobil> automobile = new ArrayList<Automobil>();

        automobile.add(new Automobil("Toyota", "Corolla", 2000, 15000.0));
        automobile.add(new Automobil("Honda", "Civic", 1800, 18000.0));
        automobile.add(new Automobil("Ford", "Mustang", 5000, 35000.0));
        automobile.add(new Automobil("BMW", "X5", 3000, 45000.0));
        automobile.add(new Automobil("BMW", "X5", 4500, 1000));
        automobile.add(new Automobil("Audi", "X5", 4500, 1000));
        automobile.add(new Automobil("Audi", "X5", 4500, 24));
        automobile.add(new Automobil("Audi", "X5", 4500, 2400));

        automobile.stream()
                .filter(a -> a.getPret() >= 5000)
                .sorted(Comparator.comparing(Automobil::getPret).reversed())
                .forEach(System.out::println);

        automobile.stream()
                .map(Automobil::getMarca)
                .distinct()
                .forEach(System.out::println);

        List<Automobil> ls = automobile.stream()
                .filter(x -> x.getCapacitate() >= 2000 && x.getCapacitate() <= 3000)
                .toList();

        automobile.stream()
                .filter(a -> a.getCapacitate() >=  2000 && a.getCapacitate() <= 3000)
                .forEach(System.out::println);

        System.out.println(automobile.stream()
                .filter(a -> a.getMarca().equals("Audi"))
                .max(Comparator.comparing(Automobil::getPret)));
    }

    public static void threads() throws InterruptedException {
        System.out.println("INTRODU CUVANT:");
        Scanner scanner = new Scanner(System.in);

        String word = scanner.nextLine();

        FirExecutare f1 = new FirExecutare("./src/fir1.txt", word);
        FirExecutare f2 = new FirExecutare("./src/fir2.txt", word);
        FirExecutare f3 = new FirExecutare("./src/fir3.txt", word);

        f1.start();
        f2.start();
        f3.start();

        f1.join();
        f2.join();
        f3.join();

        System.out.println(FirExecutare.count);
    }

    public static void main(String[] args) throws InterruptedException {
        streams();
        threads();
    }
}