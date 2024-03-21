package immutability;

public class ImmutablePerson {

    private final String name;
    private final Birthday birthday;

    public ImmutablePerson(String name, Birthday birthday) {
        this.name = name;
        Birthday cloneBirthday = new Birthday();
        cloneBirthday.setMonth(birthday.getMonth());
        cloneBirthday.setDay(birthday.getDay());
        this.birthday = cloneBirthday;
    }

    public String getName() {
        return name;
    }

    public Birthday getAddress() {
        Birthday cloneBirthday = new Birthday();
        cloneBirthday.setMonth(this.birthday.getMonth());
        cloneBirthday.setDay((this.birthday.getDay()));
        return cloneBirthday;
    }

    @Override
    public String toString() {
        return "ImmutablePerson{" +
                "name='" + name + '\'' +
                ", birthday=" + birthday +
                '}';
    }
}
