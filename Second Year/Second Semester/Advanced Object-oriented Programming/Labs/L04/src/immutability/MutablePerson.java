package immutability;

public final class MutablePerson {

    private final String name;
    private final Birthday birthday;

    public MutablePerson(String name, Birthday birthday) {
        this.name = name;
        this.birthday = birthday;
    }

    public String getName() {
        return name;
    }

    public Birthday getAddress() {
        return this.birthday;
    }

    @Override
    public String toString() {
        return "MutablePerson{" +
                "name='" + name + '\'' +
                ", birthday=" + birthday +
                '}';
    }
}
