package compare.comparator;

public class Song {
    private String name;
    private int year;
    private double rating;

    public Song(String name, int year, double rating) {
        this.name = name;
        this.year = year;
        this.rating = rating;
    }


    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getYear() {
        return year;
    }

    public void setYear(int year) {
        this.year = year;
    }

    public double getRating() {
        return rating;
    }

    public void setRating(double rating) {
        this.rating = rating;
    }
}
