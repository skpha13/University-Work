package compare.comparable;

public class Movie implements Comparable<Movie> {

    private String name;
    private String type;
    private int year;
    private double rating;

    //Constructor
    public Movie(String name, String type, int year, double rating) {
        this.name = name;
        this.type = type;
        this.year = year;
        this.rating = rating;
    }

    // Used to sort movies by year
    @Override
    public int compareTo(Movie movie) {
        /*
        * positive integer, if the current movie's year is greater than the
        specified movie's year.
        * negative integer, if the current movie's year is less than the
        specified movie's year.
        * zero, if the current movie's year is equal to the specified movie's year.
        */
        return this.year - movie.year;
    }

    // getters and setters
    public String getName() {
        return name;
    }
    public void setName(String name) {
        this.name = name;
    }
    public String getType() {
        return type;
    }
    public void setType(String type) {
        this.type = type;
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
