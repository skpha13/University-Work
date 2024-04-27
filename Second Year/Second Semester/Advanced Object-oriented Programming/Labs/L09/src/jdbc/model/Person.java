package jdbc.model;

public class Person {

    private int id;
    private String name;
    private double age;

    public Person() {
    }

    public Person(int id, String name, double age) {
        this.id = id;
        this.name = name;
        this.age = age;
    }

    public Person(String name, double age) {
        this.name = name;
        this.age = age;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public double getAge() {
        return age;
    }

    public void setAge(double age) {
        this.age = age;
    }

    @Override
    public String toString() {
        return "Person{" +
                "id=" + id +
                ", name='" + name + '\'' +
                ", age=" + age +
                '}';
    }
}
