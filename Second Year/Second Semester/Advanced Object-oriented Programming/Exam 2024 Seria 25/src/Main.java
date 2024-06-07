import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.*;
import java.util.stream.Collectors;

import static java.util.stream.Collectors.groupingBy;

class TenisATP {
    String numeJucat, nationalitateJucator;
    int pozitieATP, nrTurneeATP, puncteATP;

    public TenisATP(String numeJucat, String nationalitateJucator, int pozitieATP, int nrTurneeATP, int puncteATP) {
        this.numeJucat = numeJucat;
        this.nationalitateJucator = nationalitateJucator;
        this.pozitieATP = pozitieATP;
        this.nrTurneeATP = nrTurneeATP;
        this.puncteATP = puncteATP;
    }

    @Override
    public String toString() {
        return "TenisATP{" +
                "numeJucat='" + numeJucat + '\'' +
                ", nationalitateJucator='" + nationalitateJucator + '\'' +
                ", pozitieATP=" + pozitieATP +
                ", nrTurneeATP=" + nrTurneeATP +
                ", puncteATP=" + puncteATP +
                '}';
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        TenisATP tenisATP = (TenisATP) o;
        return pozitieATP == tenisATP.pozitieATP && nrTurneeATP == tenisATP.nrTurneeATP && puncteATP == tenisATP.puncteATP && Objects.equals(numeJucat, tenisATP.numeJucat) && Objects.equals(nationalitateJucator, tenisATP.nationalitateJucator);
    }

    @Override
    public int hashCode() {
        return Objects.hash(numeJucat, nationalitateJucator, pozitieATP, nrTurneeATP, puncteATP);
    }

    public String getNationalitateJucator() {
        return nationalitateJucator;
    }

    public int getNrTurneeATP() {
        return nrTurneeATP;
    }

    public int getPuncteATP() {
        return puncteATP;
    }
}

class Fir extends Thread {
    String fileName, nationalitate;

    public static int count = 0;

    public Fir(String fileName, String nationalitate) {
        this.fileName = fileName;
        this.nationalitate = nationalitate;
    }

    synchronized public void add() {
        count++;
    }

    @Override
    public void run() {
        Scanner scanner;
        try {
            scanner = new Scanner(new FileReader("./src/" + fileName));
        } catch (FileNotFoundException e) {
            throw new RuntimeException(e);
        }

        while (scanner.hasNextLine()) {
            String[] words = scanner.nextLine().split(",");

            if (words[1].equals(nationalitate))
                add();
        }
    }
}

class Adresa {
    String strada;
    int numar;

    public Adresa(String strada, int numar) {
        this.strada = strada;
        this.numar = numar;
    }

    public String getStrada() {
        return strada;
    }

    public void setStrada(String strada) {
        this.strada = strada;
    }

    public int getNumar() {
        return numar;
    }

    public void setNumar(int numar) {
        this.numar = numar;
    }

    @Override
    public String toString() {
        return "Adresa{" +
                "strada='" + strada + '\'' +
                ", numar=" + numar +
                '}';
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Adresa adresa = (Adresa) o;
        return numar == adresa.numar && Objects.equals(strada, adresa.strada);
    }

    @Override
    public int hashCode() {
        return Objects.hash(strada, numar);
    }

    public Adresa(Adresa adr) {
        this.strada = adr.strada;
        this.numar = adr.numar;
    }
}

final class Facultate {
    private final String denumire;
    private final Adresa adr;

    public Facultate(String denumire, Adresa adr) {
        this.denumire = denumire;
        this.adr = new Adresa(adr);
    }

    public Adresa getAdr() {
        return new Adresa(adr);
    }
}

public class Main {
    public static void streams() {
        ArrayList<TenisATP> lt = new ArrayList<TenisATP>();

        lt.add(new TenisATP("Andrei", "Roman", 2, 3, 1234));
        lt.add(new TenisATP("Marius", "Roman", 3, 7, 900));
        lt.add(new TenisATP("Nicolae", "Englez", 5, 11, 5000));
        lt.add(new TenisATP("Liviu", "Roman", 4, 0, 2000));

        lt.stream().filter(x -> x.getNrTurneeATP() >= 10).forEach(System.out::println);

        System.out.println();

        lt.stream().map(x -> x.getNationalitateJucator()).distinct().forEach(System.out::println);

        System.out.println();

        lt.stream().filter(x -> x.getPuncteATP() >= 1000 && x.getPuncteATP() <= 4000).toList().forEach(System.out::println);

        System.out.println();

        lt.stream().collect(groupingBy(TenisATP::getNationalitateJucator, Collectors.counting())).forEach((nat, nr) -> System.out.println("Nationalitate: " + nat + " = " + nr));
    }

    public static void threads() throws InterruptedException {
        Fir fir1 = new Fir("jucatori1.txt", "Roman");
        Fir fir2 = new Fir("jucatori2.txt", "Roman");

        fir1.start();
        fir2.start();

        fir1.join();
        fir2.join();

        System.out.println(Fir.count);
    }

    public static void main(String[] args) throws InterruptedException {
        streams();
        threads();
    }
}