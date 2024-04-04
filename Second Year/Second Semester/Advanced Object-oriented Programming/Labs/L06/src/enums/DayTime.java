package enums;

public enum DayTime {
    AM {
        public String getHours() { return "00:00-11:59"; }
    },
    PM {
        public String getHours() { return "12:00-23:59"; }
    };
    public abstract String getHours();

}
