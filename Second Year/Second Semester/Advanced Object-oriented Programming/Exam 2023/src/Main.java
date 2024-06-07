import javax.swing.text.Caret;
import java.io.*;
import java.util.*;
import java.util.stream.Collectors;

import static java.util.stream.Collectors.groupingBy;

class Carte {
    String titlu, autor, editura;
    int nrExemplare;
    double pret;

    public Carte(String titlu, String autor, String editura, int nrExemplare, double pret) {
        this.titlu = titlu;
        this.autor = autor;
        this.editura = editura;
        this.nrExemplare = nrExemplare;
        this.pret = pret;
    }

    @Override
    public String toString() {
        return "Carte{" +
                "titlu='" + titlu + '\'' +
                ", autor='" + autor + '\'' +
                ", editura='" + editura + '\'' +
                ", nrExemplare=" + nrExemplare +
                ", pret=" + pret +
                '}';
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Carte carte = (Carte) o;
        return nrExemplare == carte.nrExemplare && pret == carte.pret && Objects.equals(titlu, carte.titlu) && Objects.equals(autor, carte.autor) && Objects.equals(editura, carte.editura);
    }

    @Override
    public int hashCode() {
        return Objects.hash(titlu, autor, editura, nrExemplare, pret);
    }

    public String getTitlu() {
        return titlu;
    }

    public void setTitlu(String titlu) {
        this.titlu = titlu;
    }

    public String getAutor() {
        return autor;
    }

    public void setAutor(String autor) {
        this.autor = autor;
    }

    public String getEditura() {
        return editura;
    }

    public void setEditura(String editura) {
        this.editura = editura;
    }

    public int getNrExemplare() {
        return nrExemplare;
    }

    public void setNrExemplare(int nrExemplare) {
        this.nrExemplare = nrExemplare;
    }

    public double getPret() {
        return pret;
    }

    public void setPret(double pret) {
        this.pret = pret;
    }
}

class FirExecutare extends Thread {
    public static double count = 0;
    private String filePath, title, author;

    synchronized public static void add(int nr, double pret) {
        count += nr * pret;
    }

    public FirExecutare(String author, String title, String filePath) {
        this.filePath = filePath;
        this.title = title;
        this.author = author;
    }

    @Override
    public void run() {
        Scanner scan = null;
        try {
            scan = new Scanner(new FileReader("./src/" + filePath));
        } catch (FileNotFoundException e) {
            throw new RuntimeException(e);
        }

        String line;
        while(scan.hasNextLine()) {
            line = scan.nextLine();
            String[] words = line.split(",");

            if (words[0].equals(title) && words[1].equals(author)) {
                add(Integer.parseInt(words[3]), Double.parseDouble(words[4]));
            }
        }

        scan.close();
    }

}

class Persoana {
    private String nume;
    private int varsta;
    private double venit;

    public Persoana(String nume, int varsta, double venit) {
        this.nume = nume;
        this.varsta = varsta;
        this.venit = venit;
    }

    public String getNume() {
        return nume;
    }

    public int getVarsta() {
        return varsta;
    }

    public double getVenit() {
        return venit;
    }

    @Override
    public String toString() {
        return "Persoana{" +
                "nume='" + nume + '\'' +
                ", varsta=" + varsta +
                ", venit=" + venit +
                '}';
    }
}

class Singleton {
    private static Singleton instance;
    private Singleton() {}

    public static Singleton getInstance() {
        if (instance == null)
            instance = new Singleton();
        return instance;
    }

    public void get(String fileName, ArrayList<Persoana> arr) throws FileNotFoundException {
        Scanner scan = new Scanner(new FileReader(fileName));

        scan.nextLine();
        while (scan.hasNextLine()) {
            String line = scan.nextLine();
            String[] words = line.split(",");

            arr.add(new Persoana(
                    words[0],
                    Integer.parseInt(words[1]),
                    Double.parseDouble(words[2])
            ));
        }

        scan.close();
    }

    public void put(String fileName, ArrayList<Persoana> arr) throws IOException {
        BufferedWriter bw = new BufferedWriter(new FileWriter(fileName));
        bw.write("nume,varsta,venit\n");

        for (Persoana p: arr) {
            bw.write(p.getNume() + "," + p.getVarsta() + "," + p.getVenit() + "\n");
        }

        bw.close();
    }
}

public class Main {
    public static void streams() {
        ArrayList<Carte> carti = new ArrayList<Carte>();

        carti.add(new Carte("Jumbo", "Andrei", "tx", 11, 35.5));
        carti.add(new Carte("Test", "Marius", "bx", 11, 76.5));
        carti.add(new Carte("Barrrr", "Mazga", "tx", 8, 3.5));
        carti.add(new Carte("CCAc1", "tset", "cx", 7, 111.5));
        carti.add(new Carte("testst", "tstest", "tx", 23, 5.5));

        carti.stream()
                .filter(c -> c.getNrExemplare() <= 10)
                .sorted(Comparator.comparing(Carte::getAutor))
                .forEach(System.out::println);

        carti.stream().map(Carte::getEditura).distinct().forEach(System.out::println);

        List<Carte> c = carti.stream().filter(car -> car.getPret() >= 50 && car.getPret() <= 100).toList();
        System.out.println(c);

        carti.stream()
                .collect(groupingBy(Carte::getAutor))
                .forEach((a, car) -> {
                    System.out.println("Autor: " + a);
                    car.forEach(System.out::println);
                });
    }

    public static void fir() throws InterruptedException {
        FirExecutare f1 = new FirExecutare("Frances Hodgson Burnett", "The Secret Garden", "librarieCLB_1.txt");
        FirExecutare f2 = new FirExecutare("J.R.R. Tolkien", "The Hobbit", "librarieCLB_2.txt");

        f1.start();
        f2.start();

        f1.join();
        f2.join();

        System.out.println(FirExecutare.count);
    }

    public static void singleton() throws IOException {
        ArrayList<Persoana> p = new ArrayList<Persoana>();
        p.add(new Persoana("Andrei", 24, 1000.12));
        p.add(new Persoana("Marius", 32, 7000.12));
        p.add(new Persoana("Alex", 7, 0));
        p.add(new Persoana("Paul", 22, 2300.12));

        Singleton s = Singleton.getInstance();
        s.put("csv02.csv", p);
        s.get("csv02.csv", p);
    }

    public static void main(String[] args) throws InterruptedException, IOException {
        streams();
        fir();
        singleton();
    }
}