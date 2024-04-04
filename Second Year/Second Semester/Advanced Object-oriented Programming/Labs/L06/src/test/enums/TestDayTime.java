package test.enums;

import enums.DayTime;

public class TestDayTime {
    public static void main(String[] args) {

        for(DayTime dayTime : DayTime.values()) {
            System.out.println(dayTime.name() + ": " + dayTime.getHours());
        }

    }
}
