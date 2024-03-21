package immutability;

public class Birthday {
    private String month;
    private int day;

    public String getMonth() {
        return month;
    }

    public void setMonth(String month) {
        this.month = month;
    }

    public int getDay() {
        return day;
    }

    public void setDay(int day) {
        this.day = day;
    }

    @Override
    public String toString() {
        return "Birthday{" +
                "month='" + month + '\'' +
                ", day=" + day +
                '}';
    }
}
